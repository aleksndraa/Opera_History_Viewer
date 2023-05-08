//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

 VirtualStringTree1->NodeDataSize = sizeof(TreeData);
char * path = getenv("APPDATA");
std::string Path = path;
Path+="\\Opera Software\\Opera Stable\\History";
sqlite3_open(Path.c_str(),&DB);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
TreeData* treeData = (TreeData*)Sender->GetNodeData(Node);
	switch (Column) {
        case 0:
			CellText = treeData->id;
			break;
		case 1:
			CellText = treeData->url;
			break;
		case 2:
			CellText = treeData->title;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WriteDataButtonClick(TObject *Sender)
{
sqlite3_prepare_v2(DB,"select * from urls;",-1,&State,NULL);
VirtualStringTree1->Clear();
VirtualStringTree1->BeginUpdate();
 while(1)
 {
 int result = sqlite3_step(State);
 if (result!=SQLITE_ROW) break;
 PVirtualNode Node = VirtualStringTree1->AddChild(NULL);
 TreeData* treeData = (TreeData*)VirtualStringTree1->GetNodeData(Node);
	  treeData->id = sqlite3_column_int(State,0);
		treeData->url = (char*)(sqlite3_column_text(State,1));
		treeData->title = (WCHAR*)(sqlite3_column_text16(State,2));
 }


VirtualStringTree1->EndUpdate();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClearTableButtonClick(TObject *Sender)
{
VirtualStringTree1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClearHistoryButtonClick(TObject *Sender)
{
int result = sqlite3_exec(DB,"delete from urls;",NULL,NULL,&errmsg);
VirtualStringTree1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DeleteLinesButtonClick(TObject *Sender)
{
VirtualStringTree1->BeginUpdate();

PVirtualNode Node = VirtualStringTree1->GetFirstSelected();
for(int i=0;i<VirtualStringTree1->SelectedCount	;++i)
{
TreeData * treeData =(TreeData*)VirtualStringTree1->GetNodeData(Node);
std::string sql = "delete from urls where id =" + std::to_string(treeData->id) + ";";
sqlite3_exec(DB,sql.c_str(),NULL,NULL,&errmsg);
Node = VirtualStringTree1->GetNextSelected(Node);
}
VirtualStringTree1->DeleteSelectedNodes();

VirtualStringTree1->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1NodeClick(TBaseVirtualTree *Sender, const THitInfo &HitInfo)

{
auto node = Sender->GetFirstSelected();
	TreeData * treeData = (TreeData*)Sender->GetNodeData(node);
	std::string sql = "SELECT datetime((last_visit_time/1000000)-11644473600,'unixepoch','localtime') AS time FROM urls where id ="+ std::to_string(treeData->id) + ";";
	auto result = sqlite3_prepare_v2(DB,sql.c_str(),-1,&State,NULL);
	result = sqlite3_step(State);
	std::string s = (char*)sqlite3_column_text(State,0);
	s = "Дата и время последнего визита: "+s;
	Label1->Caption=s.c_str();
}
//---------------------------------------------------------------------------

