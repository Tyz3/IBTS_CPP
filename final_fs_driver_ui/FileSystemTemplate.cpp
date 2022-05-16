//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileSystemTemplate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FileSystemTemplate::FileSystemTemplate(wchar_t deviceLiteral) {

	char bootRecord[512];

	// ������ handle ��� �����
	HANDLE fileHandle = createDeviceHandle(deviceLiteral);
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		errorMsg = L"INVALID_HANDLE_VALUE";
		this->bootRecordRead = false;
		return;
	}

	// ����� ������� ������ � �����
	bool filePointerCreated = createFilePointer(fileHandle);
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		errorMsg = L"������ ����������������";
		this->bootRecordRead = false;
		return;
	}

	// ������ ������ �� �����
	bool read = readData(fileHandle, bootRecord);

	CloseHandle(fileHandle);

	// ����� ������ � �������
	if (read) {
		this->bootRecordRead = this->mapBootRecord(bootRecord);
	} else {
		this->bootRecordRead = false;
	}
}

unsigned int FileSystemTemplate::getSize() {
	return this->size;
}

unsigned int FileSystemTemplate::getClusterCount() {
	return this->clusterCount;
}

unsigned int FileSystemTemplate::getClusterSize() {
	return this->clusterSize;
}

