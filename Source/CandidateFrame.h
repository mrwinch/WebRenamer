//---------------------------------------------------------------------------

#ifndef CandidateFrameH
#define CandidateFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Objects.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.HttpClientComponent.hpp>
#include <System.Net.URLClient.hpp>
#include "Project_Const.h"
//---------------------------------------------------------------------------
class TCandidateFrameBox : public TListBoxItem{
	private:
		//TPanel *ImagePanel;
		//TPanel *MainPanel;
		TLayout *MainLayout,*ImageLayout;
		TLayout *TopLayout,*CenterLayout, *BottomLayout;
		TLabel *TitleLabel;
		TLabel *AerialLabel,*IDLabel,*SummaryLabel;
		TImage *Poster;
		Candidate_Information *FInfo;

		void __fastcall BoxResized(TObject *Sender);
		void SetTitle(String Title);
		String GetTitle();
		void SetID(String ID);
		String GetID();
		void SetAired(String ID);
		String GetAired();
		void SetSum(String ID);
		String GetSum();
		void __fastcall PosterClientRequestCompleted(TObject * const Sender, _di_IHTTPResponse AResponse);
		void __fastcall ImageLeave(TObject *Sender);
		void __fastcall ImageEnter(TObject *Sender);
		void SetInfo(Candidate_Information *Info);
		Candidate_Information *GetInfo();
        void __fastcall ImgDblClick(TObject *Sender);
	public:
		__fastcall TCandidateFrameBox(TComponent *Owner);
		__fastcall ~TCandidateFrameBox();
		void DefaultPhoto(TStream *Stream);

		__property String Title = {read = GetTitle, write = SetTitle};
		__property String ID = {read = GetID, write = SetID};
		__property String Aired = {read = GetAired, write = SetAired};
		__property String Summary = {read = GetSum, write = SetSum};
		__property Candidate_Information *DataInfo = {read = GetInfo, write = SetInfo};
		TMemoryStream *PosterData;
		String PosterURL;
		TNetHTTPClient *Client;
};
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TOnSelectCandidate)(TObject *Sender, String Candidate, String ID, int SearchID);
typedef void __fastcall (__closure *TOnSelectMovie)(TObject *Sender, String Movie, String ID, int SearchID, String Release);
typedef void __fastcall (__closure *TOnRefuseCandidate)(TObject *Sender, String Candidate, int SearchID);
//---------------------------------------------------------------------------
class TCandidateListFrame : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *RefuseButton;
	TListBox *CandidateListBox;
	void __fastcall CandidateListBoxDblClick(TObject *Sender);
	void __fastcall RefuseButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    int S_ID;
	bool FInfo;
	String FCandidate;
	
	bool GetInfo();
	void SetInfo(bool Value);
public:		// User declarations
	__fastcall TCandidateListFrame(TComponent* Owner);
	void CreateGUITxt(TNameValue *Txt);
	void ApplyLanguage(TNameValue *Txt);
	void __fastcall ManageCandidateInfo(String Candidate, int SearchID, TList *CandidateList);
	String AerialLabelValue;
	String IDLabelValue;
	String SummaryLabelValue,SearchTitle;
	TForm *Form;
	TWebSource *Source;
	TResourceStream *NoPhotoImage;
	TOnSelectCandidate OnSelectCandidate;
    TOnSelectMovie OnSelectMovie;
	TOnRefuseCandidate OnRefuseCandidate;
	
	__property bool TVShowInfo = {read = GetInfo, write = SetInfo};	
};
//---------------------------------------------------------------------------
extern PACKAGE TCandidateListFrame *CandidateListFrame;
//---------------------------------------------------------------------------
#endif
