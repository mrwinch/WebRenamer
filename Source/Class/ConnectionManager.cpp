//---------------------------------------------------------------------------
#pragma hdrstop
//#define WEB_RENEMER_DEBUG
#include "ConnectionManager.h"
#include "ExtStringList.h"
#ifdef WEB_RENAMER_DEBUG
extern TSysLog *Logger;
#endif
#pragma package(smart_init)
int ReqCreated = 0;
//---------------------------------------------------------------------------
/****************************************************
 *  DEBUG
 *
 *  Description: small function to debug class TConnectionManager
 *  
 *  Level: minimum level of debugging at which information will be show
 *  Msg: message of debug to show
 *  Return value: none
 *  
 *  Note:
 ***************************************************/
void DEBUG(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	if(Logger)
		Logger->Report("ConMgr",NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
/****************************************************
 *  DEBUG_MGR
 *
 *  Description: function to debug class TCommandList
 *
 *  Level:minimum level of debugging at which information will be show
 *  Msg: message of debug to show
 *  Return value: none
 *
 *  Note:
 ***************************************************/
void DEBUG_MGR(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	if(Logger)
		Logger->Report("CmdLst",NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
/****************************************************
 *  DEBUG_SRC
 *
 *  Description: function to debug class TWebSource
 *
 *  Level:minimum level of debugging at which information will be show
 *  Msg: message of debug to show
 *  Return value: none
 *
 *  Note:
 ***************************************************/
void DEBUG_SRC(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	if(Logger)
		Logger->Report("WebSrc",NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
/****************************************************
 *  DEBUG_GRB
 *
 *  Description: function to debug class TInfoGrabber
 *
 *  Level:minimum level of debugging at which information will be show
 *  Msg: message of debug to show
 *  Return value: none
 *
 *  Note:
 ***************************************************/
void DEBUG_GRB(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	if(Logger)
		Logger->Report("InfGrb",NAME_LEVEL(Level),Msg);
#endif	
}
//---------------------------------------------------------------------------
/****************************************************
 *  CopyNet_Operation
 *  
 *  Description: copy information from one Net_Operation struct to another
 *  
 *  Src: source of information
 *  Dest: destination of information
 *  Return value: 0 if success, -1 if Src is NULL, -2 if Dest is null
 *  
 *  Note:
 ***************************************************/
int CopyNet_Operation(Net_Operation *Src, Net_Operation* Dest){
	if(Src ){
		if(Dest){
			Dest->Url = Src->Url;
			Dest->Data = Src->Data;
			Dest->MethodType = Src->MethodType;
			Dest->ExpectedAnswer = Src->ExpectedAnswer;
			Dest->AnswerManager = Src->AnswerManager;
			return 0;
		}
		return -2;
	}
	return -1;
}
//---------------------------------------------------------------------------
void TestTheMovieDB2(TInfoGrabber *Grabber){
/*	TWebSource *Src = Grabber->CreateInfoSource("The movie DB Test","");
	CommandList *Cmd= Src->CreateCommandList("Movie DB query test","");
	Src->AddParameter("api_key","cc8c9c1f521f6b6f06cebdedf012b102");
	Cmd->CreateOperation("https://api.themoviedb.org/3/search/tv?api_key=<<api_key>>&language=en-US&query=The%20walking%20dead&page=1","",METHOD_GET);
	Src->ExecuteCommand(Cmd);      */
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::Base_Info
 *  
 *  Description: class constructor
 *  
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
Base_Info::Base_Info(){
	
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::~Base_Info
 *  
 *  Description: class destructor
 *  
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
Base_Info::~Base_Info(){
	
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::SetName
 *  
 *  Description: function set for name property
 *  
 *  Name: name to set
 *  Return value: 
 *
 *  Note:
 ***************************************************/
void Base_Info::SetName(String Name){
	FName = Name;
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::GetName
 *  
 *  Description: function that return Name property
 *  
 *  Return value: property Name
 *  
 *  Note:
 ***************************************************/
String Base_Info::GetName(){
	return FName;
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::SetID
 *  
 *  Description: function that set ID property
 *  
 *  ID: new ID value
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
void Base_Info::SetID(int ID){
	FID = ID;
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::GetID
 *  
 *  Description: function that return ID property
 *  
 *  Return value: the value of property ID
 *  
 *  Note:
 ***************************************************/
int Base_Info::GetID(){
	return FID;
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::SetDesc
 *  
 *  Description: function that set property Description
 *  
 *  Desc: new description
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
void Base_Info::SetDesc(String Desc){
	FDescription = Desc;
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::GetDesc
 *  
 *  Description: function that return Description property
 *  
 *  Return value: description value
 *  
 *  Note:
 ***************************************************/
String Base_Info::GetDesc(){
	return FDescription;
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::SetTag
 *  
 *  Description: function that set the Tag property
 *  
 *  Tag: new Tag value
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
void Base_Info::SetTag(int Tag){
	FTag = Tag;
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::GetTag
 *  
 *  Description: function to retrive Tag property
 *  
 *  Return value: Tag property value
 *  
 *  Note:
 ***************************************************/
int Base_Info::GetTag(){
	return FTag;
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::SetType
 *  
 *  Description: set the value of property Type
 *  
 *  Type: new property value
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
void Base_Info::SetType(int Type){
	FType = Type;
}
//---------------------------------------------------------------------------
/****************************************************
 *  Base_Info::GetType
 *  
 *  Description: return the value of property Type
 *  
 *  Return value: the value of the property
 *  
 *  Note:
 ***************************************************/
int Base_Info::GetType(){
	return FType;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::CommandList
 *  
 *  Description: class constructor
 *  
 *  Return value: 
 *
 *  Note:
 ***************************************************/
CommandList::CommandList():Base_Info(){	FPosition = 0;
	CommandQueue = new TList();
	Name = "Generic_queue";
	ID = 0;
	Description = "Empty queue";
	Type = QUERY_GENERIC;
	Position = -1;
	SearchInfo = "";
	OnAddOperation = NULL;
	OnRemoveOperation = NULL;
}
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::~CommandList
 *  
 *  Description: class destructor
 *  
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
CommandList::~CommandList(){
	Net_Operation *Info;
	for(int a=0; a<CommandQueue->Count; a++){
		Info = (Net_Operation*)CommandQueue->Items[a];
		FreeMemory(Info);
	}
}
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::AddOperation
 *  
 *  Description: Add an operation to queue
 *  
 *  Op: operation to add
 *  Return value: none
 *  
 *  Note: information of the operation will be added in form of Net_Operation struct
 ***************************************************/
int CommandList::AddOperation(Net_Operation Op){
	int Res;
	DEBUG_MGR(INFO_DEBUG,"AddOperation() with URL: "+Op.Url);
	Net_Operation *Info = (Net_Operation*)AllocMem(sizeof(Net_Operation));
	Res = CopyNet_Operation(&Op,Info);
	if(Res == 0){
		CommandQueue->Add(Info);
		if(OnAddOperation)
			OnAddOperation(*Info);
	}
	else
		DEBUG_MGR(ERR_DEBUG,"Error executing 'CopyNet_Operation': code "+IntToStr(Res));
	return Res;
}//---------------------------------------------------------------------------
int CommandList::ChangeOperation(Net_Operation OldOp, Net_Operation NewOp){
	DEBUG_MGR(INFO_DEBUG,"ChangeOperation()");
	int Index = GetOperationIndex(OldOp);
	if(Index > -1){
		Net_Operation *Info = (Net_Operation*)CommandQueue->Items[Index];
		Info->Url = NewOp.Url;
		Info->Data = NewOp.Data;
		Info->ExpectedAnswer = NewOp.ExpectedAnswer;
		Info->AnswerManager = NewOp.AnswerManager;
		Info->MethodType = NewOp.MethodType;
		DEBUG_MGR(TOTAL_DEBUG,"Changed operation at index "+IntToStr(Index));		
		return WEB_SOURCE_CORRECT;
	}
	DEBUG_MGR(ERR_DEBUG,"Operation not found");
	return WEB_SOURCE_INVALID_OPERATION;
}
//---------------------------------------------------------------------------
int CommandList::RemoveOperation(Net_Operation Op){
	DEBUG_MGR(INFO_DEBUG,"RemoveOperation");
	Net_Operation *Info;
	for(int a=0;a<CommandQueue->Count; a++){
		Info = (Net_Operation*)CommandQueue->Items[a];
		if(Info->Url == Op.Url){
			if(Info->Data == Op.Data){
				if(Info->ExpectedAnswer == Op.ExpectedAnswer){
					if(Info->MethodType == Op.MethodType){
						if(Info->AnswerManager == Op.AnswerManager){
							DEBUG_MGR(TOTAL_DEBUG,"Deleting operation at index "+IntToStr(a));
							if(OnRemoveOperation)
								OnRemoveOperation(*Info);							
							CommandQueue->Delete(a);
							return WEB_SOURCE_CORRECT;
						}
					}
				}
			}
		}
	}
	DEBUG_MGR(ERR_DEBUG,"Operation not found");
	return WEB_SOURCE_INVALID_OPERATION;
}
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::GetOperation
 *  
 *  Description: return operation information
 *  
 *  Index: index of the operation to read
 *  Return value: a Net_Operation struct for the operation request
 *  
 *  Note:
 ***************************************************/
Net_Operation CommandList::GetOperation(int Index){
	DEBUG_MGR(INFO_DEBUG,"GetOperation at index "+IntToStr(Index));
	Net_Operation *Info;
	if(Index < CommandQueue->Count){
		if(Index > -1){
			Info = (Net_Operation*)CommandQueue->Items[Index];
			return *Info;
		}
	}
	DEBUG_MGR(WARN_DEBUG,"No operation found: returning an empty one");
	Info = (Net_Operation*)AllocMem(sizeof(Net_Operation));
	return *Info;
}
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::GetNumOperations
 *  
 *  Description: return number of operation in queue
 *  
 *  Return value: number of operation loaded
 *  
 *  Note:
 ***************************************************/
int CommandList::GetNumOperations(){
	return CommandQueue->Count;
}
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::MoveOperation
 *
 *  Description: move an operation inside the queue
 *
 *  ActPos: actual position of the operation
 *  NewPos: new position for the operation
 *  Return value:
 *
 *  Note:
 ***************************************************/
void CommandList::MoveOperation(int ActPos, int NewPos){
	DEBUG_MGR(INFO_DEBUG,"MoveOperation: "+IntToStr(ActPos)+(String)" to "+IntToStr(NewPos));
	CommandQueue->Move(ActPos, NewPos);
}
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::Clone
 *  
 *  Description: clone this Command list and all its information
 *  
 *  Return value: a CommandList object copy of itself
 *  
 *  Note:
 ***************************************************/
CommandList *CommandList::Clone(){
	DEBUG_MGR(INFO_DEBUG,"Clone()");
	CommandList *Out = new CommandList();
	Net_Operation *Src;
	Out->Name = Name;
	Out->ID = ID;
	Out->Type = Type;
	Out->Description = Description;
	Out->Tag = Tag;
	DEBUG_MGR(TOTAL_DEBUG,"Cloning "+IntToStr(CommandQueue->Count)+" operation *********************");
	for(int a=0;a<CommandQueue->Count;a++){
		Src = (Net_Operation*)CommandQueue->Items[a];
		Out->AddOperation(*Src);
	}
	DEBUG_MGR(TOTAL_DEBUG,"Clone complete   *******************");	
	return Out; 
}
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::GetPosition
 *  
 *  Description: return position in queue of the last executed command
 *  
 *  Return value: position in queue of the last command
 *  
 *  Note:
 ***************************************************/
int CommandList::GetPosition(){
	return FPosition;
}
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::SetPosition
 *  
 *  Description: set position in queue of the last executed command
 *  
 *  Position: new position in queue
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
void CommandList::SetPosition(int Position){
	FPosition = Position;
}
//---------------------------------------------------------------------------
/****************************************************
 *  CommandList::CreateOperation
 *  
 *  Description: create a new operation using parameter
 *  
 *  Url: URL of the operation
 *  Data: additional data for the operation
 *  MethodType: method used (POST, GET,...)
 *  ExpectedAnswer: expected answer from th operation
 *  AddToList: if true, created operation will be add to the queue of operations
 *  Return value: a pointer to a Net_Operation object with the information
 *  
 *  Note:
 ***************************************************/
Net_Operation *CommandList::CreateOperation(String Url, String Data, int MethodType, int ExpectedAnswer, String AnswerManager, bool AddToList){
	DEBUG_MGR(INFO_DEBUG,"CreateOperation to URL "+QUOTE_STRING(Url));
	Net_Operation *Out = (Net_Operation*)AllocMem(sizeof(Net_Operation));
	Out->Url = Url;
	Out->Data = Data;
	Out->MethodType = MethodType;
	Out->ExpectedAnswer = ExpectedAnswer;
	Out->AnswerManager = AnswerManager;
	if(AddToList){
		DEBUG_MGR(TOTAL_DEBUG,"Operation created: request to add to internal list");
		AddOperation(*Out);
	}
	return Out;
}
//---------------------------------------------------------------------------
int CommandList::GetOperationIndex(Net_Operation Op){
	DEBUG_MGR(INFO_DEBUG,"GetOperationIndex()");
	Net_Operation *Tmp;
	for(int a=0;a<CommandQueue->Count;a++){
		Tmp = (Net_Operation*)CommandQueue->Items[a];
		if(Tmp->Url == Op.Url){
			if(Tmp->Data == Op.Data){
				if(Tmp->MethodType == Op.MethodType){
					if(Tmp->ExpectedAnswer == Op.ExpectedAnswer){
						DEBUG_MGR(TOTAL_DEBUG,"Operation found at index "+IntToStr(a));
						return a;
					}
				}
			}
		}
	}
	DEBUG_MGR(ERR_DEBUG,"Operation not found!!!");
	return WEB_SOURCE_SAFETY_VALUE;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::TWebSource
 *  
 *  Description: class constructor
 *  
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
TWebSource::TWebSource():Base_Info(){
	InternalSetup();
};
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::TWebSource
 *  
 *  Description: class constructor with an owner
 *  
 *  AOwner: component owner of this class
 *  Return value:
 *  
 *  Note:
 ***************************************************/
TWebSource::TWebSource(TComponent *AOwner):Base_Info(){
	InternalSetup();
	Owner = AOwner;
	if(Owner->ClassName() == "TNetHTTPClient")
		FClient = (TNetHTTPClient*)Owner;
	else
		FClient = new TNetHTTPClient(Owner);
	if(FClient){
		FClient->ConnectionTimeout = CLIENT_CONNECTION_TIMEOUT;
		FClient->ResponseTimeout = CLIENT_RESPONSE_TIMEOUT;
		FClient->OnValidateServerCertificate = ManageCertificate;
		FClient->HandleRedirects = true;
	}
	MultipleRequest = 1;
	if(Owner)
		DEBUG_SRC(TOTAL_DEBUG,"TWebSource owner class: "+Owner->ClassName());
	else
		DEBUG_SRC(WARN_DEBUG,"TWebSource created without an owner");
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::InternalSetup
 *  
 *  Description: setup of internal value of the class
 *  
 *  Return value: 
 *  
 *  Note: INTERNAL USAGE ONLY!!!!
 ***************************************************/
void TWebSource::InternalSetup(){
	DEBUG_SRC(INFO_DEBUG,"Creating TWebSource class");
	Name = "WebSource";
	Tag = 0;
	ID = 0;
	Description = "Web source manager";
	Type = SHOW_SOURCE_INFO;
	
	TaskList = new TList();
	Parameters = new TStringList();
	Information = new TStringList();
	ShowNamePref = new TExtendedStringList();
	//ShowNamePref->Delimiter = '|';
	//ShowNamePref->StrictDelimiter = true;
	FClient = NULL;
	RequestList = new TList();
	QueueList = new TList();
	AuthRequest = true;
    RememberPreferences = true;
	PreferedLanguage = "English";
	OnInvalidAnswer = NULL;
	OnFindCandidate = NULL;
	OnFindShowData = NULL;
	OnConnectionError = NULL;
	//OnCreateCommandList = NULL;
	OnAddCommandList = NULL;
	OnRemoveCommandList = NULL;
	DEBUG_SRC(TOTAL_DEBUG,"Created TWebSource");
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::~TWebSource
 *  
 *  Description: class destructor
 *  
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
TWebSource::~TWebSource(){
	DEBUG_SRC(INFO_DEBUG,"~TWebSource()");
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::AddParameter
 *  
 *  Description: Add a parameter to the source
 *  
 *  Key: key for the parameter
 *  Value: value for the parameter
 *  Return value: result of the function (WEB_SOURCE_CORRECT if all correct)
 *  
 *  Note:
 ***************************************************/
int TWebSource::AddParameter(String Key, String Value, bool AddAsInformation){
	TJSONObject *Tmp;
	DEBUG_SRC(INFO_DEBUG,"AddParameter(): Key "+QUOTE_STRING(Key)+" - Value "+QUOTE_STRING(Value));
	if(AddAsInformation){
		DEBUG_SRC(TOTAL_DEBUG,"Data added as information");
		Information->AddPair(Key, Value);
	}
	else{
		DEBUG_SRC(TOTAL_DEBUG,"Data added as parameter");
		Parameters->AddPair(Key, Value);
	}
	return WEB_SOURCE_CORRECT;
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::RemoveParameter
 *  
 *  Description: remove a parameter from the source
 *  
 *  Key: parameter to remove
 *  Return value: result of the function (WEB_SOURCE_CORRECT if all correct) 
 *  
 *  Note:
 ***************************************************/
int TWebSource::RemoveParameter(String Key){
	int a;
	DEBUG_SRC(INFO_DEBUG,"RemoveParameter(): Key "+QUOTE_STRING(Key));
	a = Parameters->IndexOfName(Key);
	if(a != -1){
		DEBUG_SRC(TOTAL_DEBUG,"Key found as parameter at index "+IntToStr(a));
		Parameters->Delete(a);
		return WEB_SOURCE_CORRECT;
	}
	a = Information->IndexOfName(Key);
	if(a != -1){
		DEBUG_SRC(TOTAL_DEBUG,"Key found as information at index "+IntToStr(a));		
		Information->Delete(a);
		return WEB_SOURCE_CORRECT;
	}
	DEBUG_SRC(WARN_DEBUG,"Key not found");
	return WEB_SOURCE_INVALID_KEY;
}
//---------------------------------------------------------------------------
int TWebSource::ChangeParameter(String Key, String NewValue){
	int a;
	DEBUG_SRC(INFO_DEBUG,"ChangeParameter(): Key "+QUOTE_STRING(Key)+" - NewValue "+QUOTE_STRING(NewValue));
	a = Parameters->IndexOfName(Key);
	if(a != -1){
		DEBUG_SRC(TOTAL_DEBUG,"Key found as parameter at index "+IntToStr(a));
		Parameters->Values[Key] = NewValue;
		return WEB_SOURCE_CORRECT;
	}
	a = Information->IndexOfName(Key);
	if(a != -1){
		DEBUG_SRC(TOTAL_DEBUG,"Key found as information at index "+IntToStr(a));
		Information->Values[Key] = NewValue;
		return WEB_SOURCE_CORRECT;
	}
	DEBUG_SRC(WARN_DEBUG,"Key not found");
	return WEB_SOURCE_INVALID_KEY;
}
//---------------------------------------------------------------------------
int TWebSource::RenameParameter(String OldKey, String NewKey){
	int a;
	DEBUG_SRC(INFO_DEBUG,"RenameParameter(): old value "+QUOTE_STRING(OldKey)+(String)" -> new value "+QUOTE_STRING(NewKey));
	a = Parameters->IndexOfName(OldKey);
	if(a != -1){
		DEBUG_SRC(TOTAL_DEBUG,"Key found as parameter at index "+IntToStr(a));		
		String Value = Parameters->Values[OldKey];
		Parameters->Delete(a);
		Parameters->AddPair(NewKey, Value);
		return WEB_SOURCE_CORRECT;
	}
	a = Information->IndexOfName(OldKey);
	if(a != -1){
		DEBUG_SRC(TOTAL_DEBUG,"Key found as information at index "+IntToStr(a));		
		String Value = Information->Values[OldKey];
		Information->Delete(a);
		Information->AddPair(NewKey, Value);
		return WEB_SOURCE_CORRECT;
	}
	DEBUG_SRC(WARN_DEBUG,"Key not found");
	return WEB_SOURCE_INVALID_KEY;
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::AddCommandsList
 *  
 *  Description: add an existing command list to thi source 
 *  
 *  Cmd: a CommandList to add to this source
 *  Return value: result of the function (WEB_SOURCE_CORRECT if all correct)
 *  
 *  Note:
 ***************************************************/
int TWebSource::AddCommandsList(CommandList *Cmd, bool CloneIt){
	DEBUG_SRC(INFO_DEBUG,"AddCommandsList() -> Clone: "+(String)(CloneIt?"YES":"NO"));
	if(Cmd){		
		CommandList *Tmp;
		//Check later...
/*		for(int a=0;a<TaskList->Count;a++){
			Tmp = (CommandList*)TaskList->Items[a];
			if(Tmp->Type == Cmd->Type)
				return WEB_SOURCE_COMMAND_TYPE_EXIST;
		}*/
		DEBUG_SRC(TOTAL_DEBUG,"Adding command "+QUOTED(Cmd));
		if(CloneIt)
			Tmp = Cmd->Clone();
		else
			Tmp = Cmd;
		TaskList->Add(Tmp);
		if(OnAddCommandList)
			OnAddCommandList(Tmp);		
		return WEB_SOURCE_CORRECT;
	}
	DEBUG_SRC(ERR_DEBUG,"Invalid TCommandList object");
	return WEB_SOURCE_INVALID_COMMAND_LIST;
}
//---------------------------------------------------------------------------
int TWebSource::RemoveCommandsList(CommandList *Cmd){
	DEBUG_SRC(INFO_DEBUG,"RemoveCommandsList()");
	CommandList *Tmp;
	if(Cmd){
		for(int a=0;a<TaskList->Count;a++){
			Tmp = (CommandList*)TaskList->Items[a];
			if(Tmp->Name == Cmd->Name){
				if(Tmp->Description == Cmd->Description){
					if(Tmp->ID == Cmd->ID){
						if(Tmp->Type == Cmd->Type){
							if(Tmp->Tag == Cmd->Tag){
								DEBUG_SRC(TOTAL_DEBUG,"Found command list "+QUOTED(Cmd)+(String)" at index"+IntToStr(a));
								if(OnRemoveCommandList)
									OnRemoveCommandList(Tmp);
								TaskList->Delete(a);
								return WEB_SOURCE_CORRECT;
							}
						}
					}
				}
			}
		}
		DEBUG_SRC(WARN_DEBUG,"Command list not present");
	}
	else
		DEBUG_SRC(ERR_DEBUG,"Invalid TCommandList object");
	return WEB_SOURCE_INVALID_COMMAND_LIST;
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::CommandListExist
 *  
 *  Description: check if a command list exist in source
 *  
 *  Cmd: command list to check
 *  Return value: WEB_SOURCE_INVALID_COMMAND_LIST if command list is not loaded yet
 *  
 *  Note:
 ***************************************************/
int TWebSource::CommandListExist(CommandList *Cmd){
	DEBUG_SRC(INFO_DEBUG,"CommandListExist()");
	if(Cmd){
		CommandList *Tmp;
		DEBUG_SRC(TOTAL_DEBUG,"Search for command list "+QUOTED(Cmd));
		for(int a=0;a<TaskList->Count;a++){
			Tmp = (CommandList*)TaskList->Items[a];
			if(Tmp->Type == Cmd->Type)
				return WEB_SOURCE_COMMAND_TYPE_EXIST;
			if(Tmp->Name == Cmd->Name)
				return WEB_SOURCE_COMMAND_NAME_EXIST;
			if(Tmp->ID == Cmd->ID)
				return WEB_SOURCE_COMMAND_ID_EXIST;			
		}
		DEBUG_SRC(WARN_DEBUG,"Command list not present");
	}
	else
		DEBUG_SRC(ERR_DEBUG,"Invalid TCommandList object");	
	return WEB_SOURCE_INVALID_COMMAND_LIST;
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::SetClient
 *  
 *  Description: set a new TNetHTTPClient for the class
 *  
 *  Client: the new TNetHTTPClient
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
void TWebSource::SetClient(TNetHTTPClient *Client){
	FClient = Client;
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::GetClient
 *  
 *  Description: return the TNetHTTPClient of the class
 *  
 *  Return value: the TNetHTTPClient of the class
 *  
 *  Note:
 ***************************************************/
TNetHTTPClient *TWebSource::GetClient(){
	return FClient;
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::ExecuteCommand
 *  
 *  Description: execute a command list
 *  
 *  Mgr: command list to be executed
 *  Return value: result of the function (WEB_SOURCE_CORRECT if all correct)
 *  
 *  Note:
 ***************************************************/
int TWebSource::ExecuteCommand(CommandList *Mgr){
	DEBUG_SRC(INFO_DEBUG,"ExecuteCommand()");
	if(Mgr)
		DEBUG_SRC(TOTAL_DEBUG,"Executing CommandList '"+Mgr->Name+(String)"'");
	else
		DEBUG_SRC(ERR_DEBUG,"Invalid Commandlist in ExecuteCommand");
	QueueList->Add(Mgr);
	return UpdateQueueList();
}
//---------------------------------------------------------------------------
int TWebSource::DriveOperation(TNetHTTPRequest *Request, Net_Operation Op){
	int a, b, c;
	String Url,Data,T,X,Y;
	TStringList *Tmp;
	TStringList *Tmp2;
	TURLEncoding *Encoder = new TURLEncoding();
	//DEBUG_SRC(INFO_DEBUG,"DriveOperation -> "+Request->Name+(String)" - URL: "+Op.Url);
	DEBUG_SRC(INFO_DEBUG,"DriveOperation -> "+QUOTE_STRING(Request->Name)+(String)" - URL: "+QUOTE_STRING(Op.Url));
	Url = Op.Url;
	Data = Op.Data;
	Url = System::Strutils::AnsiReplaceStr(Url,START_PARAMETER+(String)LANGUAGE_IDENTIFIER_PARAMETER+END_PARAMETER,GetShortLanguage());
	Tmp = EnumParameters(Url);
	DEBUG_SRC(TOTAL_DEBUG,"Replacing "+IntToStr(Tmp->Count)+" parameter from URL "+QUOTE_STRING(Url));
	for(a=0;a<Tmp->Count;a++){
		T = Tmp->Strings[a];
		Url = System::Strutils::AnsiReplaceStr(Url,START_PARAMETER+T+END_PARAMETER,ShareParameter(T, false));
	}
	DEBUG_SRC(TOTAL_DEBUG,"Result URL "+QUOTE_STRING(Url));
	if(Data.Length()>0){
		if(Data.Pos(START_CLIENT_PARAMETER)>0){
			Data = System::Strutils::AnsiReplaceStr(Data,START_PARAMETER+(String)LANGUAGE_IDENTIFIER_PARAMETER+END_PARAMETER,GetShortLanguage());
			Tmp = EnumClientSet(Data);
			DEBUG_SRC(TOTAL_DEBUG,"Replacing "+IntToStr(Tmp->Count)+" client sets from DATA "+QUOTE_STRING(Data));
			for(a=0;a<Tmp->Count;a++){
				T = Tmp->Strings[a];
				Tmp2 = EnumParameters(T);
				for(b=0;b<Tmp2->Count;b++){
					X = Tmp2->Strings[b];
					T = System::Strutils::AnsiReplaceStr(T,START_PARAMETER+X+END_PARAMETER,ShareParameter(X, false));
				}
				b = T.Pos(CLIENT_PARAMETER_SEPARATOR);
				if(b > 0){
					X = T.SubString(0,b - 1);
					Y = T.SubString(b+1,T.Length());
					DEBUG_SRC(TOTAL_DEBUG,"Custom header found: type "+QUOTE_STRING(X)+(String)" - value "+QUOTE_STRING(Y));
					Request->CustomHeaders[X] = Y;
				}
			}
			DEBUG_SRC(TOTAL_DEBUG,"Removing header data...");
			a = Data.LastDelimiter(END_CLIENT_PARAMETER);
			Data = Data.SubString(a + 1,Data.Length());
			DEBUG_SRC(TOTAL_DEBUG,"Result data "+QUOTE_STRING(Data));
		}
		Tmp = EnumParameters(Data);
		DEBUG_SRC(TOTAL_DEBUG,"Replacing "+IntToStr(Tmp->Count)+" parameters from DATA "+QUOTE_STRING(Data));				
		for(a=0;a<Tmp->Count;a++){
			T = Tmp->Strings[a];
			Data = System::Strutils::AnsiReplaceStr(Data,START_PARAMETER+T+END_PARAMETER,ShareParameter(T, false));
		}
		DEBUG_SRC(TOTAL_DEBUG,"Result data "+QUOTE_STRING(Data));
	}
	//Url = Encoder->Encode(Url);
	switch(Op.MethodType){
		case METHOD_POST:{
			//DEBUG_SRC(TOTAL_DEBUG,"Post command: URL '"+Url+"' - Data:'"+Data+"'");
			DEBUG_SRC(TOTAL_DEBUG,"Post command: URL "+QUOTE_STRING(Url)+(String)" - Data "+QUOTE_STRING(Data));
			TStringStream *Stream = new TStringStream(Data);
			Request->Post(Url, Stream);
		}break;
		case METHOD_GET:{
			//DEBUG_SRC(TOTAL_DEBUG,"Get command: URL '"+Url+"'");
			DEBUG_SRC(TOTAL_DEBUG,"Get command: URL "+QUOTE_STRING(Url));
			Request->Get(Url);
		}break;
	}	
	return WEB_SOURCE_CORRECT;
}
//---------------------------------------------------------------------------
int TWebSource::TestOperation(Net_Operation Op, TRequestCompletedEvent ReqCompleted, TRequestErrorEvent ReqError){
	DEBUG_SRC(INFO_DEBUG,"TestOperation: ReqCompleted function = "+(String)(ReqCompleted==NULL?"YES":"NO")+(String)" - ReqError function = "+(String)(ReqError==NULL?"YES":"NO"));
	TNetHTTPRequest *Request;
	Request = new TNetHTTPRequest(FClient);
	Request->Client = FClient;
	Request->Asynchronous = true;
	Request->OnRequestCompleted = HTTPRequestCompleted;
	Request->OnRequestError = HTTPRequestError;
	WebSource_Data *Tmp = (WebSource_Data*)AllocMem(sizeof(WebSource_Data));
	Tmp->Request = Request;
	Tmp->RequestStatus = HTTP_REQUEST_STANDBY;
	Tmp->WorkingMode = REQUEST_TEST_OPERATION;
	if(ReqCompleted)
		Tmp->ReqCompleted = ReqCompleted;
	if(ReqError)
		Tmp->ReqError = ReqError;
	Tmp->LastOperation = Op;
	Request->Tag = (int)Tmp;
	return DriveOperation(Request, Op);
}
//---------------------------------------------------------------------------
int TWebSource::TestCommand(CommandList *Mgr, TRequestCompletedEvent ReqCompleted, TRequestErrorEvent ReqError){
	DEBUG_SRC(INFO_DEBUG,"TestCommand: ReqCompleted function = "+(String)(ReqCompleted==NULL?"YES":"NO")+(String)" - ReqError function = "+(String)(ReqError==NULL?"YES":"NO"));
	if(Mgr == NULL){
		DEBUG_SRC(ERR_DEBUG,"Invalid command list");
		return WEB_SOURCE_INVALID_COMMAND_MANAGER;
	}
	TNetHTTPRequest *Request;
	Request = new TNetHTTPRequest(FClient);
	Request->Client = FClient;
	Request->Asynchronous = true;
	Request->OnRequestCompleted = HTTPRequestCompleted;
	Request->OnRequestError = HTTPRequestError;
	WebSource_Data *Tmp = (WebSource_Data*)AllocMem(sizeof(WebSource_Data));
	Tmp->Request = Request;
	Tmp->RequestStatus = HTTP_REQUEST_STANDBY;
	Tmp->WorkingMode = REQUEST_TEST_COMMAND;
	Tmp->Command = Mgr;
	if(ReqCompleted)
		Tmp->ReqCompleted = ReqCompleted;
	if(ReqError)
		Tmp->ReqError = ReqError;
	Tmp->LastOperation = Mgr->GetOperation(0);
	Mgr->Position = 0;
	Request->Tag = (int)Tmp;
	Request->Asynchronous = true;
	return DriveOperation(Request, Mgr->GetOperation(0));
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::DriveCommand
 *  
 *  Description: send a single command to the client as request
 *  
 *  Request: the request that manage the command
 *  Mgr: the CommandList object that contains command list to execute
 *  Index: index of the command to be executed
 *  Return value: result of the function (WEB_SOURCE_CORRECT if all correct)
 *  
 *  Note:
 ***************************************************/
int TWebSource::DriveCommand(TNetHTTPRequest *Request, CommandList *Mgr, int Index){
	DEBUG_SRC(INFO_DEBUG,"DriveCommand()");
	if(Mgr == NULL){
		DEBUG_SRC(ERR_DEBUG,"Invalid commmand list");
		return WEB_SOURCE_INVALID_COMMAND_MANAGER;
	}
	if(Request == NULL){
		DEBUG_SRC(ERR_DEBUG,"Invalid HTTPRequest");
		return WEB_SOURCE_INVALID_HTTPREQUEST;
	}
	if(Index < 0 || Index > Mgr->GetNumOperations()){
		DEBUG_SRC(ERR_DEBUG,"Invalid command index ("+IntToStr(Index)+(String)")");
		return WEB_SOURCE_INVALID_COMMAND_INDEX;
	}
	int a;
	Net_Operation Op = Mgr->GetOperation(Index);
	Mgr->Position = Index;
	return DriveOperation(Request, Op);
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::EnumParameters
 *  
 *  Description: enum parameters inside a string
 *  
 *  Source: string to be analized
 *  Return value: a TStringList object with founded parameters
 *  
 *  Note:
 ***************************************************/
TStringList *TWebSource::EnumParameters(String Source){
	DEBUG_SRC(INFO_DEBUG,"EnumParameters: source "+QUOTE_STRING(Source));
	return GenericEnumData(Source, START_PARAMETER, END_PARAMETER);
}
//---------------------------------------------------------------------------
TStringList *TWebSource::EnumClientSet(String Source){
	DEBUG_SRC(INFO_DEBUG,"EnumClientSet: source "+QUOTE_STRING(Source));
	return GenericEnumData(Source, START_CLIENT_PARAMETER, END_CLIENT_PARAMETER);
}
//---------------------------------------------------------------------------
TStringList *TWebSource::GenericEnumData(String Source, String StartData, String EndData){
	DEBUG_SRC(INFO_DEBUG,"GenericEnumData()");
	TStringList *Out = new TStringList();
	String Pattern;
	String Tmp;
	TMatchCollection Items;
	TRegEx *RegEx;
	Pattern = Format("%s(.*?)%s",ARRAYOFCONST((StartData,EndData)));
	RegEx = new TRegEx(Pattern,TRegExOptions());
	Items = RegEx->Matches(Source);
	DEBUG_SRC(TOTAL_DEBUG,"Found "+IntToStr(Items.Count)+(String)" items");
	for(int a=0;a<Items.Count;a++){
		Tmp = Items[a].Value;
		Tmp = System::Strutils::AnsiReplaceStr(Tmp,StartData,"");
		Tmp = System::Strutils::AnsiReplaceStr(Tmp,EndData,"");
		DEBUG_SRC(TOTAL_DEBUG,"Item "+IntToStr(a)+(String)" -> "+QUOTE_STRING(Tmp));
		Out->Add(Tmp);
	}
	return Out;
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::ShareParameter
 *  
 *  Description: return parameters/information collected from the source
 *  
 *  Key: parameter/information to be return
 *  Return value: parameter/information value
 *  
 *  Note:
 ***************************************************/
String TWebSource::ShareParameter(String Key, bool InsertWithQuotation){
	String Out;
	DEBUG_SRC(INFO_DEBUG,"ShareParameter: key "+QUOTE_STRING(Key)+(String)" - Quote: "+(String)(InsertWithQuotation?"YES":"NO"));
	int a = Parameters->IndexOfName(Key);
	if(a != -1){
		Out = Parameters->Values[Key];
		DEBUG_SRC(TOTAL_DEBUG,"Key found as Parameter at index "+IntToStr(a)+(String)" - Value: "+QUOTE_STRING(Out));		
		if(InsertWithQuotation)
			return "\""+Out+(String)"\"";
		else
			return Out;
	}
	a = Information->IndexOfName(Key);
	if(a != -1){
		Out = Information->Values[Key];
		DEBUG_SRC(TOTAL_DEBUG,"Key found as Information at index "+IntToStr(a)+(String)" - Value: "+QUOTE_STRING(Out));		
		if(InsertWithQuotation)
			return "\""+Out+(String)"\"";
		else
			return Out;
	}
	return "";
}
//---------------------------------------------------------------------------
int TWebSource::DecodeXMLAnswer(String Answer, Net_Operation Operation, CommandList *Cmd){
	int a,b,c,d,e;
	DEBUG_SRC(INFO_DEBUG,"DecodeXMLAnswer()");
	TXMLDocument *Doc = new TXMLDocument(Owner);
	TStringList *Op = new TStringList();
	TList *NodeList = new TList();
	IXMLNode *Node,*FirstNode;
	IXMLNode *SubNode;
	IXMLNode *DataNode,*InnerNode;
	String Diagnostic = "";
	String ArrayID = "", ShowNameID = "";
	String ShowNameTitle = "", ShowEpisode ="";
	String EpisodeTitle = "";
	int EpNumber, EpSeason;

	String OutputTitle = "";
	String Txt;
	String BestLang = "";
	TList *Info = new TList();
	for(a=0;a<ISO_639_LEN;a++){
		if(Language639[a].EnglishName == PreferedLanguage){
			BestLang = Language639[a].Abbreviation;
			break;
		}
	}
	Op->Delimiter = ';';
	Op->DelimitedText = Operation.AnswerManager;
	for(a=0;a<Op->Count;a++){
		if(Op->Names[a] == "ARRAY_ID"){
			ArrayID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+("ARRAY_ID:"+QUOTE_STRING(ArrayID));
		}
		if(Op->Names[a] == "ARRAY_SHOW_ID"){
			ShowNameID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" ARRAY_SHOW_ID:"+QUOTE_STRING(ShowNameID));
		}
		if(Op->Names[a] == "SHOW_TITLE"){
			ShowNameTitle = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" SHOW_TITLE:"+QUOTE_STRING(ShowNameTitle));
		}
		if(Op->Names[a] == "SHOW_EPISODE_ID"){
			ShowEpisode = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" SHOW_EPISODE_ID:"+QUOTE_STRING(ShowEpisode));
		}
	}
	Doc->LoadFromXML(Answer);
	Doc->Active=true;
	Doc->Options = TXMLDocOptions();
	Node = Doc->DocumentElement;
	b = 0;
	NodeList->Add(Doc->DocumentElement);
	do{
		Node = (IXMLNode*)NodeList->Items[b];
		for(a=0;a<Node->ChildNodes->Count;a++)
			NodeList->Add(Node->ChildNodes->Nodes[a]);
		b++;
	}while(b < NodeList->Count);                 //ixmlnodelist
	if(ArrayID != ""){
		Candidate_Information *Candidate;
		for(a=0;a<NodeList->Count;a++){
			Node = (IXMLNode*)NodeList->Items[a];
			if(Node->NodeName == ArrayID){
				if(ShowNameID != ""){
					for(b=0;b<Node->ChildNodes->Count;b++){
						SubNode = Node->ChildNodes->Nodes[b];
						Txt = SubNode->Attributes[ShowNameID];
						if(Txt != ""){
							Candidate = (Candidate_Information*)AllocMem(sizeof(Candidate_Information));
							Candidate->ID = Txt;
							for(c=0;c<SubNode->ChildNodes->Count;c++){
								DataNode = SubNode->ChildNodes->Nodes[c];
								if(c==0){
									if(DataNode->Text != "")
										Candidate->Name = DataNode->Text;
								}
								Txt = DataNode->Attributes["lang"];     //Search for lang...
								if(Txt == BestLang){
									if(DataNode->Text != "")
										Candidate->Name = DataNode->Text;
								}
							}
							Info->Add(Candidate);
						}
					}
				}
				switch(Cmd->Type){
					case QUERY_CANDIDATE:{
						if(OnFindCandidate)
							OnFindCandidate(Cmd->SearchInfo,Cmd->ID,Info);
						return WEB_SOURCE_CORRECT;
					}break;
				}
				break;
			}
		}
	}
	if(ShowNameTitle != ""){
		ShowResultDetails Details;
		EpNumber = 0;
		EpSeason = 0;
		for(a=0;a<NodeList->Count;a++){
			Node = (IXMLNode*)NodeList->Items[a];
			if(Node->NodeName == ShowNameTitle){
				for(b=0;b<Node->ChildNodes->Count;b++){
					SubNode = Node->ChildNodes->Nodes[b];
					Txt = SubNode->Attributes["lang"];
					if(Txt == "")
						Txt = SubNode->Attributes["xml:lang"];
					if(Txt != ""){
						if(Txt == BestLang)
							OutputTitle = SubNode->Text;
						if(Txt == "en"){
							if(OutputTitle == "")
								OutputTitle = SubNode->Text;
						}
					}
				}
			}
			if(Node->NodeName == ShowEpisode){
				for(b=0;b<Node->ChildNodes->Count;b++){
					SubNode = Node->ChildNodes->Nodes[b];
					for(c=0;c<SubNode->ChildNodes->Count;c++){
						DataNode = SubNode->ChildNodes->Nodes[c];
						if(DataNode->NodeName == "epno"){
							d = StrToIntDef(DataNode->Text,-1);
							if(d == Cmd->Tag % 1000){
								EpNumber = d;
								EpSeason = 1;
							}
						}
						if(EpNumber){
							if(DataNode->NodeName == "title"){
								Txt = DataNode->Attributes["lang"];
								if(Txt == "")
									Txt = DataNode->Attributes["xml:lang"];
								if(Txt != ""){
									if(Txt == BestLang)
										EpisodeTitle = DataNode->Text;
									if(Txt == "en"){
										if(EpisodeTitle == "")
											EpisodeTitle = DataNode->Text;
									}
								}
							}
						}
					}
					if(EpNumber)
						break;
				}
			}
		}
		if(OnFindShowData){
			Details.EpisodeTitle = EpisodeTitle;
			OnFindShowData(Cmd->SearchInfo,EpSeason,EpNumber,Cmd->ID,Details);
			return WEB_SOURCE_CORRECT;
		}
	}
	return WEB_SOURCE_CORRECT;
}
//---------------------------------------------------------------------------
int TWebSource::DecodeHTMLAnswer(String Answer, Net_Operation Operation, CommandList *Cmd){
	TMyHTMLParser *Parser = new TMyHTMLParser();
	Parser->LoadFromString(Answer);
	return WEB_SOURCE_CORRECT;
}
//---------------------------------------------------------------------------
int TWebSource::DecodeAnswer(String Answer, Net_Operation Operation, CommandList *Cmd){
	DEBUG_SRC(INFO_DEBUG,"DecodeAnswer()");
	if(Cmd == NULL){
		DEBUG_SRC(WARN_DEBUG,"Invalid command list: execution in REQUEST_TEST_COMMAND|REQUEST_TEST_OPERATION");
		//return WEB_SOURCE_INVALID_COMMAND_MANAGER;
	}
	if(Answer == ""){
		DEBUG_SRC(ERR_DEBUG,"No answer from server!!!");
		return WEB_SOURCE_INVALID_ANSWER;
	}
	int a;
	TStringList *Op = new TStringList();
	TStringList *ParameterToSave = new TStringList();
	TJSONObject *Element;
	TJSONArray *Array;
	TJSONPair *Pair;
	TJSONObject *Obj;
	String ArrayID = "",ShowNameID = "",TitleID = "",PosterID = "";
	String MovieNameID = "",SummaryID = "",AerialID = "";
	String RootPoster = "",ShowTitleID = "";
	String MovieName = "",ReleaseDate = "";
	String Txt;
	String Diagnostic = "";
	Txt = Answer.TrimLeft();
	if(Txt[1] == '<'){
		a = Txt.Pos("?xml");
		if(a > 0 && a < 5){
			return DecodeXMLAnswer(Answer, Operation, Cmd);
		}
		a = Txt.Pos("!DOCTYPE");
		if(a > 0 && a < 5){
			return DecodeHTMLAnswer(Answer, Operation, Cmd);
		}
		return WEB_SOURCE_INVALID_ANSWER;
	}
	Obj = (TJSONObject*) TJSONObject::ParseJSONValue(Answer);
	Op->Delimiter = ';';
	Txt = Operation.AnswerManager;
	Op->DelimitedText = Operation.AnswerManager;
	for(a=0;a<Op->Count;a++){
		if(Op->Names[a] == "ARRAY_ID"){
			ArrayID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+("ARRAY_ID:"+QUOTE_STRING(ArrayID));
		}
		if(Op->Names[a] == "SAVE_INFORMATION"){
			ParameterToSave->Add(Op->ValueFromIndex[a]);
		}
		if(Op->Names[a] == "ARRAY_TITLE_ID"){
			TitleID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" ARRAY_TTILE_ID:"+QUOTE_STRING(TitleID));
		}
		if(Op->Names[a] == "ARRAY_SHOW_ID"){
			ShowNameID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" ARRAY_SHOW_ID:"+QUOTE_STRING(ShowNameID));
		}
		if(Op->Names[a] == "ARRAY_MOVIE_ID"){
			MovieNameID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" ARRAY_MOVIE_ID:"+QUOTE_STRING(MovieNameID));
		}
		if(Op->Names[a] == "ARRAY_SUMMARY_ID"){
			SummaryID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" ARRAY_SUMMARY_ID:"+QUOTE_STRING(SummaryID));
		}
		if(Op->Names[a] == "ARRAY_AERIAL_ID"){
			AerialID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" ARRAY_AERIAL_ID:"+QUOTE_STRING(AerialID));
		}
		if(Op->Names[a] == "ARRAY_POSTER_ID"){
			PosterID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" ARRAY_POSTER_ID:"+QUOTE_STRING(PosterID));
		}
		if(Op->Names[a] == "ARRAY_SHOW_NAME_ID"){
			ShowTitleID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+(" ARRAY_SHOW_NAME_ID:"+QUOTE_STRING(ShowTitleID));
		}		
		if(Op->Names[a] == "ROOT_POSTER"){
			RootPoster = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+("ROOT_POSTER:"+QUOTE_STRING(RootPoster));
		}
/*		if(Op->Names[a] == "TV_SHOW_NAME_ID"){
			ShowTitleID = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+("TV_SHOW_NAME_ID:"+QUOTE_STRING(ShowTitleID));
		}*/
		if(Op->Names[a] == "ARRAY_MOVIE_NAME_ID"){
			MovieName = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+("ARRAY_MOVIE_NAME:"+QUOTE_STRING(MovieName));
		}		
		if(Op->Names[a] == "ARRAY_RELEASE_ID"){
			ReleaseDate = Op->ValueFromIndex[a];
			Diagnostic = Diagnostic+("ARRAY_RELEASE_ID:"+QUOTE_STRING(ReleaseDate));
		}			
	}
	Diagnostic = Diagnostic+" Parameter("+IntToStr(ParameterToSave->Count)+"):";
	for(a=0;a<ParameterToSave->Count;a++){
		Txt = Obj->Get(ParameterToSave->Strings[a])->JsonValue->ToString();
		if(Txt.Pos("\"") == 1)
			Txt = Txt.SubString(2,Txt.Length()-1);
		if(Txt.Pos("\"") == Txt.Length())
			Txt = Txt.SubString(1,Txt.Length()-1);
		Diagnostic = Diagnostic + QUOTE_STRING(ParameterToSave->Strings[a])+(String)":"+QUOTE_STRING(Txt);
		AddParameter(ParameterToSave->Strings[a],Txt,true);
	}
	DEBUG_SRC(TOTAL_DEBUG,"Data expected: "+Diagnostic);
	if(ArrayID != ""){
		if(Cmd == NULL || Cmd->Type == QUERY_CANDIDATE || Cmd->Type == QUERY_SHOW_TITLE)
		{
			Candidate_Information *Candidate;
			TList *Info = new TList();
			Array = (TJSONArray*)Obj->Get(ArrayID)->JsonValue;
			for(a=0;a<Array->Size();a++){
				Element = (TJSONObject*)Array->Get(a);
				Candidate = (Candidate_Information*)AllocMem(sizeof(Candidate_Information));
				if(ShowNameID != ""){
					Pair = Element->Get(ShowNameID);
					if(Pair){
						Txt = Pair->JsonValue->Value();
						Candidate->Name = Txt;
					}
				}
				if(TitleID != ""){
					Pair = Element->Get(TitleID);
					if(Pair){
						Txt = Pair->JsonValue->Value();
						Candidate->ID = Txt;
					}
				}
				if(AerialID != ""){
					Pair = Element->Get(AerialID);
					if(Pair){
						Txt = Pair->JsonValue->Value();
						Candidate->Aerial = Txt;
					}
				}
				if(SummaryID != ""){
					Pair = Element->Get(SummaryID);
					if(Pair){
						Txt = Pair->JsonValue->Value();
						Candidate->Summary = Txt;
					}
				}
				if(PosterID != ""){
					Pair = Element->Get(PosterID);
					if(Pair){
						Txt = Pair->JsonValue->Value();
						if(Txt != "null")
							if(Txt != "")
								Candidate->Poster = RootPoster + Txt;
							else
								Candidate->Poster = "";
						else
							Candidate->Poster = "";
					}
				}
				if(ShowTitleID != ""){
					Pair = Element->Get(ShowTitleID);
					if(Pair){
						ShowResultDetails Details;
						Txt = Pair->JsonValue->Value();
						Details.EpisodeTitle = Txt;
						if(OnFindShowData){
							DEBUG_SRC(TOTAL_DEBUG,"OnFindShowData available for "+Details.EpisodeTitle);
							OnFindShowData(Cmd->SearchInfo,Cmd->Tag/1000,Cmd->Tag % 1000,Cmd->ID,Details);
						}
						return WEB_SOURCE_CORRECT;
					}
				}	
				if(MovieName != ""){
					Pair = Element->Get(MovieName);
					if(Pair){
						Txt = Pair->JsonValue->Value();
						Candidate->Name = Txt;
					}					
				}
				if(ReleaseDate != ""){
					Pair = Element->Get(ReleaseDate);
					if(Pair){
						Txt = Pair->JsonValue->Value();
						Candidate->Release = Txt;
					}									
				}
				Info->Add(Candidate);
			}
			switch(Cmd->Type){
				case QUERY_CANDIDATE:{
					if(OnFindCandidate){
						DEBUG_SRC(TOTAL_DEBUG, "OnFindCandidate available for "+QUOTE_STRING(Cmd->SearchInfo)+(String)" - ID: "+IntToStr(Cmd->ID));
						OnFindCandidate(Cmd->SearchInfo,Cmd->ID,Info);
					}
                   	return WEB_SOURCE_CORRECT;
				}break;
				case QUERY_SHOW_TITLE:{
					
				}break;
			}
		}
	}
	if(Cmd == NULL || Cmd->Type == QUERY_SHOW_TITLE){
		ShowResultDetails Details;
		if(ShowTitleID != ""){
			Txt = Obj->Get(ShowTitleID)->JsonValue->ToString();
			if(Txt.Pos("\"") == 1)
				Txt = Txt.SubString(2,Txt.Length()-1);
			if(Txt.Pos("\"") == Txt.Length())
				Txt = Txt.SubString(1,Txt.Length()-1);
			Details.EpisodeTitle = Txt;
			if(OnFindShowData){
				DEBUG_SRC(TOTAL_DEBUG,"OnFindShowData available for "+Details.EpisodeTitle);
				OnFindShowData(Cmd->SearchInfo,Cmd->Tag/1000,Cmd->Tag%1000,Cmd->ID,Details);
			}
		}
	}
	return WEB_SOURCE_CORRECT;
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::HTTPRequestCompleted
 *  
 *  Description: function that manage server answer
 *  
 *  Sender: a TNetHTTPRequest that generate this answer
 *  AResponse: server's answer
 *  Return value: 
 *  
 *  Note:
 ***************************************************/
void __fastcall TWebSource::HTTPRequestCompleted(TObject *Sender, _di_IHTTPResponse  AResponse){
	String Answer = AResponse->ContentAsString();
	DEBUG_SRC(INFO_DEBUG,"HTTPRequestCompleted: "+Answer);
	TNetHTTPRequest *Request = (TNetHTTPRequest*)Sender;
    DEBUG_SRC(TOTAL_DEBUG,"Answer from request "+QUOTE_STRING(Request->Name));
	WebSource_Data *Info = (WebSource_Data*)Request->Tag;
	if(Info->LastOperation.ExpectedAnswer){
		if(Info->LastOperation.ExpectedAnswer != AResponse->StatusCode){
			DEBUG_SRC(ERR_DEBUG,"Invalid answer from server: status code expected "+IntToStr(Info->LastOperation.ExpectedAnswer)+(String)" - Received "+IntToStr(AResponse->StatusCode));
			if(OnInvalidAnswer){
				DEBUG_SRC(ERR_DEBUG,"OnInvalidAnswer executed");
				OnInvalidAnswer(Request, Info->LastOperation, Info->Command, Info->LastOperation.ExpectedAnswer, AResponse->StatusCode);
			}
			else{
				String Err = "Error on source "+QUOTE_STRING(Name)+(String)" - Cmd: "+QUOTED(Info->Command)+(String)"\r\n";
				Err += "Statuscode: expected "+IntToStr(Info->LastOperation.ExpectedAnswer)+(String)" - received "+IntToStr(AResponse->StatusCode);
				Err = Err+(String)"\r\n"+AResponse->ContentAsString();
				TDialogServiceSync::MessageDialog(Err,TMsgDlgType::mtError,DIALOG_OK,TMsgDlgBtn(),THelpContext());
			}
			Info->RequestStatus = HTTP_REQUEST_STANDBY;
			return;
		}
	}
	if(Info){
		switch(Info->WorkingMode){
			case REQUEST_TEST_COMMAND:{
				int Res;
				DEBUG_SRC(TOTAL_DEBUG,"REQUEST_TEST_COMMAND -> Decoding answer...");
				if(Info->LastOperation.AnswerManager.Length()>0)
					Res = DecodeAnswer(Answer,Info->LastOperation, Info->Command);
				Res = Info->Command->GetNumOperations();
				Res = Info->Command->Position + 1;
				if(Info->Command->GetNumOperations() > Res){
					DEBUG_SRC(TOTAL_DEBUG,"Executing operation "+ IntToStr(Info->Command->Position + 1)+(String)"/"+IntToStr(Info->Command->GetNumOperations()));
					Info->Command->Position = Info->Command->Position + 1;
					Info->LastOperation = Info->Command->GetOperation(Info->Command->Position);
					DriveOperation(Info->Request, Info->Command->GetOperation(Info->Command->Position));
				}
				if(Info->ReqCompleted){
					DEBUG_SRC(TOTAL_DEBUG,"ReqCompleted function available");
					Info->ReqCompleted(Sender, AResponse);
				}
			}break;
			case REQUEST_NORMAL_FLOW:{
				DEBUG_SRC(TOTAL_DEBUG,"REQUEST_NORMAL_FLOW -> Decoding answer...");
				if(Info->LastOperation.AnswerManager.Length()>0)
					DecodeAnswer(Answer,Info->LastOperation, Info->Command);
				if(Info->Command->GetNumOperations() > Info->Command->Position + 1){
					DEBUG_SRC(TOTAL_DEBUG,"Continue command "+QUOTE_STRING(Info->Command->Name)+(String)": operation "+IntToStr(Info->Command->Position + 1)+(String)"/"+IntToStr(Info->Command->GetNumOperations()));
					Info->Command->Position = Info->Command->Position + 1;
					Info->LastOperation = Info->Command->GetOperation(Info->Command->Position);
					DriveOperation(Info->Request, Info->Command->GetOperation(Info->Command->Position));
				}else{
					Info->RequestStatus = HTTP_REQUEST_STANDBY;
					UpdateQueueList();
					DEBUG_SRC(TOTAL_DEBUG,"Command "+QUOTE_STRING(Info->Command->Name)+(String)" completed");
					if(Info->ReqCompleted){
						DEBUG_SRC(TOTAL_DEBUG,"Executing ReqCompleted on command "+QUOTE_STRING(Info->Command->Name));
						Info->ReqCompleted(Sender, AResponse);
					}
					//DEBUG_SRC(TOTAL_DEBUG,"Now value "+QUOTE_STRING(Request->Name));
				}
			}break;
			case REQUEST_TEST_OPERATION:{
				DEBUG_SRC(TOTAL_DEBUG,"REQUEST_TEST_OPERATION -> Decoding answer...");
				int Res = DecodeAnswer(Answer,Info->LastOperation, Info->Command);
				if(Info->ReqCompleted){
					DEBUG_SRC(TOTAL_DEBUG,"ReqCompleted function available");
					Info->ReqCompleted(Sender, AResponse);
				}
			}break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TWebSource::HTTPRequestError(TObject* Sender, String AError){
	TNetHTTPRequest *Request = (TNetHTTPRequest*)Sender;
	DEBUG_SRC(INFO_DEBUG,"HTTPRequestError: "+AError);
	WebSource_Data *Data;
	if(Request){
		Data = (WebSource_Data*)Request->Tag;
		if(Data){
			String ErrCode = AError;
			int Code;
			ErrCode = TRegEx::Replace(ErrCode, "\\D","");
			Code = StrToIntDef(ErrCode, -1);
			if(AError.Pos("-")>0)
				Code = Code * (-1);
			if(Code != -1){
				if(OnConnectionError){
					DEBUG_SRC(TOTAL_DEBUG,"Executing OnConnectionError");
					OnConnectionError(FClient,Request,Data->Command,Data->Command->Position,Code,AError);
				}
				else
					TDialogServiceSync::MessageDialog("Error "+ErrCode,TMsgDlgType::mtInformation,DIALOG_OK,TMsgDlgBtn(),THelpContext());
			}
			Data->RequestStatus = HTTP_REQUEST_STANDBY;
			UpdateQueueList();
		}
	}
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::Clone
 *  
 *  Description: clone this source
 *  
 *  AOwner: optional Owner of the cloned object
 *  Return value: a cloned object
 *  
 *  Note:
 ***************************************************/
TWebSource *TWebSource::Clone(TComponent *AOwner){
	TWebSource *Out;
	DEBUG_SRC(INFO_DEBUG,"Clone()");
	int a;
	CommandList *Mgr,*Dest;
	TJSONPair *Pair;
	String A,B;
	if(AOwner)
		Out = new TWebSource(AOwner);
	else{
		DEBUG_SRC(WARN_DEBUG,"NULL owner!!!");
		if(Owner)
			Out = new TWebSource(Owner);
		else
			Out = new TWebSource();
	}
	Out->Name = Name;
	Out->ID = ID;
	Out->Tag = Tag;
	Out->Type = Type;
	Out->Description = Description;
	Out->AuthRequest = AuthRequest;
	Out->PreferedLanguage = PreferedLanguage;
	Out->RememberPreferences = RememberPreferences;
	for(a=0;a<TaskList->Count;a++){
		Mgr = (CommandList*)TaskList->Items[a];
		Dest = Mgr->Clone();
		Out->AddCommandsList(Dest);
	}
	for(a=0;a<Parameters->Count;a++){
		//Out->AddParameter(Parameters->Pairs[a]->JsonString->ToString(),Parameters->Pairs[a]->JsonValue->ToString());
		Out->AddParameter(Parameters->Names[a],Parameters->ValueFromIndex[a]);
	}
	for(a=0;a<GetNumShowNamePref();a++){
		A = GetShowNamePrefNameByIndex(a);
		B = GetShowNamePrefByIndex(a);
        Out->AddShowNamePref(A, B);
	}
	Out->OnConnectionError = OnConnectionError;
	Out->OnInvalidAnswer = OnInvalidAnswer;
	Out->OnFindCandidate = OnFindCandidate;
	Out->OnFindShowData = OnFindShowData;
	Out->OnAddCommandList = OnAddCommandList;
	Out->OnRemoveCommandList = OnRemoveCommandList;
	return Out;
}
//---------------------------------------------------------------------------
int TWebSource::UpdateQueueList(){
	DEBUG_SRC(INFO_DEBUG,"UpdateQueueList: items in list "+IntToStr(QueueList->Count));
	if(QueueList->Count > 0){
		CommandList *Cmd;
		TNetHTTPRequest *Request;
		Cmd = (CommandList*)QueueList->Items[0];
		WebSource_Data *Data;
		for(int a=0;a<RequestList->Count;a++){
			Request = (TNetHTTPRequest*)RequestList->Items[a];
			if(Request){
				Data = (WebSource_Data*)Request->Tag;
				if(Data->RequestStatus == HTTP_REQUEST_STANDBY){
					DEBUG_SRC(TOTAL_DEBUG,"Found an empty request: complete information on "+QUOTE_STRING(Request->Name));
					Data->Command = Cmd;
					Data->RequestStatus = HTTP_EXECUTING_COMMAND_MANAGER;
					Data->WorkingMode = REQUEST_NORMAL_FLOW;
					Data->LastOperation = Cmd->GetOperation(0);
					//DriveCommand(Request,Data->Command,0);
					Cmd->Position = 0;
					QueueList->Delete(0);
					return DriveOperation(Request, Cmd->GetOperation(0));
				}
			}
		}
		DEBUG_SRC(WARN_DEBUG,"No empty request found!!!");
	}
	return WEB_SOURCE_EMPTY_QUEUE;
}
//---------------------------------------------------------------------------
/****************************************************
 *  TWebSource::CreateCommandList
 *  
 *  Description: create a new command list using the parameter
 *  
 *  Name: name for the command list
 *  Desc: description
 *  ID: ID of the new command list
 *  Type: type of command list
 *  Tag: tag for the command list
 *  AddToList: if true, command list will be added to the source
 *  Return value: the command list created
 *  
 *  Note:
 ***************************************************/
CommandList *TWebSource::CreateCommandList(String Name,String Desc,int ID,int Type,int Tag,bool AddToList){
	DEBUG_SRC(INFO_DEBUG,"CreateCommandList -> "+QUOTE_STRING(Name));
	CommandList *Cmd = new CommandList();
	Cmd->Name = Name;
	Cmd->Description = Desc;
	Cmd->ID = ID;
	Cmd->Type = Type;
	Cmd->Tag = Tag;
	/*if(OnCreateCommandList)
		OnCreateCommandList(Cmd);*/
	if(AddToList)
		AddCommandsList(Cmd);
	return Cmd;
}
//---------------------------------------------------------------------------
void TWebSource::SetNumRequest(int Num){
	int Counter = 0;
	DEBUG_SRC(INFO_DEBUG,"SetNumRequest: from "+IntToStr(RequestList->Count)+(String)" to "+IntToStr(Num));
	if(RequestList->Count != Num){
		TNetHTTPRequest *Request;
		WebSource_Data *Tmp;
		if(RequestList->Count < Num){
			for(int a=RequestList->Count;a<Num;a++){
				Request = new TNetHTTPRequest(FClient);
				Request->Client = Client;
				Request->OnRequestCompleted = HTTPRequestCompleted;
				Request->OnRequestError = HTTPRequestError;
				Request->Name = "HTTP_Request_"+IntToStr(ReqCreated);
				ReqCreated++;
				Tmp = (WebSource_Data*)AllocMem(sizeof(WebSource_Data));
				Tmp->Request = Request;
				Tmp->RequestStatus = HTTP_REQUEST_STANDBY;
				Tmp->WorkingMode = REQUEST_NORMAL_FLOW;
				Tmp->WebSource = this;
				Request->Tag = (int)Tmp;
				Request->Asynchronous = true;
				RequestList->Add(Request);
			}
		}
		else{
			for(int a=RequestList->Count-1;a<=Num;a--){
				Request = (TNetHTTPRequest*) RequestList->Items[a];
				delete Request;
				RequestList->Delete(a);
			}
		}
	}
}
//---------------------------------------------------------------------------
int TWebSource::GetNumRequest(){
	return RequestList->Count;
}
//---------------------------------------------------------------------------
bool TWebSource::GetReqAuth(){
	return FAuthReq;
}
//---------------------------------------------------------------------------
void TWebSource::SetReqAuth(bool Auth){
	FAuthReq = Auth;
}
//---------------------------------------------------------------------------
bool TWebSource::GetAuth(){
	return FAuth;
}
//---------------------------------------------------------------------------
String TWebSource::GetPrefLang(){
	return FPrefLang;
}
//---------------------------------------------------------------------------
void TWebSource::SetPrefLang(String Lang){
	FPrefLang = Lang;
}
//---------------------------------------------------------------------------
TStringList *TWebSource::GetParameters(){
	DEBUG_SRC(INFO_DEBUG,"GetParameters()");
	TStringList *Out = new TStringList();
	for(int a=0;a<Parameters->Count;a++){
		//Out->AddPair(Parameters->Pairs[a]->JsonString->ToString(),Parameters->Pairs[a]->JsonValue->ToString());
		Out->AddPair(Parameters->Names[a],Parameters->ValueFromIndex[a]);
	}
	if(Parameters->Count == 0)
		DEBUG_SRC(TOTAL_DEBUG,"No parameters");
	return Out;
}
//---------------------------------------------------------------------------
int TWebSource::GetNumCommands(){
	return TaskList->Count;
}
//---------------------------------------------------------------------------
CommandList *TWebSource::GetCommandByIndex(int Index){
	DEBUG_SRC(INFO_DEBUG,"GetCommandByIndex: index "+IntToStr(Index));
	if(Index > -1 && Index < TaskList->Count)
		return (CommandList*)TaskList->Items[Index];
	DEBUG_SRC(ERR_DEBUG,"Index out of bound");
	return NULL;
}
//---------------------------------------------------------------------------
String TWebSource::GetShortLanguage(){
	String Short = "en";
	String Lang = FPrefLang.LowerCase();
	for(int a=0;a<ISO_639_LEN;a++){
		if(Lang == Language639[a].EnglishName.LowerCase()){
			Short = Language639[a].Abbreviation;
			a = ISO_639_LEN;
		}
	}
	return Short;
}
//---------------------------------------------------------------------------
int TWebSource::Authenticate(){
	CommandList *Tmp;
	int a;
	DEBUG_SRC(INFO_DEBUG,"Authenticate in "+QUOTED(this));
	for(a=0;a<TaskList->Count;a++){
		Tmp = (CommandList*)TaskList->Items[a];
		if(Tmp->Type == SYS_AUTHENTICATE){
			return ExecuteCommand(Tmp);
		}
	}
	DEBUG_SRC(ERR_DEBUG,"No command list for authentication");
	return WEB_SOURCE_COMMAND_NOT_EXIST;
}
//---------------------------------------------------------------------------
int TWebSource::QueryCandidate(String Candidate, TOnFoundCandidate Func, int SearchID){
	DEBUG_SRC(INFO_DEBUG,"QueryCandidate -> "+QUOTE_STRING(Candidate)+(String)" -> ID: "+
				IntToStr(SearchID)+(String)" - FoundFunc: "+(String)(Func==NULL?"Yes":"No"));
	CommandList *Tmp;
	int a;
	if(AuthRequest){
		DEBUG_SRC(TOTAL_DEBUG,"Authorization required");
		if(Authorized == false){
			DEBUG_SRC(TOTAL_DEBUG,"Not yet authenticate: executing...");
			Authenticate();
		}
		else
			DEBUG_SRC(TOTAL_DEBUG,"Already authorized");
	}
	else
		DEBUG_SRC(TOTAL_DEBUG,"No authorization required");
	if(Type == SHOW_SOURCE_INFO){
		String Txt;
		if(RememberPreferences)
			Txt = GetShowNameID(UpperFirstLetter(Candidate));
		else
			Txt = "";
		if(Txt != ""){
			if(Func){
				OnFindCandidate = Func;
			}
			if(OnFindCandidate){
				TList *List = new TList();
				Candidate_Information *CandidateList = (Candidate_Information*)AllocMem(sizeof(Candidate_Information));
				CandidateList->Name = UpperFirstLetter(Candidate);
				CandidateList->ID = Txt;
				List->Add(CandidateList);
				OnFindCandidate(Candidate, SearchID, List);
				return WEB_SOURCE_CORRECT;
			}
		}
	}
	for(a=0;a<TaskList->Count;a++){
		Tmp = (CommandList*)TaskList->Items[a];
		if(Tmp->Type == QUERY_CANDIDATE){
			DEBUG_SRC(TOTAL_DEBUG,"Found command list at index "+IntToStr(a));
			if(Func){
				OnFindCandidate = Func;
			}
			CommandList *Out = Tmp->Clone();
			Net_Operation Op1,Op2;
			Out->SearchInfo = Candidate;
			Out->ID = SearchID;
			for(int b=0;b<Out->GetNumOperations();b++){
				Op1 = Out->GetOperation(b);
				if(Op1.Url.Pos(CANDIDATE_STRING_ID) > 0){
					Op2 = Op1;
					Op1.Url = System::Strutils::AnsiReplaceStr(Op1.Url,CANDIDATE_STRING_ID,Candidate);
					Out->ChangeOperation(Op2, Op1);
				}
			}
			return ExecuteCommand(Out);
		}
	}
	DEBUG_SRC(ERR_DEBUG,"No command available to complete request");
	return WEB_SOURCE_COMMAND_NOT_EXIST;
}
//---------------------------------------------------------------------------
int TWebSource::QueryShowDetail(String ShowName, String ShowID, int Season, int Episode, TOnFindShowData Func, int SearchID){
	DEBUG_SRC(INFO_DEBUG,"QueryShowDetail: Name "+QUOTE_STRING(ShowName)+(String)" - ID "+QUOTE_STRING(ShowID)+
				(String)" - Seas. "+IntToStr(Season)+(String)" - Ep. "+IntToStr(Episode)+(String)" - Func. "+
				(String)(Func == NULL?"YES":"NO")+(String)" - SearchID "+IntToStr(SearchID));
	int a;
	CommandList *Tmp;
	if(AuthRequest){
		DEBUG_SRC(TOTAL_DEBUG,"Authorization required");
		if(Authorized == false){
			DEBUG_SRC(TOTAL_DEBUG,"Not yet authenticate: executing...");
			Authenticate();
		}
		else
			DEBUG_SRC(TOTAL_DEBUG,"Already authorized");
	}
	else
		DEBUG_SRC(TOTAL_DEBUG,"No authorization required");
	for(a=0;a<TaskList->Count;a++){
		Tmp = (CommandList*)TaskList->Items[a];
		if(Tmp->Type == QUERY_SHOW_TITLE){
			DEBUG_SRC(TOTAL_DEBUG,"Found command list at index "+IntToStr(a));
			if(Func){
				OnFindShowData = Func;
			}
			CommandList *Out = Tmp->Clone();
			Net_Operation Op1,Op2;
			Out->SearchInfo = ShowName;
			Out->ID = SearchID;
			Out->Tag = (Season * 1000) + Episode;
			bool ChangeMe = false;
			for(int b=0;b<Out->GetNumOperations();b++){
				Op1 = Out->GetOperation(b);
				Op2 = Op1;
				if(Op1.Url.Pos(SHOW_STRING_ID) > 0){
					Op1.Url = System::Strutils::AnsiReplaceStr(Op1.Url,SHOW_STRING_ID,ShowID);
					ChangeMe = true;
				}
				if(Op1.Url.Pos(SHOW_SEASON_STRING_ID) > 0){
					Op1.Url = System::Strutils::AnsiReplaceStr(Op1.Url,SHOW_SEASON_STRING_ID,IntToStr(Season));
					ChangeMe = true;
				}
				if(Op1.Url.Pos(SHOW_EPISODE_STRING_ID) > 0){
					Op1.Url = System::Strutils::AnsiReplaceStr(Op1.Url,SHOW_EPISODE_STRING_ID,IntToStr(Episode));
					ChangeMe = true;
				}
				if(ChangeMe)
					Out->ChangeOperation(Op2, Op1);
				else
					DEBUG_SRC(ERR_DEBUG,"No valid parameter found");
			}
			return ExecuteCommand(Out);
		}
	}
	return WEB_SOURCE_COMMAND_NOT_EXIST;
}
//---------------------------------------------------------------------------
int TWebSource::AddShowNamePref(String ShowName, String ID){
	DEBUG_SRC(INFO_DEBUG,"AddShowNamePref()");
	if(GetShowNameID(ShowName) == ""){
		ShowNamePref->AddPair(ShowName, ID);
		DEBUG_SRC(TOTAL_DEBUG,"Add: "+QUOTE_STRING(ShowName)+(String)" - ID: "+QUOTE_STRING(ID));
		return WEB_SOURCE_CORRECT;
	}
	DEBUG_SRC(ERR_DEBUG,"Showname alreay exist "+QUOTE_STRING(ShowName));
	return WEB_SOURCE_INVALID_KEY;
}
//---------------------------------------------------------------------------
int TWebSource::RemoveShowNamePref(String ShowName){
	int a;
	DEBUG_SRC(INFO_DEBUG,"RemoveShowNamePref()");
	a = ShowNamePref->IndexOfName(ShowName);
	if(a != -1){
		ShowNamePref->Delete(a);
		DEBUG_SRC(TOTAL_DEBUG,"Remove show name "+QUOTE_STRING(ShowName));
		return WEB_SOURCE_CORRECT;
	}
	DEBUG_SRC(ERR_DEBUG,"No show name found with name "+QUOTE_STRING(ShowName));
	return WEB_SOURCE_INVALID_KEY;
}
//---------------------------------------------------------------------------
int TWebSource::GetNumShowNamePref(){
	DEBUG_SRC(INFO_DEBUG,"GetNumShowNamePref()");
	return ShowNamePref->Count;
}
//---------------------------------------------------------------------------
String TWebSource::GetShowNameID(String ShowName){
	DEBUG_SRC(INFO_DEBUG,"GetShowNameID()");
	int a = ShowNamePref->IndexOfName(ShowName);
	if(a != -1){
		String Txt = ShowNamePref->Values[ShowName];
		DEBUG_SRC(TOTAL_DEBUG,"Found "+QUOTE_STRING(ShowName)+(String)" - ID: "+QUOTE_STRING(Txt));
		return Txt;
	}
	DEBUG_SRC(ERR_DEBUG,"No show name found with name "+QUOTE_STRING(ShowName));
	return "";
}
//---------------------------------------------------------------------------
String TWebSource::GetShowNamePrefByIndex(int Index){
	DEBUG_SRC(INFO_DEBUG,"GetShowNamePrefByIndex()");
	if(Index > -1 && Index < ShowNamePref->Count){
		String Txt = ShowNamePref->ValueFromIndex[Index];
		DEBUG_SRC(TOTAL_DEBUG,"Found id "+QUOTE_STRING(Txt)+(String)" at index "+IntToStr(Index));
		return Txt;
	}
	DEBUG_SRC(ERR_DEBUG,"Invalid index: "+IntToStr(Index));
	return "";
}
//---------------------------------------------------------------------------
String TWebSource::GetShowNamePrefNameByIndex(int Index){
	DEBUG_SRC(INFO_DEBUG,"GetShowNameNameByIndex()");
	if(Index > -1 && Index < ShowNamePref->Count){
		String Txt = ShowNamePref->Names[Index];
		DEBUG_SRC(TOTAL_DEBUG,"Found showname "+QUOTE_STRING(Txt)+(String)" at index "+IntToStr(Index));
		return Txt;
	}
	DEBUG_SRC(ERR_DEBUG,"Invalid index: "+IntToStr(Index));
	return "";
}
//---------------------------------------------------------------------------
int TWebSource::ChangeShowNamePrefID(String ShowName, String NewID){
	DEBUG_SRC(INFO_DEBUG,"ChangeShowNamePrefID()");
	int a = ShowNamePref->IndexOfName(ShowName);
	if(a>-1 && a<ShowNamePref->Count){
		ShowNamePref->ValueFromIndex[a] = NewID;
		return WEB_SOURCE_CORRECT;
	}
	return WEB_SOURCE_INVALID_KEY;
}
//---------------------------------------------------------------------------
int TWebSource::ChangeShowNamePrefID(int Index, String NewID){
	DEBUG_SRC(INFO_DEBUG,"ChangeShowNamePrefID()");
	if(Index>-1 && Index<ShowNamePref->Count){
		ShowNamePref->ValueFromIndex[Index] = NewID;
		return WEB_SOURCE_CORRECT;
	}
	return WEB_SOURCE_INVALID_KEY;
}
//---------------------------------------------------------------------------
int TWebSource::ChangeShowNamePrefName(String ShowName, String NewName){
	DEBUG_SRC(INFO_DEBUG,"ChangeShowNamePrefName()");
	int a = ShowNamePref->IndexOfName(ShowName);
	if(a>-1 && a<ShowNamePref->Count){
		String Tmp = ShowNamePref->Strings[a];
		Tmp = ReplaceStr(Tmp,ShowName,NewName);
		ShowNamePref->Strings[a] = Tmp;
		return WEB_SOURCE_CORRECT;
	}
	return WEB_SOURCE_INVALID_KEY;	
}
//---------------------------------------------------------------------------
int TWebSource::ChangeShowNamePrefName(int a, String NewName){
	DEBUG_SRC(INFO_DEBUG,"ChangeShowNamePrefName()");
	if(a>-1 && a<ShowNamePref->Count){
		String Tmp = ShowNamePref->Strings[a];
		String ShowName = ShowNamePref->Names[a];
		Tmp = ReplaceStr(Tmp,ShowName,NewName);
		ShowNamePref->Strings[a] = Tmp;
		return WEB_SOURCE_CORRECT;
	}
	return WEB_SOURCE_INVALID_KEY;	
	
}
//---------------------------------------------------------------------------
String TWebSource::ExportPreferences(){
	DEBUG_SRC(INFO_DEBUG,"ExportPreferences()");
	return ShowNamePref->DelimitedText;
}
//---------------------------------------------------------------------------
int TWebSource::ImportPreferences(String Pref){
	DEBUG_SRC(INFO_DEBUG,"ImportPreferences()");
	if(Pref != ""){
		ShowNamePref->DelimitedText = Pref;
		return WEB_SOURCE_CORRECT;
	}
	return WEB_SOURCE_EMPTY_KEY_VALUE;
}
//---------------------------------------------------------------------------
bool TWebSource::GetRemPref(){
	return FRemeberPreferences;
}
//---------------------------------------------------------------------------
void TWebSource::SetRemPref(bool Value){
	FRemeberPreferences = Value;
}
//---------------------------------------------------------------------------
void __fastcall TWebSource::ManageCertificate(System::TObject* const Sender,
	TURLRequest* const ARequest, const TCertificate &Certificate, bool &Accepted){
	Accepted = true;
	DEBUG_SRC(INFO_DEBUG,"ManageCertificate()");
	String Txt = "Expiry: "+Certificate.Expiry.DateTimeString();
	Txt = Txt+(String)" - Start: "+Certificate.Start.DateTimeString();
	Txt = Txt+(String)" - Subject: "+Certificate.Subject;
	Txt = Txt+(String)" - Issuer: "+Certificate.Issuer;
	Txt = Txt+(String)" - ProtocolName: "+Certificate.ProtocolName;
	Txt = Txt+(String)" - AlgSignature: "+Certificate.AlgSignature;
	Txt = Txt+(String)" - AlgEncryption: "+Certificate.AlgEncryption;
	Txt = Txt+(String)" - KeySize: "+IntToStr(Certificate.KeySize);
//	DEBUG_SRC(TOTAL_DEBUG,Txt);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

TInfoGrabber::TInfoGrabber(){
	InternalSetup();
}
//---------------------------------------------------------------------------
TInfoGrabber::TInfoGrabber(TComponent *AOwner){
	InternalSetup();
	Owner = AOwner;
	Client = new TNetHTTPClient(Owner);
	Client->SecureProtocols = THTTPSecureProtocols()<<THTTPSecureProtocol::TLS12
					<<THTTPSecureProtocol::TLS11<<THTTPSecureProtocol::TLS1;
	Client->AllowCookies = true;
	Client->UserAgent = "Mozilla/5.0 (Windows NT 5.1; rv:52.0) Gecko/20100101 Firefox/52.0";
	if(Owner)
		DEBUG_GRB(TOTAL_DEBUG,"Owner class name: "+Owner->ClassName());
	else
		DEBUG_GRB(TOTAL_DEBUG,"Created without owner");
}
//---------------------------------------------------------------------------
void TInfoGrabber::InternalSetup(){
	DEBUG_GRB(INFO_DEBUG,"Creating TInfoGrabber object");
	InfoSource = new TList();
	PreferedLanguage = "English";
	FLastSource = NULL;
	OnFindCandidate = NULL;
	OnFindShowData = NULL;
	OnCreateWebSource = NULL;
	OnAddWebSource = NULL;
	OnRemoveWebSource = NULL;
	OnConnectionError = NULL;
	OnCompleteAvailableSource = NULL;
	
	SearchingData = new TStringList();
	SearchList = new TList();
}
//---------------------------------------------------------------------------
TInfoGrabber::~TInfoGrabber(){
	DEBUG_GRB(INFO_DEBUG,"~TInfoGrabber()");
}
//---------------------------------------------------------------------------
TWebSource *TInfoGrabber::CreateInfoSource(String Name,String Desc,int ID,int Type,int Tag, bool AddToList){
	DEBUG_GRB(INFO_DEBUG,"CreateInfoSource with name "+QUOTE_STRING(Name));
	TWebSource *Out;
	Out = new TWebSource(Client);
	Out->Name = Name;
	Out->Description = Desc;
	Out->Type = Type;
	Out->Tag = Tag;
	Out->ID = ID;
	Out->OnInvalidAnswer = ManageInvalidAnswer;
	if(AddToList){
		DEBUG_GRB(TOTAL_DEBUG,"Add to list required");
		if(OnConnectionError)
			Out->OnConnectionError = OnConnectionError;
		InfoSource->Add(Out);
		if(OnCreateWebSource)
			OnCreateWebSource(Out);
	}
	return Out;
}
//---------------------------------------------------------------------------
int TInfoGrabber::AddInfoSource(TWebSource *Source){
	DEBUG_GRB(INFO_DEBUG,"AddInfoSource()");
	if(Source){
		TWebSource *Src = Source->Clone(Owner);
		InfoSource->Add(Src);
		Src->OnInvalidAnswer = ManageInvalidAnswer;
		if(OnConnectionError)
			Src->OnConnectionError = OnConnectionError;
		if(OnAddWebSource)
			OnAddWebSource(Src);
		DEBUG_GRB(TOTAL_DEBUG,"Added source "+QUOTED(Source));
		return WEB_SOURCE_CORRECT;
	}
	DEBUG_GRB(ERR_DEBUG,"No valid source added");
	return WEB_SOURCE_INVALID_SOURCE;
}
//---------------------------------------------------------------------------
int TInfoGrabber::GetNumInfoSource(){
	return InfoSource->Count;
}
//---------------------------------------------------------------------------
TWebSource *TInfoGrabber::GetSourceByIndex(int Index){
	DEBUG_GRB(INFO_DEBUG,"GetSourceByIndex: requested index "+IntToStr(Index));
	if(Index > -1 && Index < InfoSource->Count){
		TWebSource *Out = (TWebSource*)InfoSource->Items[Index];
		DEBUG_GRB(TOTAL_DEBUG,"Found WebSource "+QUOTED(Out));
		return Out;
	}
	DEBUG_GRB(ERR_DEBUG,"Index out of bound");
	return NULL;
}
//---------------------------------------------------------------------------
int TInfoGrabber::SaveToXML(String File){
	_di_IXMLNode Node,SubNode,TmpNode,LastNode,XNode;
	TWebSource *Src;
	TStringList *Param;
	CommandList *Cmd;
	Net_Operation Op;
	DEBUG_GRB(INFO_DEBUG,"SaveToXML -> "+File);	
	TXMLDocument *Doc = new TXMLDocument(Owner);
	Doc->DOMVendor = GetDOMVendor("ADOM XML v4");
	Doc->Active = true;
	Doc->Options = TXMLDocOptions()<<doNodeAutoIndent;
	Doc->DocumentElement = Doc->CreateNode("InfoGrabber",ntElement,"");
	Doc->DocumentElement->SetAttribute("Version",INFO_GRABBER_VERSION);
	Doc->DocumentElement->SetAttribute("Class_creator","TInfoGrabber");
	Doc->DocumentElement->SetAttribute("Info","TInfoGrabber class backup");
	for(int a=0;a<InfoSource->Count;a++){
		Src = GetSourceByIndex(a);
		Node = Doc->DocumentElement->AddChild("WebSource",-1);
		Node->SetAttribute("Name",Src->Name);
		Node->SetAttribute("Desc",Src->Description);
		Node->SetAttribute("Type",Src->Type);
		Node->SetAttribute("ID",Src->ID);
		Node->SetAttribute("Tag",Src->Tag);
		Node->SetAttribute("AuthRequest",Src->AuthRequest);
		Node->SetAttribute("Language",Src->PreferedLanguage);
		Node->SetAttribute("Preferences",Src->RememberPreferences);
		Param = Src->GetParameters();
		SubNode = Node->AddChild("Parameters",-1);
		for(int b=0;b<Param->Count;b++){
			TmpNode = SubNode->AddChild("Parameter",-1);
			TmpNode->SetAttribute("Name",Param->Names[b]);
			TmpNode->SetAttribute("Value",Param->ValueFromIndex[b]);
			TmpNode->Text = "Parameter "+IntToStr(b+1);
		}
		SubNode = Node->AddChild("Preferences",-1);
		SubNode->SetAttribute("Value",Src->ExportPreferences());
		SubNode->Text = "Preferences";

		SubNode = Node->AddChild("Commands",-1);
		for(int b=0;b<Src->GetNumCommands();b++){
			Cmd = Src->GetCommandByIndex(b);
			TmpNode = SubNode->AddChild("Command",-1);
			TmpNode->SetAttribute("Name",Cmd->Name);
			TmpNode->SetAttribute("Desc",Cmd->Description);
			TmpNode->SetAttribute("Type",Cmd->Type);
			TmpNode->SetAttribute("ID",Cmd->ID);
			TmpNode->SetAttribute("Tag",Cmd->Tag);
			LastNode = TmpNode->AddChild("Operations",-1);
			for(int c=0;c<Cmd->GetNumOperations();c++){
				Op = Cmd->GetOperation(c);
				XNode = LastNode->AddChild("Operation",-1);
				XNode->SetAttribute("Url",Op.Url);
				XNode->SetAttribute("Data",Op.Data);
				XNode->SetAttribute("ExpAnswer",Op.ExpectedAnswer);
				XNode->SetAttribute("Method",Op.MethodType);
				XNode->SetAttribute("AnswerManager",Op.AnswerManager);
				XNode->Text = "Operation "+IntToStr(c);
			}
		}
	}
	Doc->SaveToFile(File);
	return WEB_SOURCE_CORRECT;
}
//---------------------------------------------------------------------------
int TInfoGrabber::LoadFromXML(String File){
	int a, b, c;
	TXMLDocument *Doc = new TXMLDocument(Owner);
	IXMLNode *Node,*SubNode,*XNode, *LastNode, *BNode;
	String Txt;
	DEBUG_GRB(INFO_DEBUG,"LoadFromXML -> "+File);
	String Name,Desc,Lang,Manager;
	int Type,Tag,ID;
	OleVariant Ole;
	bool Auth;
	if(FileExists(File) == false)
        return WEB_SOURCE_INVALID_FILE;
	Doc->LoadFromFile(File);
	Doc->DOMVendor = GetDOMVendor("ADOM XML v4");
	Doc->Active=true;
	if(Doc->DocumentElement->NodeName == "InfoGrabber"){
		Txt = Doc->DocumentElement->GetAttribute("Class_creator");
		if(Txt == "TInfoGrabber"){
			a = Doc->DocumentElement->GetAttribute("Version");
			if(a <= INFO_GRABBER_VERSION){
				Reset();
				TWebSource *Source;
				CommandList *Cmd;
				Net_Operation Op;
				for(a=0;a<Doc->DocumentElement->ChildNodes->Count;a++){
					Node = Doc->DocumentElement->ChildNodes->Get(a);
					Name = Node->GetAttribute("Name");
					Desc = Node->GetAttribute("Desc");
					Lang = Node->GetAttribute("Language");
					Type = Node->GetAttribute("Type");
					Tag = Node->GetAttribute("Tag");
					ID = Node->GetAttribute("ID");
					Source = CreateInfoSource(Name,Desc,ID,Type,Tag);
					Source->PreferedLanguage = Lang;
					Name = Node->GetAttribute("AuthRequest");
					Name == "true"?(Source->AuthRequest = true):(Source->AuthRequest = false);
					Name = Node->GetAttribute("Preferences");
					Name == "true"?(Source->RememberPreferences = true):(Source->RememberPreferences = false);
					if(Node->ChildNodes->Count > 0){
						//Parameters...
						SubNode = Node->ChildNodes->Get(0);
						for(b=0;b<SubNode->ChildNodes->Count;b++){
							XNode = SubNode->ChildNodes->Get(b);
							Name = XNode->GetAttribute("Name");
							Desc = XNode->GetAttribute("Value");
							Source->AddParameter(Name,Desc);
						}
					}
					//Preferences...
					if(Node->ChildNodes->Count > 1){
						SubNode = Node->ChildNodes->Get(1);
						Desc = SubNode->GetAttribute("Value");
						Source->ImportPreferences(Desc);
					}
					if(Node->ChildNodes->Count > 2){
						//Commands...
						SubNode = Node->ChildNodes->Get(2);
						for(b=0;b<SubNode->ChildNodes->Count;b++){
							XNode = SubNode->ChildNodes->Get(b);
							Name = XNode->GetAttribute("Name");
							Desc = XNode->GetAttribute("Desc");
							Type = XNode->GetAttribute("Type");
							Tag = XNode->GetAttribute("Tag");
							ID = XNode->GetAttribute("ID");
							Cmd = Source->CreateCommandList(Name,Desc,ID,Type,Tag);
							if(XNode->ChildNodes->Count>0){
								//Operation...
								LastNode = XNode->ChildNodes->Get(0);
								for(c=0;c<LastNode->ChildNodes->Count;c++){
									BNode = LastNode->ChildNodes->Get(c);
									Name = BNode->GetAttribute("Url");
									Desc = BNode->GetAttribute("Data");
									Tag = BNode->GetAttribute("ExpAnswer");
									ID = BNode->GetAttribute("Method");
									Manager = BNode->GetAttribute("AnswerManager");
									Op.Url = Name,Op.Data = Desc, Op.ExpectedAnswer = Tag, Op.MethodType = ID,Op.AnswerManager = Manager;
									Cmd->AddOperation(Op);
								}
							}
						}
					}
				}
			}
		}
	}
	return WEB_SOURCE_CORRECT;
}
//---------------------------------------------------------------------------
int TInfoGrabber::Reset(){
	int a;
	DEBUG_GRB(INFO_DEBUG,"Reset()");
	for(a=InfoSource->Count-1;a>-1;a--){
		InfoSource->Delete(a);
	}
	return WEB_SOURCE_CORRECT;
}
//---------------------------------------------------------------------------
int TInfoGrabber::GetNumSourceByType(int Type){
	int Out = 0;
	TWebSource *Src;
	DEBUG_GRB(INFO_DEBUG,"GetNumSourceByType(): type "+(String)GET_SOURCE_TYPE(Type));
	for(int a=0;a<InfoSource->Count;a++){
		Src = (TWebSource*)InfoSource->Items[a];
		if(Src->Type == Type)
			Out++;
	}
	DEBUG_GRB(TOTAL_DEBUG,"Found "+IntToStr(Out)+(String)" sources of type request");
	return Out;
}
//---------------------------------------------------------------------------
bool TInfoGrabber::CompareSource(TWebSource *Src1, TWebSource *Src2){
	DEBUG_GRB(INFO_DEBUG,"CompareSource()");
	if(Src1 == NULL){
		DEBUG_GRB(ERR_DEBUG,"Invalid first source");
		return false;
	}
	if(Src2 == NULL){
		DEBUG_GRB(ERR_DEBUG,"Invalid second source");
		return false;
	}	
	if(Src1->Name != Src2->Name){
		DEBUG_GRB(TOTAL_DEBUG,"Different name: "+QUOTED(Src1)+(String)" - "+QUOTED(Src2));
		return false;
	}
	if(Src1->Type != Src2->Type){
		DEBUG_GRB(TOTAL_DEBUG,"Different type: "+IntToStr(Src1->Type)+(String)" - "+IntToStr(Src2->Type));
		return false;
	}
	if(Src1->Description != Src2->Description){
		DEBUG_GRB(TOTAL_DEBUG,"Different description: "+QUOTE_STRING(Src1->Description)+(String)" - "+QUOTE_STRING(Src2->Description));
		return false;
	}
	if(Src1->ID != Src2->ID){
		DEBUG_GRB(TOTAL_DEBUG,"Different ID: "+IntToStr(Src1->ID)+(String)" - "+IntToStr(Src2->ID));
		return false;
	}
	if(Src1->Tag != Src2->Tag){
		DEBUG_GRB(TOTAL_DEBUG,"Different Tag: "+IntToStr(Src1->Tag)+(String)" - "+IntToStr(Src2->Tag));
		return false;
	}
	if(Src1->GetNumCommands()!=Src2->GetNumCommands()){
		DEBUG_GRB(TOTAL_DEBUG,"Different num commands: "+IntToStr(Src1->GetNumCommands())+(String)" - "+IntToStr(Src2->GetNumCommands()));
		return false;
	}
	for(int a=0;a<Src1->GetNumCommands();a++){
		if(Src1->GetCommandByIndex(a)->GetNumOperations() !=
			Src2->GetCommandByIndex(a)->GetNumOperations())
			return false;
	}
	DEBUG_GRB(TOTAL_DEBUG,"Same WebSources");
	return true;
}
//---------------------------------------------------------------------------
int TInfoGrabber::GetSourceOrderInSearchIndex(TWebSource *Src){
	bool found = false;
	int Out = 0;
	TWebSource *Tmp;
	DEBUG_GRB(INFO_DEBUG,"GetSorceOrderInSearchIndex()");
	if(Src == NULL){
		DEBUG_GRB(TOTAL_DEBUG,"Request source "+QUOTED(Src));
		return WEB_SOURCE_SAFETY_VALUE;
	}
	for(int a=0;a<InfoSource->Count;a++){
		Tmp = (TWebSource*)InfoSource->Items[a];
		if(CompareSource(Tmp, Src)){
			found = true;
			DEBUG_GRB(TOTAL_DEBUG,"Source found at index "+IntToStr(a));
			break;
		}
		if(Src->Type == Tmp->Type)
			Out++;
	}
	if(found)
		return Out;
	DEBUG_GRB(ERR_DEBUG,"Source not found");
	return WEB_SOURCE_SAFETY_VALUE;
}
//---------------------------------------------------------------------------
int TInfoGrabber::ChangeSourceSearchOurder(TWebSource *Src, int NewPlace){
	int Index = -1;
	int a;
	int Count;
	DEBUG_GRB(INFO_DEBUG,"ChangeSourceSearchOurder()");
	if(Src == NULL){
		DEBUG_GRB(ERR_DEBUG,"Invalid source request");
		return WEB_SOURCE_INVALID_SOURCE;
	}
	DEBUG_GRB(TOTAL_DEBUG,"Move source "+QUOTED(Src)+(String)" to position "+IntToStr(NewPlace));
	if(GetSourceOrderInSearchIndex(Src) == NewPlace){
		DEBUG_GRB(WARN_DEBUG,"Source alreay in place");
		return WEB_SOURCE_CORRECT;
	}
	TWebSource *Tmp;
	for(a=0;a<InfoSource->Count;a++){
		Tmp = (TWebSource*)InfoSource->Items[a];
		if(CompareSource(Tmp, Src)){
			Index = a;
			DEBUG_GRB(TOTAL_DEBUG,"Found source at index "+IntToStr(a));
			break;
		}
	}
	if(Index == -1){
		DEBUG_GRB(TOTAL_DEBUG,"WebSource not found");
		return WEB_SOURCE_INVALID_SOURCE;
	}
	if(NewPlace <= 0){
		InfoSource->Move(Index, 0);
	}
	else{
		if(NewPlace >= GetNumSourceByType(Src->Type)){
			InfoSource->Move(Index, InfoSource->Count-1);
		}
		else{
			Count = 0;
			for(a=0;a<InfoSource->Count;a++){
				Tmp = (TWebSource*)InfoSource->Items[a];
				if(Count == NewPlace){
					InfoSource->Move(Index, a);
					break;
				}
				if(Tmp->Type == Src->Type){
					Count++;
				}
			}
		}
	}
	DEBUG_GRB(TOTAL_DEBUG,"WebSource moved correctly");
	return WEB_SOURCE_CORRECT;
}
//---------------------------------------------------------------------------
String TInfoGrabber::GetPrefLang(){
	return FPrefLang;
}
//---------------------------------------------------------------------------
void TInfoGrabber::SetPrefLang(String Lang){
	FPrefLang = Lang;
}
//---------------------------------------------------------------------------
int TInfoGrabber::RemoveInfoSource(TWebSource *Source){
	int a;
	TWebSource *Tmp;
	DEBUG_GRB(INFO_DEBUG,"RemoveInfoSource()");
	if(Source == NULL){
		DEBUG_GRB(ERR_DEBUG,"NULL WebSource");
		return WEB_SOURCE_INVALID_SOURCE;
	}
	DEBUG_GRB(TOTAL_DEBUG,"Removing source "+QUOTED(Source));
	for(a=0;a<InfoSource->Count;a++){
		Tmp = (TWebSource*)InfoSource->Items[a];
		if(CompareSource(Tmp, Source)){
			if(OnRemoveWebSource)
				OnRemoveWebSource(Tmp);			
			InfoSource->Delete(a);
			DEBUG_GRB(TOTAL_DEBUG,"Source found at index "+IntToStr(a));
			return WEB_SOURCE_CORRECT;
		}
	}
	DEBUG_GRB(WARN_DEBUG,"Source not found");
	return WEB_SOURCE_INVALID_SOURCE;
}
//---------------------------------------------------------------------------
int TInfoGrabber::QueryMovieCandidate(String Candidate, int SearchID){
	int a;
	int Start;
	int *X;
	Start = 0;
	DEBUG_GRB(INFO_DEBUG,"QueryMovieCandidate -> "+QUOTE_STRING(Candidate)+(String)" - ID: "+IntToStr(SearchID));
	a = SearchingData->IndexOf(Candidate);
	if(a != -1){
		DEBUG_GRB(TOTAL_DEBUG,"Search already in progress");
		X = (int*)SearchingData->Objects[a];
		Start = *X + 1;          //Searching with next source...
	}
	TWebSource *Tmp;
	SearchInfo *Info = (SearchInfo*)AllocMem(sizeof(SearchInfo));
	Info->MovieName = Candidate;
	Info->SearchID = SearchID;
	for(a=Start;a<InfoSource->Count;a++){
		Tmp = (TWebSource*)InfoSource->Items[a];
		if(Tmp->Type == MOVIE_SOURCE_INFO){
			if(Start == 0){
				X = (int*)AllocMem(sizeof(int));
				SearchingData->AddObject(Candidate, (TObject*)X);
			}
			*X = a;
			DEBUG_GRB(TOTAL_DEBUG,"WebSource used: "+QUOTED(Tmp));
			Info->WebSource = Tmp;
			SearchList->Add(Info);
            FLastSource = Tmp;
			Tmp->QueryCandidate(Candidate,InternalFoundMovieCandidate, SearchID);
			return WEB_SOURCE_CORRECT;
		}
	}
	a = SearchingData->IndexOf(Candidate);
	if(a>-1)
		SearchingData->Delete(a);
	DEBUG_GRB(ERR_DEBUG,"No valid source as MOVIE_SOURCE_INFO");
	if(OnCompleteAvailableSource)
		OnCompleteAvailableSource(Candidate, SearchID);
	return WEB_SOURCE_INVALID_SOURCE;	
}
//---------------------------------------------------------------------------
int TInfoGrabber::QueryShowCandidate(String Candidate, int SearchID){
/*
TInfoGrabber::QueryShowCandidate -> TWebSource::QueryCandidate ---> TWebSource::HTTPRequestCompleted ->
-> TWebSource::DecodeAnswer -> OnFindCandidate
							-> OnFindShowData
*/
	int a,b;
	int Start = 0;
	int *X;
	DEBUG_GRB(INFO_DEBUG,"QueryShowCandidate -> "+QUOTE_STRING(Candidate)+(String)" - ID: "+IntToStr(SearchID));
	a = SearchingData->IndexOf(Candidate);
	if(a != -1){
		DEBUG_GRB(TOTAL_DEBUG,"Search already in progress");
		X = (int*)SearchingData->Objects[a];
		Start = *X + 1;          //Searching with next source...
	}
	TWebSource *Tmp;
	SearchInfo *Info;
	for(b=0;b<SearchList->Count;b++){
		Info = (SearchInfo*)SearchList->Items[b];
		if(Info->SearchID == SearchID)
			break;
	}
	if(b == SearchList->Count){
		Info = (SearchInfo*)AllocMem(sizeof(SearchInfo));
		b = 0;
	}
	Info->ShowName = Candidate;
	Info->SearchID = SearchID;
	for(a=Start;a<InfoSource->Count;a++){
		Tmp = (TWebSource*)InfoSource->Items[a];
		if(Tmp->Type == SHOW_SOURCE_INFO){
			if(Start == 0){
				X = (int*)AllocMem(sizeof(int));
				SearchingData->AddObject(Candidate, (TObject*)X);
			}
			*X = a;
			DEBUG_GRB(TOTAL_DEBUG,"WebSource used: "+QUOTED(Tmp));
			Info->WebSource = Tmp;
			if(b == 0)
				SearchList->Add(Info);
			FLastSource = Tmp;
			Tmp->QueryCandidate(Candidate,InternalFoundShowCandidate, SearchID);
			return WEB_SOURCE_CORRECT;
		}
	}
	a = SearchingData->IndexOf(Candidate);
	if(a>-1)
		SearchingData->Delete(a);
	DEBUG_GRB(ERR_DEBUG,"No valid source as SHOW_SOURCE_INFO");
	if(OnCompleteAvailableSource)
		OnCompleteAvailableSource(Candidate, SearchID);
	return WEB_SOURCE_INVALID_SOURCE;
}
//---------------------------------------------------------------------------
void __fastcall TInfoGrabber::InternalFoundMovieCandidate(String Candidate, int SearchID, TList *Result){
	int a, b;
	DEBUG_GRB(INFO_DEBUG,"InternalFoundMovieCandidate -> "+QUOTE_STRING(Candidate)+(String)" - Search_ID: "+IntToStr(SearchID));
	if(Result->Count){
		if(OnFindCandidate){
			DEBUG_GRB(TOTAL_DEBUG,"Executing OnFindCandidate");
			OnFindCandidate(Candidate, SearchID,Result);
		}
		a = SearchingData->IndexOf(Candidate);
		if(a != -1){
			DEBUG_GRB(TOTAL_DEBUG,"Removing candidate info from index "+IntToStr(a));
			SearchingData->Delete(a);
		}
	}
	else{
		DEBUG_GRB(WARN_DEBUG,"Source not retrieve information: checking with another source...");
		TWebSource *Tmp;
		int *X;
		SearchInfo *Info;
		int b;
		a = SearchingData->IndexOf(Candidate);
		if(a != -1){
			Info = NULL;
			for(b=0;b<SearchList->Count;b++){
				Info = (SearchInfo*)SearchList->Items[b];
				if(Info->SearchID == SearchID){
					break;
				}
				else
					Info = NULL;
			}
			X = (int*)SearchingData->Objects[a];
			for(a = *X+1;a<InfoSource->Count;a++){
				Tmp = (TWebSource*)InfoSource->Items[a];
				if(Tmp->Type == MOVIE_SOURCE_INFO){
					*X = a;
					if(Info)
						Info->WebSource = Tmp;
					DEBUG_GRB(TOTAL_DEBUG,"WebSource used: "+QUOTED(Tmp));
					Tmp->QueryCandidate(Candidate,InternalFoundMovieCandidate, SearchID);
					return;
				}
			}
			a = SearchingData->IndexOf(Candidate);
			SearchingData->Delete(a);
			if(OnCompleteAvailableSource)
				OnCompleteAvailableSource(Candidate, SearchID);
		}
	}	
}
//---------------------------------------------------------------------------
void __fastcall TInfoGrabber::InternalFoundShowCandidate(String Candidate, int SearchID, TList *Result){
	int a, b;
	DEBUG_GRB(INFO_DEBUG,"InternalFoundShowCandidate -> "+QUOTE_STRING(Candidate)+(String)" - Search_ID: "+IntToStr(SearchID));
	a = SearchingData->IndexOf(Candidate);
	if(Result->Count){
		if(OnFindCandidate){
			DEBUG_GRB(TOTAL_DEBUG,"Executing OnFindCandidate");
			OnFindCandidate(Candidate, SearchID,Result);
            return;
		}
		if(a != -1){
			DEBUG_GRB(TOTAL_DEBUG,"Removing candidate info from index "+IntToStr(a));
			SearchingData->Delete(a);
		}
	}
	else{
		DEBUG_GRB(WARN_DEBUG,"Source not retrieve information: checking with another source...");
		TWebSource *Tmp;
		int *X;
		SearchInfo *Info;
		int b;
		if(a != -1){
			Info = NULL;
			for(b=0;b<SearchList->Count;b++){
				Info = (SearchInfo*)SearchList->Items[b];
				if(Info->SearchID == SearchID){
					break;
				}
				else
					Info = NULL;
			}
			X = (int*)SearchingData->Objects[a];
			for(a = *X+1;a<InfoSource->Count;a++){
				Tmp = (TWebSource*)InfoSource->Items[a];
				if(Tmp->Type == SHOW_SOURCE_INFO){
					*X = a;
					if(Info)
						Info->WebSource = Tmp;
					DEBUG_GRB(TOTAL_DEBUG,"WebSource used: "+QUOTED(Tmp));
					Tmp->QueryCandidate(Candidate,InternalFoundShowCandidate, SearchID);
					return;
				}
			}
			a = SearchingData->IndexOf(Candidate);
			SearchingData->Delete(a);
			if(OnCompleteAvailableSource)
				OnCompleteAvailableSource(Candidate, SearchID);			
		}
	}
}
//---------------------------------------------------------------------------
int TInfoGrabber::QueryShowDetail(String ShowName, String ShowID, int Season, int Episode, int SearchID){
	DEBUG_GRB(INFO_DEBUG,"QueryShowDetail: Name "+QUOTE_STRING(ShowName)+(String)" - ID "+QUOTE_STRING(ShowID)+
				(String)" - Seas. "+IntToStr(Season)+(String)" - Ep. "+IntToStr(Episode)+(String)" - SearchID "+IntToStr(SearchID));
	TWebSource *Tmp;
	int a;
	SearchInfo *Info;
	for(a=0;a<SearchList->Count;a++){
		Info = (SearchInfo*)SearchList->Items[a];
		if(Info->SearchID == SearchID){
			DEBUG_GRB(TOTAL_DEBUG,"WebSource used from search list: "+QUOTED(Info->WebSource));
			Info->ShowID = ShowID;
			Info->WebSource->QueryShowDetail(ShowName,ShowID,Season,Episode,InternalFoundShowDetails,SearchID);
			return WEB_SOURCE_CORRECT;
		}
	}
	for(a=0;a<InfoSource->Count;a++){
		Tmp = (TWebSource*)InfoSource->Items[a];
		if(Tmp->Type == SHOW_SOURCE_INFO){
			DEBUG_GRB(TOTAL_DEBUG,"WebSource used (no in search list): "+QUOTED(Tmp));
			Tmp->QueryShowDetail(ShowName,ShowID,Season,Episode,InternalFoundShowDetails,SearchID);
			return WEB_SOURCE_CORRECT;
		}
	}
	DEBUG_GRB(ERR_DEBUG,"No valid source as SHOW_SOURCE_INFO");
	return WEB_SOURCE_INVALID_SOURCE;

}
//---------------------------------------------------------------------------
void __fastcall TInfoGrabber::InternalFoundShowDetails(String ShowName, int Season, int Episode, int SearchID, ShowResultDetails Details){
	DEBUG_GRB(INFO_DEBUG,"InternalFoundShowDetails -> "+QUOTE_STRING(ShowName)+(String)" - Seas.: "+IntToStr(Season)
				+(String)" - Ep.: "+IntToStr(Episode)+(String)" - SearchID: "+IntToStr(SearchID));
	DEBUG_GRB(TOTAL_DEBUG,"Details: name "+QUOTE_STRING(Details.EpisodeTitle));
	int a;
	SearchInfo *Info;
	for(a=0;a<SearchList->Count;a++){
		Info = (SearchInfo*)SearchList->Items[a];
		if(Info->SearchID == SearchID){
			if(Info->WebSource->RememberPreferences)
				Info->WebSource->AddShowNamePref(ShowName, Info->ShowID);
			SearchList->Delete(a);
			break;
		}
	}
	if(OnFindShowData){
		DEBUG_GRB(TOTAL_DEBUG,"Executing OnFindShowData");
		OnFindShowData(ShowName, Season,Episode,SearchID,Details);
	}
}
//---------------------------------------------------------------------------
TInfoGrabber *TInfoGrabber::Clone(){
	DEBUG_GRB(INFO_DEBUG,"Clone()");
	TInfoGrabber *Out = new TInfoGrabber(Owner);
	TWebSource *Src;
	Out->PreferedLanguage = PreferedLanguage;
	for(int a=0;a<GetNumInfoSource();a++){
		Src = GetSourceByIndex(a);
		Out->AddInfoSource(Src->Clone(Owner));
	}
	Out->OnFindCandidate = OnFindCandidate;
	Out->OnFindShowData = OnFindShowData;
	Out->OnCreateWebSource = OnCreateWebSource;
	Out->OnAddWebSource = OnAddWebSource;
	Out->OnRemoveWebSource = OnRemoveWebSource;
	Out->OnConnectionError = OnConnectionError;
	DEBUG_GRB(TOTAL_DEBUG,"Clone complete");
	return Out;
}
//---------------------------------------------------------------------------
String TInfoGrabber::GetUserAgent(){
	return FUserAgent;
}
//---------------------------------------------------------------------------
void TInfoGrabber::SetUserAgent(String Agent){
	FUserAgent = Agent;
	if(Agent != "")
		Client->UserAgent = Agent;
}
//---------------------------------------------------------------------------
TWebSource *TInfoGrabber::GetLastSource(){
    return FLastSource;
}
//---------------------------------------------------------------------------
void __fastcall TInfoGrabber::ManageInvalidAnswer(TNetHTTPRequest *Request, Net_Operation Op,
										CommandList *Mgr, int Expected, int Received){
	String Candidate = Mgr->SearchInfo;
	WebSource_Data *Data = (WebSource_Data*)Request->Tag;
	TWebSource *Source = (TWebSource*)Data->WebSource;
	String Msg = "Invalid_answer manager\r\n";
	if(Source != NULL){
		switch(Source->Type){
			//OnFindCandidate(Cmd->SearchInfo,Cmd->ID,Info);
			case SHOW_SOURCE_INFO:{
				switch(Mgr->Type){
					case QUERY_CANDIDATE:{
						QueryShowCandidate(Mgr->SearchInfo, Mgr->ID);
						return;
					}break;
					case QUERY_SHOW_TITLE:{
						//QueryShowDetail(Mgr->SearchInfo,Mgr->Tag/1000,Mgr->Tag%1000,Mgr->ID);
						QueryShowCandidate(Mgr->SearchInfo, Mgr->ID);
						return;
					}break;
					default:{
						Msg = Msg+"Unknown CommandList type: 0x"+IntToHex(Mgr->Type);
					};
				}
				
			}break;
			case MOVIE_SOURCE_INFO:{
				switch(Mgr->Type){
					case QUERY_CANDIDATE:{
						QueryMovieCandidate(Mgr->SearchInfo, Mgr->ID);
					}break;
					default:{
						Msg = Msg+"Unknown CommandList type: 0x"+IntToHex(Mgr->Type);
					};
				}
			}break;
			default:{
				Msg = Msg + "Unknown WebSource type: 0x"+IntToHex(Source->Type);
			};
		}
	}
	else
		Msg += "Invalid WebSource";
	TDialogServiceSync::MessageDialog(Msg,TMsgDlgType::mtError,DIALOG_OK,TMsgDlgBtn(),THelpContext());				
}
//---------------------------------------------------------------------------
#pragma package(smart_init)