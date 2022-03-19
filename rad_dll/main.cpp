#include "rad_dllPCH1.h"

extern "C" int __stdcall GetGroupNumber2() {
	return 571227;
}

extern "C" void __stdcall GetStudentName2(wchar_t* studentName2) {
	wcscpy(studentName2, L"Ульянихин Евгений Ильич");
}
