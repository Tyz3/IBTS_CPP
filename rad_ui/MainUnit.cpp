//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
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

void __fastcall TForm1::vs_gn_btnClick(TObject *Sender)
{
	HINSTANCE hDll = LoadLibraryW(L"visualstudio_dll");
	if (hDll == NULL) {
		ShowMessage("visualstudio_dll.dll not found");
		return;
	}

	PGetGroupNumber GetGroupNumber;

	GetGroupNumber = (PGetGroupNumber) GetProcAddress(hDll, "_GetGroupNumber@0");

	if (GetGroupNumber == NULL) {
		ShowMessage("Function GetGroupNumber() not found");
	} else {
		Form1->vs_gn_label->Caption = GetGroupNumber();
	}

	FreeLibrary(hDll);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::vs_sn_btnClick(TObject *Sender)
{
	HINSTANCE hDll = LoadLibraryW(L"visualstudio_dll");
	if (hDll == NULL) {
		ShowMessage("visualstudio_dll.dll not found");
		return;
	}

	PGetStudentName GetStudentName;

	GetStudentName = (PGetStudentName) GetProcAddress(hDll, "_GetStudentName@0");

	if (GetStudentName == NULL) {
		ShowMessage("Function GetStudentName() not found");
	} else {
		Form1->vs_sn_label->Caption = GetStudentName();
	}

	FreeLibrary(hDll);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rad_gn_btnClick(TObject *Sender)
{
	HINSTANCE hDll = LoadLibraryW(L"rad_dll");
	if (hDll == NULL) {
		ShowMessage("rad_dll.dll not found");
		return;
	}

	PGetGroupNumber2 GetGroupNumber2;

	GetGroupNumber2 = (PGetGroupNumber2) GetProcAddress(hDll, "GetGroupNumber2");

	if (GetGroupNumber2 == NULL) {
		ShowMessage("Function GetGroupNumber2() not found");
	} else {
		Form1->rad_gn_label->Caption = GetGroupNumber2();
	}

	FreeLibrary(hDll);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rad_sn_btnClick(TObject *Sender)
{
	HINSTANCE hDll = LoadLibraryW(L"rad_dll");
	if (hDll == NULL) {
		ShowMessage("rad_dll.dll not found");
		return;
	}

	PGetStudentName2 GetStudentName2;
	GetStudentName2 = (PGetStudentName) GetProcAddress(hDll, "GetStudentName2");

	if (GetStudentName2 == NULL) {
		ShowMessage("Function GetStudentName2() not found");
	} else {
		Form1->rad_sn_label->Caption = GetStudentName2();
	}

	FreeLibrary(hDll);
}
//---------------------------------------------------------------------------

