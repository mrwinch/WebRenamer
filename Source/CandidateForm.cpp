//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "CandidateForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TCandidateListForm *CandidateListForm;
//---------------------------------------------------------------------------
//#define UNIT_ID                                     "CDD_FR"
//#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
__fastcall TCandidateListForm::TCandidateListForm(TComponent* Owner)
	: TForm(Owner)
{
	Frame = new TCandidateListFrame(this);
	Frame->Form = this;
	Frame->Parent = this;
	Frame->Align = TAlignLayout::Client;
	FInfo = true;
}
//---------------------------------------------------------------------------
void __fastcall TCandidateListForm::ManageCandidateInfo(String Candidate, int SearchID, TList *CandidateList){
	Frame->ManageCandidateInfo(Candidate, SearchID, CandidateList);
	ShowModal();
}
//---------------------------------------------------------------------------
void TCandidateListForm::CreateGUITxt(TNameValue *Txt){
	Frame->CreateGUITxt(Txt);
}
//---------------------------------------------------------------------------
void TCandidateListForm::ApplyLanguage(TNameValue *Txt){
	Frame->ApplyLanguage(Txt);
}
//---------------------------------------------------------------------------
bool TCandidateListForm::GetInfo(){
	return FInfo;
}
//---------------------------------------------------------------------------
void TCandidateListForm::SetInfo(bool Value){
	FInfo = Value;
	if(Frame)
        Frame->TVShowInfo = Value;
}
//---------------------------------------------------------------------------
void __fastcall TCandidateListForm::RefuseButtonClick(TObject *Sender)
{
//	Frame->RefuseButtonClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TCandidateListForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Frame->FormClose(Sender, Action);
}
//---------------------------------------------------------------------------
