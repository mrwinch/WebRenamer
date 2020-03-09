//---------------------------------------------------------------------------

#ifndef CreditsH
#define CreditsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include "Class\\Project_Const.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *Button1;
	TVertScrollBox *VertScrollBox1;
	TLabel *AppVersionLabel;
	TImage *Image1;
	TLabel *AuthorLabel;
	TLabel *ContactLabel;
	TLayout *Layout1;
	TLayout *Layout2;
	TLabel *ProjectUrl;
	TLabel *WikiLabel;
	TLabel *DescLabel;
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	void CreateGUITxt(TNameValue *Src);
	void ApplyLanguage(TNameValue *Src);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
