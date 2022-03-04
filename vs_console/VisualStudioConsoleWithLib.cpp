#include <iostream>
#include "visualstudio_dll.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << GetGroupNumber() << std::endl;
    std::wcout << GetStudentName() << std::endl;
    
    system("pause");
    return 0;
}