#include "rad_dllPCH1.h"
#include "rad_dll.h"

static wchar_t studentName[] = L"Ульянихин Евгений";

int __stdcall GetGroupNumber2() {
	return 571227;
}

wchar_t* __stdcall GetStudentName2() {
	return studentName;
}
