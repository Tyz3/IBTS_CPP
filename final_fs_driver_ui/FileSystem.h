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
	unsigned long long VolumeLength; 			// ���-�� �������� � ��
	unsigned int FatOffset;        				// ������, � ������� ���������� FAT
	unsigned int FatLength;						// ������ FAT � ��������
	unsigned int ClusterHeapOffset;				// ������ ������ ������� �����
	unsigned int ClusterCount;					// ���-�� ��������� � ��
	unsigned int FirstClusterOfRootDirectory;	// ������� ��������� ��������
	unsigned int VolumeSerialNumber;			// �������� ����� ����
	unsigned short FileSystemRevision;
	unsigned short VolumeFlags;

	unsigned char BytesPerSectorShift;     		// ������ ������� (������� 2)
	unsigned char SectorsPerClusterShift; 		// ���������� ��������� (������� 2)

} exFAT_BootRecord;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	// FAT12/16
	char Padding1[3];

	char OEM[8];                          	 	//
	unsigned short SectorSize;             		// ���-�� ���� � �������
	unsigned char ClusterSize;           		// ���-�� �������� � �������� (���������� ���������)
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

#pragma pack(push, 1)
typedef struct {
	char Padding1[3];

	char OEM[8];                           		//
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

		// ������ �������� ������� (� ������)
		unsigned long long getSize();
		// ���������� ��������� � �������� �������
		unsigned long long getClusterCount();
		// ������ �������� �������� ������� (� ������)
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
