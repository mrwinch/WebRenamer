//---------------------------------------------------------------------------

#ifndef ConnectionManagerH
#define ConnectionManagerH
//---------------------------------------------------------------------------
//#include <ExtStringList.h>
#include <System.Classes.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.HttpClientComponent.hpp>
#include <System.Net.URLClient.hpp>
#include <System.JSON.hpp>
#include <System.StrUtils.hpp>
#include <System.RegularExpressions.hpp>
#include <System.NetEncoding.hpp>
#include <FMX.DialogService.Sync.hpp>
#include <xml.xmldoc.hpp>
#include <Project_Const.h>
//---------------------------------------------------------------------------
#define WEB_SOURCE_CORRECT									0x000
#define WEB_SOURCE_INVALID_KEY								0x001
#define WEB_SOURCE_EMPTY_KEY_VALUE							0x002
#define WEB_SOURCE_INVALID_COMMAND_LIST						0x003
#define WEB_SOURCE_COMMAND_TYPE_EXIST						0x005
#define WEB_SOURCE_COMMAND_NOT_EXIST						0x006
#define WEB_SOURCE_COMMAND_NAME_EXIST						0x007
#define WEB_SOURCE_COMMAND_ID_EXIST							0x008
#define WEB_SOURCE_NO_HTTPCLIENT							0x009
#define WEB_SOURCE_INVALID_COMMAND_MANAGER					0x00A
#define WEB_SOURCE_INVALID_HTTPREQUEST						0x00B
#define WEB_SOURCE_INVALID_COMMAND_INDEX					0x00C
#define WEB_SOURCE_INVALID_SOURCE                           0x00D
#define WEB_SOURCE_INVALID_FILE                             0x00E
#define WEB_SOURCE_INVALID_OPERATION                        0x00F
#define WEB_SOURCE_EMPTY_QUEUE                              0x010
#define WEB_SOURCE_SEARCH_IN_PROGRESS                       0x011
#define WEB_SOURCE_INVALID_ANSWER							0x012
#define WEB_SOURCE_SAFETY_VALUE								0xFFFFFFFF
//---------------------------------------------------------------------------
#define METHOD_POST								0x40
#define METHOD_GET								0x41
#define METHOD_UNK                              0x4F
//---------------------------------------------------------------------------
#define SHOW_SOURCE_INFO						0x900
#define MOVIE_SOURCE_INFO						0x901
#define GET_SOURCE_TYPE(Type)					(Type == SHOW_SOURCE_INFO?"TV Show":(Type == MOVIE_SOURCE_INFO?"Movie":"Unkwnown"))
//---------------------------------------------------------------------------
#define QUERY_CANDIDATE							0xA00
#define QUERY_SHOW_TITLE						0xA01
#define QUERY_MOVIE_TITLE						0xA02
#define SYS_AUTHENTICATE     	                0xA03

#define QUERY_GENERIC							0xAFF
//---------------------------------------------------------------------------
#define HTTP_REQUEST_STANDBY						0x500
#define HTTP_EXECUTING_COMMAND_MANAGER				0x501
//---------------------------------------------------------------------------
#define INFO_GRABBER_VERSION                        0x10
//---------------------------------------------------------------------------
#define CLIENT_CONNECTION_TIMEOUT					20000
#define CLIENT_RESPONSE_TIMEOUT						20000
//---------------------------------------------------------------------------
#define REQUEST_TEST_COMMAND                        0xC0
#define REQUEST_TEST_OPERATION                      0xC1
#define REQUEST_NORMAL_FLOW                         0xC2
//---------------------------------------------------------------------------
class Base_Info{
	private:
		String FName;
		String FDescription;
		int FID;
		int FTag;
		int FType;

		String GetName();
		void SetName(String Name);
		String GetDesc();
		void SetDesc(String Desc);
		int GetID();
		void SetID(int ID);
		int GetTag();
		void SetTag(int Tag);
		void SetType(int Type);
		int GetType();
	public:
		Base_Info();
		~Base_Info();
		__property String Name = {read=GetName, write=SetName};			//Name of element
		__property String Description ={read=GetDesc, write=SetDesc};	//Description for element
		__property int ID = {read=GetID, write=SetID};					//An ID of the element
		__property int Tag = {read=GetTag, write=SetTag};				//Tag for the element
		__property int Type = {read=GetType, write=SetType};				//Type of element
};
//---------------------------------------------------------------------------
/****************************************************
 *  Net_Operation
 *  
 *  Description: a small struct to manage data to send to server
 *  
 *  Url: URL of the server at which command will be sent
 *  Data: additional data to send
 *  MethodType: POST, GET, .... (see const METHOD_POST, METHOD_GET,...)
 *  ExpectedAnswer: number of answer expected
 *  
 *  Note: parameter can be add to Data and Url using the sintax
 *  "START_PARAMETERparameterEND_PARAMETER". In this release
 *  "<<parameter>>"
 ***************************************************/
typedef struct{
	String Url;
	String Data;
	int MethodType;
	int ExpectedAnswer;
	String AnswerManager;
}Net_Operation;
//---------------------------------------------------------------------------
int CopyNet_Operation(Net_Operation *Src, Net_Operation* Dest);
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TOperationEvent)(Net_Operation Operation);
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList
 *  
 *  Description: a small class that manage a list of commands. When a TConnectionManager
 *  object will execute the command, a request with information of first operation in list:
 *  everytime server will respond, TConnectionManager will update parameter with those information 
 *  and will send next operation in this list
 ***************************************************/
class CommandList:public Base_Info{
	private:
		int FPosition;
		TList *CommandQueue;
		int FStatus;
		
		void SetPosition(int Pos);
		int GetPosition();
		int DecodeAnswer(String Answer, Net_Operation Op, CommandList *Cmd);
	public:
		CommandList();
		~CommandList();
		int AddOperation(Net_Operation Op);
		int RemoveOperation(Net_Operation Op);
		int ChangeOperation(Net_Operation OldOp, Net_Operation NewOp);
		Net_Operation GetOperation(int Index);
		int GetNumOperations();
		int GetOperationIndex(Net_Operation Op);
		void MoveOperation(int ActPos, int NewPos);
		CommandList *Clone();
		Net_Operation *CreateOperation(String Url, String Data = "", int MethodType = METHOD_GET, int ExpectedAnswer = 200, String ManageAnswer = "",bool AddToList=true);
		
		__property int Position ={read=GetPosition, write=SetPosition};
		String SearchInfo;
		
		TOperationEvent OnAddOperation;
		TOperationEvent OnRemoveOperation;
};
//---------------------------------------------------------------------------
typedef struct{
	String Name;
	String ID;
	String Aerial;
	String Summary;
	String Poster;
	String Release;
}Candidate_Information;
typedef struct{
	String EpisodeTitle;
}ShowResultDetails;
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TOnConnectionError)(TNetHTTPClient *Client,TNetHTTPRequest *Request, CommandList *Cmd, int CommandIndex, int ErrCode, String ErrDesc);
typedef void __fastcall (__closure *TOnInvalidAnswer)(TNetHTTPRequest *Request,Net_Operation Op, CommandList *Mgr, int Expected, int Received);
typedef void __fastcall (__closure *TOnFoundCandidate)(String Searched, int SearchID, TList *Candidate);
typedef void __fastcall (__closure *TOnFindShowData)(String ShowName, int Season, int Episode, int SearchID, ShowResultDetails Details);
typedef void __fastcall (__closure *TOnFindMovieData)(String MovieName,String OriginalName, int Year);
typedef void __fastcall (__closure *TOnCompleteAvailableSource)(String Searched, int SearchID);
typedef void __fastcall (__closure *TCommandListEvent)(CommandList *Command);
typedef struct{
	TNetHTTPRequest *Request;
	CommandList *Command;
	int RequestStatus;
	int WorkingMode;
	TRequestCompletedEvent ReqCompleted;
	TRequestErrorEvent ReqError;
	Net_Operation LastOperation;
	String SearchedInfo;
	void *WebSource;
}WebSource_Data;
//---------------------------------------------------------------------------
class TWebSource:public Base_Info{
	protected:

	private:
		TList *TaskList;
		TList *RequestList;
		TList *QueueList;
		//TJSONObject *Parameters;
		TStringList *Parameters;
		//TJSONObject *Information;
		TStringList *Information;
		TStringList *ShowNamePref;
		//TNameTranslator *TTT;
		TComponent *Owner;
		TNetHTTPClient *FClient;
		bool FAuthReq,FAuth,FRemeberPreferences;
		String FPrefLang;

		void SetClient(TNetHTTPClient *Client);
		TNetHTTPClient *GetClient();
		int DriveOperation(TNetHTTPRequest *Request, Net_Operation Op);
		int DriveCommand(TNetHTTPRequest *Request, CommandList *Mgr, int Index);
		TStringList *EnumParameters(String Source);
		TStringList *EnumClientSet(String Source);
		TStringList *GenericEnumData(String Source, String StartData, String EndData);
		String ShareParameter(String Key, bool InsertWithQuotation = true);
		void __fastcall HTTPRequestCompleted(TObject *Sender, _di_IHTTPResponse  AResponse);
		void __fastcall HTTPRequestError(TObject* Sender, String AError);
		void InternalSetup();
		int GetNumRequest();
		void SetNumRequest(int Num);
		int UpdateQueueList();
		bool GetReqAuth();
		void SetReqAuth(bool Auth);
		bool GetAuth();
		String GetPrefLang();
		void SetPrefLang(String Lang);
		String GetShortLanguage();
		int DecodeAnswer(String Answer, Net_Operation Operation, CommandList *Cmd);
		int DecodeXMLAnswer(String Answer, Net_Operation Operation, CommandList *Cmd);
		int DecodeHTMLAnswer(String Answer, Net_Operation Operation, CommandList *Cmd);
		int ExecuteCommand(CommandList *Mgr);
		int Authenticate();
		bool GetRemPref();
		void SetRemPref(bool Value);
		void __fastcall ManageCertificate(System::TObject* const Sender, TURLRequest* const ARequest, const TCertificate &Certificate, bool &Accepted);
//		void __fastcall ValidateServerCertificate(TObject * const Sender, TURLRequest * const ARequest, const TCertificate &Certificate, bool &Accepted);

	public:
		TWebSource();
		TWebSource(TComponent *AOwner);
		~TWebSource();
		//Parameters functions...
		int AddParameter(String Key, String Value, bool AddAsInformation = false);
		int RemoveParameter(String Key);
		int ChangeParameter(String Key, String NewValue);
		int RenameParameter(String OldKey, String NewKey);
		TStringList *GetParameters();
		//Prefereces functions
		int AddShowNamePref(String ShowName, String ID);
		int RemoveShowNamePref(String ShowName);
		int GetNumShowNamePref();
		String GetShowNameID(String ShowName);
		String GetShowNamePrefNameByIndex(int Index);
		String GetShowNamePrefByIndex(int Index);
		int ChangeShowNamePrefID(String ShowName, String NewID);
		int ChangeShowNamePrefID(int Index, String NewID);
		int ChangeShowNamePrefName(String ShowName, String NewName);
		int ChangeShowNamePrefName(int Index, String NewName);
		String ExportPreferences();
		int ImportPreferences(String Pref);
		//Command list...
		CommandList *CreateCommandList(String Name="No_Name",String Desc="No_Description",int ID=0,int Type=SYS_AUTHENTICATE,int Tag=0, bool AddToList = true);
		int AddCommandsList(CommandList *Cmd, bool CloneIt = false);
		int RemoveCommandsList(CommandList *Cmd);
		int GetNumCommands();
		CommandList *GetCommandByIndex(int Index);
		int CommandListExist(CommandList *Cmd);
		//Utility...
		int TestOperation(Net_Operation Op, TRequestCompletedEvent ReqCompleted = NULL, TRequestErrorEvent ReqError = NULL);
		int TestCommand(CommandList *Mgr, TRequestCompletedEvent ReqCompleted = NULL, TRequestErrorEvent ReqError = NULL);
		TWebSource *Clone(TComponent *AOwner);
		//HTTP functions...
		int QueryCandidate(String Candidate, TOnFoundCandidate Func = NULL, int SearchID = 0xFFFFFFFF);
		int QueryShowDetail(String ShowName, String ShowID, int Season, int Episode, TOnFindShowData Func = NULL, int SearchID = 0xFFFFFFFF);		
		//Events
		TOnConnectionError OnConnectionError;
		TOnInvalidAnswer OnInvalidAnswer;
		TOnFoundCandidate OnFindCandidate;
		TOnFindShowData OnFindShowData;
		//TCommandListEvent OnCreateCommandList;
		TCommandListEvent OnAddCommandList;
		TCommandListEvent OnRemoveCommandList;
		//Property
		__property TNetHTTPClient *Client = {read = GetClient, write = SetClient};
		__property int MultipleRequest = {read = GetNumRequest, write = SetNumRequest};
		__property bool AuthRequest = {read = GetReqAuth, write = SetReqAuth};
		__property bool Authorized = {read = GetAuth};
		__property String PreferedLanguage = {read = GetPrefLang, write = SetPrefLang};
		__property bool RememberPreferences = {read = GetRemPref, write = SetRemPref};
};
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TWebSourceEvent)(TWebSource *Source);
//---------------------------------------------------------------------------
class TInfoGrabber{
	protected:
		typedef struct{
			TWebSource *WebSource;
			int SearchID;
			String ShowName;
			String MovieName;
			String ShowID;
		}SearchInfo;
	private:
		TComponent *Owner;
		TList *InfoSource;
		TNetHTTPClient *Client;
		String FPrefLang;
		TStringList *SearchingData;
		TList *SearchList;
		String FUserAgent;
        TWebSource *FLastSource;

		void InternalSetup();
		int GetNumSourceByType(int Type);
		String GetPrefLang();
		void SetPrefLang(String Lang);
		String GetUserAgent();
		TWebSource *GetLastSource();
		void SetUserAgent(String Agent);
		void __fastcall InternalFoundShowCandidate(String Candidate, int SearchID, TList *Result);
		void __fastcall InternalFoundMovieCandidate(String Candidate, int SearchID, TList *Result);
		void __fastcall InternalFoundShowDetails(String ShowName, int Season, int Episode, int SearchID, ShowResultDetails Details);
		void __fastcall ManageInvalidAnswer(TNetHTTPRequest *Request,Net_Operation Op, CommandList *Mgr, int Expected, int Received);
	public:
		TInfoGrabber();
		TInfoGrabber(TComponent *AOwner);
		~TInfoGrabber();
		TWebSource *CreateInfoSource(String Name="No_Name",String Desc="No_Description",int ID=0,int Type=SHOW_SOURCE_INFO,int Tag=0, bool AddToList = true);
		int AddInfoSource(TWebSource *Source);
		int RemoveInfoSource(TWebSource *Source);
		int GetNumInfoSource();
		TWebSource *GetSourceByIndex(int Index);
		bool CompareSource(TWebSource *Src1, TWebSource *Src2);
		int LoadFromXML(String File);
		int SaveToXML(String File);
		int Reset();
		int GetSourceOrderInSearchIndex(TWebSource *Src);
		int ChangeSourceSearchOurder(TWebSource *Src, int NewPlace);
		int QueryShowCandidate(String Candidate, int SearchID = 0xFFFFFFFF);
		int QueryShowDetail(String ShowName, String ShowID, int Season, int Episode, int SearchID = 0xFFFFFFFF);
		int QueryMovieCandidate(String Candidate, int SearchID = 0xFFFFFFFF);
		TInfoGrabber *Clone();

		__property String PreferedLanguage = {read = GetPrefLang, write = SetPrefLang};
		__property String UserAgent = {read = GetUserAgent, write = SetUserAgent};
		__property TWebSource *LastSourceUsed = {read = GetLastSource};

		TOnFoundCandidate OnFindCandidate;
		TOnFindShowData OnFindShowData;
		TWebSourceEvent OnCreateWebSource;
		TWebSourceEvent OnAddWebSource;
		TWebSourceEvent OnRemoveWebSource;
		TOnConnectionError OnConnectionError;
        TOnCompleteAvailableSource OnCompleteAvailableSource;
};
//---------------------------------------------------------------------------
void TestTheMovieDB2(TInfoGrabber *Grabber);
//---------------------------------------------------------------------------
#endif

