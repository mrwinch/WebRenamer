//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "TestForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::RequestCompleted(TObject *Sender, _di_IHTTPResponse  AResponse){

	Memo1->Lines->Add("Response -> "+AResponse->ContentAsString());
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
    ModalResult = mrCancel;
/*	TStringList *List =new TStringList();
	List->AddPair("Name1","Value1");
	List->AddPair("Name2","Value2");
	List->AddPair("Name3","Value3");
	List->Delimiter=';';
	Memo1->Lines->Add(List->DelimitedText);   */
}
//---------------------------------------------------------------------------
void TForm3::CandidateOnForm(String Searched, int SearchID,TList *CandidateList){
	Candidate_Information *Candidate;
	int a;
	String Txt;
	TDate Aerial;
	Memo1->Lines->Clear();
	Memo1->Lines->Add("Original: "+Searched);
	for(a=0;a<CandidateList->Count;a++){
		Candidate = (Candidate_Information*)CandidateList->Items[a];
		Txt = "Candidate "+IntToStr(a+1)+(String)"\n";
		Txt+= "     Name: "+Candidate->Name+(String)"\n";
		Txt+= "     Poster: "+Candidate->Poster+(String)"\n";
		if(Candidate->Aerial != ""){
			if(Candidate->Aerial != "null")
				Aerial = ISO8601ToDate(Candidate->Aerial+(String)"T00:00:00");
		}
		Txt+= "     Aerial: "+Candidate->Aerial+(String)"-"+Aerial.DateString()+(String)"\n";
		Txt+= "     ID: "+Candidate->ID+(String)+"\n";
		Txt+= "     Summary: "+Candidate->Summary+(String)"\n";
		Memo1->Lines->Add(Txt);
	}
}
//---------------------------------------------------------------------------

