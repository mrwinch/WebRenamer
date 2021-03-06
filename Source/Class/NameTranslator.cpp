//---------------------------------------------------------------------------

#pragma hdrstop

#define WEB_RENEMER_DEBUG
#include "NameTranslator.h"
//---------------------------------------------------------------------------
#ifdef WEB_RENEMER_DEBUG
extern TSysLog *Logger;
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void DEBUG_TRL(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report("TrlTor",NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
String UpperFirstLetter(String Source){
	String a,b;
	a = Source.SubString(1,1);
	b = Source.SubString(2,Source.Length());
	return a.UpperCase()+b.LowerCase();
}
//---------------------------------------------------------------------------
String WordUpperFirstLetter(String Source){
	String Out;
	int a;
	TStringList *Tmp = new TStringList();
	Tmp->StrictDelimiter = true;
	Tmp->Delimiter = ' ';
	Tmp->DelimitedText = Source;
	Out = "";
	for(a = 0;a<Tmp->Count;a++){
		Out = Out + UpperFirstLetter(Tmp->Strings[a])+" ";
	}
	if(Out.Length()>1)
		Out = Out.SubString(1,Out.Length()-1);
	return Out;
}
//---------------------------------------------------------------------------
TNameTranslator::TNameTranslator(TComponent *AOwner){
	IgnoreParenthesys = true;
	IgnoreSquareBrackets = true;
	IgnoreCurlyBrackets = true;
    RemoveAfterSeparator = true;
	ReplaceList = new TStringList();
	Owner = AOwner;
	if(Owner != NULL)
		DEBUG_TRL(TOTAL_DEBUG,"Created TNameTranslator: owner "+Owner->Name);
	else
		DEBUG_TRL(TOTAL_DEBUG, "Created TNameTranslator: null owner");
	AddToReplaceList("."," ");
	RemoveTextAfterParenthesys = true;
}
//---------------------------------------------------------------------------
TNameTranslator::~TNameTranslator(){

}
//---------------------------------------------------------------------------
void TNameTranslator::SetParenthesys(bool YN){
	FIgnoreParenthesys = YN;
}
//---------------------------------------------------------------------------
bool TNameTranslator::GetParenthesys(){
	return FIgnoreParenthesys;
}
//---------------------------------------------------------------------------
void TNameTranslator::SetSquareBrackets(bool YN){
	FIgnoreSquareBrackets = YN;
}
//---------------------------------------------------------------------------
bool TNameTranslator::GetSquareBrackets(){
	return FIgnoreSquareBrackets;
}
//---------------------------------------------------------------------------
void TNameTranslator::SetCurlyBrackets(bool YN){
	FIgnoreCurlyBrackets = YN;
}
//---------------------------------------------------------------------------
bool TNameTranslator::GetCurlyBrackets(){
	return FIgnoreCurlyBrackets;
}
//---------------------------------------------------------------------------
void TNameTranslator::AddToReplaceList(String From, String To, bool IgnoreCase, bool Active){
	unsigned char *Info;
	Info = (unsigned char*)AllocMem(1);
	*Info = IgnoreCase + (Active?2:0);
	ReplaceList->AddPair(From, To,(TObject*)Info);
}
//---------------------------------------------------------------------------
Episode_Info TNameTranslator::TranslateEpisode(String OriginalName){
	Episode_Info Out;
	Episode_Order *Data;
	String Tmp, A, B;
	TStringList *Res;
	int a;
	unsigned char *IgnoreCase;
	DEBUG_TRL(INFO_DEBUG,"TranslateEpisode -> "+QUOTE_STRING(OriginalName));
	Out.OriginalName = OriginalName;
	Out.NameCandidate = new TStringList();
	Out.Order.Season = UNK_SEASON;
	Out.Order.Episode = UNK_EPISODE;
	Out.Order.Order_Start = -1;
	Out.Order.Order_End = -1;
	Tmp = OriginalName;
	//First of all: store file extension and delete path + extension from name...
	Out.FileExtension = System::Ioutils::TPath::GetExtension(Tmp);
	Tmp = System::Ioutils::TPath::GetFileNameWithoutExtension(Tmp);
	//Now filter name...
//	A = Tmp;
	Tmp = FilterFile(Tmp);
	//Search for episode order...
	Data = ScanForEpisodeOrder(Tmp);
	if(FRemoveSep){
		Tmp = RemoveSeparator(Tmp);
/*		a = Tmp.Pos("-");
		if(a>0)
			Tmp = Tmp.SubString(1,a-1);  */
	}
	Out.Order = *Data;
	//Ok: let's see for name tv serie name and possible episode title...
	if(Out.Order.Season != UNK_SEASON){
		//Possible serie name...
		A = Tmp.SubString(1, Out.Order.Order_Start - 1);
		A = CleanString(A);
		Out.NameCandidate->Add(A);
		//... and suggested title
		B = Tmp.SubString(Out.Order.Order_End + 1, Tmp.Length());
		Out.SuggestedTitle = B;
		DEBUG_TRL(TOTAL_DEBUG,"Show: "+QUOTE_STRING(A)+(String)" - Episode: "+IntToStr(Out.Order.Season)+
				(String)"x"+IntToStr(Out.Order.Episode)+(String)" - Title: "+QUOTE_STRING(B));
	}
	else
		DEBUG_TRL(WARN_DEBUG,"Unable to find show season");
	return Out;
}
//---------------------------------------------------------------------------
Episode_Order *TNameTranslator::ScanForEpisodeOrder(String FileName){
	Episode_Order *Out = (Episode_Order*)AllocMem(sizeof(Episode_Order));
	TStringList *Res, *Res2;
	String Tmp,A,B,C;
	int a,b,c,d,e;
	Out->Season = UNK_SEASON;
	Out->Episode = UNK_EPISODE;
	Out->Order_End = -1;
	Out->Order_Start = -1;
	//First: work with lowercase name
	Tmp = FileName.LowerCase();
	//Then start to search letter 's' for something like 'sxxeyy' where xx and yy
	//are numbers...
	Res = new TStringList();
	Res->StrictDelimiter = true;
	Res->Delimiter = ' ';
	Res->DelimitedText = Tmp;
	for(a=0;a<Res->Count;a++){
		A = Res->Strings[a];
		c = A.Pos("s");
		if(c == 1){    //sxxeyy format?
			b = A.Pos("e");
			if(b > 0){        //Ok!
				B = A.SubString(2, b-2);
				d = PickNumber(B);
				if(d != -1){
					Out->Season = d;
					Out->Order_Start = Tmp.Pos(A) - 1;
					B = A.SubString(b+1, A.Length());
					d = PickNumber(B);
					if(d != -1){
						Out->Episode = d;
						Out->Order_End = Tmp.Pos(A)+A.Length();
						return Out;
					}
				}
			}
		}
		c = A.Pos("x");
		if(c > 0){
			B = A.SubString(1,c - 1);
			d = PickNumber(B);
			if(d != -1){
				Out->Season = d;
				Out->Order_Start = Tmp.Pos(A) - 1;
				B = A.SubString(c+1,A.Length());
				d = PickNumber(B);
				Out->Episode = d;
				Out->Order_End = Tmp.Pos(A)+A.Length();
				return Out;
            }
		}
	}
	//Last chance: search for a number...
	for(a=1;a<Tmp.Length();a++){
		b = 0;
		if(IsDigit(Tmp[a])){
			if(a==1)
				b = 1;
			else{
				if(IsLetterOrDigit(Tmp[a-1]) == false)
					b = 1;
			}
			if(b){
				c = PickNumber(Tmp.SubString(a,Tmp.Length()));
				if(c != -1){
					Out->Episode = c;
					Out->Season = 1;
					Out->Order_Start = a - 1;
					Out->Order_End = Tmp.Length();
					return Out;
				}
			}
		}
	}
	return Out;
}
//---------------------------------------------------------------------------
void TNameTranslator::SetitemCase(String Item, bool IgnoreCase){
	int Index = ReplaceList->IndexOfName(Item);
	if(Index > -1){
		int *Obj = (int*)ReplaceList->Objects[Index];
		*Obj = (*Obj & 2)+(IgnoreCase?1:0);
	}
}
//---------------------------------------------------------------------------
bool TNameTranslator::GetItemCase(String Item){
	int Index = ReplaceList->IndexOfName(Item);
	if(Index > -1){
		int *Obj = (int*)ReplaceList->Objects[Index];
		return (*Obj&1?true:false);
	}
	return true;
}
//---------------------------------------------------------------------------
void TNameTranslator::SetitemActive(String Item, bool Active){
	int Index = ReplaceList->IndexOfName(Item);
	if(Index > -1){
		int *Obj = (int*)ReplaceList->Objects[Index];
		*Obj = (*Obj & 1)+(Active?2:0);
	}
}
//---------------------------------------------------------------------------
bool TNameTranslator::GetItemActive(String Item){
	int Index = ReplaceList->IndexOfName(Item);
	if(Index > -1){
		int *Obj = (int*)ReplaceList->Objects[Index];
		return (*Obj&2?true:false);
	}
	return true;
}
//---------------------------------------------------------------------------
String TNameTranslator::GetItem(int Index){
	if(Index > -1){
		if(Index < ReplaceList->Count){
			return ReplaceList->KeyNames[Index];
		}
	}
	return "";
}
//---------------------------------------------------------------------------
int TNameTranslator::GetNumReplaceItems(){

	return ReplaceList->Count;
}
//---------------------------------------------------------------------------
String TNameTranslator::ExportIgnoreList(){
	String Out = "";
	int *Obj;
	for(int a=1;a<ReplaceList->Count;a++){
		Obj = (int*)ReplaceList->Objects[a];
		if(ReplaceList->Values[a]==""){
/*			if(Out.Length()>0)
				Out = Out+",";*/
			Out = Out + ReplaceList->KeyNames[a]+IntToStr(*Obj)+(String)",";
		}
	}
	if(Out.Length() > 0){
		if(RightStr(Out,1) == ",")
			Out = LeftStr(Out,Out.Length()-1);
	}
	return Out;
}
//---------------------------------------------------------------------------
void TNameTranslator::AddToIgnoreList(String Txt, bool IgnoreCase, bool Active){
	AddToReplaceList(Txt,"",IgnoreCase,Active);
}
//---------------------------------------------------------------------------
void TNameTranslator::ImportIgnoreList(String List){
	TStringDynArray Array;
	int b;
	String Item;
	ReplaceList->Clear();
	AddToIgnoreList(".",true,true);
	Array = SplitString(List,",");
	for(int a=0;a<Array.Length;a++){
		Item = Array[a];
		b = StrToIntDef(RightStr(Item,1),-1);
		Item = LeftStr(Item,Item.Length()-1);
		if(b != -1)
			AddToIgnoreList(Item,(b&1)?true:false,(b&2)?true:false);
	}
}
//---------------------------------------------------------------------------
TStringList *TNameTranslator::EnumTextInside(String Source, String Start, String End, bool IncludeLimits){
	TStringList *Out = new TStringList();
	String Pattern;
	String Tmp;
	TMatchCollection Items;
	TRegEx *RegEx;
	Pattern = Format("%s(.*?)%s",ARRAYOFCONST((Start,End)));
	RegEx = new TRegEx(Pattern,TRegExOptions());
	Items = RegEx->Matches(Source);
	for(int a=0;a<Items.Count;a++){
		Tmp = Items[a].Value;
		if(IncludeLimits == false){
			Tmp = System::Strutils::AnsiReplaceStr(Tmp,Start,"");
			Tmp = System::Strutils::AnsiReplaceStr(Tmp,End,"");
		}
		Out->Add(Tmp);
	}
	return Out;
}
//---------------------------------------------------------------------------
int TNameTranslator::PickNumber(String Value, int DefValue){
	int Out = 0;
	int a;
	a = 1;
	//if(Value[a]<='0' && Value[a]>='9')
	if(IsDigit(Value[a]) == false)
		return DefValue;
	do{
		Out *=10;
		Out = Out + (Value[a] - '0');
		a++;
		if(a > Value.Length())
			break;
	}while(Value[a]>='0' && Value[a]<='9');
	return Out;
}
//---------------------------------------------------------------------------
String TNameTranslator::CreateTVShowName(String Format, TVShowNameDetails Details){
	DEBUG_TRL(INFO_DEBUG,"CreateTVShowName(): Format "+QUOTE_STRING(Format));
	String Out;
	String Tmp;
	int a, b;
	bool Found;
	Out = Format;
	TStringList *Data = EnumTextInside(Format, START_PARAMETER, END_PARAMETER, false);
	for(a=0;a<Data->Count;a++){
		Found = false;
		if(Data->Strings[a]=="sHowname"){
			Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Details.ShowName);
			Found = true;
		}
		if(Data->Strings[a]=="Showname"){
			Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),UpperFirstLetter(Details.ShowName));
			Found = true;
		}
		if(Found == false){
			if(Data->Strings[a]=="showname"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Details.ShowName.LowerCase());
				Found = true;
			}
		}
		if(Found == false){
			if(Data->Strings[a]=="SHOWNAME"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Details.ShowName.UpperCase());
				Found = true;
			}
		}
		if(Found == false){
			if(Data->Strings[a]=="ShowName"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),WordUpperFirstLetter(Details.ShowName));
				Found = true;
			}
		}
		if(Found == false){
			if(Data->Strings[a]=="ePisodetitle"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Details.EpisodeTitle);
				Found = true;
			}
		}
		if(Found == false){
			if(Data->Strings[a]=="Episodetitle"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),UpperFirstLetter(Details.EpisodeTitle));
				Found = true;
			}
		}
		if(Found == false){
			if(Data->Strings[a]=="episodetitle"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Details.EpisodeTitle.LowerCase());
				Found = true;
			}
		}
		if(Found == false){
			if(Data->Strings[a]=="EPISODETITLE"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Details.EpisodeTitle.UpperCase());
				Found = true;
			}
		}
		if(Found == false){
			if(Data->Strings[a]=="EpisodeTitle"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),WordUpperFirstLetter(Details.EpisodeTitle));
				Found = true;
			}
		}
		if(Found == false){
			Tmp = Data->Strings[a].LowerCase();
			if(Tmp.Pos("episode") == 1){
				if(Tmp.Length()>7){
					Tmp = Tmp.SubString(8,Tmp.Length());
					b = PickNumber(Tmp);
					if(b != -1){
						Tmp = "%."+IntToStr(b)+"d";
						Tmp = System::Sysutils::Format(Tmp,ARRAYOFCONST((Details.Episode)));
					}
					else
						Tmp = System::Sysutils::Format("%d",ARRAYOFCONST((Details.Episode)));
					Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Tmp);
				}
				else
					Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),IntToStr(Details.Episode));
				Found = true;
			}
			if(Found == false){
				if(Tmp.Pos("season") == 1){
					if(Tmp.Length()>6){
						Tmp = Tmp.SubString(7,Tmp.Length());
						b = PickNumber(Tmp);
						if(b != -1){
							Tmp = "%."+IntToStr(b)+"d";
							Tmp = System::Sysutils::Format(Tmp,ARRAYOFCONST((Details.Season)));
						}
						else
							Tmp = System::Sysutils::Format("%d",ARRAYOFCONST((Details.Season)));
						Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Tmp);
					}
					else
						Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),IntToStr(Details.Season));
					Found = true;
				}
			}
		}
	}
	Out = System::Strutils::AnsiReplaceStr(Out,":"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"\\"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"/"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"*"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"?"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"<"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,">"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"|"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"\""," ");
	DEBUG_TRL(TOTAL_DEBUG,"Result: "+QUOTE_STRING(Out));
	return Out;
}
//---------------------------------------------------------------------------
Movie_Info TNameTranslator::TranslateMovie(String Movie){
	DEBUG_TRL(INFO_DEBUG,"TranslateMovie -> "+QUOTE_STRING(Movie));
	Movie_Info Out;
	String Tmp;
//	TStringList *Res;
	int a;
	Out.Year = 0;
	Tmp = Movie;
	//First of all: store file extension and delete path + extension from name...
	Out.FileExtension = System::Ioutils::TPath::GetExtension(Tmp);
	Tmp = System::Ioutils::TPath::GetFileNameWithoutExtension(Tmp);
	//Search for a year...
	a = FindYear(Tmp);
	if(a != 0)
		Out.Year = a;
	else
		Out.Year = 0;
	Tmp = FilterFile(Tmp);
	a = FindDisc(Movie);
	if(FRemoveSep){
        Tmp = RemoveSeparator(Tmp);
/*		a = Tmp.Pos("-");
		if(a>0)
			Tmp = Tmp.SubString(1,a-1);*/
	}
	if(a > 0)
		Out.Disc = a;
	else
        Out.Disc = 0;
	Tmp = CleanString(Tmp);
	Out.Name = Tmp;//Tmp.Trim();
	return Out;
}
//---------------------------------------------------------------------------
int TNameTranslator::FindYear(String Src){
	int Out = 0;
	int Tmp;
	for(int a=1;a<Src.Length();a++){
		if(IsDigit(Src[a])){
			Tmp = PickNumber(Src.SubString(a, Src.Length()), 0);
			if(Tmp != 0){
				if(Tmp > 1800 && Tmp < 2030)
					return Tmp;
			}
		}
	}
	return Out;
}
//---------------------------------------------------------------------------
bool TNameTranslator::IsDigit(WideChar c){
	if(c>='0' && c <='9')
		return true;
	return false;
}
//---------------------------------------------------------------------------
String TNameTranslator::FilterFile(String File){
	String Tmp, A, B;
	TStringList *Res;
	int a;
	int b = -1;;
	unsigned char *IgnoreCase;	
	Tmp = File;
	//Now remove contenent beetween bracket and parenthesys/brackets (if request)
	if(IgnoreParenthesys){
		A = Tmp;
		Res = EnumTextInside(A,"\\(","\\)");
		for(a=0;a<Res->Count;a++){
			if(FRemoveText)
				b = Tmp.Pos(Res->Strings[a]);
			Tmp = ReplaceText(Tmp, Res->Strings[a],"");
			if(b > MINIMUM_PAR_TEXT)
				Tmp = Tmp.SubString(1, b);
		}
	}
	if(IgnoreSquareBrackets){
		A = Tmp;
		Res = EnumTextInside(A,"\\[","\\]");
		for(a=0;a<Res->Count;a++){
			if(FRemoveText)
				b = Tmp.Pos(Res->Strings[a]);
			Tmp = ReplaceText(Tmp, Res->Strings[a],"");
			if(b > MINIMUM_PAR_TEXT)
				Tmp = Tmp.SubString(1, b);
		}
	}
	if(IgnoreCurlyBrackets){
		A = Tmp;
		Res = EnumTextInside(A,"{","}");
		for(a=0;a<Res->Count;a++){
			if(FRemoveText)
				b = Tmp.Pos(Res->Strings[a]);
			Tmp = ReplaceText(Tmp, Res->Strings[a],"");
			if(b > MINIMUM_PAR_TEXT)
				Tmp = Tmp.SubString(1, b);
		}
	}
	A = Tmp;
	//Now: replace strings in ReplaceList with '.'...
	for(a = 0; a < ReplaceList->Count; a++){
		A = ReplaceList->Names[a];
		if(A.Pos(".") != 1){
			B = ReplaceList->Values[A];
			IgnoreCase = (unsigned char*)ReplaceList->Objects[a];
			if(*IgnoreCase)
				Tmp = ReplaceText(Tmp, A, B);
			else
				Tmp = ReplaceStr(Tmp, A, B);
		}
	}
	//Now replace '.' with space...
	Tmp = ReplaceText(Tmp,"."," ");
	//Replace all string in ReplaceList except strings containing "."
	for(a = 0; a < ReplaceList->Count; a++){
		A = ReplaceList->Names[a];
		if(A.Pos(".") == 0){
			B = ReplaceList->Values[A];
			IgnoreCase = (unsigned char*)ReplaceList->Objects[a];
			if(*IgnoreCase)
				Tmp = ReplaceText(Tmp, A, B);
			else
				Tmp = ReplaceStr(Tmp, A, B);
		}
	}
	return Tmp;
	
}
//---------------------------------------------------------------------------
bool TNameTranslator::GetRemoveText(){
	return FRemoveText;
}
//---------------------------------------------------------------------------
void TNameTranslator::SetRemoveText(bool Value){
	FRemoveText = Value;
}
//---------------------------------------------------------------------------
String TNameTranslator::CreateMovieName(String Format, MovieNamedetails Details){
	DEBUG_TRL(INFO_DEBUG,"CreateMovieName(): Format "+QUOTE_STRING(Format));
	String Out;
	String Tmp;
	String Txt;
	int a, b;
	bool Found;
	Out = Format;
	TStringList *Data = EnumTextInside(Format, START_PARAMETER, END_PARAMETER, false);
	for(a=0;a<Data->Count;a++){
		Found = false;
		if(Data->Strings[a]=="Moviename"){
			Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),UpperFirstLetter(Details.Title));
			Found = true;
		}
		if(Data->Strings[a]=="mOviename"){
			Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Details.Title);
			Found = true;
		}
		if(Found == false){
			if(Data->Strings[a]=="moviename"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Details.Title.LowerCase());
				Found = true;
			}
		}
		if(Found == false){
			if(Data->Strings[a]=="MOVIENAME"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Details.Title.UpperCase());
				Found = true;
			}
		}
		if(Found == false){
			if(Data->Strings[a]=="MovieName"){
				Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),WordUpperFirstLetter(Details.Title));
				Found = true;
			}
		}
		if(Found == false){
			Tmp = Data->Strings[a].LowerCase();
			Txt = "year";
			if(Tmp.Pos(Txt)>0){
				if(Details.Year > 0){
					Tmp = AS_PARAMETER(Data->Strings[a]);
					Tmp = System::Strutils::AnsiReplaceStr(Tmp,START_PARAMETER,"");
					Tmp = System::Strutils::AnsiReplaceStr(Tmp,END_PARAMETER,"");
					Tmp = System::Strutils::AnsiReplaceText(Tmp,Txt,IntToStr(Details.Year));
					Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Tmp);
				}
				else
					Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),"");
				Found = true;
            }
		}
		if(Found == false){
			Tmp = Data->Strings[a].LowerCase();
			Txt = "discnumber";
			if(Tmp.Pos(Txt)>0){
				if(Details.Disc > 0){
					Tmp = AS_PARAMETER(Data->Strings[a]);
					Tmp = System::Strutils::AnsiReplaceStr(Tmp,START_PARAMETER,"");
					Tmp = System::Strutils::AnsiReplaceStr(Tmp,END_PARAMETER,"");
					Tmp = System::Strutils::AnsiReplaceText(Tmp,Txt,IntToStr(Details.Disc));
					Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),Tmp);
				}
				else
					Out = System::Strutils::AnsiReplaceStr(Out,AS_PARAMETER(Data->Strings[a]),"");
				Found = true;
			}
		}
	}
	Out = System::Strutils::AnsiReplaceStr(Out,":"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"\\"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"/"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"*"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"?"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"<"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,">"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"|"," ");
	Out = System::Strutils::AnsiReplaceStr(Out,"\""," ");
	DEBUG_TRL(TOTAL_DEBUG,"Result: "+QUOTE_STRING(Out));
	return Out.Trim();
}
//---------------------------------------------------------------------------
int TNameTranslator::FindDisc(String Src){
	int a;
	String Tmp = Src.LowerCase();
	String Txt;
	String Words[] = {"cd","dvd","disc"};
	int Out = 0;
	int b;
	WideChar W;
	for(b=0;b<3;b++){       //Number of strings in array Words
		a = Pos(Words[b],Tmp);
		while(a != 0){
			if(a > 1){
				W = Tmp[a-1];
				if(IsLetter(W) == false){
					Txt = Tmp.SubString(a+Words[b].Length(),Tmp.Length());
					Out = PickNumber(Txt.TrimLeft());
					if(Out != -1)
						return Out;
				}
			}
			a = Pos(Words[b],Tmp,a + 1);
		}
	}
	return Out;
}
//---------------------------------------------------------------------------
String TNameTranslator::CleanString(String Src){
	String Out = Src;
	int Start = 1;
	int Stop = Src.Length();
	while(IsLetterOrDigit(Src[Start]) == false){
		Start++;
	}
	while(IsLetterOrDigit(Src[Stop]) == false){
		Stop--;
	}
	Out = Src.SubString(Start, Stop);
	return Out;
}
//---------------------------------------------------------------------------
bool TNameTranslator::GetRemoveSep(){
	return FRemoveSep;
}
//---------------------------------------------------------------------------
void TNameTranslator::SetRemoveSep(bool Value){
    FRemoveSep = Value;
}
//---------------------------------------------------------------------------
String TNameTranslator::RemoveSeparator(String Src){
	String Out = Src;
	int a;
	a = Out.Pos("-");
	if(a>0)
		Out = Out.SubString(1,a-1);
	a = Out.Pos("~");
	if(a>0)
		Out = Out.SubString(1,a-1);
	return Out;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
