//---------------------------------------------------------------------------

#ifndef FAT32H
#define FAT32H
#pragma pack(push, 1)
typedef struct {
	// FAT12/16
	char Padding1[3];

	char OEM_Name[8];                           //
	unsigned short SectorSize;                  // Кол-во байт в секторе
	unsigned char ClusterSize;                  // Кол-во секторов в кластере (кластерный множитель)
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
//---------------------------------------------------------------------------
#endif
