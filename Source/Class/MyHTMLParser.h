//---------------------------------------------------------------------------
#ifndef MyHTMLParserH
#define MyHTMLParserH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.StrUtils.hpp>
#include <System.RegularExpressions.hpp>
#include <System.SysUtils.hpp>
#include "Project_Const.h"
//---------------------------------------------------------------------------
typedef struct{
	int Start;
	int Stop;
	int Length;
	int StartRow;
	int EndRow;
}TagPosition;
//---------------------------------------------------------------------------
class THTMLNode{
	private:
		String FTag;
		String FText;
		TList *Child;
		TStringList *Attribute;
		TagPosition FPosition;
		THTMLNode *FParent;
		
		void Setup();
	protected:
		String GetTag();
		String GetClass();
        String GetID();
		void SetText(String Txt);
		String GetText();
		TagPosition GetPosition();
		void SetPosition(TagPosition Pos);
		THTMLNode *GetParent();
	public:
		THTMLNode();
		THTMLNode(String Start);
		THTMLNode(String Start, THTMLNode *Parent);
		~THTMLNode();
		void LoadFromString(String Src);
		int GetNumAttribute();
		String GetAttributeName(int Index);
		String GetAttributeValue(int Index);
        String GetAttribute();
		void AddChild(THTMLNode *Child);
		int GetNumChild();
		THTMLNode *GetChild(int Index);
		

		__property String Tag =  {read = GetTag};
		__property String Class = {read = GetClass};
		__property String Text = {read = GetText, write = SetText};
		__property TagPosition Position = {read = GetPosition, write = SetPosition};
		__property String ID = {read = GetID};
		__property THTMLNode *Parent = {read = GetParent};
};
//---------------------------------------------------------------------------
class TMyHTMLParser{
	private:
		TList *NodeList;
		TStringList *SingleTag;
	protected:
		TStringList *SplitString(String Source, bool WithLimit = false);
		//String MultipleBack(int Num);
	public:
		TMyHTMLParser();
		~TMyHTMLParser();
		int LoadFromString(String Src);
		int LoadFromFile(String FileName);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------