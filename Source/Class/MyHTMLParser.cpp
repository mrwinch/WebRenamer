//---------------------------------------------------------------------------
#pragma hdrstop
#include "MyHTMLParser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#ifdef WEB_RENAMER_DEBUG
extern TSysLog *Logger;
#endif
//---------------------------------------------------------------------------
void DEBUG_PRS(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	if(Logger)
		Logger->Report("HTMLPR",NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
/*TStringList *MySplitString(String Source,String StartData, String EndData, bool WithLimits){
	TStringList *Out = new TStringList();
	String Pattern;
	String Tmp;
	TMatchCollection Items;
	TRegEx *RegEx;
	Pattern = Format("%s(.*?)%s",ARRAYOFCONST((StartData,EndData)));
	RegEx = new TRegEx(Pattern,TRegExOptions());
	Items = RegEx->Matches(Source);
	for(int a=0;a<Items.Count;a++){
		Tmp = Items[a].Value;
		if(WithLimits == false){
			Tmp = System::Strutils::AnsiReplaceStr(Tmp,StartData,"");
			Tmp = System::Strutils::AnsiReplaceStr(Tmp,EndData,"");
		}
		Out->Add(Tmp);
	}
	return Out;	
}*/
//---------------------------------------------------------------------------
THTMLNode::THTMLNode(){
	Setup();
}
//---------------------------------------------------------------------------
THTMLNode::THTMLNode(String Start){
	Setup();
	LoadFromString(Start);
	FParent = NULL;
}
//---------------------------------------------------------------------------
THTMLNode::THTMLNode(String Start, THTMLNode *Parent){
	Setup();
	LoadFromString(Start);
	FParent = Parent;
	if(FParent)
		FParent->AddChild(this);
}
//---------------------------------------------------------------------------
THTMLNode::~THTMLNode(){
	
}
//---------------------------------------------------------------------------
String THTMLNode::GetTag(){
	return FTag;
}
//---------------------------------------------------------------------------
void THTMLNode::Setup(){
	FTag = "";
	Child = new TList();
	Attribute = new TStringList();
}
//---------------------------------------------------------------------------
void THTMLNode::LoadFromString(String Src){
	//TStringList *List = MySplitString(Src," "," ",false);
	int a, b ,c;
	String Tmp,Txt;
	String Key,Value;
	int Start,Stop;
	bool First;
	WideChar Ch;
	Attribute->Clear();
	if(Src.Pos(">") > 0)
		Src = Src.SubString(1,Src.Length()-1);
	a = Src.Pos(" ");
	if(a > 0){
		FTag = Src.SubString(1, a);
		FTag = FTag.Trim();
		Tmp = Src.SubString(a + 1, Src.Length() - a);
	}
	else{
		FTag = Src;
		Tmp = Src.SubString(a, Src.Length());
	}
	if(Tmp.Length()){
		if(Tmp.Pos(" ") == 0)
			Tmp = Tmp + (String)" ";
		a = 1;
		Start = a;
		do{
			if(Tmp[a] == '='){
				Key = Tmp.SubString(Start, a - Start);
			}
			if(Tmp[a] == '"' || Tmp[a]=='\''){
				b = a + 1;
				do{
					b++;
				}while(b <= Tmp.Length() && Tmp[b] != '"' && Tmp[b] != '\'');
				if(b<=Tmp.Length()){
					Value = Tmp.SubString(a + 1, b - a - 1);
					Attribute->AddPair(Key.Trim(), Value.Trim());
				}
				a = b;
				Start = a + 1;
			}
			a++;
		}while(a < Tmp.Length());
	}
}
//---------------------------------------------------------------------------
String THTMLNode::GetClass(){
	String Out = Attribute->Values["class"];
	Out = System::Strutils::AnsiReplaceStr(Out,"\"","");
	return Out;
}
//---------------------------------------------------------------------------
String THTMLNode::GetID(){
	String Out = Attribute->Values["id"];
	Out = System::Strutils::AnsiReplaceStr(Out,"\"","");
	return Out;
}
//---------------------------------------------------------------------------
int THTMLNode::GetNumAttribute(){
	return Attribute->Count;
}
//---------------------------------------------------------------------------
String THTMLNode::GetAttributeName(int Index){
	if(Index<Attribute->Count)
		return Attribute->Names[Index];
	else
		return "";
}
//---------------------------------------------------------------------------
String THTMLNode::GetAttributeValue(int Index){
	if(Index<Attribute->Count){
		String Out = Attribute->ValueFromIndex[Index];
		Out = System::Strutils::AnsiReplaceStr(Out,"\"","");
		return Out;
	}
	else
		return "";
}
//---------------------------------------------------------------------------
String THTMLNode::GetAttribute(){
	String Out;
	for(int a=0;a<GetNumAttribute();a++){
		if(a != 0)
			Out = Out+(String)":";
		Out = Out +QUOTE_STRING(GetAttributeName(a))+(String)"-"+QUOTE_STRING(GetAttributeValue(a));
	}
	return Out;
}
//---------------------------------------------------------------------------
void THTMLNode::AddChild(THTMLNode *ChildNode){
	Child->Add(ChildNode);
}
//---------------------------------------------------------------------------
int THTMLNode::GetNumChild(){
	return Child->Count;
}
//---------------------------------------------------------------------------
THTMLNode *THTMLNode::GetChild(int Index){
	if(Index < GetNumChild())
		return (THTMLNode*)Child->Items[Index];
	return NULL;
}
//---------------------------------------------------------------------------
void THTMLNode::SetText(String Txt){
	FText = Txt;
}
//---------------------------------------------------------------------------
String THTMLNode::GetText(){
	return FText;
}
//---------------------------------------------------------------------------
TagPosition THTMLNode::GetPosition(){
	return FPosition;
}
//---------------------------------------------------------------------------
void THTMLNode::SetPosition(TagPosition Pos){
	FPosition = Pos;
}
//---------------------------------------------------------------------------
THTMLNode *THTMLNode::GetParent(){
	return FParent;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TMyHTMLParser::TMyHTMLParser(){
	NodeList = new TList();
	SingleTag = new TStringList();
	
	SingleTag->Add("meta");
	SingleTag->Add("link");
	SingleTag->Add("area");
	SingleTag->Add("base");
	SingleTag->Add("basefont");
	SingleTag->Add("br");
	SingleTag->Add("embed");
	SingleTag->Add("frame");
	SingleTag->Add("hr");	
	SingleTag->Add("img");	
	SingleTag->Add("input");	
	SingleTag->Add("param");
	SingleTag->Add("source");
	SingleTag->Add("track");
	SingleTag->Add("wbr");
}
//---------------------------------------------------------------------------
TMyHTMLParser::~TMyHTMLParser(){
	
}
//---------------------------------------------------------------------------
TStringList *TMyHTMLParser::SplitString(String Source, bool WithLimits){
	String Txt;
	int a;
	int Start,Stop;
	int Row = 0;
	bool HasSpace;
	TStringList *Out = new TStringList();
	TagPosition *Position;
	Txt = "";
	for(a=1;a<Source.Length();a++){
		switch(Source[a]){
			case '<':{
				Position = (TagPosition*)AllocMem(sizeof(TagPosition));
				Start = a;
				HasSpace = false;
				Position->Start = Start;
				Position->StartRow = Row;
			}break;
			case '>':{
				Stop = a;
				if(HasSpace)
					Txt = Source.SubString(Start,Stop-Start + 1);
				else
					Txt = Source.SubString(Start,Stop-Start);
				if(WithLimits == false){
					Txt = Txt.SubString(2,Txt.Length()-1);
				}
				Position->Stop = Stop;
				Position->EndRow = Row;
				Out->AddObject(Txt,(TObject*)Position);
			}break;
			case ' ':{
				HasSpace = true;
			}break;
			case '\n':{
				Row++;
			}break;
		}
	}
	return Out;
	//return MySplitString(Source,"<",">",WithLimits);
}
//---------------------------------------------------------------------------
int TMyHTMLParser::LoadFromString(String Src){
	DEBUG_PRS(INFO_DEBUG,"LoadFromString()");
	int a;
	int b;
	bool HasComplete;
	THTMLNode *Node, *Dad;
	TagPosition *Pos1, *Pos2;
	TagPosition *SrcPos;
	String TxtNode;
	String Tag;
	String Str;
	TList *Internal = new TList();
	TStringList *Temp = SplitString(Src, false);		//Split tag without '<' and '>'
	NodeList->Clear();
	for(a = 0; a< Temp->Count;a++){
		TxtNode = Temp->Strings[a].Trim();
		SrcPos = (TagPosition*)Temp->Objects[a];
        Str = Temp->Strings[a];
		if(TxtNode.Pos("/") != 1){
			if(Internal->Count)
				Dad = (THTMLNode*)Internal->Last();
			else
				Dad = NULL;
			Node = new THTMLNode(Temp->Strings[a], Dad);
			Node->Position = *SrcPos;
			NodeList->Add(Node);
			if(SingleTag->IndexOf(Node->Tag.LowerCase()) == -1){	//No </...>
				if(TxtNode.Pos("!") != 1)
					Internal->Add(Node);
			}
			DEBUG_PRS(TOTAL_DEBUG,Str.StringOfChar(' ',Internal->Count)+Node->Tag+(String)"*"+Node->GetAttribute());
		}
		else{
			b = TxtNode.Pos(" ");
			if(b)
				Tag = TxtNode.SubString(2, b);
			else
				Tag = TxtNode.SubString(2, TxtNode.Length());
			Node = (THTMLNode*)Internal->Last();
			if(Node){
				if(Node->Tag == Tag){
					if(SrcPos->Start != Node->Position.Stop + 1){
						Node->Text = Src.SubString(Node->Position.Stop + 1, SrcPos->Start-(Node->Position.Stop + 1));
					}
					DEBUG_PRS(TOTAL_DEBUG,Str.StringOfChar(' ',Internal->Count)+(String)"/"+Node->Tag);
					Internal->Delete(Internal->Count - 1);
				}
				else{		//ERROR!!!!

				}
			}
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
int TMyHTMLParser::LoadFromFile(String FileName){
//	TStringStream *Stream = new TStringStream("");
//	Stream->LoadFromFile(FileName);
//	return LoadFromString(Stream->DataString);
	return 0;
}
//---------------------------------------------------------------------------
/*String TMyHTMLParser::MultipleBack(int Num){
	UnicodeString Str;
	return Str.StringOfChar(' ',Num);
}*/
//---------------------------------------------------------------------------
#pragma package(smart_init)