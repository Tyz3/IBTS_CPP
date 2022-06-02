//---------------------------------------------------------------------------

#ifndef FSClusterIterH
#define FSClusterIterH
#include "FileSystem.h"
//---------------------------------------------------------------------------

class FSClusterIter {
	private:
		class FileSystem* fs;
		unsigned long index;
		const unsigned long clusterCount;

		char* data;
		bool done;
	public:
		FSClusterIter(FileSystem* fs);

		void first();
		void next();
		bool isDone();
		char* currentItem();
		unsigned long getIndex();
        FileSystem* getFS();

		~FSClusterIter();
};

#endif
