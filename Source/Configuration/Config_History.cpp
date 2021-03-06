//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Config_History.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Config_Frame"
#pragma resource "*.fmx"
THistoryFrame *HistoryFrame;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "PRF_HS"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
#define CLASS_ID									"HstMgr"
//---------------------------------------------------------------------------
#define SAFE_DELIMITER								'|'
#define SAFE_EQUALS									'='
#define DELIMITER_REPLACE							"&trail;"
#define EQUALS_REPLACE								"&equals;"
#define HISTORY_NODE_ID                             "History_"
//---------------------------------------------------------------------------
extern TSysLog *Logger;
//---------------------------------------------------------------------------
void DEBUG_CFGHS(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report(UNIT_ID,NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
void DEBUG_HMGR(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report(CLASS_ID,NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
THistoryManager::THistoryManager(TComponent *AOwner){
	History = new TList();
	Owner = AOwner;

}
//---------------------------------------------------------------------------
THistoryManager::~THistoryManager(){

}
//---------------------------------------------------------------------------
void THistoryManager::AddRecord(TDateTime Moment, TStringList *Operation){
	DEBUG_HMGR(INFO_DEBUG,"AddRecord()");
	History_Record *Op = (History_Record*)AllocMem(sizeof(History_Record));
	int a;
	Op->Moment = Moment;
	Op->Operation = new TStringList();
	Op->Operation->Delimiter = '|';
	Op->Operation->StrictDelimiter = true;
	if(Operation){
		Op->Operation->DelimitedText = Operation->DelimitedText;
	}
	History->Add(Op);
}
//---------------------------------------------------------------------------
int THistoryManager::GetNumRecord(){
	DEBUG_HMGR(INFO_DEBUG,"GetNumRecord()");
	return History->Count;
}
//---------------------------------------------------------------------------
History_Record *THistoryManager::GetRecord(int Index){
	DEBUG_HMGR(INFO_DEBUG,"GetRecord()");
	if(Index > -1 && Index < History->Count)
		return (History_Record*)History->Items[Index];
	return NULL;
}
//---------------------------------------------------------------------------
void THistoryManager::DeleteRecord(int Index){
	DEBUG_HMGR(INFO_DEBUG,"GetRecord()");
	if(Index > -1 && Index < History->Count){
		History_Record *Tmp = GetRecord(Index);
		if(Tmp){
			Tmp->Operation->Clear();
		}
		History->Delete(Index);
	}
}
//---------------------------------------------------------------------------
void THistoryManager::SaveToXML(String File){
	int a;
	_di_IXMLNode Node;
	History_Record *Record;
	DEBUG_HMGR(INFO_DEBUG,"SaveToXML() -> "+File);
	TXMLDocument *Doc = new TXMLDocument(Owner);
	Doc->DOMVendor = GetDOMVendor("ADOM XML v4");
	Doc->Active = true;
	Doc->Options = TXMLDocOptions()<<doNodeAutoIndent;
	Doc->DocumentElement = Doc->CreateNode("History",ntElement,"");
	Doc->DocumentElement->SetAttribute("Class_creator","THistoryManager");
	Doc->DocumentElement->SetAttribute("Info","THistoryManager class backup");
	for(a=0;a<History->Count;a++){
		Node = Doc->DocumentElement->AddChild(HISTORY_NODE_ID+IntToStr(a),-1);
		Record = GetRecord(a);
		Node->SetAttribute("Moment",Record->Moment.DateTimeString());
		Node->SetAttribute("Operation",Record->Operation->DelimitedText);
	}
	Doc->SaveToFile(File);
}
//---------------------------------------------------------------------------
void THistoryManager::LoadFromXML(String File){
	DEBUG_HMGR(INFO_DEBUG,"LoadFromXML() -> "+File);
	TXMLDocument *Doc = new TXMLDocument(Owner);
	IXMLNode *Node;
	String Txt, Tmp;
	TStringList *List = new TStringList();
	List->Delimiter = '|';
	List->StrictDelimiter = true;

	int a;
	if(FileExists(File) == true){
		Doc->LoadFromFile(File);
		Doc->DOMVendor = GetDOMVendor("ADOM XML v4");
		Doc->Active=true;
		if(Doc->DocumentElement->NodeName == "History"){
			Txt = Doc->DocumentElement->GetAttribute("Class_creator");
			if(Txt == "THistoryManager"){
				Reset();
				for(a=0;a<Doc->DocumentElement->ChildNodes->Count;a++){
					Node = Doc->DocumentElement->ChildNodes->Get(a);
					Txt = Node->NodeName;
					if(Txt.Pos(HISTORY_NODE_ID) == 1){
						Txt = Node->GetAttribute("Moment");
						Tmp = Node->GetAttribute("Operation");
						List->DelimitedText = Tmp;
						if(List->Count > 0)
							AddRecord(StrToDateTime(Txt),List);
					}
				}
			}
		}
	}
	else
		DEBUG_HMGR(ERR_DEBUG,"File not exists");
}
//---------------------------------------------------------------------------
void THistoryManager::AddOperation(int Index, String Src, String Dest){
	History_Record *Record = GetRecord(Index);
	DEBUG_HMGR(INFO_DEBUG,"AddOperation()");
	if(Record != NULL){
		String a, b;
		a = SafeEncode(Src);
		b = SafeEncode(Dest);
		Record->Operation->AddPair(a, b);
	}
}
//---------------------------------------------------------------------------
void THistoryManager::CreateRecord(){
	DEBUG_HMGR(INFO_DEBUG,"CreateRecord()");
	AddRecord(Now(),NULL);
}
//---------------------------------------------------------------------------
String THistoryManager::SafeEncode(String Src){
	String Out = Src;
	Out = ReplaceStr(Out,(String)SAFE_DELIMITER,DELIMITER_REPLACE);
	Out = ReplaceStr(Out,(String)SAFE_EQUALS,EQUALS_REPLACE);
	return Out;
}
//---------------------------------------------------------------------------
String THistoryManager::SafeDecode(String Src){
	String Out = Src;
	Out = ReplaceStr(Out,(String)DELIMITER_REPLACE,SAFE_DELIMITER);
	Out = ReplaceStr(Out,(String)EQUALS_REPLACE,SAFE_EQUALS);
	return Out;
}
//---------------------------------------------------------------------------
int THistoryManager::GetNumOperation(int RecordIndex){
	History_Record *Record = GetRecord(RecordIndex);
	if(Record != NULL)
		return Record->Operation->Count;
	return -1;
}
//---------------------------------------------------------------------------
String THistoryManager::GetOperationSource(int RecordIndex, int OperationIndex){
	History_Record *Record = GetRecord(RecordIndex);
	if(Record != NULL){
		if(OperationIndex > -1 && OperationIndex<Record->Operation->Count){
			return Record->Operation->Names[OperationIndex];
		}
	}
	return "";
}
//---------------------------------------------------------------------------
String THistoryManager::GetOperationDest(int RecordIndex, int OperationIndex){
	History_Record *Record = GetRecord(RecordIndex);
	if(Record != NULL){
		if(OperationIndex > -1 && OperationIndex<Record->Operation->Count){
			return Record->Operation->ValueFromIndex[OperationIndex];
		}
	}
	return "";
}
//---------------------------------------------------------------------------
void THistoryManager::Reset(){
	int a;
	DEBUG_HMGR(INFO_DEBUG,"Reset()");
	for(a=0;a<GetNumRecord();a++)
		DeleteRecord(a);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall THistoryFrame::THistoryFrame(TComponent* Owner)
	: TConfig_Frame(Owner)
{
	History = new THistoryManager(this);
	GridDataList = new TList();
}
//---------------------------------------------------------------------------
void __fastcall THistoryFrame::HistoryTreeViewChange(TObject *Sender)
{
	if(HistoryTreeView->Selected){
		RestoreButton->Enabled = true;
		RemoveButton->Enabled = true;
		SetGrid(HistoryTreeView->Selected->Tag);
	}
	else{
		RestoreButton->Enabled = false;
		RemoveButton->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void THistoryFrame::SetGrid(int Record){
	GridDataList->Clear();
	int a;
	GridData *Info;
	HistoryGrid->RowCount = History->GetNumOperation(Record);
	for(a=0;a< History->GetNumOperation(Record);a++){
		Info = (GridData*)AllocMem(sizeof(GridData));
		Info->Checked = true;
		Info->Src = History->GetOperationSource(Record, a);
		Info->Dest = History->GetOperationDest(Record, a);
		GridDataList->Add(Info);
		SelectColumn->UpdateCell(a);
		SourceColumn->UpdateCell(a);
		DestColumn->UpdateCell(a);
	}
}
//---------------------------------------------------------------------------
void __fastcall THistoryFrame::HistoryGridGetValue(TObject *Sender, const int ACol, const int ARow,
		  TValue &Value)
{
	if(ARow < GridDataList->Count){
		GridData *Info;
		Info = (GridData*)GridDataList->Items[ARow];
		switch(ACol){
			case 0:{
				Value = Info->Checked;
			}break;
			case 1:{
				Value = Info->Src;
			}break;
			case 2:{
				Value = Info->Dest;
			}break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall THistoryFrame::HistoryGridSetValue(TObject *Sender, const int ACol,
		  const int ARow, const TValue &Value)
{
	if(ARow < GridDataList->Count){
		GridData *Info;
		Info = (GridData*)GridDataList->Items[ARow];
		switch(ACol){
			case 0:{
				TValue a = Value;
				Info->Checked = a.AsBoolean();
			}break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall THistoryFrame::HistoryGridHeaderClick(TColumn *Column)
{
	if(Column->ClassName() == "TCheckColumn"){
		GridData *Info;
		int a;
		bool Val;
		if(Column->Tag == 1){
			Val = true;
			Column->Tag = 0;
		}
		else{
			Val = false;
			Column->Tag = 1;
		}
		for(a=0;a<GridDataList->Count;a++){
			Info = (GridData*)GridDataList->Items[a];
			Info->Checked = Val;
			SelectColumn->UpdateCell(a);
		}
	}
}
//---------------------------------------------------------------------------
void THistoryFrame::CreateGUITxt(TNameValue *GUITxt){
	DEBUG_CFGHS(INFO_DEBUG,"CreateGUITxt()");
	GUITxt->AddString(BUILD_ID("HistoryBox"),"Operations","Group box of operation");
	GUITxt->AddString(BUILD_ID("Op_TreeItem_Text"),"Operations executed: ","Number of operation");
	GUITxt->AddString(BUILD_ID("SourceColumn"),"Source file","Source column header");
	GUITxt->AddString(BUILD_ID("DestColumn"),"Destination file","Destination column header");
	GUITxt->AddString(BUILD_ID("SelectDirTitle"),"Select a directory...","Title showed in dialog for directory choose");
	GUITxt->AddString(BUILD_ID("RestoreButton"),"Restore selected","Title showed in restore button");
	GUITxt->AddString(BUILD_ID("RemoveDlg"),"Remove data of ","Title showed in restore button");
	GUITxt->AddString(BUILD_ID("RemoveButton"),"Remove selected","Title showed in restore button");
	GUITxt->AddString(BUILD_ID("RemoveRecordCheck"),"Remove record older than ","Title showed in restore button");
	GUITxt->AddString(BUILD_ID("DayLabel"),"days","Title showed in restore button");
	GUITxt->AddString(BUILD_ID("OptionBox"),"Options","Title showed in restore button");
//RemoveRecordCheck
	if(GUITxt->ValueExist(BUILD_ID("TreeNode")) == false)
		GUITxt->AddString(BUILD_ID("TreeNode"),"Operation history","History of renamed files");
}
//---------------------------------------------------------------------------
void THistoryFrame::ApplyLanguage(TNameValue *Src){
	DEBUG_CFGHS(INFO_DEBUG,"ApplyLanguage()");
	TStringList *Cmp = new TStringList();
	Cmp->Add("HistoryBox");
	Cmp->Add("SourceColumn");
	Cmp->Add("DestColumn");
	Cmp->Add("RestoreButton");
	Cmp->Add("RemoveButton");
	Cmp->Add("RemoveRecordCheck");
	Cmp->Add("DayLabel");
	Cmp->Add("OptionBox");

	TConfig_Frame::ApplyLanguage(Src, UNIT_ID, Cmp);
	if(TreeNode)
		TreeNode->Text = Src->GetString(BUILD_ID("TreeNode"));
	Op_TreeItem_Text = Src->GetString(BUILD_ID("Op_TreeItem_Text"));
}
//---------------------------------------------------------------------------
void THistoryFrame::ResizeComponents(){
	DEBUG_CFGHS(INFO_DEBUG,"ResizeComponents()");
	RemoveRecordCheck->Width = RemoveRecordCheck->Canvas->TextWidth(RemoveRecordCheck->Text)+20;
}
//---------------------------------------------------------------------------
void THistoryFrame::LoadConfiguration(TNameValue *Conf){
	TConfig_Frame::LoadConfiguration(Conf);
	DEBUG_CFGHS(INFO_DEBUG,"LoadConfiguration()");
	RemoveRecordCheck->IsChecked = Conf->GetBool("DeleteHistory");
	DayDelete->Value = Conf->GetInt("MaxHistory");
	DayDelete->Enabled = RemoveRecordCheck->IsChecked;
}
//---------------------------------------------------------------------------
void THistoryFrame::SaveConfiguration(TNameValue *Conf){
	DEBUG_CFGHS(INFO_DEBUG,"SaveConfiguration()");
	Conf->SetBool("DeleteHistory", RemoveRecordCheck->IsChecked);
	Conf->SetInt("MaxHistory", DayDelete->Value);
}
//---------------------------------------------------------------------------
void THistoryFrame::PopulateTree(TTreeView *Tree){
	int a;
	TTreeViewItem *Item, *SubItem;
	History_Record *Record;
	HistoryTreeView->Clear();
	int Life = Config->GetInt("MaxHistory");
	bool CheckLife = Config->GetBool("DeleteHistory");
	//for(a=0;a<History->GetNumRecord();a++){
	for(a=History->GetNumRecord()-1;a>-1;a--){
		Record = History->GetRecord(a);
		if(CheckLife){
			if(DaySpan(Now(),Record->Moment)>Life){
				History->DeleteRecord(a);
                Record = NULL;
			}
		}
		if(Record){
			Item = new TTreeViewItem(HistoryTreeView);
			Item->Parent = HistoryTreeView;
			Item->Text = Record->Moment.DateTimeString();
			Item->TagObject = (TObject*)Record;
			Item->Tag = a;
			SubItem = new TTreeViewItem(Item);
			SubItem->Parent = Item;
			SubItem->Text = Op_TreeItem_Text +IntToStr(Record->Operation->Count);
			SubItem->TagObject = (TObject*)Record;
			SubItem->Tag = a;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall THistoryFrame::RestoreButtonClick(TObject *Sender)
{
	DEBUG_CFGHS(INFO_DEBUG,"RestoreSelected()");
	String Dir;
	String StartDir;
	String Title;
	String File;
	bool Res;
	Config == NULL?StartDir = "":StartDir = Config->GetString("StartSearchDir");
	Language == NULL?Title = "":Title = Language->GetString(BUILD_ID("SelectDirTitle"));
	if(Dialogs::SelectDirectory(Title, StartDir, Dir)){
		GridData *Info;
		int a;
		DEBUG_CFGHS(TOTAL_DEBUG,"Restoring file: work in directory "+QUOTE_STRING(Dir));
		for(a=0;a<GridDataList->Count;a++){
			Info = (GridData*)GridDataList->Items[a];
			File = Dir+"\\"+Info->Dest;
			if(FileExists(File)){
				Res = RenameFile(File,Dir+"\\"+Info->Src);
				if(Res)
					DEBUG_CFGHS(TOTAL_DEBUG,"Restored "+QUOTE_STRING(Info->Dest)+(String)" to "+QUOTE_STRING(Info->Src));
				else
					DEBUG_CFGHS(ERR_DEBUG,"Error renaming "+QUOTE_STRING(Info->Dest));
			}
			else
				DEBUG_CFGHS(WARN_DEBUG,"File "+QUOTE_STRING(Info->Dest)+(String)" not exists");
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall THistoryFrame::RemoveButtonClick(TObject *Sender)
{
	TTreeViewItem *Item = HistoryTreeView->Selected;
	if(Item){
		History_Record *Record = History->GetRecord(Item->Tag);
		String Msg = Language->GetString(BUILD_ID("RemoveDlg"))+Record->Moment.DateTimeString()+(String)"?";
//		int Res =  TDialogServiceSync::MessageDialog(Msg,TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),THelpContext());
		int Res = MyShowDialog("",Msg,TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),Language);
		if(Res == mrYes){
			History->DeleteRecord(Item->Tag);
			PopulateTree(NULL);
			HistoryGrid->RowCount = 0;
		}
	}
}
//---------------------------------------------------------------------------
void THistoryFrame::CreateConfiguration(TNameValue *Conf){
	TConfig_Frame::CreateConfiguration(Conf);
	Conf->AddBool("DeleteHistory",false,"Decide if delete history after some days...");
	Conf->AddInt("MaxHistory",5,"Days after which history will be deleted");
}
//---------------------------------------------------------------------------
void __fastcall THistoryFrame::RemoveRecordCheckChange(TObject *Sender)
{
	DayDelete->Enabled = RemoveRecordCheck->IsChecked;
}
//---------------------------------------------------------------------------


