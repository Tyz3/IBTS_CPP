#pragma hdrstop
#pragma argsused

#include <stdio.h>
#include "sqlite3.h"

 void addUser(sqlite3* database, const wchar_t* username, const wchar_t* password) {
	// ���������� ������������� �������, �� ��������������� ��������� ���������� (CREATE, DELETE, INSERT, UPDATE � ��.):
	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	wchar_t sql[100];

	swprintf(
		sql, 100,
		L"INSERT INTO users (username, password) VALUES ('%s', '%s')",
		username, password
	);

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result == SQLITE_OK) {
		// ��� 2 (���������� �������)
		result = sqlite3_step(pStatement);

		printf("result = %d\n", result);
	} else {
		errmsg = sqlite3_errmsg(database);
		printf("errmsg = %s\n", errmsg);
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
 }

 void printAllUsers(sqlite3* database) {
	// ���������� �������, ��������������� ��������� ���������� (SELECT)
	// ��� 1 (���������� �������)
	const char *errmsg;
	sqlite3_stmt *pStatement;

	wchar_t sql[] = L"SELECT * FROM users";

	int result = sqlite3_prepare16_v2(database, sql, -1, &pStatement, NULL);

	if (result != SQLITE_OK) {
		errmsg = sqlite3_errmsg(database);
		printf("errmsg = %s\n", errmsg);
	} else {
		wprintf(L"%3s \t %16s \t %16s\n", L"id", L"username", L"password");

		// ��� 2 (���������� ������� � ��������� ���������� ��� ��������� �����)
		while (true) {
			result = sqlite3_step(pStatement);
			if(result != SQLITE_ROW) break;

			int id = sqlite3_column_int(pStatement, 0);
			wchar_t* username = (wchar_t*) sqlite3_column_text16(pStatement, 1);
			wchar_t* password = (wchar_t*) sqlite3_column_text16(pStatement, 2);

			wprintf(L"%03d \t %16s \t %16s\n", id, username, password);
		}
	}

	// ��� 3 (���������� ��������� �������)
	sqlite3_finalize(pStatement);
 }

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	// 1. ��������� ����������:
	sqlite3* database;

	const wchar_t *filename = L"D:\\Coding\\RADStudio\\sqlite3_console\\sample.db";

	// 2. ��������� ���� ������:
	int openResult = sqlite3_open16(filename, &database);

	// �������� �������� ��
	if (openResult == 0) {
		// ��������� ������ � ������� users
		printf("// addUser\n");
		addUser(database, L"Kronos", L"P@ssw0rd");

		printf("\n");

		// �������� ���������� �� ������� users
		printf("// printAllUsers\n");
		printAllUsers(database);
	} else {
		wprintf(L"������ ��� �������� %s, openResult = %d\n", filename, openResult);
	}

	// 3. ��������� ���� ������:
	sqlite3_close(database);

	return 0;
}

