//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "Config_General.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Config_Frame"
#pragma resource "*.fmx"
//---------------------------------------------------------------------------
#define UNIT_ID                                     "CFG_GN"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
TGeneralFrame *GeneralFrame;
//---------------------------------------------------------------------------
extern TSysLog *Logger;
//---------------------------------------------------------------------------
void DEBUG_CFGGN(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report(UNIT_ID,NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
__fastcall TGeneralFrame::TGeneralFrame(TComponent* Owner)
	: TConfig_Frame(Owner)
{
	int *ID;
	for(int a=0;a<185;a++){
		ID = (int*)AllocMem(sizeof(int));
		*ID = Language639[a].ID;
		PreferedLanguageComboBox->Items->AddObject(Language639[a].EnglishName,(TObject*)ID);
		if(Language639[a].Abbreviation == "en")
			AvailableCombo->Items->AddObject(Language639[a].EnglishName,(TObject*)ID);
	}
	PreferedLanguageComboBox->ItemIndex = PreferedLanguageComboBox->Items->IndexOf("English");
	FGrabber = NULL;
}
//---------------------------------------------------------------------------
void TGeneralFrame::CreateGUITxt(TNameValue *GUITxt){
	DEBUG_CFGGN(INFO_DEBUG,"CreateGUITxt()");
	if(GUITxt){
		GUITxt->AddString(BUILD_ID("DebugGroupBox"),"Debug","Debug group box");
		GUITxt->AddString(BUILD_ID("UIGroupBox"),"User interface","User interface group box");
		GUITxt->AddString(BUILD_ID("DebugLevelLabel"),"Debug level:","Debug combo box label");
		GUITxt->AddString(BUILD_ID("DebugLevelComboBox"),"None,Error,Warning,Information,Total","Debug combo box value");
		GUITxt->AddString(BUILD_ID("MultiDebugFile"),"Debug in multi files","Debug multi files label");
		GUITxt->AddString(BUILD_ID("SingleDebugFile"),"Debug in single files","Debug single file label");
		GUITxt->AddString(BUILD_ID("IncrementalDebug"),"Incremental debug","Incremental debug label");
		GUITxt->AddString(BUILD_ID("RemeberLastModeCheckBox"),"Remember last mode","Last mode label");
		GUITxt->AddString(BUILD_ID("PreferedLanguageLabel"),"Search language:","Prefered language label");
		GUITxt->AddString(BUILD_ID("AvailableLanguageLabel"),"Window language:","Available language label");
		GUITxt->AddString(BUILD_ID("AutoRenameFile"),"Automatic rename","Automatic rename files");
		GUITxt->AddString(BUILD_ID("TreeNode"),"General settings","Title for TreeItem and node");
	}
}
//---------------------------------------------------------------------------
void TGeneralFrame::ApplyLanguage(TNameValue *Src){
	DEBUG_CFGGN(INFO_DEBUG,"ApplyLanguage()");
	TStringList *Cmp = new TStringList();
	Cmp->Add("DebugGroupBox");
	Cmp->Add("UIGroupBox");
	Cmp->Add("DebugLevelLabel");
	Cmp->Add("MultiDebugFile");
	Cmp->Add("SingleDebugFile");
	Cmp->Add("DebugLevelComboBox");
	Cmp->Add("IncrementalDebug");
	Cmp->Add("RemeberLastModeCheckBox");
	Cmp->Add("PreferedLanguageLabel");
	Cmp->Add("AvailableLanguageLabel");
	Cmp->Add("AutoRenameFile");
	TConfig_Frame::ApplyLanguage(Src, UNIT_ID, Cmp);
	if(TreeNode)
		TreeNode->Text = Src->GetString(BUILD_ID("TreeNode"));
}
//---------------------------------------------------------------------------
void TGeneralFrame::ResizeComponents(){
	DEBUG_CFGGN(INFO_DEBUG,"ResizeComponents()");
	MultiDebugFile->Width = MultiDebugFile->Canvas->TextWidth(MultiDebugFile->Text)+30;
	SingleDebugFile->Width = SingleDebugFile->Canvas->TextWidth(SingleDebugFile->Text)+30;
	IncrementalDebug->Width = IncrementalDebug->Canvas->TextWidth(IncrementalDebug->Text)+30;
	RemeberLastModeCheckBox->Width = RemeberLastModeCheckBox->Canvas->TextWidth(RemeberLastModeCheckBox->Text)+30;
	AutoRenameFile->Width = AutoRenameFile->Canvas->TextWidth(AutoRenameFile->Text)+30;
	if(MultiDebugFile->IsChecked)
		IncrementalDebug->Enabled = false;
	else
		IncrementalDebug->Enabled = true;
//	DebugLevelComboBox->ItemIndex = DebugLevelComboBox->Tag;
}
//---------------------------------------------------------------------------
TInfoGrabber *TGeneralFrame::GetGrabber(){
	return FGrabber;
}
//---------------------------------------------------------------------------
void TGeneralFrame::SetGrabber(TInfoGrabber *Grab){
	DEBUG_CFGGN(INFO_DEBUG,"SetGrabber()");
	FGrabber = Grab;
}
//---------------------------------------------------------------------------
void TGeneralFrame::LoadConfiguration(TNameValue *Conf){
	TConfig_Frame::LoadConfiguration(Conf);
	DEBUG_CFGGN(INFO_DEBUG,"LoadConfiguration()");
	int a;
	bool b;
	String Tmp;
//
	String AppDirectory = Conf->GetString("SoftwareDir");
	String Path = AppDirectory+"\\Language";
	String ShortLang = "";
	String ConfLang = Conf->GetString("WindowLanguage");
	if(TDirectory::Exists(Path)){
		TSearchRec sr;
		TNameValue *Tmp = new TNameValue(this);
		String FileName;
		int *ID;
		int iAttributes = 0;
		iAttributes |= faReadOnly, iAttributes |= faHidden, iAttributes |= faSysFile, iAttributes |= faArchive;
		iAttributes |= faAnyFile;
		FileName = Path + (String)"\\*.lng";
		AvailableCombo->Clear();
		if(FindFirst(FileName,iAttributes, sr) == 0){
			do
			{
				if (sr.Attr & iAttributes){
					FileName = Path + (String)"\\"+sr.Name;
					Tmp->LoadFromXML(FileName);
					ShortLang = Tmp->GetString("Short_Language");
					for(a=0;a<ISO_639_LEN;a++){
						if(ShortLang == Language639[a].Abbreviation){
							ID = (int*)AllocMem(sizeof(int));
							*ID = Language639[a].ID;
							AvailableCombo->Items->AddObject(Language639[a].EnglishName,(TObject*)ID);
							if(Tmp->GetString("Short_Language") == ConfLang){
								//GUITxt = Tmp->Clone(this);
								AvailableCombo->ItemIndex = AvailableCombo->Items->Count-1;
							}
							break;
						}
					}
				}
			}while (FindNext(sr) == 0);
			FindClose(sr);
		}
	}
//
	if(Conf){
		a = Conf->GetInt("DebugLevel");
		if(a == STRING_INVALID_NAME)
			a = TOTAL_DEBUG;
		DebugLevelComboBox->ItemIndex = a;
		IncrementalDebug->IsChecked = Conf->GetBool("IncrementalDebug");
		MultiDebugFile->IsChecked = Conf->GetBool("MultiDebugFile");
		SingleDebugFile->IsChecked = !(Conf->GetBool("MultiDebugFile"));
		RemeberLastModeCheckBox->IsChecked = Conf->GetBool("RememeberLastMode");
		Tmp = Conf->GetString("PreferedLanguage");
		a = PreferedLanguageComboBox->Items->IndexOf(Tmp);
		if(a == -1)
			PreferedLanguageComboBox->ItemIndex = PreferedLanguageComboBox->Items->IndexOf("English");
		else
			PreferedLanguageComboBox->ItemIndex = a;
		AutoRenameFile->IsChecked = Conf->GetBool("AutoRenameFile");
	}
	else
		DEBUG_CFGGN(ERR_DEBUG,"Invalid configuration object");
}
//---------------------------------------------------------------------------
void TGeneralFrame::SaveConfiguration(TNameValue *Conf){
	DEBUG_CFGGN(INFO_DEBUG,"SaveConfiguration()");
	DEBUG_CFGGN(INFO_DEBUG,"DebugLevelComboBoxChange()"+IntToStr(DebugLevelComboBox->ItemIndex));
	Conf->SetInt("DebugLevel",DebugLevelComboBox->ItemIndex);
	Conf->SetBool("MultiDebugFile",MultiDebugFile->IsChecked);
	Conf->SetBool("IncrementalDebug",IncrementalDebug->IsChecked);
	Conf->SetBool("RememeberLastMode",RemeberLastModeCheckBox->IsChecked);
	Conf->SetBool("AutoRenameFile",AutoRenameFile->IsChecked);
	Conf->SetString("PreferedLanguage",PreferedLanguageComboBox->Items->Strings[PreferedLanguageComboBox->ItemIndex]);
	if(AvailableCombo->Selected){
		for(int a=0;a<ISO_639_LEN;a++){
			if(Language639[a].EnglishName == AvailableCombo->Selected->Text){
				Conf->SetString("WindowLanguage",Language639[a].Abbreviation);
                break;
			}
		}
	}
}
//---------------------------------------------------------------------------
void TGeneralFrame::CreateConfiguration(TNameValue *Conf){
	TConfig_Frame::CreateConfiguration(Conf);
	DEBUG_CFGGN(INFO_DEBUG,"CreateConfiguration()");
	Conf->AddInt("DebugLevel",TOTAL_DEBUG,"Application debug level");
	Conf->AddBool("IncrementalDebug",false,"Store debug sessions in a file otherwise debug file will be overwritten");
	Conf->AddBool("MultiDebugFile",false,"Create a file for every debug session");
	Conf->AddBool("RememeberLastMode",false,"Remember last mode (TV or FILM mode)");
	Conf->AddBool("AutoRenameFile",false,"Rename files after found title");
	Conf->AddString("PreferedLanguage","English","Favorite language for search");
	Conf->AddString("WindowLanguage","en","Favorite language for GUI and title");
}
//---------------------------------------------------------------------------
void __fastcall TGeneralFrame::SingleDebugFileClick(TObject *Sender)
{
	IncrementalDebug->Enabled = SingleDebugFile->IsChecked;
}
//---------------------------------------------------------------------------
void __fastcall TGeneralFrame::PreferedLanguageComboBoxChange(TObject *Sender)
{
	if(Grabber){
		String Lang;
		Lang = PreferedLanguageComboBox->Selected->Text;
		Grabber->PreferedLanguage = Lang;
		TWebSource *Src;
		for(int a=0;a<Grabber->GetNumInfoSource();a++){
			Src = Grabber->GetSourceByIndex(a);
            Src->PreferedLanguage = Lang;
		}
	}
}
//---------------------------------------------------------------------------
void TGeneralFrame::UpdateGUILanguage(TNameValue *Src,TNameValue *Conf){
	String AppDirectory = Conf->GetString("SoftwareDir");
	String Path = AppDirectory+"\\Language";
	String ShortLang = "";
	String ConfLang = Conf->GetString("WindowLanguage");
	if(TDirectory::Exists(Path)){
		TSearchRec sr;
		TNameValue *Tmp = new TNameValue(this);
		String FileName;
		int *ID;
		int iAttributes = 0;
		iAttributes |= faReadOnly, iAttributes |= faHidden, iAttributes |= faSysFile, iAttributes |= faArchive;
		iAttributes |= faAnyFile;
		FileName = Path + (String)"\\*.lng";
		if(FindFirst(FileName,iAttributes, sr) == 0){
			do
			{
				if (sr.Attr & iAttributes){
					FileName = Path + (String)"\\"+sr.Name;
					Tmp->LoadFromXML(FileName);
					ShortLang = Tmp->GetString("Short_Language");
					if(ShortLang == ConfLang){
						//Src->LoadFromXML(FileName);
                        Src->UpdateFromSource(Tmp);
						break;
					}
				}
			}while (FindNext(sr) == 0);
			FindClose(sr);
		}
	}

}
//---------------------------------------------------------------------------
