//---------------------------------------------------------------------------

#ifndef FileUtilH
#define FileUtilH
//---------------------------------------------------------------------------
#endif

#include <windows.h>
#include <stdio.h>

HANDLE createDeviceHandle(wchar_t deviceLiteral);
bool createFilePointer(HANDLE fileHandle);
bool readData(HANDLE fileHandle, char dataBuffer[]);
void printBootRecordInfo(char dataBuffer[]);

