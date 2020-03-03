//---------------------------------------------------------------------------

#ifndef Config_OutputNameH
#define Config_OutputNameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Config_Frame.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Menus.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TOutputNameFrame : public TConfig_Frame
{
__published:	// IDE-managed Components
	TGroupBox *TVShowGroupBox;
	TGroupBox *FilmGroupBox;
	TLayout *TopLayout;
	TLabel *ShowInputTextLabel;
	TEdit *ShowFormatEdit;
	TLayout *Layout1;
	TButton *ShowFormatEditButton;
	TLayout *MiddleLayout;
	TComboBox *FormatComboBox;
	TButton *ShowFormatComboButton;
	TGroupBox *ShowExampleGroupBox;
	TLayout *Layout2;
	TLabel *ExampleShowLabel;
	TLabel *ExampleShowSeasonLabel;
	TLabel *ExampleShowEpisodeLabel;
	TLayout *Layout3;
	TLabel *ExampleShowTitle;
	TLayout *Layout4;
	TLabel *ExampleShowResult;
	TLabel *ExampleShowValue;
	TPopupMenu *ShowEditPopup;
	TMenuItem *ShowNamePopup;
	TMenuItem *ShowNameUpper;
	TMenuItem *ShowNameLower;
	TMenuItem *ShowNameFirst;
	TMenuItem *ShowNameWord;
	TMenuItem *SeasonPopup;
	TMenuItem *SeasonNumber;
	TMenuItem *Season2Digits;
	TMenuItem *Season3Digits;
	TMenuItem *EpisodePopup;
	TMenuItem *EpisodeNumber;
	TMenuItem *Episode2Digits;
	TMenuItem *Episode3Digits;
	TMenuItem *ShowTitlePopup;
	TMenuItem *ShowTitleUpper;
	TMenuItem *ShowTitleLower;
	TMenuItem *ShowTitleFirst;
	TMenuItem *ShowTitleWord;
	TLayout *Layout5;
	TLabel *MovieInputLabel;
	TEdit *MovieFormatEdit;
	TLayout *Layout6;
	TButton *MovieFormatEditButton;
	TLayout *Layout7;
	TButton *MovieFormatComboButton;
	TGroupBox *MovieExampleGroupBox;
	TLayout *Layout8;
	TLabel *ExampleMovieLabel;
	TLayout *Layout9;
	TLabel *ExampleMovieYear;
	TLayout *Layout10;
	TLabel *ExampleMovieResult;
	TLabel *ExampleMovieValue;
	TPopupMenu *MoviePopup;
	TMenuItem *MovieNamePopup;
	TMenuItem *MovieNameUpper;
	TMenuItem *MovieNameLower;
	TMenuItem *MovieNameFirst;
	TMenuItem *MovieNameWord;
	TMenuItem *MovieYear;
	TMenuItem *DiscNumber;
	TComboBox *MovieFormatComboBox;
	TMenuItem *SourceShowName;
	TMenuItem *SourceShowTitle;
	TMenuItem *SourceMovieName;

	void __fastcall GenericShowEditPopupItem(TObject *Sender);
	void __fastcall GenericMovieEditPopupItem(TObject *Sender);
	void __fastcall ShowFormatEditButtonClick(TObject *Sender);
	void __fastcall FormatComboBoxChange(TObject *Sender);
	void __fastcall ShowFormatComboButtonClick(TObject *Sender);
	void __fastcall MovieFormatEditButtonClick(TObject *Sender);
	void __fastcall MovieFormatComboButtonClick(TObject *Sender);
	void __fastcall MovieFormatComboBoxChange(TObject *Sender);
private:	// User declarations
	TNameTranslator *Translator;
	TVShowNameDetails ShowExample;
    MovieNamedetails MovieExample;

public:		// User declarations
	__fastcall TOutputNameFrame(TComponent* Owner);
	void CreateGUITxt(TNameValue *GUITxt);
	void ApplyLanguage(TNameValue *Src);
	void ResizeComponents();
	void LoadConfiguration(TNameValue *Conf);
	void SaveConfiguration(TNameValue *Conf);
    void CreateConfiguration(TNameValue *Conf);
};
//---------------------------------------------------------------------------
extern PACKAGE TOutputNameFrame *OutputNameFrame;
//---------------------------------------------------------------------------
#endif
