//---------------------------------------------------------------------------
#ifndef NameTranslatorH
#define NameTranslatorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <System.Character.hpp>
#include <system.hpp>
#include <sysutils.hpp>
#include <StrUtils.hpp>
#include "Project_Const.h"
//---------------------------------------------------------------------------
#define	UNK_SEASON										-1
#define UNK_EPISODE										-2
//---------------------------------------------------------------------------
#define MINIMUM_PAR_TEXT								5
//---------------------------------------------------------------------------
/*********************************************
*	Episode_Order: struct that manage season and episode number
*********************************************/
typedef struct{
	int Season;							//Season number
	int Episode;						//Episode number
	int Order_Start;					//Position in string where data starts
	int Order_End;						//Position in string where data end
}Episode_Order;
typedef struct{
	String OriginalName;				//Original file name
	TStringList *NameCandidate;			//List of all possible title candidate
	Episode_Order Order;				//see above
	String FileExtension;				//Original extension of the file
	String SuggestedTitle;				//Suggested title for the episode
}Episode_Info;
typedef struct{
	String ShowName;
	int Season;
	int Episode;
	String EpisodeTitle;
}TVShowNameDetails;
typedef struct{
	String Name;
	int Year;
	String FileExtension;
	int Disc;
}Movie_Info;
typedef struct{
	String Title;
	int Year;
    int Disc;
}MovieNamedetails;
//---------------------------------------------------------------------------
String UpperFirstLetter(String Source);
String WordUpperFirstLetter(String Source);
//---------------------------------------------------------------------------
class TNameTranslator{
	private:
		bool FIgnoreParenthesys;
		bool FIgnoreSquareBrackets;
		bool FIgnoreCurlyBrackets;
		bool FRemoveText;
		bool FRemoveSep;
		TStringList *ReplaceList;
		TComponent *Owner;
		
		void SetParenthesys(bool YN);
		bool GetParenthesys();
		void SetSquareBrackets(bool YN);
		bool GetSquareBrackets();
		void SetCurlyBrackets(bool YN);
		bool GetCurlyBrackets();
		bool GetItemCase(String Item);
		void SetitemCase(String Item, bool IgnoreCase);
		bool GetItemActive(String Item);
		void SetitemActive(String Item, bool IgnoreCase);
		bool GetRemoveText();
		void SetRemoveText(bool Value);
		bool GetRemoveSep();
		void SetRemoveSep(bool Value);
		String GetItem(int Index);
		TStringList *EnumTextInside(String Source, String Start, String End, bool IncludeLimits = true);
        int PickNumber(String Value, int DefValue = -1);
		int FindYear(String Src);
		bool IsDigit(WideChar c);
		String FilterFile(String File);
		int FindDisc(String Src);
		String CleanString(String Src);
        String RemoveSeparator(String Src);

		Episode_Order *ScanForEpisodeOrder(String FileName);
	protected:
	public:
		__fastcall TNameTranslator(TComponent *AOwner);
		__fastcall ~TNameTranslator();
		Episode_Info TranslateEpisode(String OriginalName);
		void AddToReplaceList(String From, String To="", bool IgnoreCase=true, bool Active = true);
		void AddToIgnoreList(String Txt, bool IgnoreCase = true, bool Active = true);
		int GetNumReplaceItems();
		String ExportIgnoreList();
		void ImportIgnoreList(String List);
		String CreateTVShowName(String Format, TVShowNameDetails Details); 
		Movie_Info TranslateMovie(String Movie);
		String CreateMovieName(String Format, MovieNamedetails Details);

		__property bool IgnoreParenthesys = {read = GetParenthesys, write = SetParenthesys};
		__property bool IgnoreSquareBrackets = {read = GetSquareBrackets, write = SetSquareBrackets};
		__property bool IgnoreCurlyBrackets = {read = GetCurlyBrackets, write = SetCurlyBrackets};
		__property bool ReplaceItemIgnoreCase[String Item] = {read = GetItemCase, write = SetitemCase};
		__property bool ReplaceItemActive[String Item] = {read = GetItemActive, write = SetitemActive};
		__property String ReplaceItem[int Index] = {read = GetItem};
		__property bool RemoveTextAfterParenthesys = {read = GetRemoveText, write = SetRemoveText};
		__property bool RemoveAfterSeparator ={read = GetRemoveSep, write = SetRemoveSep};
};
//---------------------------------------------------------------------------
#endif
