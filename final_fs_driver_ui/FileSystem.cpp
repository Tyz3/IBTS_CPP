//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileSystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FileSystem::FileSystem(wchar_t deviceLiteral, const char* name)
	: deviceLiteral(deviceLiteral), name(name) {

	fileHandle = createDeviceHandle(deviceLiteral);
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		printDebug(Form1->L_Debug, 0, L"INVALID_HANDLE_VALUE");
	}
}

FileSystem::~FileSystem() {
	CloseHandle(fileHandle);
}


unsigned long FileSystem::readCluster(char* dataBuffer, unsigned long cluster) {
	// Задаём позицию чтения в файле
	bool filePointerCreated = createFilePointer(fileHandle, clusterSize*cluster);
	if (!filePointerCreated) {
		return -1;
	}
	unsigned long res = readData(fileHandle, dataBuffer, clusterSize) ? cluster : -1;
	// Читаем данные из кластера
	return res;
}

// Размер файловой системы (в байтах)
unsigned long long FileSystem::getSize() {
	return size;
}

// Количество кластеров в файловой системе
unsigned long long FileSystem::getClusterCount() {
	return clusterCount;
}

// Размер кластера файловой системы (в байтах)
unsigned long long FileSystem::getClusterSize() {
	return clusterSize;
}

// Количество секторов в файловой системе
unsigned long long FileSystem::getSectorsCount() {
	return sectorsCount;
}


FullClusterDecorator::FullClusterDecorator(FileSystem* fs)
	: FileSystem(fs->deviceLiteral, fs->name), fs(fs) {
	this->size = fs->getSize();
	this->clusterCount = fs->getClusterCount();
	this->clusterSize = fs->getClusterSize();
	this->sectorsCount = fs->getSectorsCount();
}

unsigned long FullClusterDecorator::readCluster(char* dataBuffer, unsigned long cluster) {

	while (true) {
		cluster = fs->readCluster(dataBuffer, cluster);

		if (cluster == -1) {
			return -1;
		}

		// Если первый байт кластера 0x00, то считаем кластер пустым
		if (dataBuffer[0] == 0x00) {
			cluster++;
			continue;
		}

		return cluster;
	}
}


// EXFAT
//
exFAT::exFAT(wchar_t deviceLiteral) : FileSystem(deviceLiteral, "exFAT") {
	char bootRecord[512];

	// Задаём позицию чтения в файле
	bool filePointerCreated = createFilePointer(fileHandle, 0);
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		return;
	}

	// Читаем данные из файла
	bool read = readData(fileHandle, bootRecord, 512);

	if (read) {
		exFAT_BootRecord* br = reinterpret_cast<exFAT_BootRecord*> (bootRecord);

		clusterSize = (unsigned long long) (
			(2 << br->BytesPerSectorShift >> 1) *
			(2 << br->SectorsPerClusterShift >> 1)
		);
		sectorsCount = br->VolumeLength;
		clusterCount = br->ClusterCount;
		size = clusterSize*clusterCount;
	}
}


// NTFS
//
NTFS::NTFS(wchar_t deviceLiteral) : FileSystem(deviceLiteral, "NTFS") {
	char bootRecord[512];

	// Задаём позицию чтения в файле
	bool filePointerCreated = createFilePointer(fileHandle, 0);
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		return;
	}

	// Читаем данные из файла
	bool read = readData(fileHandle, bootRecord, 512);

	if (read) {
		NTFS_BootRecord* br = reinterpret_cast<NTFS_BootRecord*> (bootRecord);

		clusterSize = (unsigned long long)(br->SectorSize * br->ClusterSize);
		unsigned int left = br->LeftPartOfSectorsVolumeCount;
		unsigned int right = br->RightPartOfSectorsVolumeCount;
		sectorsCount = (unsigned long long) (
			right << 32 | left
		);
		clusterCount = sectorsCount*br->SectorSize/clusterSize;
		size = sectorsCount*br->SectorSize;
	}
}


// FAT32
//
FAT32::FAT32(wchar_t deviceLiteral) : FileSystem(deviceLiteral, "MSDOS5.0") {
	char bootRecord[512];

	// Задаём позицию чтения в файле
	bool filePointerCreated = createFilePointer(fileHandle, 0);
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		return;
	}

	// Читаем данные из файла
	bool read = readData(fileHandle, bootRecord, 512);

	if (read) {
		FAT32_BootRecord* br = reinterpret_cast<FAT32_BootRecord*> (bootRecord);
		clusterSize = (unsigned long long)(br->SectorSize * br->ClusterSize);
		sectorsCount = br->FSSectorsCount16 != 0 ? br->FSSectorsCount16 : br->FSSectorsCount32;
		clusterCount = (unsigned long long)(sectorsCount * br->SectorSize/clusterSize);
		size = sectorsCount * br->SectorSize;
	}
}


// Определение файловой системы по сигнатуре OEM
//
FSType getFSType(wchar_t deviceLiteral) {
	char OEM[512];

	// Создаём handle для диска
	HANDLE fileHandle = createDeviceHandle(deviceLiteral);
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		printDebug(Form1->L_Debug, 3, L"INVALID_HANDLE_VALUE");
		return DEFAULT;
	}

	// Задаём позицию чтения в файле
	bool filePointerCreated = createFilePointer(fileHandle, 0);
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		printDebug(Form1->L_Debug, 3, L"Ошибка позиционирования в файле");
		return DEFAULT;
	}

	// Читаем данные из файла
	bool read = readData(fileHandle, OEM, 512);

	CloseHandle(fileHandle);

	// Если сектор удалось прочитать
	if (read) {
		if (strstr(OEM, "MSDOS5.0") != 0) {
			return FSType::FAT32_FS;
		}

		if (strstr(OEM, "NTFS") != 0) {
			return FSType::NTFS_FS;
		}

		if (strstr(OEM, "EXFAT") != 0) {
			return FSType::exFAT_FS;
		}

		printDebug(Form1->L_Debug, 2, L"Файловая система не поддерживается");
		return DEFAULT;
	}

	printDebug(Form1->L_Debug, 3, L"Ошибка чтения данных");

	return DEFAULT;
}


// Factory Method
//
FileSystem* createFS(FSType type, wchar_t deviceLiteral) {
	FileSystem* p;
	switch (type) {
		case FSType::exFAT_FS:
			p = new exFAT(deviceLiteral);
			break;
		case FSType::NTFS_FS:
			p = new NTFS(deviceLiteral);
			break;
		case FSType::FAT32_FS:
			p = new FAT32(deviceLiteral);
			break;
	}

	return p;
}
