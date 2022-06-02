//---------------------------------------------------------------------------

#pragma hdrstop

#include "DAO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void selectStorage(TVirtualStringTree* vst, sqlite3* database, char* clusterSignature) {
	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// ��������� ������ � ����������� �������� �� ���������
	wchar_t* sql = new wchar_t[256];
	swprintf(sql, 256,
		L"SELECT id, cluster, content FROM storage WHERE content LIKE '%%%s%%';",
		clusterSignature
	);

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		vst->Clear();
		vst->BeginUpdate();

		// ��� 2 (���������� ������� � ��������� ���������� ��� ��������� �����)
		printDebug(Form1->L_Debug, 0, L"�������� ������");

		int rowsCount = 0;
		while (true) {
			result = sqlite3_step(pStatement);
			if(result != SQLITE_ROW) break;

			PVirtualNode entryNode = vst->AddChild(vst->RootNode);
			StorageTableStruct* nodeData = (StorageTableStruct*) vst->GetNodeData(entryNode);

			nodeData->id = sqlite3_column_int64(pStatement, 0);
			nodeData->cluster = sqlite3_column_int(pStatement, 1);
			nodeData->content = UnicodeString(
					(char*) sqlite3_column_blob(pStatement, 2), // ���������� ��������
					sqlite3_column_bytes(pStatement, 2) // ���-�� ����, ������� ����� ���������
			);

			rowsCount++;
			printDebug(Form1->L_Debug, 0, L"�������� ������ " + UnicodeString(rowsCount));
		}

		Form1->L_ClusterCount->Caption = rowsCount;

		vst->EndUpdate();

		printDebug(Form1->L_Debug, 0, L"������ ���������");
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(Form1->L_Debug, 3,
			L"������ ���������� SQL-�������: " + UnicodeString(errmsg) + ", " + UnicodeString(sql)
		);
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
}

void insertStorage(
	sqlite3* database,
	unsigned long cluster,
	char* content,
	unsigned long clusterSize
	) {
	// ��� 1 (���������� �������)
	const char* errmsg;
	sqlite3_stmt* pStatement;

	// ��������� �������
	wchar_t* sql = new wchar_t[clusterSize+64];
	swprintf(sql, clusterSize+64,
		L"INSERT INTO storage (cluster, content) VALUES (%d, ?);",
		cluster
	);

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);
	sqlite3_bind_blob(pStatement, 1, content, clusterSize, SQLITE_TRANSIENT);


	if (result == SQLITE_OK) {
		// ��� 2 (���������� �������)
		result = sqlite3_step(pStatement);

		// ��������� ���������
		if (result == SQLITE_DONE) {
			printDebug(Form1->L_Debug, 1, L"������ ��������� � ������� storage");
		} else {
			printDebug(Form1->L_Debug, 3, L"������ ��� ���������� ������� ��� ������� storage: result="
			+ UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(Form1->L_Debug, 3,
			L"������ ���������� SQL-�������: " + UnicodeString(errmsg)
			+ ", " + UnicodeString(sql)
		);
	}

	printDebug(Form1->L_Debug, 1, UnicodeString(sql));

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
}

void clearStorageTable(sqlite3* database) {
	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// ��������� ������
	wchar_t sql[] = L"DELETE FROM storage;";

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		// ��� 2 (���������� �������)
		result = sqlite3_step(pStatement);

		// ��������� ���������
		if (result == SQLITE_DONE) {
			printDebug(Form1->L_Debug, 1, L"������� storage �������");
		} else {
			printDebug(Form1->L_Debug, 3, L"������ ��� ���������� �������: result="
					+ UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(Form1->L_Debug, 3, L"������ ���������� SQL-�������: " + UnicodeString(errmsg)
			+ ", " + UnicodeString(sql)
		);
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
}

void deleteStorageEntry(sqlite3* database, unsigned long id) {
	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// ��������� �������
	wchar_t sql[100];
	swprintf(sql, 100, L"DELETE FROM storage WHERE id = %d;", id);

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		// ��� 2 (���������� �������)
		result = sqlite3_step(pStatement);

		// ��������� ���������
		if (result == SQLITE_DONE) {
			printDebug(Form1->L_Debug, 1, L"������ ������� �� ������� storage");
		} else {
			printDebug(Form1->L_Debug, 3, L"������ ��� ���������� ������� ��� ������� storage: result="
			+ UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(Form1->L_Debug, 3,
			L"������ ���������� SQL-�������: " + UnicodeString(errmsg)
			+ ", " + UnicodeString(sql)
		);
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
}
