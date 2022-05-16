//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree;
	TLabel *L_Debug;
	TEdit *E_DeviceFriendlyName;
	TLabel *Label1;
	TLabel *Label2;
	TRadioButton *RB_NTFS;
	TLabel *Label3;
	TRadioButton *RB_FAT32;
	TRadioButton *RB_exFAT;
	TProgressBar *ProgressBar;
	TEdit *E_SearchSig;
	TLabel *Label4;
	TCheckBox *CB_NotEmptyClasters;
	TButton *B_Start;
	TButton *B_Stop;
	TButton *B_DeleteEntry;
	TButton *Button1;
	TLabel *Label5;
	void __fastcall B_StartClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall printDebug(int colorCode, UnicodeString msg);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

//---------------------------------------------------------------------------
#endif
