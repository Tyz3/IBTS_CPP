//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *StartReadBtn;
	TLabel *DebugLabel;
	TEdit *ChooseDeviceEdit;
	TMemo *LogsMemo;
	TButton *StopReadBtn;
	TLabel *Label1;
	void __fastcall StartReadBtnClick(TObject *Sender);
	void __fastcall StopReadBtnClick(TObject *Sender);
private:	// User declarations
	class ReadThread* readThread;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

void printDebug(int colorCode, UnicodeString msg);
//---------------------------------------------------------------------------
#endif
