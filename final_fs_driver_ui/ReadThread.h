//---------------------------------------------------------------------------

#ifndef ReadThreadH
#define ReadThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "FSClusterIter.h"
#include "MainForm.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------
class ReadThread : public TThread
{
private:
	class FSClusterIter* iterator;
	class TForm1* form;
	unsigned long currentIndex;
	sqlite3* database;

protected:
	void __fastcall Execute();
public:
	__fastcall ReadThread(bool CreateSuspended, FSClusterIter* iterator, sqlite3* database, TForm1* form);
	void __fastcall updateProgressBar();
	void __fastcall enableAdditionals();
	void __fastcall fillVST();
};
//---------------------------------------------------------------------------
#endif
