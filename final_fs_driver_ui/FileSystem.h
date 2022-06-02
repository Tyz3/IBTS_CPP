//---------------------------------------------------------------------------

#ifndef FileSystemH
#define FileSystemH
#include <cstring>
#include "FileUtil.h"
#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct {
	char JumpBoot[3];

	char OEM[8];                   				//
	char MustBeZero[53];
	unsigned long long PartitionOffset;
	unsigned long long VolumeLength; 			// Кол-во секторов в ФС
	unsigned int FatOffset;        				// Сектор, в котором начинается FAT
	unsigned int FatLength;						// Размер FAT в секторах
	unsigned int ClusterHeapOffset;				// Сектор начала битовой карты
	unsigned int ClusterCount;					// Кол-во кластеров в ФС
	unsigned int FirstClusterOfRootDirectory;	// Кластер корневого каталога
	unsigned int VolumeSerialNumber;			// Серийный номер тома
	unsigned short FileSystemRevision;
	unsigned short VolumeFlags;

	unsigned char BytesPerSectorShift;     		// Размер сектора (степень 2)
	unsigned char SectorsPerClusterShift; 		// Кластерный множитель (степень 2)

} exFAT_BootRecord;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	// FAT12/16
	char Padding1[3];

	char OEM[8];                          	 	//
	unsigned short SectorSize;             		// Кол-во байт в секторе
	unsigned char ClusterSize;           		// Кол-во секторов в кластере (кластерный множитель)
	unsigned short ReservedAreaSize;            // Размер зарезервированной области (в секторах)
	unsigned char FAT_Count;                    // Кол-во копий FAT
	unsigned short MaxEntriesRootDirectory;     // Макс. кол-во 32-байтовых записей в корневом каталоге,
												// определяющее его размер (для FAT12 и FAT16)
	unsigned short FSSectorsCount16;            // Кол-во секторов в файловой системе (0, если число не
												// представить 16 разрядами)
	char DeviceType;                            // Тип носителя: F8 - стационарный, F0 - съёмный
	unsigned short FAT_Size;                    // Только FAT12/16: размер FAT в секторах

	char Padding2[2];                           // Кол-во секторов в дорожке
	char Padding3[2];                           // Кол-во головок
	char Padding4[4];                           // Кол-во секторов перед началом раздела

	unsigned int FSSectorsCount32;              // Кол-во секторов в файловой системе (0, если число можно
												// представить 16 разрядами)

	// FAT32
	unsigned int FAT_Size32;                    // Размер FAT в секторах
	unsigned int RootDirectoryCluster;    		// Кластер расположения корневого каталога
	unsigned short RecoveryBootRecordSector;    // Сектор резервной копии загрузочной записи

} FAT32_BootRecord;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	char Padding1[3];

	char OEM[8];                           		//
	unsigned short SectorSize;					// Размер сектора в байтах
	unsigned char ClusterSize;                  // Кол-во секторов в одном кластере
	char Padding2[7];
	char DeviceType;							// Тип носителя данных
	char Padding3[2];
	char Padding4[2];                       	// Кол-во секторов на дорожке
	char Padding5[2];							// Кол-во магнитных головок
	char Padding6[8];
	char Padding7[2];                           // Содержит число 0x80
	char Padding8[2];                           // Содержит число 0x80

	unsigned int LeftPartOfSectorsVolumeCount;  // Младшее слово общего количества секторов в разделе
	unsigned int RightPartOfSectorsVolumeCount; // Старшее слово общего количества секторов в разделе

	unsigned int LeftWordOfMFTCluster;          // Младшее слово номера кластера, в котором начинается таблица MFT
	unsigned int RightWordOfMFTCluster;         // Старшее слово номера кластера, в котором начинается таблица MFT
	unsigned int LeftWordOfMFTClusterCopy;      // Младшее слово номера кластера, в котором начинается копия таблицы MFT
	unsigned int RightWordOfMFTClusterCopy;     // Старшее слово номера кластера, в котором начинается копия таблицы MFT

	unsigned int MFTSizeInClusters;				// Размер записи MFT в кластерах
	unsigned int IndexesBufferSize;				// Размер буфера индексов в кластерах
	unsigned int LeftWordOfDriveSerialNumber;   // Младшее слово серийного номера диска
	unsigned int RightWordOfDriveSerialNumber;  // Старшее слово серийного номера диска

} NTFS_BootRecord;
#pragma pack(pop)

enum FSType {
	DEFAULT=0,
	exFAT_FS=1,
	NTFS_FS=2,
	FAT32_FS=3
};

class FileSystem {
	private:

	protected:
		HANDLE fileHandle;
		unsigned long long size;
		unsigned long long clusterCount;
		unsigned long long clusterSize;
		unsigned long long sectorsCount;

		FileSystem(wchar_t deviceLiteral, const char* name);

	public:
		const wchar_t deviceLiteral;
		const char* name;

		// Размер файловой системы (в байтах)
		unsigned long long getSize();
		// Количество кластеров в файловой системе
		unsigned long long getClusterCount();
		// Размер кластера файловой системы (в байтах)
		unsigned long long getClusterSize();
		unsigned long long getSectorsCount();

		virtual unsigned long readCluster(char* dataBuffer, unsigned long cluster);

		~FileSystem();
};

class exFAT : public FileSystem {
	public:
		exFAT(wchar_t deviceLiteral);
};

class NTFS : public FileSystem {
	public:
		NTFS(wchar_t deviceLiteral);
};

class FAT32 : public FileSystem {
	public:
		FAT32(wchar_t deviceLiteral);
};

class FullClusterDecorator : public FileSystem {
	public:
		class FileSystem* fs;
		FullClusterDecorator(FileSystem* fs);

		unsigned long readCluster(char* dataBuffer, unsigned long cluster);
};

FSType getFSType(wchar_t deviceLiteral);
FileSystem* createFS(FSType type, wchar_t deviceLiteral);


#endif
