//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Credits.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm2 *Form2;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "CRTDLG"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TForm2::CreateGUITxt(TNameValue *Src){
	if(Src != NULL){
		Src->AddString(BUILD_ID("Title"),"Credits","Title for credits dialog");
		Src->AddString(BUILD_ID("OkButton"),"Ok","Text for ok button");
		Src->AddString(BUILD_ID("Author"),"Author: ","Text for ok button");
		Src->AddString(BUILD_ID("Contact"),"Contact: ","Text for ok button");
		Src->AddString(BUILD_ID("ProjectURL"),"Web: ","Text for ok button");
		Src->AddString(BUILD_ID("WikiLabel"),"Wiki: ","Text for ok button");
		Src->AddString(BUILD_ID("DescLabel"),"WebRenamer","Text for ok button");
	}
}
//---------------------------------------------------------------------------
void TForm2::ApplyLanguage(TNameValue *Src){
	if(Src){
		String Txt;
		Txt = Src->GetString(BUILD_ID("Title"));
		if(Txt == "")
			Txt = "Credits";
		Caption = Txt;
		Txt = Src->GetString(BUILD_ID("OkButton"));
		if(Txt == "")
			Txt = "Ok";
		Button1->Text = Txt;
		AuthorLabel->Text = Src->GetString(BUILD_ID("Author"))+(String)"Mirko Dall'Armellina";
		ContactLabel->Text = Src->GetString(BUILD_ID("Contact"))+(String)"WebRenamer@gmail.com";
		ProjectUrl->Text = Src->GetString(BUILD_ID("ProjectURL"))+(String)"https://github.com/mrwinch/WebRenamer";
		WikiLabel->Text = Src->GetString(BUILD_ID("WikiLabel"))+(String)"https://github.com/mrwinch/WebRenamer/wiki";
		DescLabel->Text = Src->GetString(BUILD_ID("DescLabel"));
	}
}
//---------------------------------------------------------------------------




