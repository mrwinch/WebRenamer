#include "ExtStringList.h"
//---------------------------------------------------------------------------
TExtendedStringList::TExtendedStringList():TStringList(){
	StrictDelimiter = true;
	Delimiter = LIST_DELIMITER;
	NameValueSeparator = LIST_EQUALS;
}
//---------------------------------------------------------------------------
TExtendedStringList::~TExtendedStringList(){
	
}
//---------------------------------------------------------------------------
TStrings* __fastcall TExtendedStringList::AddPair(String Name, String Value){
	String a;
	String b;
	a = SafeEncode(Name);
	b = SafeEncode(Value);
	return TStringList::AddPair(a, b);
}
//---------------------------------------------------------------------------
String TExtendedStringList::SafeEncode(String Src){
	String Out = Src;
	Out = ReplaceStr(Out,(String)LIST_DELIMITER,LIST_DELIMITER_REPLACE);
	Out = ReplaceStr(Out,(String)LIST_EQUALS,LIST_EQUALS_REPLACE);
	return Out;
}
//---------------------------------------------------------------------------
String TExtendedStringList::SafeDecode(String Src){
	String Out = Src;
	Out = ReplaceStr(Out,(String)LIST_DELIMITER_REPLACE,LIST_DELIMITER);
	Out = ReplaceStr(Out,(String)LIST_EQUALS_REPLACE,LIST_EQUALS);
	return Out;	
}
//---------------------------------------------------------------------------
TStrings* __fastcall TExtendedStringList::AddPair(String Name, String Value, TObject *AObject){
	String a;
	String b;
	a = SafeEncode(Name);
	b = SafeEncode(Value);
	return TStringList::AddPair(a, b, AObject);
}
//---------------------------------------------------------------------------
int __fastcall TExtendedStringList::IndexOf(String S){
	return TStringList::IndexOf(SafeEncode(S));
}
//---------------------------------------------------------------------------
int __fastcall TExtendedStringList::IndexOfName(String Name){
	return TStringList::IndexOfName(SafeEncode(Name));
}
//---------------------------------------------------------------------------
void __fastcall TExtendedStringList::Insert(int Index, String S){
	TStringList::Insert(Index, SafeEncode(S));
}
//---------------------------------------------------------------------------
void __fastcall TExtendedStringList::InsertObject(int Index, String S, System::TObject* AObject){
	TStringList::InsertObject(Index, SafeEncode(S), AObject);
}
//---------------------------------------------------------------------------
String TExtendedStringList::operator[](int Index){
	return SafeDecode(TStringList::Strings[Index]);
}
//---------------------------------------------------------------------------
String __fastcall TExtendedStringList::ExtGetKeyName(int Index){
	String Tmp = TStringList::KeyNames[Index];
	return SafeDecode(Tmp);
}
//---------------------------------------------------------------------------
String __fastcall TExtendedStringList::ExtGetName(int Index){
	String Tmp = TStringList::Names[Index];
	return SafeDecode(Tmp);	
}
//---------------------------------------------------------------------------
String __fastcall TExtendedStringList::ExtGet(int Index){
	String Out;
	Out = KeyNames[Index]+(String)LIST_DELIMITER+ValueFromIndex[Index];
	return Out;
}
//---------------------------------------------------------------------------
void TExtendedStringList::ExtPut(int Index, String S){
	TStringList::Strings[Index] = SafeEncode(S);
}
//---------------------------------------------------------------------------
String __fastcall TExtendedStringList::ExtGetValueFromIndex(int Index){
	return SafeDecode(TStringList::ValueFromIndex[Index]);
}
//---------------------------------------------------------------------------
void TExtendedStringList::ExtSetValueFromIndex(int Index, String S){
	TStringList::ValueFromIndex[Index] = SafeEncode(S);
}
//---------------------------------------------------------------------------
String TExtendedStringList::ExtGetValue(String Name){
	return SafeDecode(TStringList::Values[Name]);
}
//---------------------------------------------------------------------------
void TExtendedStringList::ExtSetValue(String Name, String S){
	TStringList::Values[SafeEncode(Name)] = SafeEncode(S);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
