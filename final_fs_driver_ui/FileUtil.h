//---------------------------------------------------------------------------

#ifndef FileUtilH
#define FileUtilH
//---------------------------------------------------------------------------
#endif

#include <windows.h>
#include <stdio.h>

HANDLE createDeviceHandle(wchar_t deviceLiteral);
bool createFilePointer(HANDLE fileHandle, unsigned long long skip);
bool readData(HANDLE fileHandle, char dataBuffer[], DWORD bytesToRead);
void printBootRecordInfo(char dataBuffer[]);

