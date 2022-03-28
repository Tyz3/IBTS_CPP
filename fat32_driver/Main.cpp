#include <iostream>
#include <windows.h>
#include "Header.h"

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	char dataBuffer[512];
	FAT32_BootRecord* p = (FAT32_BootRecord*) dataBuffer;

	char deviceLetter;
	wcout << endl << L"Введите букву диска с файловой системой FAT32: ";
	cin >> deviceLetter;

	char deviceName[9];
	sprintf(deviceName, "\\\\.\\%c:", deviceLetter);

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

	// Проверяем создание handle
	if (fileHandle != INVALID_HANDLE_VALUE) {
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = 0;

		// Задаём позицию
		unsigned long currentPosition = SetFilePointer(
			fileHandle,
			sectorOffset.LowPart,
			&sectorOffset.HighPart,
			FILE_BEGIN
		);

		// Проверям позицию
		if (currentPosition == sectorOffset.LowPart) {
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

			if (readResult && bytesRead == bytesToRead) {
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
				return 0;
			} else {
				wcout << L"Ошибка чтения данных" << endl << endl;
			}

		} else {
			wcout << L"Какая-то ошибка позиционирования" << endl << endl;
		}

	} else {
		wcout << L"INVALID_HANDLE_VALUE" << endl << endl;
	}

	CloseHandle(fileHandle);

	return 1;
}
