//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Credits.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.Macintosh.fmx", _PLAT_MACOS)

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
		Src->AddString(BUILD_ID("ForumLabel"),"Forum: ","Text for ok button");
		Src->AddString(BUILD_ID("DescLabel"),"WebRenamer is an open source software\
			distributed under GNU GPL v.3 license. \
			For more information, refer to github information page:\
			https://github.com/mrwinch/WebRenamer/blob/master/LICENSE","Text for ok button");
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
		ForumLabel->Text = Src->GetString(BUILD_ID("ForumLabel"))+(String)"https://webrenamer.forumattivo.com/";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ProjectUrlClick(TObject *Sender)
{
#ifdef _Windows
	ShellExecuteA(0, "OPEN", "https://github.com/mrwinch/WebRenamer", NULL, NULL, SW_SHOWNORMAL);
#endif
#ifdef TARGET_OS_MAC
	system(String("open " + String(_sCommand)).c_str());
#endif // Mac
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ContactLabelClick(TObject *Sender)
{
#ifdef _Windows
	ShellExecuteA(0, "OPEN", "mailto:webrenamer@gmail.com", NULL, NULL, SW_SHOWNORMAL);
#endif
}
//---------------------------------------------------------------------------
void __fastcall TForm2::WikiLabelClick(TObject *Sender)
{
#ifdef _Windows
	ShellExecuteA(0, "OPEN", "https://github.com/mrwinch/WebRenamer/wiki", NULL, NULL, SW_SHOWNORMAL);
#endif
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DescLabelClick(TObject *Sender)
{
#ifdef _Windows
	ShellExecuteA(0, "OPEN", "https://github.com/mrwinch/WebRenamer/blob/master/LICENSE", NULL, NULL, SW_SHOWNORMAL);
#endif
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ForumLabelClick(TObject *Sender)
{
#ifdef _Windows
	ShellExecuteA(0, "OPEN", "https://webrenamer.forumattivo.com/", NULL, NULL, SW_SHOWNORMAL);
#endif
}
//---------------------------------------------------------------------------

