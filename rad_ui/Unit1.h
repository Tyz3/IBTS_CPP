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
	TLabel *rad_gn_label;
	TLabel *rad_sn_label;
	TLabel *vs_gn_label;
	TLabel *vs_sn_label;
	TLabel *rad_head_label;
	TLabel *vs_head_label;
	TButton *rad_gn_btn;
	TButton *rad_sn_btn;
	TButton *vs_gn_btn;
	TButton *vs_sn_btn;
	void __fastcall rad_gn_btnClick(TObject *Sender);
	void __fastcall rad_sn_btnClick(TObject *Sender);
	void __fastcall vs_gn_btnClick(TObject *Sender);
	void __fastcall vs_sn_btnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

#include <stdio.h>
#include <wchar.h>

// Visual Studio Dll
typedef int (__stdcall * PGetGroupNumber) (void);
typedef void (__stdcall * PGetStudentName) (wchar_t *);

// RAD Studio Dll
typedef int (__stdcall * PGetGroupNumber2) (void);
typedef void (__stdcall * PGetStudentName2) (wchar_t *);

