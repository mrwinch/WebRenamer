//---------------------------------------------------------------------------
#ifndef NameValueH
#define NameValueH
//---------------------------------------------------------------------------
#include <system.hpp>
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <sysutils.hpp>
#include <StrUtils.hpp>
#include <xml.xmldoc.hpp>
#include "ExtStringList.h"
//---------------------------------------------------------------------------
#define STRING_NAME_EXIST                       					0x100
#define STRING_INVALID_NAME                                         0x12345678
#define NAME_VALUE_CORRECT                                          0x0

#define OBJ_BOOL                                                    0x20
#define OBJ_INT                                                     0x21
#define OBJ_STR                                                     0x22
#define OBJ_FLT                                                     0x23

#define NAMEVALUE_VERSION                                               0x10
#define NAMEVALUE_NODE_NAME                                             "Configuration"
//---------------------------------------------------------------------------
typedef struct{
	int Type;
	String Comment;
}Value_Info;
//---------------------------------------------------------------------------
class TNameValue{
	private:
		TStringList *Main;
		int InternalAdd(String Name, String Value, int Type, String Comment);
        TComponent *Owner;
	public:
		__fastcall TNameValue(TComponent *AOwner);
		__fastcall  ~TNameValue();
		int AddBool(String Name, bool Value, String Comment = "");
		int AddInt(String Name, int Value, String Comment = "");
		int AddString(String Name, String Value, String Comment = "");
		int AddFloat(String Name, float Value, String Comment = "");
		int SetBool(String Name, bool Value);
		int SetInt(String Name, int Value);
		int SetString(String Name, String Value);
		int SetFloat(String Name, float Value);
		bool GetBool(String Name);
		int GetInt(String Name);
        float GetFloat(String Name);
		String GetString(String Name);
		bool ValueExist(String Name);
		int SaveToXML(String File);
		void Reset();
		int GetNumValue();
		String GetValueNameByIndex(int Index);
		int GetValueTypeByIndex(int Index);
		int GetValueType(String Name);
        int GetValueIndex(String Name);
		int LoadFromXML(String File);
		int SetComment(String Value, String Comment);
		int RemoveValue(String Value);
		String GetComment(String Name);
		TStringList *GetValues();
		TNameValue *Clone(TComponent *AOwner=NULL);
		int UpdateFromSource(TNameValue *Src);
};
//---------------------------------------------------------------------------
#endif
