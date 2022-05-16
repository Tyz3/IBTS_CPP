//---------------------------------------------------------------------------

#ifndef FAT32H
#define FAT32H
#pragma pack(push, 1)
typedef struct {
	// FAT12/16
	char Padding1[3];

	char OEM_Name[8];                           //
	unsigned short SectorSize;                  // ���-�� ���� � �������
	unsigned char ClusterSize;                  // ���-�� �������� � �������� (���������� ���������)
	unsigned short ReservedAreaSize;            // ������ ����������������� ������� (� ��������)
	unsigned char FAT_Count;                    // ���-�� ����� FAT
	unsigned short MaxEntriesRootDirectory;     // ����. ���-�� 32-�������� ������� � �������� ��������,
												// ������������ ��� ������ (��� FAT12 � FAT16)
	unsigned short FSSectorsCount16;            // ���-�� �������� � �������� ������� (0, ���� ����� ��
												// ����������� 16 ���������)
	char DeviceType;                            // ��� ��������: F8 - ������������, F0 - �������
	unsigned short FAT_Size;                    // ������ FAT12/16: ������ FAT � ��������

	char Padding2[2];                           // ���-�� �������� � �������
	char Padding3[2];                           // ���-�� �������
	char Padding4[4];                           // ���-�� �������� ����� ������� �������

	unsigned int FSSectorsCount32;              // ���-�� �������� � �������� ������� (0, ���� ����� �����
												// ����������� 16 ���������)

	// FAT32
	unsigned int FAT_Size32;                    // ������ FAT � ��������
	unsigned int RootDirectoryCluster;    		// ������� ������������ ��������� ��������
	unsigned short RecoveryBootRecordSector;    // ������ ��������� ����� ����������� ������

} FAT32_BootRecord;
#pragma pack(pop)
//---------------------------------------------------------------------------
#endif
