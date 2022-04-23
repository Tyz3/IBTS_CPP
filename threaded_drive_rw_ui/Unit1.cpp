//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
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

HANDLE createDeviceHandle(wchar_t deviceLiteral) {
	wchar_t deviceName[18];
	swprintf(deviceName, L"\\\\.\\%c:", deviceLiteral);

	// ������ handle ��� �����
	HANDLE fileHandle = CreateFile(
		deviceName,
		GENERIC_READ,
		FILE_SHARE_READ, //| FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	return fileHandle;
}

bool createFilePointer(HANDLE fileHandle) {
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = 0;

	// ����� �������
	unsigned long currentPosition = SetFilePointer(
		fileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN
	);

	return currentPosition == sectorOffset.LowPart;
}

bool readData(HANDLE fileHandle, char dataBuffer[], DWORD bytesToRead) {
	// DWORD bytesToRea ������� ������ ����� �������
	DWORD bytesRead; 			// ������� ������ ������� �������

	// ������ ������
	bool readResult = ReadFile(
		fileHandle,
		dataBuffer,
		bytesToRead,
		&bytesRead,
		NULL
	);

	return readResult && bytesRead == bytesToRead;
}

void __fastcall TForm1::StartReadBtnClick(TObject *Sender)
{
	// ��������� ����� ����� (����) �� �����
	UnicodeString deviceName = ChooseDeviceEdit->Text;
	wchar_t deviceLiteral = deviceName.w_str()[0];

	// ������ handle ��� �����
	HANDLE fileHandle = createDeviceHandle(deviceLiteral);

	// ��������� �������� handle
	if (fileHandle == INVALID_HANDLE_VALUE) {
		CloseHandle(fileHandle);
		printDebug(1, u"������ �������� HANDLE: INVALID_HANDLE_VALUE");
		return;
	} else {
		printDebug(9, u"������ HANDLE ��� ����� " + UnicodeString(deviceLiteral));
	}

	// ����� ������� ������ � �����
	bool filePointerCreated = createFilePointer(fileHandle);

	// �������� �������
	if (!filePointerCreated) {
		CloseHandle(fileHandle);
		printDebug(1, u"������ ����������������");
		return;
	} else {
		printDebug(9, u"���������������� ���������");
	}

	// ������ ������ �� �����
	char dataBuffer[1024];
	bool read = readData(fileHandle, dataBuffer, 1024);
	CloseHandle(fileHandle);

	// ����� ������ � �������
	if (read) {
		printDebug(9, u"������ ��������� � ����� (" + UnicodeString(sizeof(dataBuffer)) + " ����) ");
		// TODO ������ ������
	} else {
		printDebug(1, u"������ ������ ������");
		return;
	}

}
//---------------------------------------------------------------------------
