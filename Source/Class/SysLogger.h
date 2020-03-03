//---------------------------------------------------------------------------
#ifndef SysLoggerH
#define SysLoggerH
//---------------------------------------------------------------------------
#include<system.hpp>
#include<sysutils.hpp>
#include<DateUtils.hpp>
//---------------------------------------------------------------------------
#define     INVALID_HANDLE_LOGFILE                              -0x1000
#define     MINIMUM_DEBUG_LEVEL                                 -0x100
#define     DEBUG_LEVEL_INSUFFICENT                             0x700
//---------------------------------------------------------------------------
/*
	TSysLog: a small class to manage log to file
*/
class TSysLog{
	private:
		String FileName;
		int MinDebugLevel;
		int Handle;
		String GetValidName();
		String GetMyTime();
		void GenericCreation();
		int GenericWrite(String Txt);
        void InternalCreateWrite(String File, bool OverWrite);
	public:
		__fastcall TSysLog();
		__fastcall TSysLog(String Name, bool OverWrite = true);
		__fastcall ~TSysLog();
		int Report(String Log);
		int Report(String Level, String Log);
		int Report(String Obj,String Level, String Log);
        int Report(String Obj, int Level, String Log);
		String GetLogFileName();
		void SetLogFile(String File, bool OverWrite = true);
};
//---------------------------------------------------------------------------

#endif
