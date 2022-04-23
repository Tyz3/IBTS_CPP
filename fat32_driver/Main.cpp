#include <iostream>
#include <windows.h>
#include "Header.h"

//static char dataBuffer[512];

using namespace std;

char requestDeviceLiteral() {
	char deviceLiteral;
	wcout << endl << L"������� ����� ����� � �������� �������� FAT32: ";
	cin >> deviceLiteral;
	return deviceLiteral;
}

HANDLE createDeviceHandle(char deviceLiteral) {
	char deviceName[9];
	sprintf(deviceName, "\\\\.\\%c:", deviceLiteral);

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
	return fileHandle;
}

bool createFilePointer(HANDLE fileHandle) {
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = 0;

	// ����� �������
	unsigned long currentPosition = SetFilePointer(
		fileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN
	);

	return currentPosition == sectorOffset.LowPart;
}

bool readData(HANDLE fileHandle, char dataBuffer[]) {
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

	return readResult && bytesRead == bytesToRead;
}

void printBootRecordInfo(char dataBuffer[]) {
	FAT32_BootRecord* p = reinterpret_cast<FAT32_BootRecord*> (dataBuffer);

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
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	char dataBuffer[512];

	// ����������� � ������� ����� ����� (����)
	char deviceLiteral = requestDeviceLiteral();

	// ������ handle ��� �����
	HANDLE fileHandle = createDeviceHandle(deviceLiteral);

	// ��������� �������� handle
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		wcout << L"INVALID_HANDLE_VALUE" << endl << endl;
		return 1;
	}

	// ����� ������� ������ � �����
	bool filePointerCreated = createFilePointer(fileHandle);

	// �������� �������
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		wcout << L"������ ����������������" << endl << endl;
		return 1;
	}

	// ������ ������ �� �����
	bool read = readData(fileHandle, dataBuffer);
	
	CloseHandle(fileHandle);

	// ����� ������ � �������
	if (read) {
		printBootRecordInfo(dataBuffer);
	} else {
		wcout << L"������ ������ ������" << endl << endl;
		return 1;
	}

	return 0;
}

