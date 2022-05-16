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

	// Запрашиваем в консоли букву диска (тома)
	UnicodeString friendlyName = E_DeviceFriendlyName->Text;
	char deviceLiteral = friendlyName.w_str()[0];

	// Создаём handle для диска
	HANDLE fileHandle = createDeviceHandle(deviceLiteral);

	// Проверяем создание handle
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		printDebug(3, L"INVALID_HANDLE_VALUE");
		return;
	}

	// Задаём позицию чтения в файле
	bool filePointerCreated = createFilePointer(fileHandle);

	// Проверям позицию
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		printDebug(3, L"Ошибка позиционирования");
		return;
	}

	// Читаем данные из файла
	bool read = readData(fileHandle, dataBuffer);

	CloseHandle(fileHandle);

	// Вывод данных в консоль
	if (read) {
		printDebug(1, L"Данные готовы к чтению");
	} else {
		printDebug(3, L"Ошибка чтения данных с диска");
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

