//---------------------------------------------------------------------------

#pragma hdrstop

#include "FormUtil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

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
