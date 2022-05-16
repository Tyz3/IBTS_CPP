//---------------------------------------------------------------------------

#ifndef NTFSH
#define NTFSH
#pragma pack(push, 1)
typedef struct {
	char Padding1[3];

	char OEM_Name[8];                           //
	unsigned short SectorSize;					// ������ ������� � ������
	unsigned char ClusterSize;                  // ���-�� �������� � ����� ��������
	char Padding2[7];
	char DeviceType;							// ��� �������� ������
	char Padding3[2];
	char Padding4[2];                       	// ���-�� �������� �� �������
	char Padding5[2];							// ���-�� ��������� �������
	char Padding6[8];
	char Padding7[2];                           // �������� ����� 0x80
	char Padding8[2];                           // �������� ����� 0x80

	unsigned int LeftPartOfSectorsVolumeCount;  // ������� ����� ������ ���������� �������� � �������
	unsigned int RightPartOfSectorsVolumeCount; // ������� ����� ������ ���������� �������� � �������

	unsigned int LeftWordOfMFTCluster;          // ������� ����� ������ ��������, � ������� ���������� ������� MFT
	unsigned int RightWordOfMFTCluster;         // ������� ����� ������ ��������, � ������� ���������� ������� MFT
	unsigned int LeftWordOfMFTClusterCopy;      // ������� ����� ������ ��������, � ������� ���������� ����� ������� MFT
	unsigned int RightWordOfMFTClusterCopy;     // ������� ����� ������ ��������, � ������� ���������� ����� ������� MFT

	unsigned int MFTSizeInClusters;				// ������ ������ MFT � ���������
	unsigned int IndexesBufferSize;				// ������ ������ �������� � ���������
	unsigned int LeftWordOfDriveSerialNumber;   // ������� ����� ��������� ������ �����
	unsigned int RightWordOfDriveSerialNumber;  // ������� ����� ��������� ������ �����

	// ������ ��
	// ���-�� ���������
	// ������ ��������

} NTFS_BootRecord;
#pragma pack(pop)
//---------------------------------------------------------------------------
#endif
