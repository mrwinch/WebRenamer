//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SysDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)
#pragma resource ("*.Macintosh.fmx", _PLAT_MACOS)
#pragma resource ("*.Surface.fmx", _PLAT_MSWINDOWS)

TMyDialog *MyDialog;
typedef struct{
	TMsgDlgBtn Btn;
	String Translation;
	String DefaultText;
	int ModalResult;
}InternalButton;

InternalButton FuncButton[]={
	{TMsgDlgBtn::mbYes,"Dialog_Button_Yes","Yes",mrYes},
	{TMsgDlgBtn::mbNo,"Dialog_Button_No","No",mrNo},
	{TMsgDlgBtn::mbOK,"Dialog_Button_Ok","Ok",mrOk},
	{TMsgDlgBtn::mbCancel,"Dialog_Button_Cancel","Cancel",mrCancel},
	{TMsgDlgBtn::mbAbort,"Dialog_Button_Abort","Abort",mrAbort},
	{TMsgDlgBtn::mbRetry,"Dialog_Button_Retry","Retry",mrRetry},
	{TMsgDlgBtn::mbIgnore,"Dialog_Button_Ignore","Ignore",mrIgnore},
	{TMsgDlgBtn::mbAll,"Dialog_Button_All","All",mrAll},
	{TMsgDlgBtn::mbNoToAll,"Dialog_Button_NoToAll","No to all",mrNoToAll},
	{TMsgDlgBtn::mbYesToAll,"Dialog_Button_YesToAll","Yes to all",mrYesToAll},
	{TMsgDlgBtn::mbHelp,"Dialog_Button_Help","Help",mrHelp},
	{TMsgDlgBtn::mbClose,"Dialog_Button_Close","Close",mrClose},
};
//---------------------------------------------------------------------------
int MyShowDialog(String Title, String Msg, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons,
			const System::Uitypes::TMsgDlgBtn ADefaultButton,TNameValue *Data){
	TMyDialog *Dlg = new TMyDialog(Application);
	TStringList *List = new TStringList();
	TButton *Button;
	String Txt;
	bool BVal;
	int W = 0;
	int a;
	Dlg->Caption = Title;
	List->Text = Msg;
	if(List->Count > 1){
		int b;
		for(a=0;a<List->Count;a++){
			b = Dlg->MessageLabel->Canvas->TextWidth(List->Strings[a]);
			if(b > W)
				W = b;
		}
	}
	else
		W = Dlg->MessageLabel->Canvas->TextWidth(Msg);
	Dlg->Width = W + Dlg->Layout1->Width;
	Dlg->MessageLabel->Text = Msg;
	switch(ADialogType){
		case TMsgDlgType::mtError:{
			Dlg->Glyph1->ImageIndex = 1;
			if(Title == "")
				Dlg->Caption = "Error";
		}break;
		case TMsgDlgType::mtConfirmation:{
			Dlg->Glyph1->ImageIndex = 0;
			if(Title == "")
				Dlg->Caption = "Confirmation";
		}break;
		default:{
		};
	}
	for(a=11;a>-1;a--){
		if(AButtons.Contains(FuncButton[a].Btn)){
			Button = new TButton(Dlg->Panel1);
			Button->Parent = Dlg->Panel1;
			Button->ModalResult = FuncButton[a].ModalResult;
			Txt = "";
			if(Data)
				Txt = Data->GetString(FuncButton[a].Translation);
			if(Txt == "")
				Txt = FuncButton[a].DefaultText;
			Button->Text = Txt;
		}
	}
	Dlg->ShowModal();
	return Dlg->ModalResult;
}
//---------------------------------------------------------------------------
__fastcall TMyDialog::TMyDialog(TComponent* Owner)
	: TForm(Owner)
{
	FMessage = "";
}
//---------------------------------------------------------------------------
String TMyDialog::GetMess(){
	return FMessage;
}
//---------------------------------------------------------------------------
void TMyDialog::SetMess(String Msg){
	FMessage = Msg;
}
//---------------------------------------------------------------------------
void __fastcall TMyDialog::FormShow(TObject *Sender)
{
	TStringList *List = new TStringList();
	int W = 0;
	int FixW = 60;
	int Left = 20;
	TButton *Button;
	List->Text = MessageLabel->Text;
	if(List->Count > 1){
		int b;
		for(int a=0;a<List->Count;a++){
			b = MessageLabel->Canvas->TextWidth(List->Strings[a]);
			if(b > W)
				W = b+FixW;
		}
	}
	else
		W = MessageLabel->Canvas->TextWidth(MessageLabel->Text) + FixW;
	if(W > 360)
		W = 360;
	Width = W + Layout1->Width;
	for(int a = 0; a<Panel1->ChildrenCount;a++){
		Button = (TButton*)Panel1->Children->Items[a];
		Button->Position->Y = 8;
		Button->Position->X = Width - (Button->Width + Left);
		Left += Button->Width + 10;
	}
}
//---------------------------------------------------------------------------


