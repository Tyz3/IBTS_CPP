//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

static wchar_t visualStudioDllName[] = L"vs_dll";
static wchar_t radStudioDllName[] = L"rad_dll";

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
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
	GetStudentName2 = (PGetStudentName2) GetProcAddress(hDll, "GetStudentName2");

	if (GetStudentName2 == NULL) {
		ShowMessage("Function GetStudentName2() not found");
	} else {
		wchar_t studentName[80];
		GetStudentName2(studentName);
		Form1->rad_sn_label->Caption = studentName;
	}

	FreeLibrary(hDll);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::vs_gn_btnClick(TObject *Sender)
{
	HINSTANCE hDll = LoadLibraryW(L"vs_dll");
	if (hDll == NULL) {
		ShowMessage("vs_dll.dll not found");
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
	HINSTANCE hDll = LoadLibraryW(L"vs_dll");
	if (hDll == NULL) {
		ShowMessage("vs_dll.dll not found");
		return;
	}

	PGetStudentName GetStudentName;

	GetStudentName = (PGetStudentName) GetProcAddress(hDll, "_GetStudentName@4");

	if (GetStudentName == NULL) {
		ShowMessage("Function GetStudentName() not found");
	} else {
		wchar_t studentName[80];
		GetStudentName(studentName);
		Form1->vs_sn_label->Caption = studentName;
	}

	FreeLibrary(hDll);
}
//---------------------------------------------------------------------------

