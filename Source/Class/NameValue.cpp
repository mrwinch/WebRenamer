//---------------------------------------------------------------------------
#pragma hdrstop

#include "NameValue.h"
//---------------------------------------------------------------------------
TNameValue::TNameValue(TComponent *AOwner){
	Owner = AOwner;
	Main = new TStringList();
	Main->StrictDelimiter = true;
	Main->Delimiter = LIST_DELIMITER;
}
//---------------------------------------------------------------------------
TNameValue::~TNameValue(){
}
//---------------------------------------------------------------------------
int TNameValue::AddInt(String Name, int Value, String Comment){
	return InternalAdd(Name, IntToStr(Value), OBJ_INT, Comment);
}
//---------------------------------------------------------------------------
int TNameValue::AddBool(String Name, bool Value, String Comment){
	return InternalAdd(Name, BoolToStr(Value), OBJ_BOOL, Comment);
}
//---------------------------------------------------------------------------
int TNameValue::AddFloat(String Name, float Value, String Comment){
	return InternalAdd(Name,FloatToStr(Value), OBJ_FLT, Comment);
}
//---------------------------------------------------------------------------
int TNameValue::AddString(String Name, String Value, String Comment){
	return InternalAdd(Name, Value, OBJ_STR, Comment);
}
//---------------------------------------------------------------------------
int TNameValue::InternalAdd(String Name, String Value, int Type, String Comment){
	int a;
	Value_Info *Info = (Value_Info*)AllocMem(sizeof(Value_Info));
	a = Main->IndexOfName(Name);
	Info->Type = Type;
	Info->Comment = "";
	if(Comment.Length() == 0){
		switch(Type){
			case OBJ_BOOL:{
				Info->Comment = "Boolean value";
			}break;
			case OBJ_INT:{
				Info->Comment = "Integer value";
			}break;
			case OBJ_STR:{
				Info->Comment = "String value";
			}break;
			case OBJ_FLT:{
				Info->Comment = "Float value";
			}break;
		}
	}
	else
		Info->Comment = Comment;
	if(a == -1){
		Main->AddPair(Name, Value, (TObject*)Info);
		//Main->AddPair(SafeEncode(Name), SafeEncode(Value), (TObject*)Info);
		SetComment(Name,Comment);
	}
	else
		return STRING_NAME_EXIST;
	return NAME_VALUE_CORRECT;
}
//---------------------------------------------------------------------------
String TNameValue::GetString(String Name){
	int a = Main->IndexOfName(Name);
	if(a != -1){
		return Main->ValueFromIndex[a];
	}
	return "";
}
//---------------------------------------------------------------------------
float TNameValue::GetFloat(String Name){
	String a = GetString(Name);
	if(a != "")
		return StrToFloat(a);
	return STRING_INVALID_NAME;
}
//---------------------------------------------------------------------------
bool TNameValue::GetBool(String Name){
	String a = GetString(Name);
	if(a != "")
		return StrToBool(a);
	return 0;
}
//---------------------------------------------------------------------------
int TNameValue::GetInt(String Name){
	String a = GetString(Name);
	if(a != ""){
		return StrToInt(a);
	}
	return STRING_INVALID_NAME;
}
//---------------------------------------------------------------------------
bool TNameValue::ValueExist(String Name){
	int a = Main->IndexOfName(Name);
	if(a != -1)
		return true;
    return false;
}
//---------------------------------------------------------------------------
int TNameValue::SetBool(String Name, bool Value){
//	int a;
	if(ValueExist(Name) == false)
		return STRING_INVALID_NAME;
	Main->Values[Name] = BoolToStr(Value);
	return NAME_VALUE_CORRECT;
}
//---------------------------------------------------------------------------
int TNameValue::SetInt(String Name,int Value){
	if(ValueExist(Name) == false)
		return STRING_INVALID_NAME;
	Main->Values[Name] = IntToStr(Value);
	return NAME_VALUE_CORRECT;
}
//---------------------------------------------------------------------------
int TNameValue::SetString(String Name, String Value){
	if(ValueExist(Name) == false)
		return STRING_INVALID_NAME;
	Main->Values[Name] = Value;
	return NAME_VALUE_CORRECT;
}
//---------------------------------------------------------------------------
int TNameValue::SetFloat(String Name, float Value){
	if(ValueExist(Name) == false)
		return STRING_INVALID_NAME;
	Main->Values[Name] = FloatToStr(Value);
	return NAME_VALUE_CORRECT;
}
//---------------------------------------------------------------------------
int TNameValue::SaveToXML(String File){
	_di_IXMLNode Node;
	int a;
	Value_Info *Info;
	TXMLDocument *Doc = new TXMLDocument(Owner);
	Doc->DOMVendor = GetDOMVendor("ADOM XML v4");
	Doc->Active = true;
	Doc->Options = TXMLDocOptions()<<doNodeAutoIndent;
	Doc->DocumentElement = Doc->CreateNode(NAMEVALUE_NODE_NAME,ntElement,"");
	Doc->DocumentElement->SetAttribute("Version",NAMEVALUE_VERSION);
	Doc->DocumentElement->SetAttribute("Class_creator","TNameValue");
	Doc->DocumentElement->SetAttribute("Info","TNameValue class backup");
	for(a=0;a<Main->Count;a++){
		Node = Doc->DocumentElement->AddChild("Value",-1);
		Node->SetAttribute("Name",Main->Names[a]);
		Node->SetAttribute("Value",Main->ValueFromIndex[a]);
		Info = (Value_Info*)Main->Objects[a];
		Node->SetAttribute("Type",IntToStr(Info->Type));
		Node->Text = Info->Comment;
	}
	Doc->SaveToFile(File);

	return 0;
}
//---------------------------------------------------------------------------
void TNameValue::Reset(){
	Main->Clear();
}
//---------------------------------------------------------------------------
int TNameValue::GetNumValue(){
	return Main->Count;
}
//---------------------------------------------------------------------------
String TNameValue::GetValueNameByIndex(int Index){
	if(Index < Main->Count)
		return Main->Names[Index];
	return "";
}
//---------------------------------------------------------------------------
int TNameValue::GetValueTypeByIndex(int Index){
	if(Index < Main->Count){
		int *a = (int*)Main->Objects[Index];
		return *a;
	}
	return STRING_INVALID_NAME;
}
//---------------------------------------------------------------------------
int TNameValue::GetValueType(String Name){
	int a = Main->IndexOfName(Name);
	if(a != -1){
		Value_Info *b = (Value_Info*)Main->Objects[a];
		return b->Type;
	}
	return STRING_INVALID_NAME;
}
//---------------------------------------------------------------------------
int TNameValue::GetValueIndex(String Name){
	int a = Main->IndexOfName(Name);
	if(a != -1){
		return a;
	}
	return STRING_INVALID_NAME;
}
//---------------------------------------------------------------------------
int TNameValue::LoadFromXML(String Name){
	TXMLDocument *Doc = new TXMLDocument(Owner);
	IXMLNode *Node;
	String Tmp;
	String Value;
	int Type;
	String Cmt;
	int a;
	Doc->LoadFromFile(Name);
	Doc->DOMVendor = GetDOMVendor("ADOM XML v4");
    Doc->Active=true;
	if(Doc->DocumentElement->NodeName == NAMEVALUE_NODE_NAME){
		Tmp = Doc->DocumentElement->GetAttribute("Class_creator");
		if(Tmp == "TNameValue"){
			a = Doc->DocumentElement->GetAttribute("Version");
			if(a <= NAMEVALUE_VERSION){
				Reset();
				for(a=0;a<Doc->DocumentElement->ChildNodes->Count;a++){
					Node = Doc->DocumentElement->ChildNodes->Get(a);
					Tmp = Node->GetAttribute("Name");
					Value = Node->GetAttribute("Value");
					Type = Node->GetAttribute("Type");
					Cmt = Node->Text;
					InternalAdd(Tmp,Value,Type,Cmt);
				}
			}
		}
	}
	return NAME_VALUE_CORRECT;
}
//---------------------------------------------------------------------------
int TNameValue::SetComment(String Name, String Comment){
	int a = Main->IndexOfName(Name);
	if(a != -1){
		Value_Info *b = (Value_Info*)Main->Objects[a];
		b->Comment = Comment;
		return NAME_VALUE_CORRECT;
	}
	return STRING_INVALID_NAME;
}
//---------------------------------------------------------------------------
String TNameValue::GetComment(String Name){
	int a = Main->IndexOfName(Name);
	if(a != -1){
		Value_Info *b = (Value_Info*)Main->Objects[a];
		return b->Comment;
	}
	return "";
}
//---------------------------------------------------------------------------
TStringList *TNameValue::GetValues(){
	TStringList *Out = new TStringList();
	for(int a=0;a<Main->Count;a++){
		Out->Add(Main->KeyNames[a]);
	}
	return Out;
}
//---------------------------------------------------------------------------
TNameValue *TNameValue::Clone(TComponent *AOwner){
	TNameValue *Out;
	if(AOwner)
		Out = new TNameValue(AOwner);
	else
        Out = new TNameValue(Owner);
	Value_Info *Info;
	for(int a=0;a<Main->Count;a++){
		Info = (Value_Info*)AllocMem(sizeof(Value_Info));
		Move(Main->Objects[a],Info,sizeof(Value_Info));
		switch(Info->Type){
			case OBJ_BOOL:{
				Out->AddBool(Main->KeyNames[a],StrToBool(Main->ValueFromIndex[a]),Info->Comment);
			}break;
			case OBJ_INT:{
				Out->AddInt(Main->KeyNames[a],StrToInt(Main->ValueFromIndex[a]),Info->Comment);
			}break;
			case OBJ_STR:{
				Out->AddString(Main->KeyNames[a],Main->ValueFromIndex[a],Info->Comment);
			}break;
			case OBJ_FLT:{
				Out->AddFloat(Main->KeyNames[a],StrToFloat(Main->ValueFromIndex[a]),Info->Comment);
			}break;
		};
	}
	return Out;
}
//---------------------------------------------------------------------------
int TNameValue::RemoveValue(String Value){
	int a = Main->IndexOfName(Value);
	if(a != -1){
		FreeMemory(Main->Objects[a]);
		Main->Delete(a);
		return NAME_VALUE_CORRECT;
	}
	return STRING_INVALID_NAME;
}
//---------------------------------------------------------------------------
int TNameValue::UpdateFromSource(TNameValue *Src){
	String Name;
	bool BVal;
	int IVal;
	String SVal;
	float FVal;
	int Type;
	for(int a=0;a<Src->GetNumValue();a++){
		Name = Src->GetValueNameByIndex(a);
		Type = Src->GetValueType(Name);
		RemoveValue(Name);
		switch(Type){
			case OBJ_BOOL:{
				AddBool(Name,Src->GetBool(Name),Src->GetComment(Name));
			}break;
			case OBJ_INT:{
				AddInt(Name,Src->GetInt(Name),Src->GetComment(Name));
			}break;
			case OBJ_STR:{
				AddString(Name,Src->GetString(Name),Src->GetComment(Name));
			}break;
			case OBJ_FLT:{
				AddFloat(Name,Src->GetFloat(Name),Src->GetComment(Name));
			}break;
		};
	}
    return NAME_VALUE_CORRECT;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
