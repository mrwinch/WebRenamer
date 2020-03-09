//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Config_DataSourceInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Config_Frame"
#pragma resource "*.fmx"
TDataSourceInfoFrame *DataSourceInfoFrame;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "CFG_DI"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
extern TSysLog *Logger;
//---------------------------------------------------------------------------
void DEBUG_CFGDI(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report(UNIT_ID,NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
__fastcall TDataSourceInfoFrame::TDataSourceInfoFrame(TComponent* Owner)
	: TConfig_Frame(Owner)
{
	int *ID;
	for(int a=0;a<185;a++){
		ID = (int*)AllocMem(sizeof(int));
		*ID = Language639[a].ID;
		PrefLanguageCombo->Items->AddObject(Language639[a].EnglishName,(TObject*)ID);
	}
	PrefLanguageCombo->ItemIndex = PrefLanguageCombo->Items->IndexOf("English");
	FWebSource = NULL;
    TestForm = new TForm3(this);
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::CreateGUITxt(TNameValue *GUITxt){
	DEBUG_CFGDI(INFO_DEBUG,"CreateGUITxt()");
	GUITxt->AddString(BUILD_ID("TestOpMenu"),"Test operation","Test operation popup menu");
	GUITxt->AddString(BUILD_ID("TestCommMenu"),"Test command","Test command popup menu");
	GUITxt->AddString(BUILD_ID("InfoGroupBox"),"Source data","Text show in source group box");
	GUITxt->AddString(BUILD_ID("SourceNameLabel"),"Name:","Data source label text");
	GUITxt->AddString(BUILD_ID("DescriptionLabel"),"Description","Text show description label");
	GUITxt->AddString(BUILD_ID("AuthRequiredCheckBox"),"Auth. required","Text for auth required checkbox");
	GUITxt->AddString(BUILD_ID("PreferedLanguageLabel"),"Prefered language:","Text for prefered language");
	GUITxt->AddString(BUILD_ID("SourceTypeLabel"),"Source type:","Text for source type");
	GUITxt->AddString(BUILD_ID("SourceTypeComboBox"),"TV show source,Movie source","Text for source type combo box");
	GUITxt->AddString(BUILD_ID("UsePreferences"),"Use preferences","Text for preferences check box");
	GUITxt->AddString(BUILD_ID("ParameterColumn"),"Parameters","Text for parameter column");
	GUITxt->AddString(BUILD_ID("ValueColumn"),"Values","Text for parameter value column");
	GUITxt->AddString(BUILD_ID("AddButton"),"Add parameter","Text for adding button");
	GUITxt->AddString(BUILD_ID("RemoveButton"),"Remove parameter","Text for removing button");
	GUITxt->AddString(BUILD_ID("CommandGroupBox"),"Commands","Text for commands group box");
	GUITxt->AddString(BUILD_ID("AddCommButton"),"Add command","Add command button text");
	GUITxt->AddString(BUILD_ID("RemoveCommButton"),"Remove command","Remove command button text");
	GUITxt->AddString(BUILD_ID("AddOpButton"),"Add operation","Add operation button text");
	GUITxt->AddString(BUILD_ID("RemoveOpButton"),"Remove operation","Remove operation button text");
	GUITxt->AddString(BUILD_ID("ListNameLabel"),"Name:","Data source label text");
	GUITxt->AddString(BUILD_ID("CommandTypeLabel"),"Type:","Command type label text");
	GUITxt->AddString(BUILD_ID("CommandTypeCombo"),"Authentication,Query Candidate,Query info","Command type combo value");
	GUITxt->AddString(BUILD_ID("TreeNode"),"WebSource","Treenode text");
	GUITxt->AddString(BUILD_ID("RemoveLineMsg"),"Remove ","Text show in remove dialog");
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::ResizeComponents(){
	DEBUG_CFGDI(INFO_DEBUG,"ResizeComponents()");
	UpdateInfo();
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::ApplyLanguage(TNameValue *Src){
	DEBUG_CFGDI(INFO_DEBUG,"ApplyLanguage()");
	TStringList *Cmp = new TStringList();
	Cmp->Add("TestOpMenu");
	Cmp->Add("TestCommMenu");
	Cmp->Add("InfoGroupBox");
	Cmp->Add("SourceNameLabel");
	Cmp->Add("DescriptionLabel");
	Cmp->Add("AuthRequiredCheckBox");
	Cmp->Add("PreferedLanguageLabel");
	Cmp->Add("SourceTypeLabel");
	Cmp->Add("SourceTypeComboBox");
	Cmp->Add("UsePreferences");
	Cmp->Add("ParameterColumn");
	Cmp->Add("ValueColumn");
	Cmp->Add("AddButton");
	Cmp->Add("RemoveButton");
	Cmp->Add("CommandGroupBox");
	Cmp->Add("AddCommButton");
	Cmp->Add("RemoveCommButton");
	Cmp->Add("AddOpButton");
	Cmp->Add("RemoveOpButton");
	Cmp->Add("ListNameLabel");
	Cmp->Add("CommandTypeLabel");
	Cmp->Add("CommandTypeCombo");

	TConfig_Frame::ApplyLanguage(Src, UNIT_ID, Cmp);
	if(TreeNode){
		if(FWebSource == NULL)
			TreeNode->Text = Src->GetString(BUILD_ID("TreeNode"));
		else
			TreeNode->Text = FWebSource->Name;
	}
	RemoveLineMsg = Src->GetString(BUILD_ID("RemoveLineMsg"));
}
//---------------------------------------------------------------------------
TWebSource *TDataSourceInfoFrame::GetSrc(){
	return FWebSource;
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::SetSrc(TWebSource *Src){
	FWebSource = Src;
	if(Src){
		TreeNode->Text = Src->Name;
		UpdateInfo();
	}
	else
		TreeNode->Text = "WebSource";
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::UpdateInfo(){
	if(FWebSource){
		int a;
		DataSourceEditName->Text = FWebSource->Name;
		DescriptionMemo->Text = FWebSource->Description;
		AuthRequiredCheckBox->IsChecked = FWebSource->AuthRequest;
		a = PrefLanguageCombo->Items->IndexOf(FWebSource->PreferedLanguage);
		if(a != -1)
			PrefLanguageCombo->ItemIndex = a;
		else
			PrefLanguageCombo->ItemIndex = PrefLanguageCombo->Items->IndexOf("English");
		FWebSource->Type == SHOW_SOURCE_INFO?SourceTypeComboBox->ItemIndex=0:SourceTypeComboBox->ItemIndex=1;
		UsePreferences->IsChecked = FWebSource->RememberPreferences;
		UpdateParameterGrid();
		UpdateCommandTreeView();
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::GenericChange(TObject *Sender){
	TComponent *Src = (TComponent*)Sender;
	if(Src){
		if(FWebSource){
			if(Src->Name == "DataSourceEditName"){
				FWebSource->Name = DataSourceEditName->Text;
				TreeNode->Text = FWebSource->Name;
			}
			if(Src->Name == "DescriptionMemo")
				FWebSource->Description = DescriptionMemo->Text;
			if(Src->Name == "AuthRequiredCheckBox")
				FWebSource->AuthRequest = AuthRequiredCheckBox->IsChecked;
			if(Src->Name == "PrefLanguageCombo")
				FWebSource->PreferedLanguage = PrefLanguageCombo->Selected->Text;
			if(Src->Name == "SourceTypeComboBox"){
				FWebSource->Type = SourceTypeComboBox->ItemIndex == 0?SHOW_SOURCE_INFO:MOVIE_SOURCE_INFO;
				if(FWebSource->Type == MOVIE_SOURCE_INFO){
                    UsePreferences->Enabled = false;
					if(TreeNode){
						if(TreeNode->Count > 0){
                            TreeNode->Items[0]->Visible = false;
						}
					}
				}
			}
			if(Src->Name == "UsePreferences")
				FWebSource->RememberPreferences = UsePreferences->IsChecked;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::AddButtonClick(TObject *Sender)
{
	if(FWebSource){
		int a = ParameterGrid->RowCount;
		FWebSource->AddParameter("Param_"+IntToStr(a+1),"Value_"+(IntToStr(a+1)));
		UpdateParameterGrid();
	}
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::UpdateParameterGrid(){
	if(FWebSource){
		TStringList *List = FWebSource->GetParameters();
		ParameterGrid->RowCount = List->Count;
		for(int a=0;a<List->Count;a++){
			ParameterGrid->Cells[0][a] = List->Names[a];
			ParameterGrid->Cells[1][a] = List->ValueFromIndex[a];
		}
    }
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::RemoveButtonClick(TObject *Sender)
{
	if(FWebSource){
		int a;
		a = ParameterGrid->Selected;
		if(a>-1){
			String Key = ParameterGrid->Cells[0][a];
			int Res = TDialogServiceSync::MessageDialog(RemoveLineMsg+Key+(String)"?",
					TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),THelpContext());
			if(Res == mrYes){
				FWebSource->RemoveParameter(Key);
				UpdateParameterGrid();
			}
		}
	}
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::UpdateCommandTreeView(){
	if(FWebSource){
		TTreeViewItem *Item;
		CommandList *Cmd;
		CommandTreeView->Clear();
		for(int a=0;a<FWebSource->GetNumCommands();a++){
			Item = new TTreeViewItem(CommandTreeView);
			Item->Parent = CommandTreeView;
			Cmd = FWebSource->GetCommandByIndex(a);
			Item->Text = Cmd->Name;
			Item->TagObject = (TObject*)Cmd;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::CommandTreeViewChange(TObject *Sender)
{
	if(CommandTreeView->Selected){
		CommandList *Cmd = (CommandList*)CommandTreeView->Selected->TagObject;
		ActivateCmdButton(true);
		OperationTabControl->TagObject = (TObject*)Cmd;
		CommandTypeCombo->Enabled = true;
		ListNameEdit->Enabled = true;
		UpdateCommandInfo();
	}
	else{
		CommandTypeCombo->Enabled = false;
		ListNameEdit->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::AddCommButtonClick(TObject *Sender)
{
	if(FWebSource){
		CommandList *Cmd = FWebSource->CreateCommandList("Command "+IntToStr(FWebSource->GetNumCommands()+1));
		UpdateCommandTreeView();
		CommandTreeView->Selected = CommandTreeView->Items[CommandTreeView->Count-1];
	}
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::ActivateCmdButton(bool YN){
	AddOpButton->Enabled = YN;
	RemoveCommButton->Enabled = YN;
	RemoveOpButton->Enabled = YN;
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::RemoveCommButtonClick(TObject *Sender)
{
	if(FWebSource){
		if(CommandTreeView->Selected){
			CommandList *Cmd = (CommandList*)CommandTreeView->Selected->TagObject;
			if(Cmd){
				int Res = TDialogServiceSync::MessageDialog(RemoveLineMsg+Cmd->Name+(String)"?",
						TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),THelpContext());
				if(Res == mrYes){
					FWebSource->RemoveCommandsList(Cmd);
					UpdateCommandTreeView();
					if(CommandTreeView->Count > 0){
						CommandTreeView->Selected = CommandTreeView->Items[CommandTreeView->Count-1];
						ActivateCmdButton(true);
					}
					else
						ActivateCmdButton(false);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::UpdateCommandInfo(){
	CommandList *Cmd = (CommandList*)OperationTabControl->TagObject;
	if(Cmd){
		int a;
		ListNameEdit->Text = Cmd->Name;
			switch(Cmd->Type){
				case QUERY_CANDIDATE:{
					CommandTypeCombo->ItemIndex = 1;
				}break;
				case QUERY_SHOW_TITLE:
				case QUERY_MOVIE_TITLE:{
					CommandTypeCombo->ItemIndex = 2;
				}break;
				case SYS_AUTHENTICATE:{
					CommandTypeCombo->ItemIndex = 0;
				}break;
				default:{
					CommandTypeCombo->ItemIndex = -1;
				}break;
			}
        UpdateOperationInfo();
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::AddOpButtonClick(TObject *Sender)
{
	CommandList *Cmd = (CommandList*)OperationTabControl->TagObject;
	if(Cmd){
		Net_Operation *Op = Cmd->CreateOperation("");
		UpdateOperationInfo();
	}
}
//---------------------------------------------------------------------------
void TDataSourceInfoFrame::UpdateOperationInfo(){
	int a;
	TOperationFrame *Frame;
	TTabItem *Tab;
	Net_Operation Op;
	CommandList *Cmd = (CommandList*)OperationTabControl->TagObject;
	if(Cmd){
		for(a=OperationTabControl->TabCount-1;a>-1;a--){
			OperationTabControl->Delete(a);
		}
		for(a=0;a<Cmd->GetNumOperations();a++){
			Tab = OperationTabControl->Add(NULL);
			Tab->Text = "Operation "+IntToStr(a+1);
			Frame = new TOperationFrame(Tab);
			Frame->Parent = Tab;
			Frame->Align = TAlignLayout::Top;
			Frame->TagObject = (TObject*)Cmd;
			Frame->CreateGUITxt(Language);
			Frame->ApplyLanguage(Language);
			Op = Cmd->GetOperation(a);
			Frame->ApplyOperation(Op);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::RemoveOpButtonClick(TObject *Sender)
{
	CommandList *Cmd = (CommandList*)OperationTabControl->TagObject;
	if(Cmd){
		int Res = TDialogServiceSync::MessageDialog(RemoveLineMsg+OperationTabControl->ActiveTab->Text+(String)"?",
				TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),THelpContext());
		if(Res == mrYes){
			Net_Operation Op = Cmd->GetOperation(OperationTabControl->TabIndex);
			Cmd->RemoveOperation(Op);
			UpdateOperationInfo();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::TestOpMenuClick(TObject *Sender)
{
	DEBUG_CFGDI(INFO_DEBUG,"MenuItem1Click()");
	if(WebSource){
		TTabItem *TabItem = OperationTabControl->ActiveTab;
		if(TabItem){
			TOperationFrame *Frame = (TOperationFrame*)TabItem->Components[1];
			if(Frame){
				TestForm->Memo1->Lines->Clear();
				WebSource->TestOperation(Frame->Operation,TestForm->RequestCompleted);
				TestForm->ShowModal();
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::TestCommMenuClick(TObject *Sender)
{
	DEBUG_CFGDI(INFO_DEBUG,"MenuItem2Click()");
	if(WebSource){
		TTreeViewItem *Item = CommandTreeView->Selected;
		if(Item){
			CommandList *Cmd = (CommandList*)Item->TagObject;
			if(Cmd){
				TestForm->Memo1->Lines->Clear();
				WebSource->TestCommand(Cmd,TestForm->RequestCompleted);
				TestForm->ShowModal();
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::ParameterGridEditingDone(TObject *Sender, const int ACol,
		  const int ARow)
{
	switch(ACol){
		case 0:{    //Parameter change...
			WebSource->RenameParameter(ParameterGrid->TagString,ParameterGrid->Cells[ACol][ARow]);
		}break;
		case 1:{    //Value change...
			WebSource->ChangeParameter(ParameterGrid->Cells[0][ARow],ParameterGrid->Cells[1][ARow]);
		}break;
	}
	UpdateParameterGrid();
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::ParameterGridSelectCell(TObject *Sender, const int ACol,
		  const int ARow, bool &CanSelect)
{
	ParameterGrid->TagString = ParameterGrid->Cells[ACol][ARow];
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::ListNameEditChange(TObject *Sender)
{
	if(CommandTreeView->Selected){
		CommandList *Cmd = (CommandList*)CommandTreeView->Selected->TagObject;
		if(Cmd){
			Cmd->Name = ListNameEdit->Text;
			CommandTreeView->Selected->Text = Cmd->Name;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::CommandTypeComboChange(TObject *Sender)
{
	if(CommandTreeView->Selected){
		CommandList *Cmd = (CommandList*)CommandTreeView->Selected->TagObject;
		if(Cmd){
			switch(CommandTypeCombo->ItemIndex){
				case 0:{
					Cmd->Type = SYS_AUTHENTICATE;
				}break;
				case 1:{
					Cmd->Type = QUERY_CANDIDATE;
				}break;
				case 2:{
					if(FWebSource->Type == SHOW_SOURCE_INFO)
						Cmd->Type = QUERY_SHOW_TITLE;
					else
						Cmd->Type = QUERY_MOVIE_TITLE;
				}break;

			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDataSourceInfoFrame::ParameterGridCellClick(TColumn * const Column,
		  const int Row)
{
	int ACol;
	String Txt = Language->GetString(BUILD_ID("ParameterColumn"));
	if(Txt == Column->Header)
		ACol = 0;
	else
        ACol = 1;
	ParameterGrid->TagString = ParameterGrid->Cells[ACol][Row];
}
//---------------------------------------------------------------------------

