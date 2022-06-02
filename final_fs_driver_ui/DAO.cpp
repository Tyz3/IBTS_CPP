//---------------------------------------------------------------------------

#pragma hdrstop

#include "DAO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void selectStorage(TVirtualStringTree* vst, sqlite3* database, char* clusterSignature) {
	// Шаг 1 (подготовка запроса)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// Формируем запрос с фильтрацией кластера по сигнатуре
	wchar_t* sql = new wchar_t[256];
	swprintf(sql, 256,
		L"SELECT id, cluster, content FROM storage WHERE content LIKE '%%%s%%';",
		clusterSignature
	);

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		vst->Clear();
		vst->BeginUpdate();

		// Шаг 2 (выполнение запроса и получение результата для множества строк)
		printDebug(Form1->L_Debug, 0, L"Загрузка данных");

		int rowsCount = 0;
		while (true) {
			result = sqlite3_step(pStatement);
			if(result != SQLITE_ROW) break;

			PVirtualNode entryNode = vst->AddChild(vst->RootNode);
			StorageTableStruct* nodeData = (StorageTableStruct*) vst->GetNodeData(entryNode);

			nodeData->id = sqlite3_column_int64(pStatement, 0);
			nodeData->cluster = sqlite3_column_int(pStatement, 1);
			nodeData->content = UnicodeString(
					(char*) sqlite3_column_blob(pStatement, 2), // содержимое кластера
					sqlite3_column_bytes(pStatement, 2) // кол-во байт, которые нужно прочитать
			);

			rowsCount++;
			printDebug(Form1->L_Debug, 0, L"Загрузка данных " + UnicodeString(rowsCount));
		}

		Form1->L_ClusterCount->Caption = rowsCount;

		vst->EndUpdate();

		printDebug(Form1->L_Debug, 0, L"Данные загружены");
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(Form1->L_Debug, 3,
			L"Ошибка компиляции SQL-запроса: " + UnicodeString(errmsg) + ", " + UnicodeString(sql)
		);
	}

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatement);
}

void insertStorage(
	sqlite3* database,
	unsigned long cluster,
	char* content,
	unsigned long clusterSize
	) {
	// Шаг 1 (подготовка запроса)
	const char* errmsg;
	sqlite3_stmt* pStatement;

	// Формируем запросы
	wchar_t* sql = new wchar_t[clusterSize+64];
	swprintf(sql, clusterSize+64,
		L"INSERT INTO storage (cluster, content) VALUES (%d, ?);",
		cluster
	);

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);
	sqlite3_bind_blob(pStatement, 1, content, clusterSize, SQLITE_TRANSIENT);


	if (result == SQLITE_OK) {
		// Шаг 2 (выполнение запроса)
		result = sqlite3_step(pStatement);

		// Проверяем результат
		if (result == SQLITE_DONE) {
			printDebug(Form1->L_Debug, 1, L"Запись добавлена в таблицу storage");
		} else {
			printDebug(Form1->L_Debug, 3, L"Ошибка при выполнении запроса для таблицы storage: result="
			+ UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(Form1->L_Debug, 3,
			L"Ошибка компиляции SQL-запроса: " + UnicodeString(errmsg)
			+ ", " + UnicodeString(sql)
		);
	}

	printDebug(Form1->L_Debug, 1, UnicodeString(sql));

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatement);
}

void clearStorageTable(sqlite3* database) {
	// Шаг 1 (подготовка запроса)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// Формируем запрос
	wchar_t sql[] = L"DELETE FROM storage;";

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		// Шаг 2 (выполнение запроса)
		result = sqlite3_step(pStatement);

		// Проверяем результат
		if (result == SQLITE_DONE) {
			printDebug(Form1->L_Debug, 1, L"Таблица storage очищена");
		} else {
			printDebug(Form1->L_Debug, 3, L"Ошибка при выполнении запроса: result="
					+ UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(Form1->L_Debug, 3, L"Ошибка компиляции SQL-запроса: " + UnicodeString(errmsg)
			+ ", " + UnicodeString(sql)
		);
	}

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatement);
}

void deleteStorageEntry(sqlite3* database, unsigned long id) {
	// Шаг 1 (подготовка запроса)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	// Формируем запросы
	wchar_t sql[100];
	swprintf(sql, 100, L"DELETE FROM storage WHERE id = %d;", id);

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		// Шаг 2 (выполнение запроса)
		result = sqlite3_step(pStatement);

		// Проверяем результат
		if (result == SQLITE_DONE) {
			printDebug(Form1->L_Debug, 1, L"Запись удалена из таблицы storage");
		} else {
			printDebug(Form1->L_Debug, 3, L"Ошибка при выполнении запроса для таблицы storage: result="
			+ UnicodeString(result));
		}
	} else {
		errmsg = sqlite3_errmsg(database);
		printDebug(Form1->L_Debug, 3,
			L"Ошибка компиляции SQL-запроса: " + UnicodeString(errmsg)
			+ ", " + UnicodeString(sql)
		);
	}

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatement);
}
