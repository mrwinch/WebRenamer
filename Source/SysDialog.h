//---------------------------------------------------------------------------

#ifndef SysDialogH
#define SysDialogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.ImgList.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.ImageList.hpp>
#include "Class\\Project_Const.h"
//---------------------------------------------------------------------------
int MyShowDialog(String Title,String Msg, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons,
			const System::Uitypes::TMsgDlgBtn ADefaultButton, TNameValue *Data = NULL);
//---------------------------------------------------------------------------
class TMyDialog : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLayout *Layout1;
	TImageList *ImageList1;
	TGlyph *Glyph1;
	TLabel *MessageLabel;
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	String FMessage;
	
	String GetMess();
	void SetMess(String Msg);
public:		// User declarations
	__fastcall TMyDialog(TComponent* Owner);
	__property String Message = {read = GetMess, write = SetMess};
};
//---------------------------------------------------------------------------
extern PACKAGE TMyDialog *MyDialog;
//---------------------------------------------------------------------------
#endif
