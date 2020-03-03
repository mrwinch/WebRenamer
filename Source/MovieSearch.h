//---------------------------------------------------------------------------

#ifndef MovieSearchH
#define MovieSearchH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "Project_Const.h"
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.ListBox.hpp>
#include "CandidateFrame.h"
//---------------------------------------------------------------------------
class TMovieSearchForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *SearchButton;
	TButton *ApplyButton;
	TGroupBox *DataGroupBox;
	TLayout *Layout1;
	TLabel *MovieLabel;
	TEdit *TitleEdit;
	TLabel *YearLabel;
	TLayout *Layout2;
	TSpinBox *YearSpin;
	TLabel *DiscLabel;
	TSpinBox *DiscSpin;
	TLayout *Layout3;
	TLabel *SourceLabel;
	TComboBox *SourceCombo;
	TLayout *Layout4;
	TLabel *FormatLabel;
	TComboBox *FormatCombo;
	TLayout *Layout5;
	TLabel *ResultLabel;
	TEdit *ResultValue;
	TPanel *FramePanel;
	void __fastcall ResultValueChange(TObject *Sender);
	void __fastcall SearchButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMovieSearchForm(TComponent* Owner);
	void CreateGUITxt(TNameValue *Txt);
	void ApplyLanguage(TNameValue *Txt);
	void __fastcall FoundCandidate(String Searched, int SearchID, TList *Candidate);
	void __fastcall SelectCandidate(TObject *Sender, String Movie, String ID, int SearchID, String Release);

	TInfoGrabber *Grabber;
	TCandidateListFrame *Frame;
	int SearchID;
};
//---------------------------------------------------------------------------
extern PACKAGE TMovieSearchForm *MovieSearchForm;
//---------------------------------------------------------------------------
#endif
