//---------------------------------------------------------------------------

#ifndef exFATH
#define exFATH
#pragma pack(push, 1)
typedef struct {
	char Padding1[3];

	char OEM_Name[8];                           //
	char Padding2[37];
	unsigned long long FSSectorsCount; 	// Кол-во секторов в ФС
	unsigned int StartFatSector;        // Сектор, в котором начинается FAT
	unsigned int FATSizeInSectors;		// Размер FAT в секторах
	unsigned int BitMapSector;			// Сектор начала битовой карты
	unsigned int SectorsCount;			// Кол-во секторов в ФС
	unsigned int RootDirCluster;		// Кластер корневого каталога
	unsigned int SerialVolumeNumber;	// Серийный номер тома

	char Padding3[8];
	unsigned char SectorSize;           // Размер сектора (степень 2)
	unsigned char ClusterMultiplier;    // Кластерный множитель (степень 2)

	// Размер ФС
	// Кол-во кластеров
	// Размер кластера

} exFAT_BootRecord;
#pragma pack(pop)
//---------------------------------------------------------------------------
#endif
