//---------------------------------------------------------------------------

#ifndef FileSystemTemplateH
#define FileSystemTemplateH
#include "FileUtil.h"
#include <windows.h>
//---------------------------------------------------------------------------
class FileSystemTemplate {
private:
	unsigned int size;
	unsigned int clusterCount;
	unsigned int clusterSize;
public:
	FileSystemTemplate(wchar_t deviceFriendlyName);
	//virtual __fastcall ~FileSystemTemplate();
	virtual void readCluster(int clusterNumber);
	virtual bool mapBootRecord(char* bootRecord);
	unsigned int getSize();
	unsigned int getClusterCount();
	unsigned int getClusterSize();

	bool bootRecordRead;
	wchar_t* errorMsg;
};
#endif
