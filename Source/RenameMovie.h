//---------------------------------------------------------------------------

#ifndef RenameMovieH
#define RenameMovieH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "Class\\Project_Const.h"
//---------------------------------------------------------------------------
class TRenameMovieForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *CancelButton;
	TButton *OkButton;
	TGroupBox *RenameBox;
	TLayout *Layout1;
	TLabel *MovieLabel;
	TEdit *MovieEdit;
	TLayout *Layout2;
	TLabel *YearLabel;
	TSpinBox *YearBox;
	TLayout *Layout3;
	TLabel *FormatLabel;
	TComboBox *FormatComboBox;
	TLayout *Layout4;
	TLabel *ResultLabel;
	TEdit *OutputEdit;
	TLabel *DiscLabel;
	TSpinBox *DiscBox;
    void __fastcall GenericChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TRenameMovieForm(TComponent* Owner);
	void CreateGUITxt(TNameValue *GUITxt);
	void ApplyLanguage(TNameValue *GUITxt);
};
//---------------------------------------------------------------------------
extern PACKAGE TRenameMovieForm *RenameMovieForm;
//---------------------------------------------------------------------------
#endif
