//---------------------------------------------------------------------------

#ifndef ShowSearchH
#define ShowSearchH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "Project_Const.h"
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.SpinBox.hpp>
#include "CandidateFrame.h"
//---------------------------------------------------------------------------
class TShowSearchForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TLayout *Layout1;
	TLabel *SearchTitleLabel;
	TEdit *TitleEdit;
	TLayout *Layout2;
	TLabel *SeasonLabel;
	TSpinBox *SeasonSpin;
	TLabel *EpisodeLabel;
	TSpinBox *EpisodeSpin;
	TLayout *Layout3;
	TLabel *SourceLabel;
	TComboBox *SourceCombo;
	TButton *SearchButton;
	TPanel *FramePanel;
	TLabel *FormatLabel;
	TLayout *Layout4;
	TComboBox *FormatCombo;
	TLayout *Layout5;
	TLabel *ResultLabel;
	TEdit *ResultValue;
	TButton *ApplyButton;
	void __fastcall SearchButtonClick(TObject *Sender);
	void __fastcall ResultValueChange(TObject *Sender);
private:	// User declarations
	TInfoGrabber *FGrabber;
	TNameValue *GUITxt;
	int SearchID;
	TInfoGrabber *GetGrabber();
	void SetGrabber(TInfoGrabber *Grabber);
	void __fastcall FoundCandidate(String Searched, int SearchID, TList *Candidate);
	void __fastcall RefuseCandidate(TObject *Sender, String Candidate, int SearchID);
	void __fastcall SelectCandidate(TObject *Sender, String Candidate, String ID, int SearchID);
	void __fastcall FindShowData(String ShowName, int Season, int Episode, int SearchID, ShowResultDetails Details);
public:		// User declarations
	__fastcall TShowSearchForm(TComponent* Owner);
	void CreateGUITxt(TNameValue *Txt);
	void ApplyLanguage(TNameValue *Txt);
    TCandidateListFrame *Frame;

	__property TInfoGrabber *Grabber = {read = GetGrabber, write = SetGrabber};
};
//---------------------------------------------------------------------------
extern PACKAGE TShowSearchForm *ShowSearchForm;
//---------------------------------------------------------------------------
#endif
