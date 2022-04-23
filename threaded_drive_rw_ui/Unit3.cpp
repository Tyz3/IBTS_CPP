//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall ProcessThread::ProcessThread(bool CreateSuspended, TEvent* myEvent, char (&dataBufferPtr)[4096])
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	this->myEvent = myEvent;
	this->dataBufferPtr = dataBufferPtr;
}
//---------------------------------------------------------------------------
void __fastcall ProcessThread::Execute()
{
    // ��������� ������
	while (1) {
		if (Terminated) {
			messageStatus = 0; Synchronize(&printStatus);
			break;
		}

		if (myEvent->WaitFor(0) == wrSignaled) {
			messageStatus = 1; Synchronize(&printStatus);

			// TODO ����������� ������ � ����

			// ������� ������
			// ������� ������ ReadThread � ���, ��� ������ ����������
			myEvent->ResetEvent();

			// ��������� ������������� ������
			Sleep(3000);
		}

		Sleep(20);
	}

	// �������� ������ ���������
	Form1->StartReadBtn->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall ProcessThread::printStatus()
{
	switch (messageStatus) {
	case 0:
		printDebug(9, u"|||| ProcessThread Terminated...");
		break;
	case 1:
		printDebug(9, u"| - ProcessThread Processing...");
		break;
	}
}