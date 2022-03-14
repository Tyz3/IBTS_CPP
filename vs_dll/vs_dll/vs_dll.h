#pragma once

#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

extern "C" LIBRARY_API int __stdcall GetGroupNumber();
extern "C" LIBRARY_API void __stdcall GetStudentName(wchar_t* studentName);