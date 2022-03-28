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
	wcout << endl << L"������� ����� ����� � �������� �������� FAT32: ";
	cin >> deviceLetter;

	char deviceName[9];
	sprintf(deviceName, "\\\\.\\%c:", deviceLetter);

	// ������ handle ��� �����
	HANDLE fileHandle = CreateFile(
		deviceName,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// ��������� �������� handle
	if (fileHandle != INVALID_HANDLE_VALUE) {
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = 0;

		// ����� �������
		unsigned long currentPosition = SetFilePointer(
			fileHandle,
			sectorOffset.LowPart,
			&sectorOffset.HighPart,
			FILE_BEGIN
		);

		// �������� �������
		if (currentPosition == sectorOffset.LowPart) {
			DWORD bytesToRead = 512;	// ������� ������ ����� �������
			DWORD bytesRead; 	    	// ������� ������ ������� �������

			// ������ ������
			bool readResult = ReadFile(
				fileHandle,
				dataBuffer,
				bytesToRead,
				&bytesRead,
				NULL
			);

			if (readResult && bytesRead == bytesToRead) {
				wcout << L"������ ������� ���������" << endl << endl;
				printf("OEM \t\t\t\t\t\t\t %s\n", p->OEM_Name);
				wprintf(L"���� � ������� \t\t\t\t\t\t %u\n", p->SectorSize);
				wprintf(L"�������� � �������� (���������� ���������) \t\t %u\n", p->ClusterSize);
				wprintf(L"������ ����������������� ������� (� ��������) \t\t %u\n", p->ReservedAreaSize);
				wprintf(L"���-�� ����� FAT \t\t\t\t\t %u\n", p->FAT_Count);
				wprintf(
					L"���-�� �������� � �� \t\t\t\t\t %u\n",
					(p->FSSectorsCount16 != 0 ? p->FSSectorsCount16 : p->FSSectorsCount32 )
				);
				wprintf(L"������ FAT � �������� \t\t\t\t\t %u\n", p->FAT_Size32);
				wprintf(L"������� ������������ ��������� �������� \t\t %u\n", p->RootDirectoryCluster);
				wprintf(L"������ ��������� ����� ����������� ������ \t\t %u\n\n", p->RecoveryBootRecordSector);
				return 0;
			} else {
				wcout << L"������ ������ ������" << endl << endl;
			}

		} else {
			wcout << L"�����-�� ������ ����������������" << endl << endl;
		}

	} else {
		wcout << L"INVALID_HANDLE_VALUE" << endl << endl;
	}

	CloseHandle(fileHandle);

	return 1;
}
