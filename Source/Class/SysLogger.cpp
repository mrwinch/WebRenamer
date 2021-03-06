//---------------------------------------------------------------------------
#pragma hdrstop

#include "SysLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog::GetValidName
*  
*  Create a valid file name using incremental notation: for example,
*  		file "Log_02.log" exists, function will return "Log_03.log"
*  ------
*  return: a valid log file name
*  ------
*  Notes:
*****************************************/
String TSysLog::GetValidName(){
	String Path = GetCurrentDir();
	String Temp;
	String Name ="Log";
	int a = 0;
	do{
		Temp = Path+"\\"+Name+Path.Format("_%2d%s",ARRAYOFCONST((a,".log")));
		if(FileExists(Temp)==false)
			return Temp;
		a++;
	}while (FileExists(Temp) == true);
	return "";
}
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog::TSysLog
*  
*  
*  Generic constructor for the class
*  ------
*  return: 
*  ------
*  Notes:
*****************************************/
TSysLog::TSysLog(){
	Handle = (int)INVALID_HANDLE_VALUE;
	MinDebugLevel = MINIMUM_DEBUG_LEVEL;
	//GenericCreation();
}
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog::TSysLog
*  
*  Constructor for the class: this version allow you to insert a file where log	
*	will be written
*  ------
*  File: file where log will be written
*  OverWrite: if true, file will be overwritten otherwise logs will append to existing
*				file
*  ------
*  return: 
*  ------
*  Notes:
*****************************************/
TSysLog::TSysLog(String File, bool OverWrite){
	FileName = File;
	MinDebugLevel = MINIMUM_DEBUG_LEVEL;
	InternalCreateWrite(File, OverWrite);
/*	if(OverWrite)
		Handle = FileOpen(FileName,fmOpenWrite|fmShareDenyWrite);
	else{
		Handle = FileOpen(FileName,fmOpenReadWrite|fmShareDenyWrite);
		FileSeek(Handle,0,2);
	}
	if(Handle <= 0){
		Handle = FileCreate(FileName,fmShareDenyWrite);
		if(Handle <=0){
			this->GenericCreation();
			Report("Unable to open '"+File+"'");
		}
	} */
}
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog
*  
*	Class destructor....  
*  ------
*  ------
*  return: Return_Description
*  ------
*  Notes:
*****************************************/
TSysLog::~TSysLog(){
	FileClose(Handle);
}
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog::GenericWrite
*  
*  Function that write a string to the log file
*  ------
*  Txt: string that must be written in the file
*  ------
*  return: 0 if success otherwise number of bytes written
*  ------
*  Notes:
*****************************************/
int TSysLog::GenericWrite(String Txt){
	AnsiString a;
	int b;
	a = Txt;
	b = FileWrite(Handle,a.c_str(),a.Length());
	if(a.Length()!=b)
		return b;
	else
		return 0;
}
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog::Report
*  
*	Write a simple string to log file (with date-time)  
*  ------
*  Log: string that must be written in the file
*  ------
*  return: 0 if success otherwise number of bytes written
*  ------
*  Notes:
*****************************************/
int TSysLog::Report(String Log){
	String Line;

	Line = GetMyTime()+Log+"\r\n";
	return GenericWrite(Line);
}
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog::GetMyTime
*  
*  Create log date-time
*  ------
*  ------
*  return: a string rappresenting date and time in format year/month/date-hours:minutes:seconds.milliseconds
*  ------
*  Notes:
*****************************************/
String TSysLog::GetMyTime(){
	TDateTime a = Now();
	String Out;
	String Tmp;

	DateTimeToString(Tmp,"yy/mm/dd-hh:mm:ss.zzz",a);
	Out = Out.Format("[%s]",ARRAYOFCONST((Tmp)));
	return Out;
}
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog::GenericCreation
*  
*  Function that create a generic file for log
*  ------
*  ------
*  return: Return_Description
*  ------
*  Notes:
*****************************************/
void TSysLog::GenericCreation(){
	FileName = GetValidName();
	if(FileExists(FileName))
		Handle = FileOpen(FileName,fmOpenWrite|fmShareDenyWrite);
	else
		Handle = FileCreate(FileName);
}
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog::Report
*  
*  Write a string to log file indicating level of information written
*  ------
*  Level: string rappresenting level information (user defined string as "INFO", "ERR"...)
*  Log: string written
*  ------
*  return: 0 if success otherwise number of bytes written
*  ------
*  Notes:
*****************************************/
int TSysLog::Report(String Level,String Log){
	if(Level.Length()>0)
		return Report("["+Level+"]"+Log);
	else
		return Report(Log);
}
//---------------------------------------------------------------------------
/*****************************************
*  TSysLog::Report
*  
*  Write a string to log file indicating source of string and level of information 
*  ------
*  Obj: string rappresenting source of log string (user defined)
*  Level: string rappresenting level information (user defined string as "INFO", "ERR"...)
*  Log: string written
*  ------
*  return: 0 if success otherwise number of bytes written
*  ------
*  Notes:
*****************************************/
int TSysLog::Report(String Obj, String Level, String Log){
//	if(Level > MinDebugLevel){
		if(Obj.Length()>0){
			if(Level.Length()>0)
				return Report("["+Obj+"]["+Level+"]"+Log);
			else
				return Report("["+Obj+"]"+Log);
		}
		else{
			if(Level.Length()>0)
				return Report("["+Level+"]"+Log);
			else
				return Report(Log);
		}
//	}
//	return DEBUG_LEVEL_INSUFFICENT;
}
//---------------------------------------------------------------------------
int TSysLog::Report(String Obj, int Level, String Log){
	if(Level > MinDebugLevel){
		if(Obj.Length()>0){
			//if(Level.Length()>0)
			return Report("["+Obj+"][LEV"+IntToHex(Level,2)+"]"+Log);
			//else
			//	return Report("["+Obj+"]"+Log);
		}
		else{
			//if(Level.Length()>0)
			return Report("[LEV"+IntToHex(Level,2)+"]"+Log);
		   //	else
			//	return Report(Log);
		}
	}
	return DEBUG_LEVEL_INSUFFICENT;
}
//---------------------------------------------------------------------------
String TSysLog::GetLogFileName(){
	return FileName;
}
//---------------------------------------------------------------------------
void TSysLog::SetLogFile(String File, bool OverWrite){
	if(Handle == -1){
		InternalCreateWrite(File, OverWrite);
	}
	else
	{
		FileClose(Handle);
		RenameFile(FileName,File);
		FileName = File;
		if(OverWrite)
			Handle = FileOpen(File,fmOpenWrite|fmShareDenyWrite);
		else{
			Handle = FileOpen(File,fmOpenReadWrite|fmShareDenyWrite);
			FileSeek(Handle,0,2);
		}
    }
}
//---------------------------------------------------------------------------
void TSysLog::InternalCreateWrite(String File, bool OverWrite){
	if(OverWrite){
		DeleteFile(File);
		Handle = FileOpen(File,fmOpenWrite|fmShareDenyWrite);
	}
	else{
		Handle = FileOpen(File,fmOpenReadWrite|fmShareDenyWrite);
		FileSeek(Handle,0,2);
	}
	if(Handle <= 0){
		Handle = FileCreate(File,fmShareDenyWrite);
		if(Handle <=0){
			GenericCreation();
			Report("Unable to open '"+File+"'");
		}
	}
}
//---------------------------------------------------------------------------
