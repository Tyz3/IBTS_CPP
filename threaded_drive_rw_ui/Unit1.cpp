//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void printDebug(int colorCode, UnicodeString msg) {
	TColor colors[] = {
		// GREEN - 9
		// YELLOW - 2
		// RED - 1
		clBlack, clRed, clYellow, clLime, clAqua, clBlue, clFuchsia, clWhite,
		clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver
	};

	Form1->DebugLabel->Font->Color = colors[colorCode];
	Form1->DebugLabel->Caption = msg;
	Form1->LogsMemo->Lines->Append(msg);
}

void __fastcall TForm1::StartReadBtnClick(TObject *Sender)
{
	// «читываем букву диска (тома) из формы
	UnicodeString deviceName = ChooseDeviceEdit->Text;
	wchar_t deviceLiteral = deviceName.w_str()[0];

	readThread = new ReadThread(false, deviceLiteral);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StopReadBtnClick(TObject *Sender)
{
	StopReadBtn->Enabled = false;
	readThread->Terminate();
}
//---------------------------------------------------------------------------


