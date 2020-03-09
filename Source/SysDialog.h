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
//---------------------------------------------------------------------------
class TMyDialog : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLayout *Layout1;
	TImageList *ImageList1;
	TGlyph *Glyph1;
	TButton *Button1;
	TButton *Button2;
	TLabel *MessageLabel;
private:	// User declarations
public:		// User declarations
	__fastcall TMyDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMyDialog *MyDialog;
//---------------------------------------------------------------------------
#endif
