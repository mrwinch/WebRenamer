//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MovieSearch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMovieSearchForm *MovieSearchForm;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "SMV_FR"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
__fastcall TMovieSearchForm::TMovieSearchForm(TComponent* Owner)
	: TForm(Owner)
{
	Grabber = NULL;
	Frame = new TCandidateListFrame(FramePanel);
	Frame->Parent = FramePanel;
	Frame->Align = TAlignLayout::Client;
	Frame->NoPhotoImage = new TResourceStream((int)HInstance,"NoPhoto",RT_RCDATA);
//	Frame->OnRefuseCandidate = RefuseCandidate;
	Frame->OnSelectMovie = SelectCandidate;
	Frame->Panel1->Visible = false;
	Frame->TVShowInfo = false;

	SearchID = 0;
}
//---------------------------------------------------------------------------
void TMovieSearchForm::CreateGUITxt(TNameValue *Txt){
	if(Txt->ValueExist(BUILD_ID("SearchDataGroup")) == false)
		Txt->AddString(BUILD_ID("SearchDataGroup"),"Search parameter","Text for parameter group bopx");
	if(Txt->ValueExist(BUILD_ID("SearchButton")) == false)
		Txt->AddString(BUILD_ID("SearchButton"),"Search","Text for window title");
	if(Txt->ValueExist(BUILD_ID("ApplyButton")) == false)
		Txt->AddString(BUILD_ID("ApplyButton"),"Apply","Text for apply button");
	if(Txt->ValueExist(BUILD_ID("MovieLabel")) == false)
		Txt->AddString(BUILD_ID("MovieLabel"),"Movie:","Text for movie label");
	if(Txt->ValueExist(BUILD_ID("YearLabel")) == false)
		Txt->AddString(BUILD_ID("YearLabel"),"Year:","Text for year label");
	if(Txt->ValueExist(BUILD_ID("DiscLabel")) == false)
		Txt->AddString(BUILD_ID("DiscLabel"),"Disc:","Text for year label");
	if(Txt->ValueExist(BUILD_ID("Caption")) == false)
		Txt->AddString(BUILD_ID("Caption"),"Manual search...","Text for window title");
	if(Txt->ValueExist(BUILD_ID("SourceLabel")) == false)
		Txt->AddString(BUILD_ID("SourceLabel"),"Source: ","Text for source label");
	if(Txt->ValueExist(BUILD_ID("FormatLabel")) == false)
		Txt->AddString(BUILD_ID("FormatLabel"),"Format: ","Text for format label");
	if(Txt->ValueExist(BUILD_ID("ResultLabel")) == false)
		Txt->AddString(BUILD_ID("ResultLabel"),"Result: ","Text for format label");
}
//---------------------------------------------------------------------------
void TMovieSearchForm::ApplyLanguage(TNameValue *Txt){
	Caption = Txt->GetString(BUILD_ID("Caption"));
	DataGroupBox->Text = Txt->GetString(BUILD_ID("SearchDataGroup"));
	SearchButton->Text = Txt->GetString(BUILD_ID("SearchButton"));
	ApplyButton->Text = Txt->GetString(BUILD_ID("ApplyButton"));
	MovieLabel->Text = Txt->GetString(BUILD_ID("MovieLabel"));
	YearLabel->Text = Txt->GetString(BUILD_ID("YearLabel"));
	DiscLabel->Text = Txt->GetString(BUILD_ID("DiscLabel"));
	SourceLabel->Text = Txt->GetString(BUILD_ID("SourceLabel"));
	FormatLabel->Text = Txt->GetString(BUILD_ID("FormatLabel"));
	ResultLabel->Text = Txt->GetString(BUILD_ID("ResultLabel"));
}
//---------------------------------------------------------------------------
void __fastcall TMovieSearchForm::ResultValueChange(TObject *Sender)
{
	if(ResultValue->Text.Length() > 0)
		ApplyButton->Enabled = true;
	else
		ApplyButton->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMovieSearchForm::SearchButtonClick(TObject *Sender)
{
	TWebSource *Source;
	for(int a=0;a<Grabber->GetNumInfoSource();a++){
		Source = Grabber->GetSourceByIndex(a);
		if(Source->Name == SourceCombo->Selected->Text){
			Source->RememberPreferences = false;
			Source->QueryCandidate(TitleEdit->Text, FoundCandidate,SearchID);
			DataGroupBox->Enabled = false;
			break;
		}
	}
	SearchID++;
}
//---------------------------------------------------------------------------
void __fastcall TMovieSearchForm::FoundCandidate(String Searched, int SearchID, TList *Candidate){
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
	DataGroupBox->Enabled = true;
	ClientHeight = 600;
	FramePanel->Height = 400;
	FramePanel->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TMovieSearchForm::SelectCandidate(TObject *Sender, String Movie, String ID, int SearchID, String Release){
	TWebSource *Source;
	String Res;
	ClientHeight = 200;
	FramePanel->Height = 2;
	FramePanel->Visible = false;

	TNameTranslator *Tr = new TNameTranslator(this);
	MovieNamedetails Details;
	Details.Title = Movie;
	TDateTime Rel = ISO8601ToDate(Release+(String)"T00:00:00");
	Details.Year = YearOf(Rel);
	Details.Disc = DiscSpin->Value;
	Res = Tr->CreateMovieName(FormatCombo->Selected->Text,Details);
	ResultValue->Text = Res;
}
//---------------------------------------------------------------------------

