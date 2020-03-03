//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "RenameMovie.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TRenameMovieForm *RenameMovieForm;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "RNM_FR"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
__fastcall TRenameMovieForm::TRenameMovieForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TRenameMovieForm::CreateGUITxt(TNameValue *GUITxt){
	GUITxt->AddString(BUILD_ID("MovieLabel"),"Movie: ","Text for movie label");
	GUITxt->AddString(BUILD_ID("ResultLabel"),"Result: ","Text for Result label");
	GUITxt->AddString(BUILD_ID("YearLabel"),"Year: ","Text for year label");
	GUITxt->AddString(BUILD_ID("RenameBox"),"Rename data","Text for rename group box");
	GUITxt->AddString(BUILD_ID("ManualRename"),"Manual rename","Text for manual rename label");
	GUITxt->AddString(BUILD_ID("OkButton"),"Ok","Text for ok button");
	GUITxt->AddString(BUILD_ID("CancelButton"),"Cancel","Text for cancel button");
	GUITxt->AddString(BUILD_ID("FormatLabel"),"Output:","Text for output label");
	GUITxt->AddString(BUILD_ID("DiscLabel"),"Disc:","Text for disc label");
}
//---------------------------------------------------------------------------
void TRenameMovieForm::ApplyLanguage(TNameValue *GUITxt){
	MovieLabel->Text = GUITxt->GetString(BUILD_ID("MovieLabel"));
	ResultLabel->Text = GUITxt->GetString(BUILD_ID("ResultLabel"));
	RenameBox->Text = GUITxt->GetString(BUILD_ID("RenameBox"));
	YearLabel->Text = GUITxt->GetString(BUILD_ID("YearLabel"));
	OkButton->Text = GUITxt->GetString(BUILD_ID("OkButton"));
	CancelButton->Text = GUITxt->GetString(BUILD_ID("CancelButton"));
	FormatLabel->Text = GUITxt->GetString(BUILD_ID("FormatLabel"));
	DiscLabel->Text = GUITxt->GetString(BUILD_ID("DiscLabel"));
	Caption = GUITxt->GetString(BUILD_ID("ManualRename"));
}
//---------------------------------------------------------------------------
void __fastcall TRenameMovieForm::GenericChange(TObject *Sender){
	TNameTranslator *Tmp = new TNameTranslator(this);
	String Txt = "";
	MovieNamedetails Det;
	Det.Title = MovieEdit->Text;
	Det.Year = YearBox->Value;
	Det.Disc = DiscBox->Value;
	if(FormatComboBox->Selected){
		Txt = Tmp->CreateMovieName(FormatComboBox->Selected->Text, Det);
	}
	OutputEdit->Text = Txt;
}
//---------------------------------------------------------------------------

