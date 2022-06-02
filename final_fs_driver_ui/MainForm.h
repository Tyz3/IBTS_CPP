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
#include "DAO.h"
#include "sqlite3.h"
#include "FileSystem.h"
#include "FSClusterIter.h"
#include "ReadThread.h"

//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree;
	TLabel *L_Debug;
	TEdit *E_DeviceFriendlyName;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TProgressBar *ProgressBar;
	TEdit *E_SearchSig;
	TLabel *Label4;
	TCheckBox *CB_NotEmptyClusters;
	TButton *B_Start;
	TButton *B_Stop;
	TButton *B_DeleteEntry;
	TButton *B_ClearAll;
	TLabel *Label5;
	TLabel *L_FSKeyWord;
	TMemo *M_Info;
	TLabel *Label6;
	TLabel *L_Id;
	TLabel *Label8;
	TLabel *L_ClusterCount;
	void __fastcall B_StartClick(TObject *Sender);
	void __fastcall VirtualStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall VirtualStringTreeAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node);
	void __fastcall B_StopClick(TObject *Sender);
	void __fastcall B_DeleteEntryClick(TObject *Sender);
	void __fastcall B_ClearAllClick(TObject *Sender);


private:	// User declarations
	class FileSystem* currentFS;
	class ReadThread* readThread;
	sqlite3* database;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

void __fastcall showFSInfo(TMemo* memo, FileSystem* fs);
void __fastcall printDebug(TLabel* label, int colorCode, UnicodeString msg);

typedef struct {
	unsigned long id;
	unsigned long cluster;
	UnicodeString content;
    int contentSize;
} StorageTableStruct;
//---------------------------------------------------------------------------
#endif
