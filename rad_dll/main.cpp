#include "rad_dllPCH1.h"

static wchar_t studentName[] = L"Ульянихин Евгений";

extern "C" int __stdcall GetGroupNumber2() {
	return 571227;
}

extern "C" wchar_t* __stdcall GetStudentName2() {
	return studentName;
}
