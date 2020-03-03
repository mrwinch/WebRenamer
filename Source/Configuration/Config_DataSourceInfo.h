//---------------------------------------------------------------------------

#ifndef Config_DataSourceInfoH
#define Config_DataSourceInfoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Config_Frame.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ImgList.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Menus.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.TreeView.hpp>
#include <FMX.Types.hpp>
#include <System.ImageList.hpp>
#include <System.Rtti.hpp>
#include "OperationFrameInfo.h"
#include "TestForm.h"
//---------------------------------------------------------------------------
//extern TForm3 *TestForm;
//---------------------------------------------------------------------------
class TDataSourceInfoFrame : public TConfig_Frame
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TPopupMenu *PopupMenu1;
	TMenuItem *TestOpMenu;
	TPopupMenu *PopupMenu2;
	TMenuItem *TestCommMenu;
	TVertScrollBox *VertScrollBox1;
	TGroupBox *InfoGroupBox;
	TLayout *Layout1;
	TEdit *DataSourceEditName;
	TLabel *SourceNameLabel;
	TLayout *Layout2;
	TLabel *DescriptionLabel;
	TMemo *DescriptionMemo;
	TLayout *Layout3;
	TCheckBox *AuthRequiredCheckBox;
	TComboBox *PrefLanguageCombo;
	TLabel *PreferedLanguageLabel;
	TLayout *Layout4;
	TLabel *SourceTypeLabel;
	TComboBox *SourceTypeComboBox;
	TCheckBox *UsePreferences;
	TLayout *Layout5;
	TStringGrid *ParameterGrid;
	TStringColumn *ParameterColumn;
	TStringColumn *ValueColumn;
	TButton *AddButton;
	TButton *RemoveButton;
	TGroupBox *CommandGroupBox;
	TPanel *Panel1;
	TButton *AddCommButton;
	TButton *RemoveCommButton;
	TButton *RemoveOpButton;
	TButton *AddOpButton;
	TTreeView *CommandTreeView;
	TPanel *Panel2;
	TLayout *Layout6;
	TEdit *ListNameEdit;
	TLabel *ListNameLabel;
	TLayout *Layout7;
	TLabel *CommandTypeLabel;
	TComboBox *CommandTypeCombo;
	TTabControl *OperationTabControl;

    void __fastcall GenericChange(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall RemoveButtonClick(TObject *Sender);
	void __fastcall CommandTreeViewChange(TObject *Sender);
	void __fastcall AddCommButtonClick(TObject *Sender);
	void __fastcall RemoveCommButtonClick(TObject *Sender);
	void __fastcall AddOpButtonClick(TObject *Sender);
	void __fastcall RemoveOpButtonClick(TObject *Sender);
	void __fastcall TestOpMenuClick(TObject *Sender);
	void __fastcall TestCommMenuClick(TObject *Sender);
	void __fastcall ParameterGridEditingDone(TObject *Sender, const int ACol, const int ARow);
	void __fastcall ParameterGridSelectCell(TObject *Sender, const int ACol, const int ARow,
          bool &CanSelect);
	void __fastcall ListNameEditChange(TObject *Sender);
	void __fastcall CommandTypeComboChange(TObject *Sender);
	void __fastcall ParameterGridCellClick(TColumn * const Column, const int Row);

private:	// User declarations
	TWebSource *FWebSource;
	String RemoveLineMsg;
    TForm3 *TestForm;

	TWebSource *GetSrc();
	void SetSrc(TWebSource *Src);
	void UpdateParameterGrid();
	void UpdateCommandTreeView();
	void ActivateCmdButton(bool YN);
	void UpdateCommandInfo();
	void UpdateOperationInfo();
public:		// User declarations
	__fastcall TDataSourceInfoFrame(TComponent* Owner);
	void CreateGUITxt(TNameValue *GUITxt);
	void ApplyLanguage(TNameValue *Src);
	void ResizeComponents();
    void UpdateInfo();

	__property TWebSource *WebSource = {read = GetSrc, write = SetSrc};
};
//---------------------------------------------------------------------------
extern PACKAGE TDataSourceInfoFrame *DataSourceInfoFrame;
//---------------------------------------------------------------------------
#endif
