//---------------------------------------------------------------------------

#ifndef exFATH
#define exFATH
#pragma pack(push, 1)
typedef struct {
	char Padding1[3];

	char OEM_Name[8];                           //
	char Padding2[37];
	unsigned long long FSSectorsCount; 	// ���-�� �������� � ��
	unsigned int StartFatSector;        // ������, � ������� ���������� FAT
	unsigned int FATSizeInSectors;		// ������ FAT � ��������
	unsigned int BitMapSector;			// ������ ������ ������� �����
	unsigned int SectorsCount;			// ���-�� �������� � ��
	unsigned int RootDirCluster;		// ������� ��������� ��������
	unsigned int SerialVolumeNumber;	// �������� ����� ����

	char Padding3[8];
	unsigned char SectorSize;           // ������ ������� (������� 2)
	unsigned char ClusterMultiplier;    // ���������� ��������� (������� 2)

	// ������ ��
	// ���-�� ���������
	// ������ ��������

} exFAT_BootRecord;
#pragma pack(pop)
//---------------------------------------------------------------------------
#endif
