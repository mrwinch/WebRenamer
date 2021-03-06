//---------------------------------------------------------------------------
#ifndef ExtStringListH
#define ExtStringListH
//---------------------------------------------------------------------------
#include <system.hpp>
#include <sysutils.hpp>
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <StrUtils.hpp>
#include "Project_Const.h"
//---------------------------------------------------------------------------
#define LIST_DELIMITER								'|'
#define LIST_DELIMITER_REPLACE						"&trail;"
#define LIST_EQUALS									'='
#define LIST_EQUALS_REPLACE							"&sum;"
//---------------------------------------------------------------------------
class TExtendedStringList:public TStringList{
	private:
		String SafeEncode(String Src);
		String SafeDecode(String Strc);
		String __fastcall ExtGetKeyName(int Index);
		String __fastcall ExtGetName(int Index);
		String __fastcall ExtGet(int Index);
		void ExtPut(int Index, String S);
		String __fastcall ExtGetValueFromIndex(int Index);
		void ExtSetValueFromIndex(int Index, String S);
		String __fastcall ExtGetValue(String Name);
		void ExtSetValue(String Index, String S);
	public:
		TExtendedStringList();
		__fastcall ~TExtendedStringList();
		TStrings* __fastcall AddPair(String Name, String Value);
		TStrings* __fastcall AddPair(String Name, String Value, TObject *AObject);
		int __fastcall IndexOf(String S);
		int __fastcall IndexOfName(String Name);
		void __fastcall Insert(int Index, String S);
		void __fastcall InsertObject(int Index, String S, System::TObject* AObject);

		String operator[](int Index);

		__property String KeyNames[int Index] = {read=ExtGetKeyName};
		__property String Names[int Index] = {read=ExtGetName};
		__property String Strings[int Index] = {read=ExtGet, write=ExtPut/*, default*/};
		__property String ValueFromIndex[int Index] = {read=ExtGetValueFromIndex, write=ExtSetValueFromIndex};
		__property String Values[String Name] = {read=ExtGetValue, write=ExtSetValue};

};
//---------------------------------------------------------------------------
#endif