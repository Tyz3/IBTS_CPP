#pragma hdrstop
#pragma argsused

#include <iostream>
#include "rad_console.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	cout << "Visual Studio Dll" << endl;
	cout << GetGroupNumber() << endl;
	wcout << GetStudentName() << endl << endl;

	cout << "RAD Studio Dll" << endl;
	cout << GetGroupNumber2() << endl;
	wcout << GetStudentName2() << endl;

    system("pause");
	return 0;
}
