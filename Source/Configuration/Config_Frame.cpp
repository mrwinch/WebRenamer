//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Config_Frame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TConfig_Frame *ConfigFrame;
//---------------------------------------------------------------------------
__fastcall TConfig_Frame::TConfig_Frame(TComponent* Owner)
	: TFrame(Owner)
{
	FTreeNode = NULL;
	FConfig = NULL;
	FLang = NULL;
}
//---------------------------------------------------------------------------
void TConfig_Frame::CreateGUITxt(TNameValue *GUITxt){
}
//---------------------------------------------------------------------------
void TConfig_Frame::ApplyLanguage(TNameValue *Src){

}
//---------------------------------------------------------------------------
TComponent *TConfig_Frame::SearchComponent(String Name){
	TList *Tmp = new TList();
	int a,b;
	Tmp->Add(this);
	TComponent *Cmp;
	a = 0;
	do{
		Cmp = (TComponent*)Tmp->Items[a];
		if(Cmp->Name == Name)
			return Cmp;
		for(b=0;b<Cmp->ComponentCount;b++)
			Tmp->Add(Cmp->Components[b]);
		a++;
	}while(a < Tmp->Count);
	return NULL;
}
//---------------------------------------------------------------------------
void TConfig_Frame::ResizeComponents(){

}
//---------------------------------------------------------------------------
void TConfig_Frame::ApplyLanguage(TNameValue *Src, String Prefix, TStringList *Cmp){
	int a;
	TComponent *Tmp;
	for(a=0;a<Cmp->Count;a++){
		Tmp = SearchComponent(Cmp->Strings[a]);
		if(Tmp){
			if(Tmp->ClassName() == "TLabel")
				((TLabel*)Tmp)->Text = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			if(Tmp->ClassName() == "TButton")
				((TButton*)Tmp)->Text = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			if(Tmp->ClassName() == "TGroupBox")
				((TGroupBox*)Tmp)->Text = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			if(Tmp->ClassName() == "TMenuItem")
				((TMenuItem*)Tmp)->Text = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			if(Tmp->ClassName() == "TTreeViewItem")
				((TTreeViewItem*)Tmp)->Text = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			if(Tmp->ClassName() == "TStringColumn")
				((TStringColumn*)Tmp)->Header = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			if(Tmp->ClassName() == "TCheckColumn")
				((TCheckColumn*)Tmp)->Header = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			if(Tmp->ClassName() == "TCheckBox")
				((TCheckBox*)Tmp)->Text = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			if(Tmp->ClassName() == "TRadioButton")
				((TRadioButton*)Tmp)->Text = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			if(Tmp->ClassName() == "TComboBox"){
				((TComboBox*)Tmp)->Items->StrictDelimiter = true;
				((TComboBox*)Tmp)->Items->DelimitedText = Src->GetString(Prefix+(String)"_"+Tmp->Name);
			}
		}
	}
	Language = Src;
//	ResizeComponents();
}
//---------------------------------------------------------------------------
void TConfig_Frame::LoadConfiguration(TNameValue *Conf){
	Config = Conf;
}
//---------------------------------------------------------------------------
void TConfig_Frame::SaveConfiguration(TNameValue *Conf){
}
//---------------------------------------------------------------------------
void TConfig_Frame::CreateConfiguration(TNameValue *Conf){
	Config = Conf;
}
//---------------------------------------------------------------------------
void TConfig_Frame::SetTreeNode(TTreeViewItem *Item){
	FTreeNode = Item;
}
//---------------------------------------------------------------------------
TTreeViewItem *TConfig_Frame::GetTreeNode(){
	return FTreeNode;
}
//---------------------------------------------------------------------------
void TConfig_Frame::SetConf(TNameValue *Conf){
	FConfig = Conf;
}
//---------------------------------------------------------------------------
TNameValue *TConfig_Frame::GetConf(){
	return FConfig;
}
//---------------------------------------------------------------------------
void TConfig_Frame::SetLang(TNameValue *Lang){
	FLang = Lang;
}
//---------------------------------------------------------------------------
TNameValue *TConfig_Frame::GetLang(){
	return FLang;
}
//---------------------------------------------------------------------------
