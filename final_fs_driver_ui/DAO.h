//---------------------------------------------------------------------------

#ifndef DAOH
#define DAOH
#include "sqlite3.h"
#include "MainForm.h"
#include <cstring>
#include <wchar.h>
//---------------------------------------------------------------------------
void selectStorage(TVirtualStringTree* vst, sqlite3* database, char* clusterSignature);
void insertStorage(sqlite3* database, unsigned long cluster, char* content, unsigned long clusterSize);
void clearStorageTable(sqlite3* database);
void deleteStorageEntry(sqlite3* database, unsigned long id);
#endif
