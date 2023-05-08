//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <windows.h>
#include"sqlite3.h"
#include <string>
using namespace std;
typedef struct
{
	int id;
	UnicodeString url;
	UnicodeString title;
} TreeData;


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree1;
	TButton *WriteDataButton;
	TButton *ClearTableButton;
	TButton *DeleteLinesButton;
	TButton *ClearHistoryButton;
	TLabel *Label1;
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall WriteDataButtonClick(TObject *Sender);
	void __fastcall ClearTableButtonClick(TObject *Sender);
	void __fastcall ClearHistoryButtonClick(TObject *Sender);
	void __fastcall DeleteLinesButtonClick(TObject *Sender);
	void __fastcall VirtualStringTree1NodeClick(TBaseVirtualTree *Sender, const THitInfo &HitInfo);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	sqlite3 * DB;
	sqlite3_stmt * State;
	char * errmsg;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
