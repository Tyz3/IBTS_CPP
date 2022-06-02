//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree->NodeDataSize = sizeof(StorageTableStruct);

	// Открываем БД, если что-то пошло не так - блокируем работу
	int openResult = sqlite3_open16(L".\\storage.db", &database);
	if (openResult != 0) {
		printDebug(L_Debug, 3, L"Ошибка открытия БД: .\\storage.db (" + UnicodeString(openResult) + L")");
		B_Start->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B_StartClick(TObject *Sender)
{
	// Запрашиваем в консоли букву диска (тома)
	UnicodeString friendlyName = E_DeviceFriendlyName->Text;
	wchar_t deviceLiteral = friendlyName.w_str()[0];

	// Определяем тип ФС
	FSType fsType = getFSType(deviceLiteral);
	if (fsType == FSType::DEFAULT) {
		return;
	}

	// Создаём объект ФС
	currentFS = createFS(fsType, deviceLiteral);
	if (currentFS == NULL) {
		printDebug(L_Debug, 3, L"Эта файловая система не поддерживается");
		return;
	}

	// Выводим инфо о ФС
	L_FSKeyWord->Caption = currentFS->name;
	showFSInfo(M_Info, currentFS);
	printDebug(L_Debug, 0, L"Файловая система " + L_FSKeyWord->Caption + L" поддерживается");

	ProgressBar->Max = currentFS->getClusterCount();

	bool onlyFullCusters = CB_NotEmptyClusters->Checked;

	FSClusterIter* iter;

	if (onlyFullCusters) {
		iter = new FSClusterIter(new FullClusterDecorator(currentFS));
	} else {
		iter = new FSClusterIter(currentFS);
	}

	readThread = new ReadThread(false, iter, database, Form1);

	B_Start->Enabled = false;
	B_Stop->Enabled = true;

//	sqlite3_close(database);
//	delete currentFS;
}

void __fastcall TForm1::B_StopClick(TObject *Sender)
{
	readThread->Terminate();
	B_Stop->Enabled = false;
	readThread->WaitFor();

    ProgressBar->Position = ProgressBar->Max;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (Node == NULL) return;
	// Накладываем структуру на узел
	StorageTableStruct* nodeData = (StorageTableStruct*) VirtualStringTree->GetNodeData(Node);

	// Инициализируем отображаемые данные в VT
	switch (Column) {
		case 0: {
			CellText = nodeData->cluster;
			break;
		}
		case 1: {
			CellText = nodeData->content;
			break;
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTreeAddToSelection(TBaseVirtualTree *Sender,
		  PVirtualNode Node)
{
	if (Node == NULL) return;

	// Накладываем структуру на узел
	StorageTableStruct* nodeData = (StorageTableStruct*) VirtualStringTree->GetNodeData(Node);

	// Выводим на форму доп. информацию по записи
	L_Id->Caption = nodeData->id;
}
//---------------------------------------------------------------------------

void __fastcall showFSInfo(TMemo* memo, FileSystem* fs) {
	memo->Lines->Clear();
	memo->Lines->Add(L"Размер: " + UnicodeString(fs->getSize()/1024L/1024L) + L"МБ");
	memo->Lines->Add(L"Секторов: " + UnicodeString(fs->getSectorsCount()));
	memo->Lines->Add(L"Кластеров: " + UnicodeString(fs->getClusterCount()));
	memo->Lines->Add(L"Размер кластера: " + UnicodeString(fs->getClusterSize()/1024L) + L"кБ");
}

void __fastcall printDebug(TLabel* label, int colorCode, UnicodeString msg) {
	colorCode = colorCode % 16;

	TColor colors[] = {
		// BLACK	0
		// GREEN	1
		// YELLOW	2
		// RED		3
		clBlack, clGreen, clYellow, clRed, clLime, clAqua, clBlue, clFuchsia,
		clMaroon, clOlive, clNavy, clPurple, clTeal, clGray, clSilver, clWhite
	};

	label->Font->Color = colors[colorCode];
	label->Caption = msg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::B_DeleteEntryClick(TObject *Sender)
{
    // Получаем выделенный узел
	PVirtualNode selectedNode = VirtualStringTree->FocusedNode;
	if (selectedNode == NULL) return;

	// Накладываем структуру на узел
	StorageTableStruct* nodeData = (StorageTableStruct*) VirtualStringTree->GetNodeData(selectedNode);


	// Удаляем запись из таблицы
	deleteStorageEntry(database, nodeData->id);

	// Обновляем отображение на форме
	VirtualStringTree->BeginUpdate();
	VirtualStringTree->DeleteNode(selectedNode);
	VirtualStringTree->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::B_ClearAllClick(TObject *Sender)
{
	// Удаляем данные из БД
	clearStorageTable(database);

	// Очищаем элемент в форме
	VirtualStringTree->Clear();
}
//---------------------------------------------------------------------------

