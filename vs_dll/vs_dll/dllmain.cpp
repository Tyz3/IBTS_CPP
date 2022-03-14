#include "pch.h"
#include "vs_dll.h"

int __stdcall GetGroupNumber() {
    return 571227;
}

void __stdcall GetStudentName(wchar_t* studentName) {
    wcscpy(studentName, L"Ульянихин Евгений");
}
