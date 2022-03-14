#include "pch.h"
#include "vs_dll.h"

static wchar_t studentName[] = L"Ульянихин Евгений";

int __stdcall GetGroupNumber() {
    return 571227;
}

wchar_t* __stdcall GetStudentName() {
    return studentName;
}
