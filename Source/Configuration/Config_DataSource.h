//---------------------------------------------------------------------------

#ifndef Config_DataSourceH
#define Config_DataSourceH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Config_Frame.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ImgList.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.ImageList.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TDataSourceFrame : public TConfig_Frame
{
__published:	// IDE-managed Components
	TButton *AddSourceButton;
	TImageList *ImageList1;
	TGroupBox *MovieGroupBox;
	TPanel *Panel2;
	TButton *MovieDownBtn;
	TButton *MovieUpBtn;
	TStringGrid *MovieGrid;
	TStringColumn *MovieStringColumn;
	TButton *RemoveSourceButton;
	TGroupBox *TVShowGroupBox;
	TPanel *Panel1;
	TButton *TVShowDownBtn;
	TButton *TVShowUpBtn;
	TStringGrid *TVShowGrid;
	TStringColumn *TVShowStringColumn;

	void __fastcall RemoveSourceButtonClick(TObject *Sender);
	void __fastcall GenericUpDownClick(TObject *Sender);
	void __fastcall AddSourceButtonClick(TObject *Sender);
private:	// User declarations
	TInfoGrabber *FGrabber;
	TStringList *TVShowList, *MovieList;

	TInfoGrabber *GetGrabber();
	void SetGrabber(TInfoGrabber *Grab);
    TNameValue *GUI;
public:		// User declarations
	__fastcall TDataSourceFrame(TComponent* Owner);
	void UpdateGrids();
	void CreateGUITxt(TNameValue *GUITxt);
	void ApplyLanguage(TNameValue *Src);

	__property TInfoGrabber *Grabber = {read = GetGrabber, write = SetGrabber};
};
//---------------------------------------------------------------------------
extern PACKAGE TDataSourceFrame *DataSourceFrame;
//---------------------------------------------------------------------------
#endif
