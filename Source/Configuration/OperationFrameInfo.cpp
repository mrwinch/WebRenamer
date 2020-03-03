//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "OperationFrameInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TOperationFrame *OperationFrame;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "CFG_OF"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
//---------------------------------------------------------------------------
extern TSysLog *Logger;
//---------------------------------------------------------------------------
void DEBUG_CFGOF(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report(UNIT_ID,NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
__fastcall TOperationFrame::TOperationFrame(TComponent* Owner)
	: TFrame(Owner)
{
	OperationNameLabel = "Name:";
	UrlLabelValue = "Url:";
	DataLabelValue = "Data:";
	OperationAnswerLabelValue = "Exp. answer:";
	OperationMethodLabelValue = "Method:";
	OperationMethodComboItems = "GET,POST";
	OperationAnswerManagerLabelValue = "Answer\nmanager:";
}
//---------------------------------------------------------------------------
void __fastcall TOperationFrame::ResizeComponents(){
	UrlLabel->Text = UrlLabelValue;
	UrlLabel->Width = UrlLabel->Canvas->TextWidth(UrlLabel->Text);
	DataLabel->Text = DataLabelValue;
	DataLabel->Width = DataLabel->Canvas->TextWidth(DataLabel->Text);
	OperationMethodLabel->Text = OperationMethodLabelValue;
	OperationMethodLabel->Width = OperationMethodLabel->Canvas->TextWidth(OperationMethodLabel->Text);
	OperationMethodComboBox->Items->StrictDelimiter = true;
	OperationMethodComboBox->Items->DelimitedText = OperationMethodComboItems;
	OperationAnswerLabel->Text = OperationAnswerLabelValue;
	OperationAnswerLabel->Width = OperationAnswerLabel->Canvas->TextWidth(OperationAnswerLabel->Text);
	AnswerManagerLabel->Text = OperationAnswerManagerLabelValue;
	AnswerManagerLabel->Width = AnswerManagerLabel->Canvas->TextWidth(AnswerManagerLabel->Text);
}
//---------------------------------------------------------------------------
void __fastcall TOperationFrame::ApplyOperation(Net_Operation Op){
	CopyNet_Operation(&Op,&Operation);
	UrlMemo->Text = Op.Url;
	DataMemo->Text = Op.Data;
	OperationAnswerBox->Value = Op.ExpectedAnswer;
	OperationMethodComboBox->ItemIndex = Op.MethodType == METHOD_POST?1:(Op.MethodType == METHOD_GET?0:-1);
	AnswerManagerMemo->Text = Op.AnswerManager;
}
//---------------------------------------------------------------------------
void __fastcall TOperationFrame::GenericChange(TObject *Sender){
	Net_Operation Tmp;
	CopyNet_Operation(&Operation, &Tmp);
	TComponent *C = (TComponent*)Sender;
	if(C->Name == "UrlMemo"){
		Tmp.Url = UrlMemo->Text;
	}
	else{
		if(C->Name == "DataMemo"){
			Tmp.Data = DataMemo->Text;
		}
		else{
			if(C->Name == "OperationAnswerBox"){
				Tmp.ExpectedAnswer = OperationAnswerBox->Value;
			}
			else{
				if(C->Name == "OperationMethodComboBox"){
					Tmp.MethodType = OperationMethodComboBox->ItemIndex == 0 ? METHOD_GET :(OperationMethodComboBox->ItemIndex == 1?METHOD_POST:METHOD_UNK);
				}
				else{
					if(C->Name == "AnswerManagerMemo"){
						Tmp.AnswerManager = AnswerManagerMemo->Text;
					}
                }
            }
        }
    }
	CommandList *Cmd = (CommandList*)TagObject;
	if(Cmd){
		Cmd->ChangeOperation(Operation, Tmp);
		Operation = Tmp;
	}
}
//---------------------------------------------------------------------------
void __fastcall TOperationFrame::CreateGUITxt(TNameValue *GUI){
	GUI->AddString(BUILD_ID("OperationNameLabel"),"Name:","Test operation popup menu");
	GUI->AddString(BUILD_ID("UrlLabelValue"),"Url:","Test operation popup menu");
	GUI->AddString(BUILD_ID("DataLabelValue"),"Data:","Test operation popup menu");
	GUI->AddString(BUILD_ID("OperationAnswerLabelValue"),"Exp. answer:","Test operation popup menu");
	GUI->AddString(BUILD_ID("OperationMethodLabelValue"),"Method:","Test operation popup menu");
	GUI->AddString(BUILD_ID("OperationMethodComboItems"),"GET,POST","Test operation popup menu");
	GUI->AddString(BUILD_ID("OperationAnswerManagerLabelValue"),"Answer manager:","Test operation popup menu");
}
//---------------------------------------------------------------------------
void __fastcall TOperationFrame::ApplyLanguage(TNameValue *GUI){
	OperationNameLabel = GUI->GetString(BUILD_ID("OperationNameLabel"));
	UrlLabelValue = GUI->GetString(BUILD_ID("UrlLabelValue"));
	DataLabelValue = GUI->GetString(BUILD_ID("DataLabelValue"));
	OperationAnswerLabelValue = GUI->GetString(BUILD_ID("OperationAnswerLabelValue"));
	OperationMethodLabelValue = GUI->GetString(BUILD_ID("OperationMethodLabelValue"));
	OperationMethodComboItems = GUI->GetString(BUILD_ID("OperationMethodComboItems"));
	OperationAnswerManagerLabelValue = GUI->GetString(BUILD_ID("OperationAnswerManagerLabelValue"));
	ResizeComponents();
}
//---------------------------------------------------------------------------


