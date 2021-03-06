//---------------------------------------------------------------------------

#ifndef Config_NameManagerH
#define Config_NameManagerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Config_Frame.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TNameManagerFrame : public TConfig_Frame
{
__published:	// IDE-managed Components
	TGroupBox *AcceptedExtensionGroupBox;
	TLayout *Layout3;
	TCheckBox *AcceptedExtensionCheckBox;
	TLayout *Layout4;
	TEdit *AcceptedExtensionEdit;
	TGroupBox *IgnoreTextGroupBox;
	TPanel *Panel1;
	TButton *RemoveButton;
	TButton *OkButton;
	TGroupBox *ParenthesysGroupBox;
	TLayout *Layout1;
	TCheckBox *IgnoreParenthesys;
	TCheckBox *IgnoreSquare;
	TLayout *Layout2;
	TCheckBox *IgnoreAfterParenthesys;
	TCheckBox *IgnoreCurly;
	TGrid *IgnoreGrid;
	TStringColumn *IgnoreTextColumn;
	TCheckColumn *IgnoreTextEnableColumn;
	TCheckColumn *IgnoreTextCaseColumn;
	TLayout *Layout5;
	TCheckBox *RemoveAfterSeparator;

	void __fastcall AcceptedExtensionCheckBoxChange(TObject *Sender);
	void __fastcall IgnoreGridGetValue(TObject *Sender, const int ACol, const int ARow,
		  TValue &Value);
	void __fastcall OkButtonClick(TObject *Sender);
	void __fastcall RemoveButtonClick(TObject *Sender);
	void __fastcall IgnoreGridSetValue(TObject *Sender, const int ACol, const int ARow,
          const TValue &Value);
	void __fastcall GenericColumnResize(TObject *Sender);
private:	// User declarations
	TNameTranslator *FTranslator;
    String RemoveLineMsg;

	void SetTranslator(TNameTranslator *Tr);
	TNameTranslator *GetTranslator();
	String ExportIgnoreText();
public:		// User declarations
	__fastcall TNameManagerFrame(TComponent* Owner);
	void CreateGUITxt(TNameValue *GUITxt);
	void ApplyLanguage(TNameValue *Src);
	void ResizeComponents();
	void LoadConfiguration(TNameValue *Conf);
	void SaveConfiguration(TNameValue *Conf);
	void CreateConfiguration(TNameValue *Conf);
	void RemoveLineFromGrid(int Index);
	void AddLineToGrid(String Text, bool Enabled, bool IgnoreCase);
	void UpdateIgnoreGrid();

	TStringList *IgnoreText;
	__property TNameTranslator *Translator = {read = GetTranslator, write = SetTranslator};

};
//---------------------------------------------------------------------------
extern PACKAGE TNameManagerFrame *NameManagerFrame;
//---------------------------------------------------------------------------
#endif
