//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <System.Math.Vectors.hpp>
#include <System.ImageList.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Layers3D.hpp>
#include <FMX.Viewport3D.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Controls3D.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Rtti.hpp>
#include <FMX.ImgList.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Menus.hpp>
#include <FMX.DialogService.hpp>
#include <Xml.adomxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include "Configuration_Dialog.h"
#include "CandidateForm.h"
#include "Class\\Project_Const.h"
#include "RenameShow.h"
#include "RenameMovie.h"
#include "ShowSearch.h"
#include "MovieSearch.h"
#include "Credits.h"
//---------------------------------------------------------------------------
#define THE_TVDB_SOURCE                                         0
#define THE_MOVIEDB_SOURCE                                      1
//---------------------------------------------------------------------------
#define TV_MODE                                             0x100
#define FILM_MODE                                           0x101
//---------------------------------------------------------------------------
#define ERROR_ICON											0
#define OK_ICON												1
#define WAIT_ICON											2
#define QUESTION_ICON										3
#define UNDO_ICON											4
#define EXECUTE_ICON                                        5
#define ATTENTION_ICON                                      6
//---------------------------------------------------------------------------
TSysLog *Logger;
//---------------------------------------------------------------------------
typedef struct{
	String SourceFile;
	String SuggestedName;
	int SuggestSeason, SuggestEpisode;
	String SuggestedShow;
	String SearchName;
	String ID;
	int SearchID;
    String FinalValue;
	bool Selected;
	int ImageIndex;
	int SuggestedYear;
    int DiscNumber;
	String FindName;
	String FindTitle;
    String ActualValue;
}MainGridRowInfo;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel2;
	TRectangle *MainRectangle;
	TViewport3D *ModeIconViewport;
	TImage3D *ModeIcon;
	TBitmapAnimation *ModeIconAnimation;
	TGradientAnimation *MainRectangleGradientAnimation;
	TStatusBar *StatusBar;
	TViewport3D *MainViewport;
	TLabel *MainRectangleLabel;
	TGrid *MainGrid;
	TImageList *ImageList1;
	TSpeedButton *NewScanBtn;
	TGlyph *NewScanBtnGlyph;
	TLabel *ModeLabel;
	TFloatAnimation *MainRectangleOpacityAnimation;
	TLabel *StatusBarLabel;
	TFloatAnimation *MainGridOpacityAnimation;
	TFloatAnimation *ModeLabelAnimation;
	TGlyph *StatusBarModeIcon;
	TImageList *ImageList2;
	TSpeedButton *LoadFileBtn;
	TGlyph *LoadFileBtnGlyph;
	TSpeedButton *LoadDirBtn;
	TGlyph *LoadDirBtnGlyph;
	TOpenDialog *FileOpenDialog;
	TSpeedButton *CreditsBtn;
	TGlyph *CreditsBtnGlyph;
	TSpeedButton *ConfigBtn;
	TGlyph *ConfigBtnGlyph;
	TSpeedButton *ExitBtn;
	TGlyph *ExitBtnGlyph;
	TImageList *ImageList3;
	TPopupMenu *MainGridPopup;
	TMenuItem *Rename_Popup;
	TMenuItem *Rename_File;
	TMenuItem *Rename_Selected;
	TMenuItem *Rename_All;
	TMenuItem *Undo_Popup;
	TMenuItem *Undo_File;
	TMenuItem *Undo_Selected;
	TMenuItem *Undo_All;
	TSpeedButton *RenameButton;
	TGlyph *RenameBtnGlyph;
	TMenuItem *MenuItem1;
	TMenuItem *ManualRename;
	TMenuItem *ManualSearch;
	TLayout *BottomLayout;
	TPanel *Panel1;
	TImage *CopyrightImage;
	TFloatAnimation *CopyrightAnimation;
	TLabel *CopyrightLabel;
	void __fastcall ModeIconClick(TObject *Sender);
	void __fastcall MainRectangleGradientAnimationFinish(TObject *Sender);
	void __fastcall ModeIconViewportResize(TObject *Sender);
	void __fastcall MainRectangleDragOver(TObject *Sender, const TDragObject &Data,
          const TPointF &Point, TDragOperation &Operation);
	void __fastcall MainRectangleDragDrop(TObject *Sender, const TDragObject &Data,
          const TPointF &Point);
	void __fastcall NewScanBtnClick(TObject *Sender);
	void __fastcall MainRectangleOpacityAnimationFinish(TObject *Sender);
	void __fastcall MainGridOpacityAnimationFinish(TObject *Sender);
	void __fastcall ModeLabelAnimationFinish(TObject *Sender);
	void __fastcall MainGridGetValue(TObject *Sender, const int ACol, const int ARow,
          TValue &Value);
	void __fastcall LoadDirBtnClick(TObject *Sender);
	void __fastcall LoadFileBtnClick(TObject *Sender);
	void __fastcall CreditsBtnClick(TObject *Sender);
	void __fastcall ConfigBtnClick(TObject *Sender);
	void __fastcall ExitBtnClick(TObject *Sender);
	void __fastcall UndoRename(TObject *Sender);		//Undo only selected row
	void __fastcall UndoSelected(TObject *Sender);		//Undo selected row (AutoRename = false)
	void __fastcall UndoAll(TObject *Sender);			//Undo all renamed files
	void __fastcall Rename(TObject *Sender);			//Rename only selected row
	void __fastcall RenameSelected(TObject *Sender);	//Rename selected row
	void __fastcall RenameAll(TObject *Sender);			//Rename all files
	void __fastcall MainGridSetValue(TObject* Sender, const int ACol, const int ARow, const TValue &Value);
	void __fastcall MainGridPopupPopup(TObject *Sender);
	void __fastcall ManualRenameClick(TObject *Sender);
	void __fastcall UserRefuseCandidate(TObject *Sender, String Candidate, int SearchID);
	void __fastcall ManualSearchClick(TObject *Sender);
	void __fastcall CopyrightAnimationFinish(TObject *Sender);
private:	// User declarations
	void CreateGUITxt();
	void ApplyLanguage();
	void LoadConfiguration();
	void CreateConfiguration();
	void ReverseMainViewport(bool MainRectangleSource);
	void AddFiles(TStringList *Files);
	void SetMainRectangle(int Mode);
	void UpdateShowGridInfo();
	void UpdateMovieGridInfo();
	void __fastcall TestSelectCandidate(TObject *Sender, String ShowName, String ShowID);
	void __fastcall ManageCandidateFound(String Searched, int SearchID, TList *Candidate);
	void __fastcall ShowSelectCandidate(TObject *Sender, String Candidate, String ID, int SearchID);
	void __fastcall ShowFoundData(String ShowName, int Season, int Episode, int SearchID, ShowResultDetails Details);
    void __fastcall MovieSelectCandidate(TObject *Sender, String Candidate, String ID, int SearchID, String Release);
	void __fastcall ConnectionError(TNetHTTPClient *Client,TNetHTTPRequest *Request, CommandList *Cmd, int CommandIndex, int ErrCode, String ErrDesc);
	void __fastcall CompleteSource(String Searched,int ID);
	void __fastcall ColumnResize(TObject *Sender);
	void ShowCopyrightPanel(int Type);
	void UndoRenameRow(int Row);
	void RenameRow(int Row);
	void LoadLanguage();
    String GetIncrementalLogFile();
	TStringColumn *FileNameColumn;
	TCheckColumn *CheckColumn;
	TGlyphColumn *StatusColumn;
	TStringColumn *FinalNameColumn;
	String AppDirectory;
    String ConfigFileName;
	TGradient *FilmGradient,*ShowGradient;
	TStringList *FoundCandidate;
	TCandidateListForm *CandidateForm;
	TRenameShowForm *RenameForm;
	TRenameMovieForm *RenameForm2;
	TShowSearchForm *SearchForm;
	TMovieSearchForm *SearchForm2;
	
	int ExecutedSearch;
	//int FinalNameColumnIndex;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	//void __fastcall ApplyWebSourceLanguage(TObject *Sender);
//    void __fastcall ConnectionError(TNetHTTPClient *Client,TNetHTTPRequest *Request, CommandList *Cmd, int CommandIndex, int ErrCode, String ErrDesc);
	TResourceStream *TVIcon;
	TResourceStream *FilmIcon;
	TNameValue *Config;
	TNameValue *GUITxt;
	TList *MainGridRows;
	TNameTranslator *Translator;
	TForm2 *CreditsForm;
    TConf_Dialog *Conf_Dialog;
//	TConfigDialog *ConfigDlg;
	TInfoGrabber *Grabber;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
int Rand = 0;
//---------------------------------------------------------------------------
#endif
