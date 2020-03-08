//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "ShowSearch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TShowSearchForm *ShowSearchForm;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "SSR_FR"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
__fastcall TShowSearchForm::TShowSearchForm(TComponent* Owner)
	: TForm(Owner)
{
	FGrabber = NULL;
	Frame = new TCandidateListFrame(FramePanel);
	Frame->Parent = FramePanel;
	Frame->Align = TAlignLayout::Client;
	Frame->NoPhotoImage = new TResourceStream((int)HInstance,"NoPoster_TV",RT_RCDATA);
	Frame->OnRefuseCandidate = RefuseCandidate;
	Frame->OnSelectCandidate = SelectCandidate;
    Frame->Panel1->Visible = false;

	GUITxt = NULL;
	SearchID = 0;
}
//---------------------------------------------------------------------------
void TShowSearchForm::CreateGUITxt(TNameValue *Txt){
	if(Txt->ValueExist(BUILD_ID("SearchTitleLabel")) == false)
		Txt->AddString(BUILD_ID("SearchTitleLabel"),"Show title: ","Text for title label");
	if(Txt->ValueExist(BUILD_ID("SeasonLabel")) == false)
		Txt->AddString(BUILD_ID("SeasonLabel"),"Season: ","Text for season label");
	if(Txt->ValueExist(BUILD_ID("EpisodeLabel")) == false)
		Txt->AddString(BUILD_ID("EpisodeLabel"),"Episode: ","Text for episode label");
	if(Txt->ValueExist(BUILD_ID("SourceLabel")) == false)
		Txt->AddString(BUILD_ID("SourceLabel"),"Source: ","Text for source label");
	if(Txt->ValueExist(BUILD_ID("Caption")) == false)
		Txt->AddString(BUILD_ID("Caption"),"Manual search...","Text for window title");
	if(Txt->ValueExist(BUILD_ID("SearchDataGroup")) == false)
		Txt->AddString(BUILD_ID("SearchDataGroup"),"Search parameter","Text for parameter group bopx");
	if(Txt->ValueExist(BUILD_ID("SearchButton")) == false)
		Txt->AddString(BUILD_ID("SearchButton"),"Search","Text for window title");
	if(Txt->ValueExist(BUILD_ID("FormatLabel")) == false)
		Txt->AddString(BUILD_ID("FormatLabel"),"Format: ","Text for format label");
	if(Txt->ValueExist(BUILD_ID("ResultLabel")) == false)
		Txt->AddString(BUILD_ID("ResultLabel"),"Result: ","Text for format label");
	if(Txt->ValueExist(BUILD_ID("ApplyButton")) == false)
		Txt->AddString(BUILD_ID("ApplyButton"),"Apply","Text for apply button");

	GUITxt = Txt;
}
//---------------------------------------------------------------------------
void TShowSearchForm::ApplyLanguage(TNameValue *Txt){
	SearchTitleLabel->Text = Txt->GetString(BUILD_ID("SearchTitleLabel"));
	SeasonLabel->Text = Txt->GetString(BUILD_ID("SeasonLabel"));
	EpisodeLabel->Text = Txt->GetString(BUILD_ID("EpisodeLabel"));
	SourceLabel->Text = Txt->GetString(BUILD_ID("SourceLabel"));
	SearchButton->Text = Txt->GetString(BUILD_ID("SearchButton"));
	ApplyButton->Text = Txt->GetString(BUILD_ID("ApplyButton"));
	Caption = Txt->GetString(BUILD_ID("Caption"));
	GroupBox1->Text = Txt->GetString(BUILD_ID("SearchDataGroup"));
	FormatLabel->Text = Txt->GetString(BUILD_ID("FormatLabel"));
	ResultLabel->Text = Txt->GetString(BUILD_ID("ResultLabel"));
    GUITxt = Txt;
}
//---------------------------------------------------------------------------
TInfoGrabber *TShowSearchForm::GetGrabber(){
	return FGrabber;
}
//---------------------------------------------------------------------------
void TShowSearchForm::SetGrabber(TInfoGrabber *Grabber){
	FGrabber = Grabber;
}
//---------------------------------------------------------------------------
void __fastcall TShowSearchForm::SearchButtonClick(TObject *Sender)
{
	TWebSource *Source;
	for(int a=0;a<Grabber->GetNumInfoSource();a++){
		Source = Grabber->GetSourceByIndex(a);
		if(Source->Name == SourceCombo->Selected->Text){
			Source->RememberPreferences = false;
			Source->QueryCandidate(TitleEdit->Text, FoundCandidate,SearchID);
			GroupBox1->Enabled = false;
			break;
		}
	}
	SearchID++;
}
//---------------------------------------------------------------------------
void __fastcall TShowSearchForm::FoundCandidate(String Searched, int SearchID, TList *Candidate){
	TWebSource *Source;
	for(int a=0;a<Grabber->GetNumInfoSource();a++){
		Source = Grabber->GetSourceByIndex(a);
		if(Source->Name == SourceCombo->Selected->Text){
			Source->RememberPreferences = (bool)SourceCombo->Selected->Tag;
			break;
		}
	}
	Frame->CandidateListBox->Clear();
	Frame->ManageCandidateInfo(Searched, SearchID, Candidate);
	GroupBox1->Enabled = true;
	ClientHeight = 600;
	FramePanel->Height = 400;
	FramePanel->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TShowSearchForm::RefuseCandidate(TObject *Sender, String Candidate, int SearchID){
	ClientHeight = 200;
	FramePanel->Height = 2;
	FramePanel->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TShowSearchForm::SelectCandidate(TObject *Sender, String Candidate, String ID, int SearchID){
	TWebSource *Source;
	ClientHeight = 200;
	FramePanel->Height = 2;
	FramePanel->Visible = false;
	for(int a=0;a<Grabber->GetNumInfoSource();a++){
		Source = Grabber->GetSourceByIndex(a);
		if(Source->Name == SourceCombo->Selected->Text){
			Source->QueryShowDetail(Candidate, ID, SeasonSpin->Value, EpisodeSpin->Value,FindShowData, SearchID);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TShowSearchForm::FindShowData(String ShowName, int Season, int Episode, int SearchID, ShowResultDetails Details){
//	Label1->Text = Details.EpisodeTitle;
	TNameTranslator *Tr = new TNameTranslator(this);
	TVShowNameDetails Dt;
	String Res;
	Dt.ShowName = ShowName;
	Dt.Season = Season;
	Dt.Episode = Episode;
	Dt.EpisodeTitle = Details.EpisodeTitle;
	if(FormatCombo->Selected){
		Res = Tr->CreateTVShowName(FormatCombo->Selected->Text, Dt);
        ResultValue->Text = Res;
	}
}
//---------------------------------------------------------------------------
void __fastcall TShowSearchForm::ResultValueChange(TObject *Sender)
{
	if(ResultValue->Text.Length() > 0)
		ApplyButton->Enabled = true;
	else
	    ApplyButton->Enabled = false;
}
//---------------------------------------------------------------------------

