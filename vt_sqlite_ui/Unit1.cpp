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
	// Шаг 1 (подготовка запроса)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// Формируем запрос
	wchar_t sql[] = L"SELECT id, url, title, visit_count FROM urls;";

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		Form1->VirtualStringTree1->Clear();
		Form1->VirtualStringTree1->BeginUpdate();

		// Шаг 2 (выполнение запроса и получение результата для множества строк)
		printDebug(1, u"Загрузка данных");

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
			printDebug(1, u"Загрузка данных " + UnicodeString(rowsCount));
		}

		Form1->VirtualStringTree1->EndUpdate();

		printDebug(0, u"Данные загружены");
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(2,
			u"Ошибка компиляции SQL-запроса: " + UnicodeString(errmsg)
			+ "\n" + UnicodeString(sql)
		);
		// Сброс пути
		Form1->dbPath = u"";
	}

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatement);
}

void removeEntryCascadeById(sqlite3* database, int id) {
	// Шаг 1 (подготовка запроса)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// Формируем запросы
	wchar_t sql[100];
	wchar_t sql2[100];
	swprintf(sql, 100, L"DELETE FROM urls WHERE id = %d;", id);
	swprintf(sql2, 100, L"DELETE FROM visits WHERE url = %d;", id);

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		// Шаг 2 (выполнение запроса)
		result = sqlite3_step(pStatement);

		// Проверяем результат
		if (result == SQLITE_DONE) {
			// Второй запрос для другой таблицы если 1-ый выполнился
			result = sqlite3_prepare16_v2(database, sql2, -1, &pStatement, NULL);

			if (result == SQLITE_OK) {
				// Шаг 2 (выполнение запроса)
				result = sqlite3_step(pStatement);

				// Проверяем результат
				if (result == SQLITE_DONE) {
					printDebug(0, u"Запись удалена из таблицы urls, также удалены записи по внешним ключам из visits");
				} else {
					printDebug(2, u"Ошибка при выполнении 2-го запроса для таблицы visits: result=" + UnicodeString(result));
				}
			} else {
				errmsg = sqlite3_errmsg(database);
				printDebug(2,
					u"Ошибка компиляции SQL-запроса: " + UnicodeString(errmsg)
					+ "\n" + UnicodeString(sql)
				);
			}
		} else {
			printDebug(2, u"Ошибка при выполнении 1-го запроса для таблицы urls: result=" + UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(2,
			u"Ошибка компиляции SQL-запроса: " + UnicodeString(errmsg)
			+ "\n" + UnicodeString(sql)
		);
	}

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatement);
}

void dropTable(sqlite3* database) {
	// Шаг 1 (подготовка запроса)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// Формируем запрос
	wchar_t sql[] = L"DROP TABLE IF EXISTS urls;";

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		// Шаг 2 (выполнение запроса)
		result = sqlite3_step(pStatement);

		// Проверяем результат
		if (result == SQLITE_DONE) {
			printDebug(0, u"Таблица urls удалена");
		} else {
			printDebug(2, u"Ошибка при выполнении запроса: result=" + UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(2,
			u"Ошибка компиляции SQL-запроса: " + UnicodeString(errmsg)
			+ "\n" + UnicodeString(sql)
		);
	}

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatement);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FillButtonClick(TObject *Sender)
{
	// Запрос на выбор файла с БД
	sendFilePathRequest();

	// Проверяем наличие пути к БД
	if (dbPath == u"") {
		printDebug(2, u"Сначала загрузите данные");
		return;
	}

	// 1. Объявляем переменную:
	sqlite3* database;

	const wchar_t *filename = dbPath.w_str(); // L".\\History.db";
	int openResult = sqlite3_open16(filename, &database);

	// Проверка открытия БД
	if (openResult == 0) {
		// Заполнение данными из таблицы
		fillVirtualTree(database);
	} else {
		printDebug(2,
			"Ошибка при открытии БД: openResult=" + UnicodeString(openResult)
		);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (Node == NULL) return;
	// Накладываем структуру на узел
	UrlsTableStruct* nodeData = (UrlsTableStruct*) VirtualStringTree1->GetNodeData(Node);

	// Инициализируем отображаемые данные в VT
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

	// Накладываем структуру на узел
	UrlsTableStruct* nodeData = (UrlsTableStruct*) VirtualStringTree1->GetNodeData(Node);

	// Выводим на форму кол-во посещений выделенной url
	Label2->Caption = nodeData->VisitCount;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RemoveLineButtonClick(TObject *Sender)
{
	// Проверяем наличие пути к БД
	if (dbPath == u"") {
		printDebug(2, u"Сначала загрузите данные");
		return;
	}

	// Получаем выделенный узел
	PVirtualNode selectedNode = VirtualStringTree1->FocusedNode;
	if (selectedNode == NULL) return;

	// Накладываем структуру на узел
	UrlsTableStruct* nodeData = (UrlsTableStruct*) VirtualStringTree1->GetNodeData(selectedNode);

	// 1. Объявляем переменную:
	sqlite3* database;

	const wchar_t *filename = dbPath.w_str(); // L".\\History.db";
	int openResult = sqlite3_open16(filename, &database);

	// Проверка открытия БД
	if (openResult == 0) {
		// Удаляем запись из таблицы
		removeEntryCascadeById(database, nodeData->Id);

		// Обновляем отображение на форме
		VirtualStringTree1->BeginUpdate();
		VirtualStringTree1->DeleteNode(selectedNode);
		VirtualStringTree1->EndUpdate();
	} else {
		printDebug(2, u"Ошибка при открытии БД: openResult=" + UnicodeString(openResult));
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DropTableButtonClick(TObject *Sender)
{
	// Проверяем наличие пути к БД
	if (dbPath == u"") {
		printDebug(2, u"Сначала загрузите данные");
		return;
	}

	// 1. Объявляем переменную:
	sqlite3* database;

	const wchar_t *filename = dbPath.w_str(); // L".\\History.db";
	int openResult = sqlite3_open16(filename, &database);

	// Проверка открытия БД
	if (openResult == 0) {
		// Удаляем запись из таблицы
		dropTable(database);

		// Очищаем элемент в форме
		VirtualStringTree1->Clear();
	} else {
		printDebug(2, u"Ошибка при открытии БД: openResult=" + UnicodeString(openResult));
	}
}
//---------------------------------------------------------------------------

