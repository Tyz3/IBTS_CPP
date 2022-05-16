//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "FileUtil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B_StartClick(TObject *Sender)
{
	char dataBuffer[512];

	// ����������� � ������� ����� ����� (����)
	UnicodeString friendlyName = E_DeviceFriendlyName->Text;
	char deviceLiteral = friendlyName.w_str()[0];

	// ������ handle ��� �����
	HANDLE fileHandle = createDeviceHandle(deviceLiteral);

	// ��������� �������� handle
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		printDebug(3, L"INVALID_HANDLE_VALUE");
		return;
	}

	// ����� ������� ������ � �����
	bool filePointerCreated = createFilePointer(fileHandle);

	// �������� �������
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		printDebug(3, L"������ ����������������");
		return;
	}

	// ������ ������ �� �����
	bool read = readData(fileHandle, dataBuffer);

	CloseHandle(fileHandle);

	// ����� ������ � �������
	if (read) {
		printDebug(1, L"������ ������ � ������");
	} else {
		printDebug(3, L"������ ������ ������ � �����");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::printDebug(int colorCode, UnicodeString msg) {
	colorCode = colorCode % 16;

	TColor colors[] = {
		// BLACK	0
		// GREEN	1
		// YELLOW	2
		// RED		3
		clBlack, clGreen, clYellow, clRed, clLime, clAqua, clBlue, clFuchsia,
		clMaroon, clOlive, clNavy, clPurple, clTeal, clGray, clSilver, clWhite
	};

	L_Debug->Font->Color = colors[colorCode];
	L_Debug->Caption = msg;
}

