//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ReadThread::ReadThread(bool CreateSuspended, wchar_t deviceLiteral)
	: TThread(CreateSuspended)
{
	this->myEvent = new TEvent(NULL, true, false, "", false);
	this->processThread = new ProcessThread(true, myEvent, &dataBuffer);
	this->bytesToRead = 4096;
	this->deviceLiteral = deviceLiteral;

	FreeOnTerminate = true;
}

HANDLE createDeviceHandle(wchar_t deviceLiteral) {
	wchar_t deviceName[18];
	swprintf(deviceName, L"\\\\.\\%c:", deviceLiteral);

	// Создаём handle для диска
	HANDLE fileHandle = CreateFile(
		deviceName,
		GENERIC_READ,
		FILE_SHARE_READ, //| FILE_SHARE_WRITE,
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

bool readData(HANDLE fileHandle, char dataBuffer[], DWORD bytesToRead) {
	// DWORD bytesToRea Сколько байтов нужно считать
	DWORD bytesRead; 			// Сколько байтов удалось считать

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

//---------------------------------------------------------------------------
void __fastcall ReadThread::Execute()
{
	processThread->Start();

	// Создаём handle для диска
	HANDLE fileHandle = createDeviceHandle(deviceLiteral);

	// Проверяем создание handle
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		printDebug(1, u"Ошибка создания HANDLE: INVALID_HANDLE_VALUE");
		return;
	} else {
		printDebug(9, u"Создан HANDLE для диска " + UnicodeString(deviceLiteral));
	}

	// Задаём позицию чтения в файле
	bool filePointerCreated = createFilePointer(fileHandle);

	// Проверям позицию
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		printDebug(1, u"Ошибка позиционирования");
		return;
	} else {
		printDebug(9, u"Позиционирование настроено");
	}


	// Отключаем кнопку Прочитать
	Form1->StartReadBtn->Enabled = false;
	Form1->StopReadBtn->Enabled = true;

	// Чтение данных
	while (readData(fileHandle, dataBuffer, bytesToRead)) {
		// Завершаем работу потока
		if (Terminated) {
			messageStatus = 0; Synchronize(&printStatus);
			break;
		}

		messageStatus = 4; Synchronize(&printStatus);

		// Переключаем события в активное состояние
		// второй поток начинает считывать из dataBuffer
		myEvent->SetEvent();

		messageStatus = 3; Synchronize(&printStatus);

		// Цикл работает пока не произойдёт myEvent->ResetEvent()
		while (myEvent->WaitFor(0) == wrSignaled) {
			Sleep(20);
		}

		messageStatus = 1; Synchronize(&printStatus);
	}

	CloseHandle(fileHandle);
	processThread->Terminate();

	messageStatus = 2; Synchronize(&printStatus);
	delete processThread;
}
//---------------------------------------------------------------------------
void __fastcall ReadThread::printStatus()
{
	switch (messageStatus) {
	case 0:
		printDebug(1, u"|||| ReadThread Terminated...");
		break;
	case 1:
		printDebug(2, u"* ReadThread Success...");
		break;
	case 2:
		printDebug(9, u"|||| ReadThread Done...");
		break;
	case 3:
		printDebug(1, u"| ReadThread Waiting...");
		break;
	case 4:
		printDebug(1, u"");
		printDebug(1, u"* ReadThread Start...");
		break;
	}
}

