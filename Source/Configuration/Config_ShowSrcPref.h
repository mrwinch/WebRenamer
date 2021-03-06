//---------------------------------------------------------------------------

#ifndef Config_ShowSrcPrefH
#define Config_ShowSrcPrefH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Config_Frame.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TShowPrefFrame : public TConfig_Frame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TPanel *Panel1;
	TStringGrid *PreferencesGrid;
	TStringColumn *NamePrefColumn;
	TStringColumn *IDPrefColumn;
	TButton *AddPrefButton;
	TButton *RemovePrefButton;
	void __fastcall AddPrefButtonClick(TObject *Sender);
	void __fastcall RemovePrefButtonClick(TObject *Sender);
	void __fastcall PreferencesGridEditingDone(TObject *Sender, const int ACol, const int ARow);
private:	// User declarations
	String InternalRemoveDlg;
	TWebSource *FWebSource;

	TWebSource *GetSrc();
	void SetSrc(TWebSource *Src);
	void UpdateGrid();
public:		// User declarations
	__fastcall TShowPrefFrame(TComponent* Owner);
	void CreateGUITxt(TNameValue *GUITxt);
	void ApplyLanguage(TNameValue *Src);
	void ResizeComponents();
	void LoadConfiguration(TNameValue *Conf);
	void SaveConfiguration(TNameValue *Conf);

//	TWebSource *WebSource = NULL;
	__property TWebSource *WebSource = {read = GetSrc, write = SetSrc};
};
//---------------------------------------------------------------------------
extern PACKAGE TShowPrefFrame *ShowPrefFrame;
//---------------------------------------------------------------------------
#endif
