#pragma hdrstop
#pragma argsused

#include <iostream>
#include "rad_console.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	wchar_t studentName[128];
	wchar_t studentName2[128];

	cout << "Visual Studio Dll" << endl;
	cout << GetGroupNumber() << endl;
	GetStudentName(studentName);
	wcout << studentName << endl << endl;

	cout << "RAD Studio Dll" << endl;
	cout << GetGroupNumber2() << endl;
	GetStudentName2(studentName2);
	wcout << studentName2 << endl;

    system("pause");
	return 0;
}
