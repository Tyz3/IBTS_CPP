//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1->NodeDataSize = sizeof(UrlsTableStruct);
}

void printDebug(int statusCode, UnicodeString msg) {
	Form1->DebugLabel->Caption = msg;

	TColor color;
	switch (statusCode) {
	case 0:
		color = 0x63AF00;
		break;
	case 1:
		color = 0xDE9414;
		break;
	case 2:
		color = 0xCA3120;
		break;
	}                      
	Form1->DebugLabel->Font->Color = color;
}

void sendFilePathRequest() {
	if (Form1->dbPath == u"") {
		Form1->FileDialog->Execute();
		Form1->dbPath = Form1->FileDialog->FileName;
	}
}

void fillVirtualTree(sqlite3* database) {
	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// ��������� ������
	wchar_t sql[] = L"SELECT id, url, title, visit_count FROM urls;";

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		Form1->VirtualStringTree1->Clear();
		Form1->VirtualStringTree1->BeginUpdate();

		// ��� 2 (���������� ������� � ��������� ���������� ��� ��������� �����)
		printDebug(1, u"�������� ������");

		int rowsCount = 0;
		while (true) {
			result = sqlite3_step(pStatement);
			if(result != SQLITE_ROW) break;

			PVirtualNode entryNode = Form1->VirtualStringTree1->AddChild(Form1->VirtualStringTree1->RootNode);
			UrlsTableStruct* nodeData = (UrlsTableStruct*) Form1->VirtualStringTree1->GetNodeData(entryNode);

			nodeData->Id = sqlite3_column_int(pStatement, 0);
			nodeData->Url = UnicodeString((wchar_t*) sqlite3_column_text16(pStatement, 1));
			nodeData->Title = UnicodeString((wchar_t*) sqlite3_column_text16(pStatement, 2));
			nodeData->VisitCount = sqlite3_column_int(pStatement, 3);
			
			rowsCount++;
			printDebug(1, u"�������� ������ " + UnicodeString(rowsCount));
		}

		Form1->VirtualStringTree1->EndUpdate();

		printDebug(0, u"������ ���������");
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(2,
			u"������ ���������� SQL-�������: " + UnicodeString(errmsg)
			+ "\n" + UnicodeString(sql)
		);
		// ����� ����
		Form1->dbPath = u"";
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
}

void removeEntryCascadeById(sqlite3* database, int id) {
	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// ��������� �������
	wchar_t sql[100];
	wchar_t sql2[100];
	swprintf(sql, 100, L"DELETE FROM urls WHERE id = %d;", id);
	swprintf(sql2, 100, L"DELETE FROM visits WHERE url = %d;", id);

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		// ��� 2 (���������� �������)
		result = sqlite3_step(pStatement);

		// ��������� ���������
		if (result == SQLITE_DONE) {
			// ������ ������ ��� ������ ������� ���� 1-�� ����������
			result = sqlite3_prepare16_v2(database, sql2, -1, &pStatement, NULL);

			if (result == SQLITE_OK) {
				// ��� 2 (���������� �������)
				result = sqlite3_step(pStatement);

				// ��������� ���������
				if (result == SQLITE_DONE) {
					printDebug(0, u"������ ������� �� ������� urls, ����� ������� ������ �� ������� ������ �� visits");
				} else {
					printDebug(2, u"������ ��� ���������� 2-�� ������� ��� ������� visits: result=" + UnicodeString(result));
				}
			} else {
				errmsg = sqlite3_errmsg(database);
				printDebug(2,
					u"������ ���������� SQL-�������: " + UnicodeString(errmsg)
					+ "\n" + UnicodeString(sql)
				);
			}
		} else {
			printDebug(2, u"������ ��� ���������� 1-�� ������� ��� ������� urls: result=" + UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(2,
			u"������ ���������� SQL-�������: " + UnicodeString(errmsg)
			+ "\n" + UnicodeString(sql)
		);
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
}

void dropTable(sqlite3* database) {
	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// ��������� ������
	wchar_t sql[] = L"DROP TABLE IF EXISTS urls;";

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		// ��� 2 (���������� �������)
		result = sqlite3_step(pStatement);

		// ��������� ���������
		if (result == SQLITE_DONE) {
			printDebug(0, u"������� urls �������");
		} else {
			printDebug(2, u"������ ��� ���������� �������: result=" + UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(2,
			u"������ ���������� SQL-�������: " + UnicodeString(errmsg)
			+ "\n" + UnicodeString(sql)
		);
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FillButtonClick(TObject *Sender)
{
	// ������ �� ����� ����� � ��
	sendFilePathRequest();

	// ��������� ������� ���� � ��
	if (dbPath == u"") {
		printDebug(2, u"������� ��������� ������");
		return;
	}

	// 1. ��������� ����������:
	sqlite3* database;

	const wchar_t *filename = dbPath.w_str(); // L".\\History.db";
	int openResult = sqlite3_open16(filename, &database);

	// �������� �������� ��
	if (openResult == 0) {
		// ���������� ������� �� �������
		fillVirtualTree(database);
	} else {
		printDebug(2,
			"������ ��� �������� ��: openResult=" + UnicodeString(openResult)
		);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (Node == NULL) return;
	// ����������� ��������� �� ����
	UrlsTableStruct* nodeData = (UrlsTableStruct*) VirtualStringTree1->GetNodeData(Node);

	// �������������� ������������ ������ � VT
	switch (Column) {
		case 0: {
			CellText = nodeData->Id;
			break;
		}
		case 1: {
			CellText = nodeData->Url;
			break;
		}
		case 2: {
			CellText = nodeData->Title;
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender,
		  PVirtualNode Node)
{
	if (Node == NULL) return;

	// ����������� ��������� �� ����
	UrlsTableStruct* nodeData = (UrlsTableStruct*) VirtualStringTree1->GetNodeData(Node);

	// ������� �� ����� ���-�� ��������� ���������� url
	Label2->Caption = nodeData->VisitCount;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RemoveLineButtonClick(TObject *Sender)
{
	// ��������� ������� ���� � ��
	if (dbPath == u"") {
		printDebug(2, u"������� ��������� ������");
		return;
	}

	// �������� ���������� ����
	PVirtualNode selectedNode = VirtualStringTree1->FocusedNode;
	if (selectedNode == NULL) return;

	// ����������� ��������� �� ����
	UrlsTableStruct* nodeData = (UrlsTableStruct*) VirtualStringTree1->GetNodeData(selectedNode);

	// 1. ��������� ����������:
	sqlite3* database;

	const wchar_t *filename = dbPath.w_str(); // L".\\History.db";
	int openResult = sqlite3_open16(filename, &database);

	// �������� �������� ��
	if (openResult == 0) {
		// ������� ������ �� �������
		removeEntryCascadeById(database, nodeData->Id);

		// ��������� ����������� �� �����
		VirtualStringTree1->BeginUpdate();
		VirtualStringTree1->DeleteNode(selectedNode);
		VirtualStringTree1->EndUpdate();
	} else {
		printDebug(2, u"������ ��� �������� ��: openResult=" + UnicodeString(openResult));
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DropTableButtonClick(TObject *Sender)
{
	// ��������� ������� ���� � ��
	if (dbPath == u"") {
		printDebug(2, u"������� ��������� ������");
		return;
	}

	// 1. ��������� ����������:
	sqlite3* database;

	const wchar_t *filename = dbPath.w_str(); // L".\\History.db";
	int openResult = sqlite3_open16(filename, &database);

	// �������� �������� ��
	if (openResult == 0) {
		// ������� ������ �� �������
		dropTable(database);

		// ������� ������� � �����
		VirtualStringTree1->Clear();
	} else {
		printDebug(2, u"������ ��� �������� ��: openResult=" + UnicodeString(openResult));
	}
}
//---------------------------------------------------------------------------

