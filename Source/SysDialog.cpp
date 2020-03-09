//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SysDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)
#pragma resource ("*.Macintosh.fmx", _PLAT_MACOS)
#pragma resource ("*.Surface.fmx", _PLAT_MSWINDOWS)

TMyDialog *MyDialog;
//---------------------------------------------------------------------------
__fastcall TMyDialog::TMyDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
