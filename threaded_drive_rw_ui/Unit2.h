//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class ReadThread : public TThread
{
private:
	class ProcessThread* processThread;
	TEvent* myEvent;
	int messageStatus;
protected:
	void __fastcall Execute();
	void __fastcall printStatus();
public:
	__fastcall ReadThread(bool CreateSuspended, wchar_t deviceLiteral);

	char dataBuffer[4096];
	DWORD bytesToRead;
	wchar_t deviceLiteral;
};
//---------------------------------------------------------------------------
#endif
