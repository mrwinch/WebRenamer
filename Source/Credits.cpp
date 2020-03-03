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
		if(Src->ValueExist(BUILD_ID("Title")) == false)
			Src->AddString(BUILD_ID("Title"),"Credits","Title for credits dialog");
		if(Src->ValueExist(BUILD_ID("OkButton")) == false)
			Src->AddString(BUILD_ID("OkButton"),"Ok","Text for ok button");
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
	}
}
//---------------------------------------------------------------------------
