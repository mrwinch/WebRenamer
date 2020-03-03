//---------------------------------------------------------------------------

#ifndef RenameShowH
#define RenameShowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "Class\\Project_Const.h"
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
class TRenameShowForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *CancelButton;
	TButton *OkButton;
	TGroupBox *RenameBox;
	TLayout *Layout1;
	TLabel *ShowLabel;
	TEdit *ShowEdit;
	TLayout *Layout2;
	TLabel *SeasonLabel;
	TSpinBox *SeasonSpin;
	TLabel *EpisodeLabel;
	TSpinBox *EpisodeSpin;
	TLayout *Layout3;
	TLabel *TitleLabel;
	TEdit *TitleEdit;
	TLayout *Layout4;
	TLabel *ResultLabel;
	TLayout *Layout5;
	TLayout *Layout6;
	TLabel *FormatLabel;
	TComboBox *FormatComboBox;
	TEdit *OutputEdit;
	void __fastcall GenericChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TRenameShowForm(TComponent* Owner);
	void CreateGUITxt(TNameValue *GUITxt);
	void ApplyLanguage(TNameValue *GUITxt);
//    String Extension;
};
//---------------------------------------------------------------------------
extern PACKAGE TRenameShowForm *RenameShowForm;
//---------------------------------------------------------------------------
#endif
