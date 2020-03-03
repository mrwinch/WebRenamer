//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Config_OutputName.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Config_Frame"
#pragma resource "*.fmx"
TOutputNameFrame *OutputNameFrame;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "CFG_ON"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
extern TSysLog *Logger;
//---------------------------------------------------------------------------
void DEBUG_CFGON(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report(UNIT_ID,NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
__fastcall TOutputNameFrame::TOutputNameFrame(TComponent* Owner)
	: TConfig_Frame(Owner)
{
	Translator = new TNameTranslator(this);
	ShowExample.ShowName = "The big bang theory";
	ShowExample.Season = 6;
	ShowExample.Episode = 15;
	ShowExample.EpisodeTitle = "The Spoiler Alert Segmentation";
	MovieExample.Title = "Avengers - Infinity war";
	MovieExample.Year = 2018;
}
//---------------------------------------------------------------------------
void TOutputNameFrame::CreateGUITxt(TNameValue *GUITxt){
	DEBUG_CFGON(INFO_DEBUG,"CreateGUITxt()");
	GUITxt->AddString(BUILD_ID("TVShowGroupBox"),"TV Show name","Group box for TV Show");
	GUITxt->AddString(BUILD_ID("ShowInputTextLabel"),"Name format:","Format of output file");
	GUITxt->AddString(BUILD_ID("ShowFormatEditButton"),"Add","Text for add button");
	GUITxt->AddString(BUILD_ID("ShowFormatComboButton"),"Remove","Text for remove button");
	GUITxt->AddString(BUILD_ID("ShowExampleGroupBox"),"Example","Example group box for TV Show");
	GUITxt->AddString(BUILD_ID("ExampleShowLabel"),"Show: "+ShowExample.ShowName,"Example group box for TV Show");
	GUITxt->AddString(BUILD_ID("ExampleShowSeasonLabel"),"Season: "+IntToStr(ShowExample.Season),"Example group box for TV Show");
	GUITxt->AddString(BUILD_ID("ExampleShowEpisodeLabel"),"Episode: "+IntToStr(ShowExample.Episode),"Example group box for TV Show");
	GUITxt->AddString(BUILD_ID("ExampleShowTitle"),"Title: "+ShowExample.EpisodeTitle,"Example group box for TV Show");
	GUITxt->AddString(BUILD_ID("ExampleShowResult"),"Result:","Example group box for TV Show");
	GUITxt->AddString(BUILD_ID("ShowNamePopup"),"TV Show Name","Text for popup");
	GUITxt->AddString(BUILD_ID("ShowNameFirst"),"First letter uppercase","Text for popup");
	GUITxt->AddString(BUILD_ID("ShowNameLower"),"Lowercase","Text for popup");
	GUITxt->AddString(BUILD_ID("ShowNameUpper"),"Uppercase","Text for popup");
	GUITxt->AddString(BUILD_ID("ShowNameWord"),"First word letter uppercase","Text for popup");
	GUITxt->AddString(BUILD_ID("SourceShowName"),"Show name as source","Text for popup");
	GUITxt->AddString(BUILD_ID("SeasonPopup"),"Season","Text for popup");
	GUITxt->AddString(BUILD_ID("SeasonNumber"),"Season number","Text for popup");
	GUITxt->AddString(BUILD_ID("Season2Digits"),"Season in 2 digits","Text for popup");
	GUITxt->AddString(BUILD_ID("Season3Digits"),"Season in 3 digits","Text for popup");
	GUITxt->AddString(BUILD_ID("EpisodePopup"),"Episode","Text for popup");
	GUITxt->AddString(BUILD_ID("EpisodeNumber"),"Episode number","Text for popup");
	GUITxt->AddString(BUILD_ID("Episode2Digits"),"Episode in 2 digits","Text for popup");
	GUITxt->AddString(BUILD_ID("Episode3Digits"),"Episode in 3 digits","Text for popup");
	GUITxt->AddString(BUILD_ID("ShowTitlePopup"),"TV Show Title","Text for popup");
	GUITxt->AddString(BUILD_ID("ShowTitleFirst"),"First letter uppercase","Text for popup");
	GUITxt->AddString(BUILD_ID("ShowTitleLower"),"Lowercase","Text for popup");
	GUITxt->AddString(BUILD_ID("ShowTitleUpper"),"Uppercase","Text for popup");
	GUITxt->AddString(BUILD_ID("ShowTitleWord"),"First word letter uppercase","Text for popup");
	GUITxt->AddString(BUILD_ID("SourceShowTitle"),"Title as source","Text for popup");

	GUITxt->AddString(BUILD_ID("FilmGroupBox"),"Film name","Group box for Film");
	GUITxt->AddString(BUILD_ID("MovieInputLabel"),"Name format:","Format of output file");
	GUITxt->AddString(BUILD_ID("MovieFormatEditButton"),"Add","Text for add button");
	GUITxt->AddString(BUILD_ID("MovieFormatComboButton"),"Remove","Text for remove button");
	GUITxt->AddString(BUILD_ID("MovieExampleGroupBox"),"Example","Example group box for TV Show");
	GUITxt->AddString(BUILD_ID("MovieNamePopup"),"Movie Name","Text for popup");
	GUITxt->AddString(BUILD_ID("MovieNameFirst"),"First letter uppercase","Text for popup");
	GUITxt->AddString(BUILD_ID("MovieNameLower"),"Lowercase","Text for popup");
	GUITxt->AddString(BUILD_ID("MovieNameUpper"),"Uppercase","Text for popup");
	GUITxt->AddString(BUILD_ID("MovieNameWord"),"First word letter uppercase","Text for popup");
	GUITxt->AddString(BUILD_ID("SourceMovieName"),"Name as source","Text for popup");
	GUITxt->AddString(BUILD_ID("MovieYear"),"Year","Text for popup");
	GUITxt->AddString(BUILD_ID("ExampleMovieLabel"),"Movie: "+MovieExample.Title,"Example group box for TV Show");
	GUITxt->AddString(BUILD_ID("ExampleMovieYear"),"Year: "+IntToStr(MovieExample.Year),"Example group box for TV Show");
	GUITxt->AddString(BUILD_ID("ExampleMovieResult"),"Result:","Example group box for TV Show");


	GUITxt->AddString(BUILD_ID("TreeNode"),"Output name","Preferences on output name");
}
//---------------------------------------------------------------------------
void TOutputNameFrame::ApplyLanguage(TNameValue *Src){

	DEBUG_CFGON(INFO_DEBUG,"ApplyLanguage()");
	TStringList *Cmp = new TStringList();
	Cmp->Add("TVShowGroupBox");
	Cmp->Add("FilmGroupBox");
	Cmp->Add("MovieInputLabel");
	Cmp->Add("MovieFormatEditButton");
	Cmp->Add("MovieFormatComboButton");
	Cmp->Add("MovieExampleGroupBox");
	Cmp->Add("ExampleMovieLabel");
	Cmp->Add("ExampleMovieYear");
	Cmp->Add("ExampleMovieResult");
	Cmp->Add("MovieNamePopup");
	Cmp->Add("MovieNameFirst");
	Cmp->Add("MovieNameLower");
	Cmp->Add("MovieNameUpper");
	Cmp->Add("MovieNameWord");
	Cmp->Add("MovieYear");
	Cmp->Add("ShowInputTextLabel");
	Cmp->Add("ShowFormatEditButton");
	Cmp->Add("ShowFormatComboButton");
	Cmp->Add("ShowExampleGroupBox");
	Cmp->Add("ExampleShowLabel");
	Cmp->Add("ExampleShowSeasonLabel");
	Cmp->Add("ExampleShowEpisodeLabel");
	Cmp->Add("ExampleShowTitle");
	Cmp->Add("ExampleShowResult");
	Cmp->Add("ShowNamePopup");
	Cmp->Add("ShowNameFirst");
	Cmp->Add("ShowNameLower");
	Cmp->Add("ShowNameUpper");
	Cmp->Add("ShowNameWord");
	Cmp->Add("SeasonPopup");
	Cmp->Add("SeasonNumber");
	Cmp->Add("Season2Digits");
	Cmp->Add("Season3Digits");
	Cmp->Add("EpisodePopup");
	Cmp->Add("EpisodeNumber");
	Cmp->Add("Episode2Digits");
	Cmp->Add("Episode3Digits");
	Cmp->Add("ShowTitlePopup");
	Cmp->Add("ShowTitleFirst");
	Cmp->Add("ShowTitleLower");
	Cmp->Add("ShowTitleUpper");
	Cmp->Add("ShowTitleWord");
	Cmp->Add("SourceShowName");
	Cmp->Add("SourceMovieName");
	Cmp->Add("SourceShowTitle");

	TConfig_Frame::ApplyLanguage(Src, UNIT_ID, Cmp);
	if(TreeNode)
		TreeNode->Text = Src->GetString(BUILD_ID("TreeNode"));
}
//---------------------------------------------------------------------------
void TOutputNameFrame::ResizeComponents(){
	DEBUG_CFGON(INFO_DEBUG,"ResizeComponents()");
}
//---------------------------------------------------------------------------
void __fastcall TOutputNameFrame::GenericMovieEditPopupItem(TObject *Sender){
	TMenuItem *Item = (TMenuItem*)Sender;
	if(Item){
		String Input, Output;
		String Value;
		Input = MovieFormatEdit->Text;
		if(Item->Name == "MovieNameFirst")
			Value = START_PARAMETER+(String)"Moviename"+END_PARAMETER;
		if(Item->Name == "SourceMovieName")
			Value = START_PARAMETER+(String)"mOviename"+END_PARAMETER;
		if(Item->Name == "MovieNameLower")
			Value = START_PARAMETER+(String)"moviename"+END_PARAMETER;
		if(Item->Name == "MovieNameUpper")
			Value = START_PARAMETER+(String)"MOVIENAME"+END_PARAMETER;
		if(Item->Name == "MovieNameWord")
			Value = START_PARAMETER+(String)"MovieName"+END_PARAMETER;
		if(Item->Name == "MovieYear")
			Value = START_PARAMETER+(String)"Year"+END_PARAMETER;
		if(Item->Name == "DiscNumber")
			Value = START_PARAMETER+(String)"DiscNumber"+END_PARAMETER;
		Output = Input.Insert(Value,MovieFormatEdit->SelStart+1);
		MovieFormatEdit->Text = Output;
		MovieFormatEdit->SelStart += Value.Length();
	}
}
//---------------------------------------------------------------------------
void __fastcall TOutputNameFrame::GenericShowEditPopupItem(TObject *Sender){
	TMenuItem *Item = (TMenuItem*)Sender;
	if(Item){
		String Input, Output;
		String Value;
		Input = ShowFormatEdit->Text;
		if(Item->Name == "ShowNameFirst")
			Value = START_PARAMETER+(String)"Showname"+END_PARAMETER;
		if(Item->Name == "ShowNameLower")
			Value = START_PARAMETER+(String)"showname"+END_PARAMETER;
		if(Item->Name == "ShowNameUpper")
			Value = START_PARAMETER+(String)"SHOWNAME"+END_PARAMETER;
		if(Item->Name == "ShowNameWord")
			Value = START_PARAMETER+(String)"ShowName"+END_PARAMETER;
		if(Item->Name == "SourceShowName")
			Value = START_PARAMETER+(String)"sHowname"+END_PARAMETER;
		if(Item->Name == "SeasonNumber")
			Value = START_PARAMETER+(String)"Season"+END_PARAMETER;
		if(Item->Name == "Season2Digits")
			Value = START_PARAMETER+(String)"Season2"+END_PARAMETER;
		if(Item->Name == "Season3Digits")
			Value = START_PARAMETER+(String)"Season3"+END_PARAMETER;
		if(Item->Name == "EpisodeNumber")
			Value = START_PARAMETER+(String)"Episode"+END_PARAMETER;
		if(Item->Name == "Episode2Digits")
			Value = START_PARAMETER+(String)"Episode2"+END_PARAMETER;
		if(Item->Name == "Episode3Digits")
			Value = START_PARAMETER+(String)"Episode3"+END_PARAMETER;
		if(Item->Name == "ShowTitleFirst")
			Value = START_PARAMETER+(String)"Episodetitle"+END_PARAMETER;
		if(Item->Name == "ShowTitleLower")
			Value = START_PARAMETER+(String)"episodetitle"+END_PARAMETER;
		if(Item->Name == "ShowTitleUpper")
			Value = START_PARAMETER+(String)"EPISODETITLE"+END_PARAMETER;
		if(Item->Name == "ShowTitleWord")
			Value = START_PARAMETER+(String)"EpisodeTitle"+END_PARAMETER;
		if(Item->Name == "SourceShowTitle")
			Value = START_PARAMETER+(String)"ePisodetitle"+END_PARAMETER;

		Output = Input.Insert(Value,ShowFormatEdit->SelStart+1);
		ShowFormatEdit->Text = Output;
		ShowFormatEdit->SelStart += Value.Length();
	}
}
//---------------------------------------------------------------------------
void __fastcall TOutputNameFrame::ShowFormatEditButtonClick(TObject *Sender)
{
	FormatComboBox->Items->Add(ShowFormatEdit->Text);
	FormatComboBox->ItemIndex = FormatComboBox->Items->Count - 1;
}
//---------------------------------------------------------------------------
void __fastcall TOutputNameFrame::FormatComboBoxChange(TObject *Sender)
{
	String Txt = "";
	if(FormatComboBox->Selected)
		Txt = Translator->CreateTVShowName(FormatComboBox->Selected->Text,ShowExample);
	ExampleShowValue->Text = Txt;
}
//---------------------------------------------------------------------------
void __fastcall TOutputNameFrame::ShowFormatComboButtonClick(TObject *Sender)
{
	FormatComboBox->Items->Delete(FormatComboBox->ItemIndex);
	FormatComboBox->ItemIndex = FormatComboBox->Items->Count - 1;
}
//---------------------------------------------------------------------------
void TOutputNameFrame::LoadConfiguration(TNameValue *Conf){
	TConfig_Frame::LoadConfiguration(Conf);
	if(Conf){
		int a = 0;
		FormatComboBox->Clear();
		while(Conf->ValueExist("ShowOutFormat_"+IntToStr(a))){
			FormatComboBox->Items->Add(Conf->GetString("ShowOutFormat_"+IntToStr(a)));
			a++;
		}
		if(Conf->ValueExist("ShowOutFormatIndex"))
			FormatComboBox->ItemIndex = Conf->GetInt("ShowOutFormatIndex");
		else
			FormatComboBox->ItemIndex = 0;
		MovieFormatComboBox->Clear();
		a = 0;
		while(Conf->ValueExist("MovieOutFormat_"+IntToStr(a))){
			MovieFormatComboBox->Items->Add(Conf->GetString("MovieOutFormat_"+IntToStr(a)));
			a++;
		}
		if(Conf->ValueExist("MovieOutFormatIndex")){
			MovieFormatComboBox->ItemIndex = Conf->GetInt("MovieOutFormatIndex");
		}
		else
			MovieFormatComboBox->ItemIndex = 0;

	}
}
//---------------------------------------------------------------------------
void TOutputNameFrame::SaveConfiguration(TNameValue *Conf){
	if(Conf){
		int a = 0;
		Conf->SetInt("ShowOutFormatIndex",FormatComboBox->ItemIndex);
		while(Conf->ValueExist("ShowOutFormat_"+IntToStr(a))){
			Conf->RemoveValue("ShowOutFormat_"+IntToStr(a));
			a++;
		}
		for(a=0;a<FormatComboBox->Count;a++){
			Conf->AddString("ShowOutFormat_"+IntToStr(a),FormatComboBox->Items->Strings[a],"Format for show output name");
		}
		a = 0;
		Conf->SetInt("MovieOutFormatIndex",MovieFormatComboBox->ItemIndex);
		while(Conf->ValueExist("MovieOutFormat_"+IntToStr(a))){
			Conf->RemoveValue("MovieOutFormat_"+IntToStr(a));
			a++;
		}
		for(a=0;a<MovieFormatComboBox->Count;a++){
			Conf->AddString("MovieOutFormat_"+IntToStr(a),MovieFormatComboBox->Items->Strings[a],"Format for movie output name");
		}
	}
}
//---------------------------------------------------------------------------
void TOutputNameFrame::CreateConfiguration(TNameValue *Conf){
	TConfig_Frame::CreateConfiguration(Conf);
	if(Conf){
		Conf->AddInt("ShowOutFormatIndex",0,"Index of format for show output name");
		Conf->AddString("ShowOutFormat_0","<<ShowName>> - <<season2>>x<<episode2>> - <<EpisodeTitle>>","Format for show output name");
		Conf->AddString("ShowOutFormat_1","<<ShowName>> - S<<season2>>e<<episode2>> - <<EpisodeTitle>>","Format for show output name");
		Conf->AddString("ShowOutFormat_2","<<ShowName>> * S<<season2>>e<<episode2>> * <<EpisodeTitle>>","Format for show output name");
		Conf->AddInt("MovieOutFormatIndex",0,"Index of format for movie output name");
		Conf->AddString("MovieOutFormat_0","<<MovieName>> - <<Year>>","Format for movie output name");
		Conf->AddString("MovieOutFormat_1","<<Moviename>> (<<Year>>)","Format for movie output name");
	}
}
//---------------------------------------------------------------------------
void __fastcall TOutputNameFrame::MovieFormatEditButtonClick(TObject *Sender)
{
	MovieFormatComboBox->Items->Add(MovieFormatEdit->Text);
	MovieFormatComboBox->ItemIndex = MovieFormatComboBox->Items->Count - 1;
}
//---------------------------------------------------------------------------
void __fastcall TOutputNameFrame::MovieFormatComboButtonClick(TObject *Sender)
{
	MovieFormatComboBox->Items->Delete(MovieFormatComboBox->ItemIndex);
	MovieFormatComboBox->ItemIndex = MovieFormatComboBox->Items->Count - 1;
}
//---------------------------------------------------------------------------
void __fastcall TOutputNameFrame::MovieFormatComboBoxChange(TObject *Sender)
{
	String Txt = "";
	if(FormatComboBox->Selected){
		Txt = Translator->CreateMovieName(MovieFormatComboBox->Selected->Text,MovieExample);
		ExampleMovieValue->Text = Txt;
	}
}
//---------------------------------------------------------------------------

