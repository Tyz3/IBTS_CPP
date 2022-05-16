//---------------------------------------------------------------------------

#ifndef NTFSH
#define NTFSH
#pragma pack(push, 1)
typedef struct {
	char Padding1[3];

	char OEM_Name[8];                           //
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

	// Размер ФС
	// Кол-во кластеров
	// Размер кластера

} NTFS_BootRecord;
#pragma pack(pop)
//---------------------------------------------------------------------------
#endif
