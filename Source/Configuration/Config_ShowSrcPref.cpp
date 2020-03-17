//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Config_ShowSrcPref.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Config_Frame"
#pragma resource "*.fmx"
TShowPrefFrame *ShowPrefFrame;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "PRF_FM"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
extern TSysLog *Logger;
//---------------------------------------------------------------------------
void DEBUG_CFGSP(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report(UNIT_ID,NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
__fastcall TShowPrefFrame::TShowPrefFrame(TComponent* Owner)
	: TConfig_Frame(Owner)
{
	InternalRemoveDlg ="Remove ";
}
//---------------------------------------------------------------------------
void TShowPrefFrame::CreateGUITxt(TNameValue *GUITxt){
	DEBUG_CFGSP(INFO_DEBUG,"CreateGUITxt()");
	if(GUITxt->ValueExist(BUILD_ID("GroupBox1")) == false)
		GUITxt->AddString(BUILD_ID("GroupBox1"),"TV Show preferences","Group box for TV Show");
	if(GUITxt->ValueExist(BUILD_ID("NamePrefColumn")) == false)
		GUITxt->AddString(BUILD_ID("NamePrefColumn"),"TV Show name","Title for show column");
	if(GUITxt->ValueExist(BUILD_ID("IDPrefColumn")) == false)
		GUITxt->AddString(BUILD_ID("IDPrefColumn"),"Show name ID","Title for show column");
	if(GUITxt->ValueExist(BUILD_ID("RemovePrefButton")) == false)
		GUITxt->AddString(BUILD_ID("RemovePrefButton"),"Remove","Title for show column");
	if(GUITxt->ValueExist(BUILD_ID("AddPrefButton")) == false)
		GUITxt->AddString(BUILD_ID("AddPrefButton"),"Add","Title for show column");
	if(GUITxt->ValueExist(BUILD_ID("RemoveDlg")) == false)
		GUITxt->AddString(BUILD_ID("RemoveDlg"),InternalRemoveDlg,"Title for remove dialog");
	if(GUITxt->ValueExist(BUILD_ID("TreeNode")) == false)
		GUITxt->AddString(BUILD_ID("TreeNode"),"Source preferences","Preferences on show name");
}
//---------------------------------------------------------------------------
void TShowPrefFrame::ApplyLanguage(TNameValue *Src){
	DEBUG_CFGSP(INFO_DEBUG,"ApplyLanguage()");
	TStringList *Cmp = new TStringList();
	Cmp->Add("GroupBox1");
	Cmp->Add("NamePrefColumn");
	Cmp->Add("IDPrefColumn");
	Cmp->Add("AddPrefButton");
	Cmp->Add("RemovePrefButton");

	TConfig_Frame::ApplyLanguage(Src, UNIT_ID, Cmp);
	if(TreeNode)
		TreeNode->Text = Src->GetString(BUILD_ID("TreeNode"));
	String Tmp = Src->GetString(BUILD_ID("RemoveDlg"));
	if(Tmp != "")
        InternalRemoveDlg = Tmp;
}
//---------------------------------------------------------------------------
void __fastcall TShowPrefFrame::AddPrefButtonClick(TObject *Sender)
{
	DEBUG_CFGSP(INFO_DEBUG,"AddPrefButtonClick()");
	if(WebSource){
		PreferencesGrid->RowCount++;
		PreferencesGrid->Cells[0][PreferencesGrid->RowCount-1]="ShowName "+IntToStr(PreferencesGrid->RowCount-1);
		PreferencesGrid->Cells[1][PreferencesGrid->RowCount-1]="ID "+IntToStr(PreferencesGrid->RowCount-1);
		WebSource->AddShowNamePref(PreferencesGrid->Cells[0][PreferencesGrid->RowCount-1],
									PreferencesGrid->Cells[1][PreferencesGrid->RowCount-1]);
	}
	else
		DEBUG_CFGSP(WARN_DEBUG,"Invalid WebSource");
}
//---------------------------------------------------------------------------
void TShowPrefFrame::UpdateGrid(){
	DEBUG_CFGSP(INFO_DEBUG,"UpdateGrid()");
	if(WebSource){
		int a;
		PreferencesGrid->RowCount = WebSource->GetNumShowNamePref();
		for(a=0;a<PreferencesGrid->RowCount;a++){
			PreferencesGrid->Cells[0][a]= WebSource->GetShowNamePrefNameByIndex(a);
			PreferencesGrid->Cells[1][a]=WebSource->GetShowNamePrefByIndex(a);
		}
	}
	else
		DEBUG_CFGSP(WARN_DEBUG,"Invalid WebSource");
}
//---------------------------------------------------------------------------
void __fastcall TShowPrefFrame::RemovePrefButtonClick(TObject *Sender)
{
	DEBUG_CFGSP(INFO_DEBUG,"RemovePrefButtonClick()");
	if(PreferencesGrid->Selected>-1){
		//String
		//int Result = TDialogServiceSync::MessageDialog(InternalRemoveDlg+PreferencesGrid->Cells[0][PreferencesGrid->Selected]+
		//				(String)"?",TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),THelpContext());
		int Result = MyShowDialog("",InternalRemoveDlg+PreferencesGrid->Cells[0][PreferencesGrid->Selected]+(String)"?",
						TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),Language);
		if(Result == mrYes){
			if(WebSource){
				WebSource->RemoveShowNamePref(PreferencesGrid->Cells[0][PreferencesGrid->Selected]);
				UpdateGrid();
			}
		}
	}
	else
		DEBUG_CFGSP(WARN_DEBUG,"Invalid grid selection");
}
//---------------------------------------------------------------------------
void TShowPrefFrame::ResizeComponents(){
	DEBUG_CFGSP(INFO_DEBUG,"ResizeComponents()");
	TConfig_Frame::ResizeComponents();
}
//---------------------------------------------------------------------------
void TShowPrefFrame::LoadConfiguration(TNameValue *Conf){
	TConfig_Frame::LoadConfiguration(Conf);
	DEBUG_CFGSP(INFO_DEBUG,"LoadConfiguration()");
	UpdateGrid();
}
//---------------------------------------------------------------------------
void TShowPrefFrame::SaveConfiguration(TNameValue *Conf){
	DEBUG_CFGSP(INFO_DEBUG,"SaveConfiguration()");
	int a;
	if(WebSource){
		for(a=0;a<WebSource->GetNumShowNamePref();a++)
			WebSource->RemoveShowNamePref(WebSource->GetShowNamePrefNameByIndex(a));
		for(a=0;a<PreferencesGrid->RowCount;a++)
			WebSource->AddShowNamePref(PreferencesGrid->Cells[0][a],PreferencesGrid->Cells[1][a]);
	}
	else
		DEBUG_CFGSP(WARN_DEBUG,"Invalid grid selection");
}
//---------------------------------------------------------------------------
void __fastcall TShowPrefFrame::PreferencesGridEditingDone(TObject *Sender, const int ACol,
          const int ARow)
{
	if(WebSource){
		String Name, ID;
		Name = PreferencesGrid->Cells[0][ARow];
		ID = PreferencesGrid->Cells[1][ARow];
		switch(ACol){
			case 0:{    //Change show tv name
				WebSource->ChangeShowNamePrefName(ARow,Name);
			}break;
			case 1:{    //Change show tv id
				WebSource->ChangeShowNamePrefID(ARow, ID);
			}break;
		};
	}
}
//---------------------------------------------------------------------------
TWebSource *TShowPrefFrame::GetSrc(){
	return FWebSource;
}
//---------------------------------------------------------------------------
void TShowPrefFrame::SetSrc(TWebSource *Src){
	FWebSource = Src;
    UpdateGrid();
}
//---------------------------------------------------------------------------

