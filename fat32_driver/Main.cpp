#include <iostream>
#include <windows.h>
#include "Header.h"

//static char dataBuffer[512];

using namespace std;

char requestDeviceLiteral() {
	char deviceLiteral;
	wcout << endl << L"Введите букву диска с файловой системой FAT32: ";
	cin >> deviceLiteral;
	return deviceLiteral;
}

HANDLE createDeviceHandle(char deviceLiteral) {
	char deviceName[9];
	sprintf(deviceName, "\\\\.\\%c:", deviceLiteral);

	// Создаём handle для диска
	HANDLE fileHandle = CreateFile(
		deviceName,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
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

void printBootRecordInfo(char dataBuffer[]) {
	FAT32_BootRecord* p = reinterpret_cast<FAT32_BootRecord*> (dataBuffer);

	wcout << L"Данные успешно прочитаны" << endl << endl;
	printf("OEM \t\t\t\t\t\t\t %s\n", p->OEM_Name);
	wprintf(L"Байт в секторе \t\t\t\t\t\t %u\n", p->SectorSize);
	wprintf(L"Секторов в кластере (кластерный множитель) \t\t %u\n", p->ClusterSize);
	wprintf(L"Размер зарезервированной области (в секторах) \t\t %u\n", p->ReservedAreaSize);
	wprintf(L"Кол-во копий FAT \t\t\t\t\t %u\n", p->FAT_Count);
	wprintf(
		L"Кол-во секторов в ФС \t\t\t\t\t %u\n",
		(p->FSSectorsCount16 != 0 ? p->FSSectorsCount16 : p->FSSectorsCount32 )
	);
	wprintf(L"Размер FAT в секторах \t\t\t\t\t %u\n", p->FAT_Size32);
	wprintf(L"Кластер расположения корневого каталога \t\t %u\n", p->RootDirectoryCluster);
	wprintf(L"Сектор резервной копии загрузочной записи \t\t %u\n\n", p->RecoveryBootRecordSector);
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	char dataBuffer[512];

	// Запрашиваем в консоли букву диска (тома)
	char deviceLiteral = requestDeviceLiteral();

	// Создаём handle для диска
	HANDLE fileHandle = createDeviceHandle(deviceLiteral);

	// Проверяем создание handle
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		wcout << L"INVALID_HANDLE_VALUE" << endl << endl;
		return 1;
	}

	// Задаём позицию чтения в файле
	bool filePointerCreated = createFilePointer(fileHandle);

	// Проверям позицию
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		wcout << L"Ошибка позиционирования" << endl << endl;
		return 1;
	}

	// Читаем данные из файла
	bool read = readData(fileHandle, dataBuffer);
	
	CloseHandle(fileHandle);

	// Вывод данных в консоль
	if (read) {
		printBootRecordInfo(dataBuffer);
	} else {
		wcout << L"Ошибка чтения данных" << endl << endl;
		return 1;
	}

	return 0;
}

