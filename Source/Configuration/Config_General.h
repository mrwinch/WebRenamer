//---------------------------------------------------------------------------
#ifndef Config_GeneralH
#define Config_GeneralH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "Config_Frame.h"
//---------------------------------------------------------------------------
class TGeneralFrame : public TConfig_Frame
{
__published:	// IDE-managed Components
	TGroupBox *UIGroupBox;
	TLayout *Layout3;
	TCheckBox *RemeberLastModeCheckBox;
	TLabel *PreferedLanguageLabel;
	TComboBox *PreferedLanguageComboBox;
	TGroupBox *DebugGroupBox;
	TLayout *Layout1;
	TComboBox *DebugLevelComboBox;
	TLabel *DebugLevelLabel;
	TLayout *Layout2;
	TCheckBox *IncrementalDebug;
	TRadioButton *MultiDebugFile;
	TRadioButton *SingleDebugFile;
	TLayout *Layout4;
	TCheckBox *AutoRenameFile;
	void __fastcall SingleDebugFileClick(TObject *Sender);
	void __fastcall PreferedLanguageComboBoxChange(TObject *Sender);
private:	// User declarations
	TInfoGrabber *FGrabber;

	TInfoGrabber *GetGrabber();
	void SetGrabber(TInfoGrabber *Grab);
public:		// User declarations
	__fastcall TGeneralFrame(TComponent* Owner);
	void CreateGUITxt(TNameValue *GUITxt);
	void ApplyLanguage(TNameValue *Src);
	void ResizeComponents();
	void LoadConfiguration(TNameValue *Conf);
	void SaveConfiguration(TNameValue *Conf);
    void CreateConfiguration(TNameValue *Conf);
	__property TInfoGrabber *Grabber = {read = GetGrabber, write = SetGrabber};
};
//---------------------------------------------------------------------------
extern PACKAGE TGeneralFrame *GeneralFrame;
//---------------------------------------------------------------------------
#endif
