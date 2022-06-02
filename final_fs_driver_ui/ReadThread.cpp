//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ReadThread.h"
#include "DAO.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ReadThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ReadThread::ReadThread(bool CreateSuspended, FSClusterIter* iterator, sqlite3* database, TForm1* form)
	: TThread(CreateSuspended), iterator(iterator), database(database), form(form)
{
	FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void __fastcall ReadThread::Execute()
{
	//---- Place thread code here ----
	// Удаляем кэш
	clearStorageTable(database);

	for (iterator->first(); !iterator->isDone() && !Terminated; iterator->next()) {
		// Прочитали кластер
		char* dataBuffer = iterator->currentItem();

		// Вставили запись в БД
		insertStorage(database, iterator->getIndex(), dataBuffer, iterator->getFS()->getClusterSize());

		// Обновили прогресс бар
		currentIndex = iterator->getIndex();
		Synchronize(&updateProgressBar);
	}

	// Вывод инфы из БД в vst
	// Заполнение данными из таблицы
	Synchronize(&enableAdditionals);
	Synchronize(&fillVST);
}
//---------------------------------------------------------------------------

void __fastcall ReadThread::updateProgressBar() {
	form->ProgressBar->Position = currentIndex;
}

void __fastcall ReadThread::enableAdditionals() {
	form->B_Start->Enabled = true;
	form->B_Stop->Enabled = false;
	form->B_ClearAll->Enabled = true;
	form->B_DeleteEntry->Enabled = true;
	form->ProgressBar->Position = form->ProgressBar->Max;
}

void __fastcall ReadThread::fillVST() {
	selectStorage(form->VirtualStringTree, database, (char*) form->E_SearchSig->Text.t_str());
}
