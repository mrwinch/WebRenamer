//---------------------------------------------------------------------------

#ifndef OperationFrameInfoH
#define OperationFrameInfoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.NumberBox.hpp>
#include "Project_Const.h"
//---------------------------------------------------------------------------
class TOperationFrame : public TFrame
{
__published:	// IDE-managed Components
	TLayout *LayoutBottom1;
	TLabel *UrlLabel;
	TMemo *UrlMemo;
	TLayout *LayoutBottom2;
	TLabel *DataLabel;
	TMemo *DataMemo;
	TLayout *LayoutMiddle;
	TLabel *OperationAnswerLabel;
	TNumberBox *OperationAnswerBox;
	TLabel *OperationMethodLabel;
	TComboBox *OperationMethodComboBox;
	TLayout *Layout1;
	TLabel *AnswerManagerLabel;
	TMemo *AnswerManagerMemo;
	void __fastcall GenericChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TOperationFrame(TComponent* Owner);
	void __fastcall ResizeComponents();
	void __fastcall ApplyOperation(Net_Operation Op);
	void __fastcall CreateGUITxt(TNameValue *GUI);
	void __fastcall ApplyLanguage(TNameValue *GUI);

	String UrlLabelValue;
	String DataLabelValue;
	String OperationMethodComboItems;
	String OperationMethodLabelValue;
	String OperationAnswerLabelValue;
	String OperationNameLabel;
    String OperationAnswerManagerLabelValue;
    Net_Operation Operation;
};
//---------------------------------------------------------------------------
extern PACKAGE TOperationFrame *OperationFrame;
//---------------------------------------------------------------------------
#endif
