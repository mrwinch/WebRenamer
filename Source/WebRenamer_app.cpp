//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Form1);
USEFORM("CandidateForm.cpp", CandidateListForm);
USEFORM("CandidateFrame.cpp", CandidateListFrame); /* TFrame: File Type */
USEFORM("Credits.cpp", Form2);
USEFORM("MovieSearch.cpp", MovieSearchForm);
USEFORM("RenameMovie.cpp", RenameMovieForm);
USEFORM("RenameShow.cpp", RenameShowForm);
USEFORM("ShowSearch.cpp", ShowSearchForm);
USEFORM("SysDialog.cpp", MyDialog);
USEFORM("Configuration\Config_Frame.cpp", Config_Frame); /* TFrame: File Type */
USEFORM("Configuration\Config_General.cpp", GeneralFrame); /* TFrame: File Type */
USEFORM("Configuration\Config_History.cpp", HistoryFrame); /* TFrame: File Type */
USEFORM("Configuration\Config_NameManager.cpp", NameManagerFrame); /* TFrame: File Type */
USEFORM("Configuration\Config_OutputName.cpp", OutputNameFrame); /* TFrame: File Type */
USEFORM("Configuration\Config_ShowSrcPref.cpp", ShowPrefFrame); /* TFrame: File Type */
USEFORM("Configuration\Configuration_Dialog.cpp", Conf_Dialog);
USEFORM("Configuration\OperationFrameInfo.cpp", OperationFrame); /* TFrame: File Type */
USEFORM("Configuration\TestForm.cpp", Form3);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TCandidateListForm), &CandidateListForm);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->CreateForm(__classid(TMovieSearchForm), &MovieSearchForm);
		Application->CreateForm(__classid(TRenameMovieForm), &RenameMovieForm);
		Application->CreateForm(__classid(TRenameShowForm), &RenameShowForm);
		Application->CreateForm(__classid(TShowSearchForm), &ShowSearchForm);
		Application->CreateForm(__classid(TForm3), &Form3);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
