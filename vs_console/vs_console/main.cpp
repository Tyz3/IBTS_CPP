#include <iostream>
#include "vs_dll.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    wchar_t studentName[80];

    std::cout << GetGroupNumber() << std::endl;
    GetStudentName(studentName);
    std::wcout << studentName << std::endl;

    system("pause");
    return 0;
}
