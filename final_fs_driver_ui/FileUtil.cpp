//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileUtil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

HANDLE createDeviceHandle(wchar_t deviceLiteral) {
	wchar_t deviceName[12];
	swprintf(deviceName, L"\\\\.\\%c:", deviceLiteral);

	// Создаём handle для диска
	HANDLE fileHandle = CreateFileW(
		deviceName,
		GENERIC_READ,
		FILE_SHARE_READ, // | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	return fileHandle;
}

bool createFilePointer(HANDLE fileHandle) {
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = 0;

	// Задаём позицию
	unsigned long currentPosition = SetFilePointer(
		fileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN
	);

	return currentPosition == sectorOffset.LowPart;
}

bool readData(HANDLE fileHandle, char dataBuffer[]) {
	DWORD bytesToRead = 512;	// Сколько байтов нужно считать
	DWORD bytesRead; 	    	// Сколько байтов удалось считать

	// Чтение данных
	bool readResult = ReadFile(
		fileHandle,
		dataBuffer,
		bytesToRead,
		&bytesRead,
		NULL
	);

	return readResult && bytesRead == bytesToRead;
}