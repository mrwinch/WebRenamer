//---------------------------------------------------------------------------

#ifndef CandidateFormH
#define CandidateFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include "Project_Const.h"
#include <FMX.Objects.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.HttpClientComponent.hpp>
#include <System.Net.URLClient.hpp>
#include "CandidateFrame.h"
//---------------------------------------------------------------------------
class TCandidateListForm : public TForm
{
__published:	// IDE-managed Components
	void __fastcall RefuseButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	int S_ID;
	bool FInfo;
	String FCandidate;

	bool GetInfo();
	void SetInfo(bool Value);
public:		// User declarations
	__fastcall TCandidateListForm(TComponent* Owner);
	void CreateGUITxt(TNameValue *Txt);
	void ApplyLanguage(TNameValue *Txt);
	void __fastcall ManageCandidateInfo(String Candidate, int SearchID, TList *CandidateList);
	String AerialLabelValue;
	String IDLabelValue;
	String SummaryLabelValue,SearchTitle;
	TCandidateListFrame *Frame;
	TResourceStream *NoPhotoImage;
	__property bool TVShowInfo = {read = GetInfo, write = SetInfo};
};
//---------------------------------------------------------------------------
extern PACKAGE TCandidateListForm *CandidateListForm;
//---------------------------------------------------------------------------
#endif
