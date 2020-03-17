//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Config_NameManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Config_Frame"
#pragma resource "*.fmx"
TNameManagerFrame *NameManagerFrame;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "CFG_NM"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
extern TSysLog *Logger;
//---------------------------------------------------------------------------
void DEBUG_CFGNM(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report(UNIT_ID,NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
__fastcall TNameManagerFrame::TNameManagerFrame(TComponent* Owner)
	: TConfig_Frame(Owner)
{
	IgnoreText = new TStringList();
	IgnoreGrid->RowCount = 0;
	IgnoreTextCaseColumn->Width = 100;
    IgnoreGrid->ReadOnly = false;
	
	IgnoreTextEnableColumn->Tag = IgnoreTextEnableColumn->Width;
	IgnoreTextCaseColumn->Tag = IgnoreTextCaseColumn->Width;
	IgnoreTextEnableColumn->OnResize = GenericColumnResize;
	IgnoreTextEnableColumn->OnResize = GenericColumnResize;
}
//---------------------------------------------------------------------------
void TNameManagerFrame::CreateGUITxt(TNameValue *GUITxt){
	DEBUG_CFGNM(INFO_DEBUG,"CreateGUITxt()");
	GUITxt->AddString(BUILD_ID("ParenthesysGroupBox"),"Text to remove","Text for parenthesys group box");
	GUITxt->AddString(BUILD_ID("IgnoreParenthesys"),"Ignore parenthesys","Text for parenthesys group box");
	GUITxt->AddString(BUILD_ID("IgnoreSquare"),"Ignore square brackets","Text for parenthesys group box");
	GUITxt->AddString(BUILD_ID("IgnoreCurly"),"Ignore curly brackets","Text for parenthesys group box");
	GUITxt->AddString(BUILD_ID("IgnoreAfterParenthesys"),"Ignore text after parenthesys/brackets","Text for parenthesys group box");
	GUITxt->AddString(BUILD_ID("AcceptedExtensionGroupBox"),"Accepted extension","Text for extension group box");
	GUITxt->AddString(BUILD_ID("AcceptedExtensionCheckBox"),"Accept only below extension","Text for extension group box");
	GUITxt->AddString(BUILD_ID("IgnoreTextGroupBox"),"Text to ignore","Text to ignore in file name");
	GUITxt->AddString(BUILD_ID("IgnoreTextColumn"),"Text to ignore","Text to ignore column header");
	GUITxt->AddString(BUILD_ID("IgnoreTextEnableColumn"),"Enabled","Text to ignore enabled column header");
	GUITxt->AddString(BUILD_ID("IgnoreTextCaseColumn"),"Ignore case","Text to ignore case column header");
	GUITxt->AddString(BUILD_ID("IgnoreTextRemoveDlg"),"Remove line ","Text show in remove line dialog");
	GUITxt->AddString(BUILD_ID("IgnoreTextRemoveMsg"),"Remove ","Text show in remove line dialog");
	GUITxt->AddString(BUILD_ID("RemoveAfterSeparator"),"Remove text after separator","Text show in remove separtor box");
	GUITxt->AddString(BUILD_ID("OkButton"),"Add row","Text show in add row button");
	GUITxt->AddString(BUILD_ID("RemoveButton"),"Remove row","Text show in add row button");
	GUITxt->AddString(BUILD_ID("TreeNode"),"File name settings","Text for file name settings item");
}
//---------------------------------------------------------------------------
void TNameManagerFrame::ApplyLanguage(TNameValue *Src){
	DEBUG_CFGNM(INFO_DEBUG,"ApplyLanguage()");
	TStringList *Cmp = new TStringList();
	Cmp->Add("ParenthesysGroupBox");
	Cmp->Add("IgnoreParenthesys");
	Cmp->Add("IgnoreSquare");
	Cmp->Add("IgnoreCurly");
	Cmp->Add("IgnoreAfterParenthesys");
	Cmp->Add("AcceptedExtensionGroupBox");
	Cmp->Add("AcceptedExtensionCheckBox");
	Cmp->Add("IgnoreTextGroupBox");
	Cmp->Add("IgnoreTextColumn");
	Cmp->Add("IgnoreTextEnableColumn");
	Cmp->Add("IgnoreTextCaseColumn");
	Cmp->Add("IgnoreTextRemoveDlg");
	Cmp->Add("OkButton");
	Cmp->Add("RemoveButton");
	Cmp->Add("RemoveAfterSeparator");

	TConfig_Frame::ApplyLanguage(Src, UNIT_ID, Cmp);
	if(TreeNode)
		TreeNode->Text = Src->GetString(BUILD_ID("TreeNode"));
	RemoveLineMsg = Src->GetString(BUILD_ID("IgnoreTextRemoveMsg"));
}
//---------------------------------------------------------------------------
void TNameManagerFrame::ResizeComponents(){
	DEBUG_CFGNM(INFO_DEBUG,"ResizeComponents()");
	IgnoreParenthesys->Width = IgnoreParenthesys->Canvas->TextWidth(IgnoreParenthesys->Text)+25;
	IgnoreSquare->Width = IgnoreSquare->Canvas->TextWidth(IgnoreSquare->Text)+25;
	IgnoreCurly->Width = IgnoreCurly->Canvas->TextWidth(IgnoreCurly->Text)+25;
	IgnoreAfterParenthesys->Width = IgnoreAfterParenthesys->Canvas->TextWidth(IgnoreAfterParenthesys->Text)+25;
	RemoveAfterSeparator->Width = RemoveAfterSeparator->Canvas->TextWidth(RemoveAfterSeparator->Text)+25;
}
//---------------------------------------------------------------------------
void TNameManagerFrame::LoadConfiguration(TNameValue *Conf){
	TConfig_Frame::LoadConfiguration(Conf);
	DEBUG_CFGNM(INFO_DEBUG,"LoadConfiguration()");

	IgnoreParenthesys->IsChecked = Conf->GetBool("IgnoreParenthesys");
	IgnoreSquare->IsChecked = Conf->GetBool("IgnoreSquareBrackets");
	IgnoreCurly->IsChecked = Conf->GetBool("IgnoreCurlyBrackets");
	IgnoreAfterParenthesys->IsChecked = Conf->GetBool("IgnoreTextAfterParenthesys");
	AcceptedExtensionCheckBox->IsChecked = Conf->GetBool("AcceptOnlyExtension");
	AcceptedExtensionEdit->Text = Conf->GetString("AcceptedExtension");
	AcceptedExtensionEdit->Enabled = AcceptedExtensionCheckBox->IsChecked;
	RemoveAfterSeparator->IsChecked = Conf->GetBool("RemoveAfterSeparator");
	if(Translator){
		int Count;
		int a;
        String Txt;
		Count = Translator->GetNumReplaceItems();
		for(a=IgnoreGrid->RowCount - 1;a>-1;a--){
			RemoveLineFromGrid(a);
		}
		if(Count > 1){
			IgnoreGrid->RowCount = Count-1;
			for(a = 1;a<Count;a++){
				Txt = Translator->ReplaceItem[a];
				AddLineToGrid(Txt,Translator->ReplaceItemActive[Txt],Translator->ReplaceItemIgnoreCase[Txt]);
			}
		}
	}
}
//---------------------------------------------------------------------------
void TNameManagerFrame::CreateConfiguration(TNameValue *Conf){
	TConfig_Frame::CreateConfiguration(Conf);
	DEBUG_CFGNM(INFO_DEBUG,"CreateConfiguration()");
	String Txt;
	TNameTranslator *Tr;
	if(Translator)
		Tr = Translator;
	else
		Tr = new TNameTranslator(this);
	Tr->AddToIgnoreList("x264");
	Tr->AddToIgnoreList("x265");
	Tr->AddToIgnoreList("h264");
	Tr->AddToIgnoreList("h265");
	Tr->AddToIgnoreList("HDTV");
	Tr->AddToIgnoreList("720p");
	Tr->AddToIgnoreList("1080p");
	Txt = Tr->ExportIgnoreList();
	Conf->AddBool("IgnoreParenthesys",true,"Ignore text beetween parenthesys");
	Conf->AddBool("IgnoreSquareBrackets",true,"Ignore text beetween square brackets");
	Conf->AddBool("IgnoreCurlyBrackets",true,"Ignore text beetween curly brackets");
	Conf->AddBool("IgnoreTextAfterParenthesys",false,"Ignore text after parenthesys/brackets");
	Conf->AddBool("RemoveAfterSeparator",true,"Remove text after separator");
	Conf->AddBool("AcceptOnlyExtension",false,"Accept only files with correct extension");
	Conf->AddString("AcceptedExtension","mkv,mov,mp4","Accepted extension");
	Conf->AddString("IgnoreList",Txt,"Word to ignore in file analysis");
	if(Translator){
		Translator->IgnoreParenthesys = true;
		Translator->IgnoreSquareBrackets = true;
		Translator->IgnoreCurlyBrackets = true;
		Translator->RemoveTextAfterParenthesys = true;
	}
}
//---------------------------------------------------------------------------
void TNameManagerFrame::SetTranslator(TNameTranslator *Tr){
	DEBUG_CFGNM(INFO_DEBUG,"SetTranslator()");
	FTranslator = Tr;
}
//---------------------------------------------------------------------------
TNameTranslator *TNameManagerFrame::GetTranslator(){
	return FTranslator;
}
//---------------------------------------------------------------------------
void __fastcall TNameManagerFrame::AcceptedExtensionCheckBoxChange(TObject *Sender)
{
	DEBUG_CFGNM(INFO_DEBUG,"AcceptedExtensionCheckBoxChange()");
	AcceptedExtensionEdit->Enabled = !AcceptedExtensionEdit->Enabled;
}
//---------------------------------------------------------------------------
void TNameManagerFrame::RemoveLineFromGrid(int Index){
	DEBUG_CFGNM(INFO_DEBUG,"RemoveLineFromGrid()");
	if(Index > -1){
		if(Index <IgnoreGrid->RowCount){
			IgnoreText->Delete(Index);
			IgnoreGrid->RowCount--;
			UpdateIgnoreGrid();
		}
	}
}
//---------------------------------------------------------------------------
void TNameManagerFrame::AddLineToGrid(String Text, bool Enabled, bool IgnoreCase){
	DEBUG_CFGNM(INFO_DEBUG,"AddLineToGrid()");
	int *Value;
	Value = (int*)AllocMem(sizeof(int));
	*Value = Enabled + (IgnoreCase) * 2;
	IgnoreText->AddObject(Text,(TObject*)Value);
	UpdateIgnoreGrid();
}
//---------------------------------------------------------------------------
void TNameManagerFrame::UpdateIgnoreGrid(){
	DEBUG_CFGNM(INFO_DEBUG,"UpdateIgnoreGrid()");
	for(int a=0;a<IgnoreGrid->RowCount;a++){
		for(int b=0;b<IgnoreGrid->ColumnCount;b++){
			IgnoreGrid->Columns[b]->UpdateCell(a);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TNameManagerFrame::IgnoreGridGetValue(TObject *Sender, const int ACol,
          const int ARow, TValue &Value)
{
	int *Obj;
	if(ARow > -1){
		if(ARow < IgnoreText->Count){
			switch(ACol){
				case 0:{
					Value = IgnoreText->Strings[ARow];
				}break;
				case 1:{
					Obj = (int*)IgnoreText->Objects[ARow];
					Value = (*Obj & 1)?true:false;
				}break;
				case 2:{
					Obj = (int*)IgnoreText->Objects[ARow];
					Value = (*Obj & 2)?true:false;
				}break;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TNameManagerFrame::OkButtonClick(TObject *Sender)
{
	DEBUG_CFGNM(INFO_DEBUG,"OkButtonClick()");
	IgnoreGrid->RowCount++;
	AddLineToGrid("Text_"+IntToStr(IgnoreGrid->RowCount),true,true);
}
//---------------------------------------------------------------------------
void __fastcall TNameManagerFrame::RemoveButtonClick(TObject *Sender)
{
	DEBUG_CFGNM(INFO_DEBUG,"RemoveButtonClick()");
	int Res = MyShowDialog("",RemoveLineMsg+IgnoreText->Strings[IgnoreGrid->Selected]+(String)"?",
						TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),Language);
	//int Res = TDialogServiceSync::MessageDialog(RemoveLineMsg+IgnoreText->Strings[IgnoreGrid->Selected]+
	//				(String)"?",TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),THelpContext());
	if(Res == mrYes){
		RemoveLineFromGrid(IgnoreGrid->Selected);
	}
}
//---------------------------------------------------------------------------
void TNameManagerFrame::SaveConfiguration(TNameValue *Conf){
	DEBUG_CFGNM(INFO_DEBUG,"SaveConfiguration()");
    String Txt;
	Conf->SetBool("IgnoreParenthesys",IgnoreParenthesys->IsChecked);
	Conf->SetBool("IgnoreSquareBrackets",IgnoreSquare->IsChecked);
	Conf->SetBool("IgnoreCurlyBrackets",IgnoreCurly->IsChecked);
	Conf->SetBool("IgnoreTextAfterParenthesys",IgnoreAfterParenthesys->IsChecked);
	Conf->SetBool("RemoveAfterSeparator",RemoveAfterSeparator->IsChecked);
	Conf->SetBool("AcceptOnlyExtension",AcceptedExtensionCheckBox->IsChecked);
	Conf->SetString("AcceptedExtension",AcceptedExtensionEdit->Text);
	Txt = ExportIgnoreText();
	if(Translator){
		Translator->ImportIgnoreList(Txt);
		Translator->IgnoreParenthesys = IgnoreParenthesys->IsChecked;
		Translator->IgnoreSquareBrackets = IgnoreSquare->IsChecked;
		Translator->IgnoreCurlyBrackets = IgnoreCurly->IsChecked;
		Translator->RemoveTextAfterParenthesys = IgnoreAfterParenthesys->IsChecked;
	}
	Conf->SetString("IgnoreList",Txt);
}
//---------------------------------------------------------------------------
String TNameManagerFrame::ExportIgnoreText(){
	DEBUG_CFGNM(INFO_DEBUG,"ExportIgnoreText()");
	String Out = "";
	int *Obj;
	int Res;
	for(int a=0;a<IgnoreText->Count;a++){
		Obj = (int*)IgnoreText->Objects[a];
		Res = ((*Obj & 2)?1:0)+((*Obj & 1)?2:0);
		Out = Out+IgnoreText->Strings[a]+IntToStr(Res)+",";
	}
	if(Out.Length() > 0){
		if(RightStr(Out,1) == ",")
			Out = LeftStr(Out,Out.Length()-1);
	}
	return Out;
}
//---------------------------------------------------------------------------
void __fastcall TNameManagerFrame::IgnoreGridSetValue(TObject *Sender, const int ACol,
		  const int ARow, const TValue &Value)
{
	int *Obj;
	TValue a = Value;
	bool b;
	switch(ACol){
		case 0:{
			String Txt = a.AsString();
			IgnoreText->Strings[ARow] = Txt;
			IgnoreTextColumn->UpdateCell(ARow);
		}break;
		case 1:{
			b = a.AsBoolean();
			Obj = (int*)IgnoreText->Objects[ARow];
			*Obj = (*Obj & 2) + b;
		}break;
		case 2:{
			b = a.AsBoolean();
			Obj = (int*)IgnoreText->Objects[ARow];
			*Obj = (*Obj & 1) + (b?2:0);
		}break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TNameManagerFrame::GenericColumnResize(TObject *Sender)
{
	TColumn *Column = (TColumn*)Sender;
	if(Column)
		Column->Width = Column->Tag;
}
//---------------------------------------------------------------------------

