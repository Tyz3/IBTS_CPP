//---------------------------------------------------------------------------

#pragma hdrstop

#include "FSClusterIter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FSClusterIter::FSClusterIter(FileSystem* fs)
: fs(fs), index(0), clusterCount(fs->getClusterCount()), done(false) {
	data = new char[fs->getClusterSize()];
}

FSClusterIter::~FSClusterIter() {
	delete[] data;
}

void FSClusterIter::first() {
	index = 0;
}

void FSClusterIter::next() {
	index++;
}

bool FSClusterIter::isDone() {
	return done || index + 1 == clusterCount;
}

char* FSClusterIter::currentItem() {
	char* data = new char[fs->getClusterSize()];
	index = fs->readCluster(data, index);
	if (index == -1) {
		done = true;
	}
	return index == -1 ? NULL : data;
}

unsigned long FSClusterIter::getIndex() {
	return index;
}

FileSystem* FSClusterIter::getFS() {
	return fs;
}


