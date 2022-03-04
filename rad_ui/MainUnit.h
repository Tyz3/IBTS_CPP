//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *rad_gn_btn;
	TButton *rad_sn_btn;
	TLabel *rad_gn_label;
	TLabel *rad_sn_label;
	TButton *vs_gn_btn;
	TButton *vs_sn_btn;
	TLabel *vs_gn_label;
	TLabel *vs_sn_label;
	TLabel *rad_head_label;
	TLabel *vs_head_label;
	void __fastcall vs_gn_btnClick(TObject *Sender);
	void __fastcall vs_sn_btnClick(TObject *Sender);
	void __fastcall rad_gn_btnClick(TObject *Sender);
	void __fastcall rad_sn_btnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif


// Visual Studio Dll
typedef int (__stdcall * PGetGroupNumber) (void);
typedef wchar_t* (__stdcall * PGetStudentName) (void);

// RAD Studio Dll
typedef int (__stdcall * PGetGroupNumber2) (void);
typedef wchar_t* (__stdcall * PGetStudentName2) (void);
