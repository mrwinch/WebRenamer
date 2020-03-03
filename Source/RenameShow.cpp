//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "RenameShow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TRenameShowForm *RenameShowForm;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "RNS_FR"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
__fastcall TRenameShowForm::TRenameShowForm(TComponent* Owner)
	: TForm(Owner)
{
//	Extension = "";
}
//---------------------------------------------------------------------------
void TRenameShowForm::CreateGUITxt(TNameValue *GUITxt){
	GUITxt->AddString(BUILD_ID("ShowLabel"),"Show: ","Text for show label");
	GUITxt->AddString(BUILD_ID("SeasonLabel"),"Season: ","Text for Season label");
	GUITxt->AddString(BUILD_ID("EpisodeLabel"),"Episode: ","Text for Episode label");
	GUITxt->AddString(BUILD_ID("TitleLabel"),"Title: ","Text for title label");
	GUITxt->AddString(BUILD_ID("ResultLabel"),"Result: ","Text for Result label");
	GUITxt->AddString(BUILD_ID("RenameBox"),"Rename data","Text for rename group");
	GUITxt->AddString(BUILD_ID("ManualRename"),"Manual rename","Text for manual rename label");
	GUITxt->AddString(BUILD_ID("OkButton"),"Ok","Text for ok button");
	GUITxt->AddString(BUILD_ID("CancelButton"),"Cancel","Text for cancel button");
	GUITxt->AddString(BUILD_ID("FormatLabel"),"Output:","Text for output label");
}
//---------------------------------------------------------------------------
void TRenameShowForm::ApplyLanguage(TNameValue *GUITxt){
	ShowLabel->Text = GUITxt->GetString(BUILD_ID("ShowLabel"));
	SeasonLabel->Text = GUITxt->GetString(BUILD_ID("SeasonLabel"));
	EpisodeLabel->Text = GUITxt->GetString(BUILD_ID("EpisodeLabel"));
	TitleLabel->Text = GUITxt->GetString(BUILD_ID("TitleLabel"));
	ResultLabel->Text = GUITxt->GetString(BUILD_ID("ResultLabel"));
	RenameBox->Text = GUITxt->GetString(BUILD_ID("RenameBox"));
	OkButton->Text = GUITxt->GetString(BUILD_ID("OkButton"));
	CancelButton->Text = GUITxt->GetString(BUILD_ID("CancelButton"));
	FormatLabel->Text = GUITxt->GetString(BUILD_ID("FormatLabel"));
	Caption = GUITxt->GetString(BUILD_ID("ManualRename"));
}
//---------------------------------------------------------------------------
void __fastcall TRenameShowForm::GenericChange(TObject *Sender){
	TNameTranslator *Tmp = new TNameTranslator(this);
	String Txt = "";
	TVShowNameDetails Det;
	Det.ShowName = ShowEdit->Text;
	Det.Season = SeasonSpin->Value;
	Det.Episode = EpisodeSpin->Value;
	Det.EpisodeTitle = TitleEdit->Text;
	if(FormatComboBox->Selected){
		Txt = Tmp->CreateTVShowName(FormatComboBox->Selected->Text, Det);
	}
	OutputEdit->Text = Txt;
}
//---------------------------------------------------------------------------

