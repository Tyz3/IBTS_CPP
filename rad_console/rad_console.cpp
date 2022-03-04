#include <iostream>
#include "rad_consolePCH1.h"
#include "rad_dll.h"
#include "visualstudio_dll.h"

using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");

	cout << "Visual Studio Dll" << endl;
	cout << GetGroupNumber() << endl;
	wcout << GetStudentName() << endl;

	cout << "RAD Studio Dll" << endl;
	cout << GetGroupNumber2() << endl;
	wcout << GetStudentName2() << endl;

    system("pause");
	return 0;
}
