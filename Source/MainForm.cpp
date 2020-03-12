//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainForm.h"
//#include "Credits.h"
//#include "TestForm.h"
//#include "CandidateForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.Surface.fmx", _PLAT_MSWINDOWS)

TForm1 *Form1;
//---------------------------------------------------------------------------
/****************************************************
 *  DEBUG
 *
 *  Description: small function to debug
 *
 *  Level: minimum level of debugging at which information will be show
 *  Msg: message of debug to show
 *  Return value: none
 *
 *  Note:
 ***************************************************/
void DEBUG_APP(int Level, String Msg){
#ifdef WEB_RENAMER_DEBUG
	Logger->Report("APPFR1",NAME_LEVEL(Level),Msg);
#endif
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	AppDirectory = System::Ioutils::TDirectory::GetCurrentDirectory();
	ConfigFileName = AppDirectory+"\\"+CONFIGURATION_FILE;
	Logger = new TSysLog();
	Config = new TNameValue(this);
	GUITxt = new TNameValue(this);
	Translator = new TNameTranslator(this);
	Grabber = new TInfoGrabber(this);
	MainGridRows = new TList();
	FileNameColumn = new TStringColumn(MainGrid);
	FilmGradient = new TGradient();
	ShowGradient = new TGradient();
	CheckColumn = new TCheckColumn(MainGrid);
	StatusColumn = new TGlyphColumn(MainGrid);
	FileNameColumn = new TStringColumn(MainGrid);
	FinalNameColumn = new TStringColumn(MainGrid);
	CandidateForm = new TCandidateListForm(this);
	RenameForm = new TRenameShowForm(this);
	RenameForm2 = new TRenameMovieForm(this);
	SearchForm2 = new TMovieSearchForm(this);
	SearchForm = new TShowSearchForm(this); 
	
	FileNameColumn->Parent = MainGrid;
	FileNameColumn->Width = 300;
	FileNameColumn->ReadOnly = true;
	CheckColumn->Parent = MainGrid;
	CheckColumn->Width = 20;
	CheckColumn->Tag = CheckColumn->Width;
	CheckColumn->OnResize = ColumnResize;
//    CheckColumn->ReadOnly = false;
	StatusColumn->Parent = MainGrid;
	StatusColumn->Width = 25;
	StatusColumn->ReadOnly = true;
	StatusColumn->Tag = StatusColumn->Width;
	StatusColumn->OnResize = ColumnResize;
	FinalNameColumn->Parent = MainGrid;
	FinalNameColumn->Width = 300;
	FinalNameColumn->ReadOnly = true;
	BottomLayout->Visible = false;

	FilmIcon = new TResourceStream((int)HInstance,"FilmIcon",RT_RCDATA);
	TVIcon = new TResourceStream((int)HInstance,"TVIcon",RT_RCDATA);
	ModeIcon->Bitmap->LoadFromStream(FilmIcon);
	ModeIcon->Tag = FILM_MODE;
	CreditsForm = new TForm2(this);
	Conf_Dialog = new TConf_Dialog(this);
	FilmGradient->Assign(MainRectangle->Fill->Gradient);
	ShowGradient->Assign(MainRectangleGradientAnimation->StopValue);
	MainRectangleGradientAnimation->StartValue = MainRectangle->Fill->Gradient;
	MainRectangleLabel->Position->X = 100;
	MainRectangleLabel->Position->Y = 100;
	MainRectangleLabel->Width = 400;
	MainGrid->Visible = false;
	MainGrid->Align = TAlignLayout::Client;
	Grabber->OnFindCandidate = ManageCandidateFound;
	Grabber->OnFindShowData = ShowFoundData;
	Grabber->OnConnectionError = ConnectionError;
	Grabber->OnCompleteAvailableSource = CompleteSource;
	

	LoadConfiguration();
	if(Config->GetInt("DebugLevel") > NO_DEBUG){
		if(Config->GetBool("MultiDebugFile") == false)
			Logger->SetLogFile(AppDirectory+"\\"+DEBUG_FILE,!(Config->GetBool("IncrementalDebug")));
		else{
			Logger->SetLogFile(GetIncrementalLogFile());
		}
		DEBUG_APP(INFO_DEBUG,"Starting WebRenamer ver. "+IntToHex(APP_VERSION));
		DEBUG_APP(INFO_DEBUG,"Work directory: "+AppDirectory);
	}
	CreateGUITxt();
	ApplyLanguage();
	if(Config->GetBool("RememeberLastMode"))
		SetMainRectangle(Config->GetInt("LastMode"));
	Caption = APP_NAME + (String)" - "+IntToStr(APP_VERSION)+(String)"."+IntToStr(APP_SUBVERSION)+" Build "+IntToStr(APP_BUILD);
	FoundCandidate = new TStringList();
	ExecutedSearch = 0;
	Conf_Dialog->HistoryFrame->History->LoadFromXML(AppDirectory+"\\History.xml");
	Conf_Dialog->HistoryFrame->PopulateTree(NULL);
	Conf_Dialog->Grabber = Grabber;
	Grabber->OnCreateWebSource = Conf_Dialog->CreateWebSource;
	//FinalNameColumnIndex = 2;
}
//---------------------------------------------------------------------------
String TForm1::GetIncrementalLogFile(){
	String Out;
	String Dir = AppDirectory+"\\Debug";
	int a = 0;
	if(System::Ioutils::TDirectory::Exists(Dir) == false){
		System::Ioutils::TDirectory::CreateDirectory(Dir);
	}
	do{
		Out = Dir+(String)"\\WebRenamer Log_"+IntToStr(a)+(String)".log";
		a++;
	}while(System::Ioutils::TFile::Exists(Out) == true);
	return Out;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ModeIconClick(TObject *Sender)
{
	DEBUG_APP(INFO_DEBUG,"ModeIconClick()");
	TResourceStream *Start, *Stop;
	float Duration = 0.8;
	Stop = NULL;
	TAnimator::AnimateFloat(ModeIcon, "Position.Z", 5, Duration/2);
	TAnimator::AnimateFloatDelay(ModeIcon, "Position.Z", 0,Duration/2, Duration/2);
	TAnimator::AnimateFloat(ModeIcon, "RotationAngle.y", 360, Duration);
	DEBUG_APP(TOTAL_DEBUG,"Switch to "+(ModeIcon->Tag == FILM_MODE?(String)"TV Show mode":"Film mode"));
	switch(ModeIcon->Tag){
		case FILM_MODE:{
			DEBUG_APP(TOTAL_DEBUG,"Switch to TV Show mode...");
			Start = FilmIcon;
			Stop = TVIcon;
			ModeIcon->Tag = TV_MODE;
			ModeLabel->Text = GUITxt->GetString("ModeLabel_Show");
			StatusBarModeIcon->ImageIndex = 1;
		}break;
		case  TV_MODE:{
			DEBUG_APP(TOTAL_DEBUG,"Switch to Film mode...");
			Start = TVIcon;
			Stop = FilmIcon;
			ModeIcon->Tag = FILM_MODE;
			ModeLabel->Text = GUITxt->GetString("ModeLabel_Film");
			StatusBarModeIcon->ImageIndex = 0;
		}break;
	};
	StatusBarLabel->Text = ModeLabel->Text;
	ModeLabel->AutoSize = false;
	ModeLabel->Width = 0;
	ModeLabelAnimation->StopValue = 200;
	ModeLabelAnimation->Start();
	if(Stop){
		ModeIconAnimation->StartValue->LoadFromStream(Start);
		ModeIconAnimation->StopValue->LoadFromStream(Stop);
		ModeIconAnimation->Delay = Duration - 0.4;
		ModeIconAnimation->Duration = 0.4;
		ModeIconAnimation->Start();
		MainRectangleGradientAnimation->Duration = Duration;
		MainRectangleGradientAnimation->Start();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainRectangleGradientAnimationFinish(TObject *Sender)
{
	DEBUG_APP(INFO_DEBUG,"MainRectangleGradientAnimationFinish()");
	TGradient *Tmp = new TGradient();
	Tmp->Assign(MainRectangleGradientAnimation->StartValue);
	MainRectangleGradientAnimation->StartValue->Assign(MainRectangleGradientAnimation->StopValue);
	MainRectangleGradientAnimation->StopValue->Assign(Tmp);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ModeIconViewportResize(TObject *Sender)
{
	if(ModeIconViewport){
		TControl *Dad = (TControl*)ModeIconViewport->Parent;
		if(Dad){
			ModeIconViewport->Position->X = Dad->Width - 10 - ModeIconViewport->Width;
			ModeIconViewport->Position->Y = Dad->Height - 10 - ModeIconViewport->Height;
			ModeLabel->Position->X = 50;
			ModeLabel->Position->Y = Dad->Height - 50;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainRectangleDragOver(TObject *Sender, const TDragObject &Data,
          const TPointF &Point, TDragOperation &Operation)
{
	Operation = TDragOperation::Link;
}
//---------------------------------------------------------------------------
void TForm1::AddFiles(TStringList *Files){
	DEBUG_APP(INFO_DEBUG,"AddFiles()");
	DEBUG_APP(TOTAL_DEBUG,"Adding "+IntToStr(Files->Count)+(String)" files to search...");
	MainGridRowInfo *Info;
	String Ext;
	TStringList *Extension = new TStringList();
	if(Config->GetBool("AcceptOnlyExtension")){
		Ext = Config->GetString("AcceptedExtension");
		Ext = ReplaceStr(Ext,";",",");
		Extension->CommaText = Ext;
	}
	int a;
	bool Accept;
	int Attr;
	for(a = MainGridRows->Count-1;a>-1;a--){
		MainGridRows->Delete(a);
	}
	MainGridRows->Clear();
	for(a=0;a<Files->Count;a++){
		Attr = FileGetAttr(Files->Strings[a]);
		if((Attr & faDirectory) == 0){
			Accept = true;
			if(Config->GetBool("AcceptOnlyExtension")){
				Ext = ExtractFileExt(Files->Strings[a]);
				Ext = Ext.SubString(2, Ext.Length());
				if(Extension->IndexOf(Ext) == -1)
					Accept = false;
			}
			if(Accept){
				Info = (MainGridRowInfo*)AllocMem(sizeof(MainGridRowInfo));
				Info->SourceFile = Files->Strings[a];
				Info->Selected = true;
				Info->ImageIndex = QUESTION_ICON;
				Info->ActualValue = ExtractFileName(Info->SourceFile);
				MainGridRows->Add(Info);
				DEBUG_APP(TOTAL_DEBUG,"Accepting "+Info->SourceFile);
			}
			else
				DEBUG_APP(TOTAL_DEBUG,"Refusing (wrong extension)"+Files->Strings[a]);
		}
		else
			DEBUG_APP(TOTAL_DEBUG,"Refuse as directory: "+Files->Strings[a]);
	}
	MainGrid->RowCount = MainGridRows->Count;
	DEBUG_APP(TOTAL_DEBUG,"Accepted "+IntToStr(MainGridRows->Count)+(String)" files");
	if(MainGridRows->Count > 0){
		Conf_Dialog->HistoryFrame->History->CreateRecord();
	}
	if(ModeIcon->Tag == FILM_MODE){//Movie...
		UpdateMovieGridInfo();
	}
	else{// TV SHOW...
		UpdateShowGridInfo();
	}
}
//---------------------------------------------------------------------------
void TForm1::UpdateMovieGridInfo(){
	DEBUG_APP(INFO_DEBUG,"UpdateMovieGridInfo()");
	int a;
	MainGridRowInfo *Info;
	Movie_Info Movie;
	bool AutoRename = Config->GetBool("AutoRenameFile");
	CheckColumn->Visible = !AutoRename;
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		Movie = Translator->TranslateMovie(ExtractFileName(Info->SourceFile));
		Info->SearchName = UpperFirstLetter(Movie.Name);
		Info->ID = "";
		Info->SearchID = ExecutedSearch;
		Info->SuggestedYear = Movie.Year;
		Info->DiscNumber = Movie.Disc;
		FileNameColumn->UpdateCell(a);
		StatusColumn->UpdateCell(a);
		if(AutoRename == false)
			CheckColumn->UpdateCell(a);
		ExecutedSearch++;
		Config->SetString("StartSearchDir",ExtractFilePath(Info->SourceFile));
		Info->FinalValue = Info->SearchName+(String)" - "+IntToStr(Movie.Year);
        FinalNameColumn->UpdateCell(a);
	}
	if(MainGridRows->Count > 0){
		Info = (MainGridRowInfo*)MainGridRows->Items[0];
		Grabber->QueryMovieCandidate(Info->SearchName, Info->SearchID);
	}	
}
//---------------------------------------------------------------------------
void TForm1::UpdateShowGridInfo(){
	DEBUG_APP(INFO_DEBUG,"UpdateShowGridInfo()");
//	DEBUG_APP(TOTAL_DEBUG,"Glyph "+IntToStr(StatusColumn->Index)+(String)" - "+IntToStr(CheckColumn->Index));
	int a;
	MainGridRowInfo *Info;
	Episode_Info Episode;
	bool AutoRename = Config->GetBool("AutoRenameFile");
	CheckColumn->Visible = !AutoRename;
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		Episode = Translator->TranslateEpisode(ExtractFileName(Info->SourceFile));
		if(Episode.NameCandidate->Count>0)
			Info->SuggestedShow = Episode.NameCandidate->Strings[0];
		Info->SuggestSeason = Episode.Order.Season;
		Info->SuggestEpisode = Episode.Order.Episode;
		Info->SuggestedName = Episode.SuggestedTitle;
		Info->SearchName = UpperFirstLetter(Info->SuggestedShow);
		Info->ID = "";
		Info->SearchID = ExecutedSearch;
		FileNameColumn->UpdateCell(a);
		StatusColumn->UpdateCell(a);
		if(AutoRename == false)
			CheckColumn->UpdateCell(a);
		ExecutedSearch++;
		Config->SetString("StartSearchDir",ExtractFilePath(Info->SourceFile));
	}
	if(MainGridRows->Count > 0){
		Info = (MainGridRowInfo*)MainGridRows->Items[0];
		Grabber->QueryShowCandidate(Info->SearchName, Info->SearchID);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainRectangleDragDrop(TObject *Sender, const TDragObject &Data,
		  const TPointF &Point)
{
	TStringList *List = new TStringList();
	int a;
	ReverseMainViewport(true);
	for(a=0;a<Data.Files.Length;a++){
		List->Add(Data.Files[a]);
	}
	AddFiles(List);
}
//---------------------------------------------------------------------------
void TForm1::CreateGUITxt(){
//	DEBUG_APP(TOTAL_DEBUG,"Executing CreateGUITxt()");
	GUITxt->AddString("Short_Language","en","ISO639 short identificatin for language");
	GUITxt->AddString("MainRectangleLabel","Drop your files here...","Text showed in gradient main rectangle");
	GUITxt->AddString("NewScanBtn_Hint","Start a new scan...","Hint for new scan button");
	GUITxt->AddString("LoadFileBtn_Hint","Load some file...","Hint for load file button");
	GUITxt->AddString("LoadDirBtn_Hint","Load file from directory","Hint for load dir button");
	GUITxt->AddString("CreditsBtn_Hint","Credits","Hint for credits button");
	GUITxt->AddString("ConfigBtn_Hint","Configuration","Hint for configuration button");
	GUITxt->AddString("ExitBtn_Hint","Close application","Hint for exit button");
	GUITxt->AddString("ModeLabel_Film","Film mode","Text for mode label (Film)");
	GUITxt->AddString("ModeLabel_Show","TV Show mode","Text for mode label (TV Show)");
	GUITxt->AddString("SourceFileColumnHeader","Source file","Header of the column in main grid with file name");
	GUITxt->AddString("DestFileColumnHeader","Renamed file","Header of the column in main grid with output name");
	GUITxt->AddString("SelectedColumnHeader","Selected","Header of the column in main grid with selection");	
	GUITxt->AddString("SelectDirectoryDlg_Title","Select a directory...","Title showed in dialog for directory choose");
	GUITxt->AddString("SelectFileDlg_Title","Select files to rename...","Title showed in dialog for file choose");
	GUITxt->AddString("ConnErrorCode","Error: code 0x","Connection error code");
	GUITxt->AddString("Rename_Popup","Rename...","Rename popup item");
	GUITxt->AddString("Rename_File","Rename this file","Rename single file popup item");
	GUITxt->AddString("Rename_Selected","Rename selected files","Rename selected file popup item");
	GUITxt->AddString("Rename_All","Rename all files","Rename all file popup item");
	GUITxt->AddString("Undo_Popup","Undo...","Undo popup item");
	GUITxt->AddString("Undo_File","Undo this file","Undo single file popup item");
	GUITxt->AddString("Undo_Selected","Undo selected files","Undo selected file popup item");
	GUITxt->AddString("Undo_All","Undo all files","Undo all file popup item");
	GUITxt->AddString("ManualRename","Manual rename","Manual rename popup item");
	GUITxt->AddString("ManualSearch","Manual search","Manual search popup item");
	GUITxt->AddString("NoSourceMess","Sorry, no other source for search ","Message for no more source error");
	GUITxt->AddString("StopScan","Search in progress: stop it?","Message for no more source error");
	GUITxt->AddString("Dialog_Button_Yes","Yes","Message for no more source error");
	GUITxt->AddString("Dialog_Button_No","No","Message for no more source error");
	GUITxt->AddString("Dialog_Button_Ok","Ok","Message for no more source error");
	GUITxt->AddString("Dialog_Button_Cancel","Cancel","Message for no more source error");
	GUITxt->AddString("Dialog_Button_Abort","Abort","Message for no more source error");
	GUITxt->AddString("Dialog_Button_Retry","Retry","Message for no more source error");
	GUITxt->AddString("Dialog_Button_Ignore","Ignore","Message for no more source error");
	GUITxt->AddString("Dialog_Button_All","All","Message for no more source error");
	GUITxt->AddString("Dialog_Button_NoToAll","No to all","Message for no more source error");
	GUITxt->AddString("Dialog_Button_YesToAll","Yes to all","Message for no more source error");
	GUITxt->AddString("Dialog_Button_Help","Help","Message for no more source error");
	GUITxt->AddString("Dialog_Button_Close","Close","Message for no more source error");
	//Dialogs CreateGUITxt...
	CreditsForm->CreateGUITxt(GUITxt);
	Conf_Dialog->CreateGUITxt(GUITxt);
	CandidateForm->CreateGUITxt(GUITxt);
	RenameForm->CreateGUITxt(GUITxt);
	RenameForm2->CreateGUITxt(GUITxt);
	SearchForm->CreateGUITxt(GUITxt);	
	SearchForm2->CreateGUITxt(GUITxt);
    SaveLanguage();
}
//---------------------------------------------------------------------------
void TForm1::ApplyLanguage(){
//	DEBUG_APP(TOTAL_DEBUG,"Executing ApplyLanguage()");
//	SaveLanguage();
	Conf_Dialog->GeneralFrame->UpdateGUILanguage(GUITxt,Config);
	MainRectangleLabel->Text = GUITxt->GetString("MainRectangleLabel");
	NewScanBtn->Hint = GUITxt->GetString("NewScanBtn_Hint");
	LoadFileBtn->Hint = GUITxt->GetString("LoadFileBtn_Hint");
	LoadDirBtn->Hint = GUITxt->GetString("LoadDirBtn_Hint");
	CreditsBtn->Hint = GUITxt->GetString("CreditsBtn_Hint");
	ConfigBtn->Hint = GUITxt->GetString("ConfigBtn_Hint");
	ExitBtn->Hint = GUITxt->GetString("ExitBtn_Hint");
	if(ModeIcon->Tag == FILM_MODE)
		ModeLabel->Text = GUITxt->GetString("ModeLabel_Film");
	else
        ModeLabel->Text = GUITxt->GetString("ModeLabel_Show");
	StatusBarLabel->Text = ModeLabel->Text;
	FileNameColumn->Header = GUITxt->GetString("SourceFileColumnHeader");
	FinalNameColumn->Header = GUITxt->GetString("DestFileColumnHeader");
	Rename_Popup->Text = GUITxt->GetString("Rename_Popup");
	Rename_File->Text = GUITxt->GetString("Rename_File");
	Rename_Selected->Text = GUITxt->GetString("Rename_Selected");
	Rename_All->Text = GUITxt->GetString("Rename_All");
	Undo_Popup->Text = GUITxt->GetString("Undo_Popup");
	Undo_File->Text = GUITxt->GetString("Undo_File");
	Undo_Selected->Text = GUITxt->GetString("Undo_Selected");
	Undo_All->Text = GUITxt->GetString("Undo_All");
	ManualRename->Text = GUITxt->GetString("ManualRename");
	ManualSearch->Text = GUITxt->GetString("ManualSearch");

	//Dialogs apply...
	CreditsForm->ApplyLanguage(GUITxt);
	Conf_Dialog->ApplyLanguage(GUITxt);
	CandidateForm->ApplyLanguage(GUITxt);
	RenameForm->ApplyLanguage(GUITxt);
	RenameForm2->ApplyLanguage(GUITxt);
	SearchForm->ApplyLanguage(GUITxt);
	SearchForm2->ApplyLanguage(GUITxt);
}
//---------------------------------------------------------------------------
void TForm1::LoadConfiguration(){
	String CFile = AppDirectory+"\\"+CONFIGURATION_FILE;
	String Txt;
	CreateConfiguration();
	if(System::Ioutils::TFile::Exists(CFile)){
		TNameValue *Tmp = new TNameValue(this);
		TStringList *Obj;
		Tmp->LoadFromXML(CFile);
		Obj = Tmp->GetValues();
		int b;
		for(int a=0;a<Obj->Count;a++){
			Txt = Obj->Strings[a];
			if(Config->ValueExist(Obj->Strings[a])){    //Update value...
				b = Config->GetValueIndex(Obj->Strings[a]);
				switch(Config->GetValueTypeByIndex(b)){
					case OBJ_BOOL:{
						Config->SetBool(Obj->Strings[a],Tmp->GetBool(Obj->Strings[a]));
					}break;
					case OBJ_INT:{
						Txt = Obj->Strings[a];
						Config->SetInt(Obj->Strings[a],Tmp->GetInt(Obj->Strings[a]));
					}break;
					case OBJ_STR:{
						Config->SetString(Obj->Strings[a],Tmp->GetString(Obj->Strings[a]));
					}break;
					case OBJ_FLT:{
						Config->SetFloat(Obj->Strings[a],Tmp->GetFloat(Obj->Strings[a]));
					}break;
				}
			}
			else{   //Insert a new value
				switch(Tmp->GetValueType(Txt)){
					case OBJ_BOOL:{
						Config->AddBool(Obj->Strings[a],Tmp->GetBool(Obj->Strings[a]),Tmp->GetComment(Txt));
					}break;
					case OBJ_INT:{
						Txt = Obj->Strings[a];
						Config->AddInt(Obj->Strings[a],Tmp->GetInt(Obj->Strings[a]),Tmp->GetComment(Txt));
					}break;
					case OBJ_STR:{
						Config->AddString(Obj->Strings[a],Tmp->GetString(Obj->Strings[a]),Tmp->GetComment(Txt));
					}break;
					case OBJ_FLT:{
						Config->AddFloat(Obj->Strings[a],Tmp->GetFloat(Obj->Strings[a]),Tmp->GetComment(Txt));
					}break;
				}
            }
		}
	}
	Config->SetString("SoftwareDir",AppDirectory);
	Txt = Config->GetString("IgnoreList");
	Translator->ImportIgnoreList(Txt);
	CFile = AppDirectory+"\\Grabber.xml";
	if(Config->ValueExist("UserAgent"))
		Grabber->UserAgent = Config->GetString("UserAgent");
	Grabber->PreferedLanguage = Config->GetString("PreferedLanguage");
	Grabber->LoadFromXML(CFile);
	Conf_Dialog->LoadConfiguration(Config);
//    SaveLanguage();
}
//---------------------------------------------------------------------------
void TForm1::CreateConfiguration(){
	Config->AddString("StartSearchDir",AppDirectory,"Initial search directory");
	Config->AddInt("LastMode",FILM_MODE,"Last mode of the software...");
	Config->AddString("SoftwareDir",AppDirectory,"Directory with software");
	Conf_Dialog->NameManagerFrame->Translator = Translator;
	Conf_Dialog->CreateConfiguration(Config);
}
//---------------------------------------------------------------------------
void TForm1::ReverseMainViewport(bool MainRectangleSource){
//	DEBUG_APP(INFO_DEBUG,"ReverseMainViewport()");
	if(MainRectangleSource){
		MainRectangleOpacityAnimation->StartValue = 1.0;
		MainRectangleOpacityAnimation->StopValue = 0.0;
		MainRectangleOpacityAnimation->Start();
	}
	else{
		MainGridOpacityAnimation->StartValue = 1.0;
		MainGridOpacityAnimation->StopValue = 0.0;
		MainRectangleOpacityAnimation->StartValue = 0.0;
		MainRectangleOpacityAnimation->StopValue = 1.0;
		MainGridOpacityAnimation->Start();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NewScanBtnClick(TObject *Sender)
{
	DEBUG_APP(INFO_DEBUG,"NewScanBtnClick()");
	MainGridRowInfo *Info;
	for(int a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		Info->FinalValue = "";
		FinalNameColumn->UpdateCell(a);
	}
	MainGridRows->Clear();
	ReverseMainViewport(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainRectangleOpacityAnimationFinish(TObject *Sender)
{
	bool Value;
	bool Auto = false;
//	DEBUG_APP(INFO_DEBUG,"MainRectangleOpacityAnimationFinish()");
	if(MainRectangleOpacityAnimation->StopValue > 0.9){
		//MainRectangle visible...
		Value = true;
	}
	else{
		Value = false;
		MainGrid->Opacity = 1.0;
	}
	MainGrid->Visible = !Value;
	MainRectangle->Visible = Value;
	NewScanBtn->Enabled = !Value;
	NewScanBtnGlyph->Enabled = !Value;
	if(Config)
		Auto = Config->GetBool("AutoRenameFile");
	if(Auto == false){
		RenameButton->Enabled = !Value;
		RenameBtnGlyph->Enabled = !Value;
	}
	else{
		RenameButton->Enabled = false;
		RenameBtnGlyph->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainGridOpacityAnimationFinish(TObject *Sender)
{
	bool Value;
	float Tmp;
	DEBUG_APP(INFO_DEBUG,"MainGridOpacityAnimationFinish()");
	if(MainGridOpacityAnimation->StopValue > 0.9){
		Value = false;
	}
	else{
		Value = true;
	}
	MainGrid->Visible = !Value;
	MainRectangle->Visible = Value;
	MainRectangleOpacityAnimation->Start();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ModeLabelAnimationFinish(TObject *Sender)
{
	DEBUG_APP(INFO_DEBUG,"ModeLabelAnimationFinish()");
	ModeLabel->AutoSize = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainGridGetValue(TObject *Sender, const int ACol, const int ARow,
		  TValue &Value)
{
//	DEBUG_APP(INFO_DEBUG,"MainGridGetValue()");
	MainGridRowInfo *Info;
	if(ARow < MainGridRows->Count){
		Info = (MainGridRowInfo*)MainGridRows->Items[ARow];
		bool AutoRename = Config->GetBool("AutoRenameFile");
		switch(ACol){
			case 0:{    //File name...
				if(ARow < MainGridRows->Count && ARow >-1){
					Value = ExtractFileName(Info->SourceFile);
				}
				else{
					Value = "Row "+IntToStr(ARow);
				}
			}break;
			case 1:{
				Value = Info->Selected;
			}
			break;
			case 2:{
				Value = Info->ImageIndex;
			}break;
			case 3:{
				Value = Info->FinalValue;
			}break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadDirBtnClick(TObject *Sender)
{
	DEBUG_APP(INFO_DEBUG,"LoadDirBtnClick()");
	String StartDir = Config->GetString("StartSearchDir");
	String Dir;
	if(Dialogs::SelectDirectory(GUITxt->GetString("SelectDirectoryDlg_Title"), StartDir, Dir)){
		Config->SetString("StartSearchDir",Dir);
		Config->SaveToXML(ConfigFileName);
		String SearchTxt = Dir+(String)"\\*.*";
		TSearchRec SR;
		TStringList *List = new TStringList();
		int Attr = faAnyFile|faNormal;
		if(FindFirst(SearchTxt,faAnyFile,SR) == 0){
			do{
				if(SR.Attr & Attr){
					List->Add(Dir+(String)"\\"+SR.Name);
				}
			}while(FindNext(SR) == 0);
			ReverseMainViewport(true);
			AddFiles(List);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadFileBtnClick(TObject *Sender)
{
	DEBUG_APP(INFO_DEBUG,"LoadFileBtnClick()");
	String Dir = Config->GetString("StartSearchDir");
	FileOpenDialog->Title = GUITxt->GetString("SelectFileDlg_Title");
	FileOpenDialog->InitialDir = Dir;
	if(Config->GetBool("AcceptOnlyExtension")){
		String Ext = Config->GetString("AcceptedExtension");
		String Filter = "Files "+Ext+(String)"|*.";
		Ext = ReplaceStr(Ext,";",",");
		Ext = ReplaceStr(Ext,",",";*.");
		FileOpenDialog->Filter = Filter + Ext;
	}
	if(FileOpenDialog->Execute()){
		if(FileOpenDialog->Files->Count>0){
			Dir = ExtractFilePath(FileOpenDialog->Files->Strings[0]);
			Config->SetString("StartSearchDir",Dir);
			Config->SaveToXML(ConfigFileName);
			ReverseMainViewport(true);
			TStringList *List = new TStringList();
			for(int a=0;a<FileOpenDialog->Files->Count;a++)
				List->Add(FileOpenDialog->Files->Strings[a]);
			AddFiles(List);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CreditsBtnClick(TObject *Sender)
{
	DEBUG_APP(INFO_DEBUG,"CreditsBtnClick()");
	CreditsForm->AppVersionLabel->Text = "WebRenamer ver. "+IntToStr(APP_VERSION)+(String)"."+IntToStr(APP_SUBVERSION);
	CreditsForm->ShowModal();
//	MyShowDialog("Title","Message test\r\nOne line\r\nSecond line of text with information",TMsgDlgType::mtError,DIALOG_OK_ABORT,TMsgDlgBtn());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TestSelectCandidate(TObject *Sender, String ShowName, String ShowID){
	TForm *F = (TForm*)Sender;
	F->ModalResult = mrOk;
    Grabber->QueryShowDetail(ShowName, ShowID, 1, 3);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ConfigBtnClick(TObject *Sender)
{
	int Count;
	int a,b;
	String Txt;
	TInfoGrabber *Grab = Grabber->Clone();
	DEBUG_APP(INFO_DEBUG,"ConfigBtnClick(): entering configuration.... ***************************");
	String CFile = AppDirectory+"\\"+CONFIGURATION_FILE;
	for(a=0;a<Grabber->GetNumInfoSource();a++){
		DEBUG_APP(TOTAL_DEBUG,"Grabber: source "+IntToStr(a+1)+(String)" -> "+QUOTED(Grabber->GetSourceByIndex(a)));
	}
	Conf_Dialog->LoadConfiguration(Config);
	if(Conf_Dialog->ShowModal() == mrOk){
		Conf_Dialog->SaveConfiguration(Config);
		Config->SaveToXML(CFile);
		CFile = AppDirectory+"\\Grabber.xml";
		Grabber->SaveToXML(CFile);
		ApplyLanguage();
	}
	else{
		Grabber = Grab;
		Conf_Dialog->Grabber = Grabber;
	}
	for(a=0;a<Grabber->GetNumInfoSource();a++){
		DEBUG_APP(TOTAL_DEBUG,"Grabber: source "+IntToStr(a+1)+(String)" -> "+QUOTED(Grabber->GetSourceByIndex(a)));
	}	
   	DEBUG_APP(TOTAL_DEBUG,"Exiting configuration.... ***************************");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ExitBtnClick(TObject *Sender)
{
	DEBUG_APP(INFO_DEBUG,"ExitBtnClick()");
	if(Config->GetBool("RememeberLastMode")){
		Config->SetInt("LastMode",ModeIcon->Tag);
		Config->SaveToXML(ConfigFileName);
	}
	if(Conf_Dialog->HistoryFrame->History->GetNumOperation(Conf_Dialog->HistoryFrame->History->GetNumRecord()-1) == 0)
        Conf_Dialog->HistoryFrame->History->DeleteRecord(Conf_Dialog->HistoryFrame->History->GetNumRecord()-1);
	String CFile = AppDirectory+"\\Grabber.xml";
	Grabber->SaveToXML(CFile);
	Conf_Dialog->HistoryFrame->History->SaveToXML(AppDirectory+"\\History.xml");
	Application->Terminate();
}
//---------------------------------------------------------------------------
void TForm1::SetMainRectangle(int Mode){
//	DEBUG_APP(INFO_DEBUG,"SetMainRectangle()");
	ModeIcon->Tag = Mode;
	ModeIcon->Bitmap->LoadFromStream((Mode != TV_MODE)?FilmIcon:TVIcon);
	MainRectangle->Fill->Gradient->Assign((Mode != TV_MODE)?FilmGradient:ShowGradient);
	MainRectangleGradientAnimation->StartValue->Assign((Mode != TV_MODE)?FilmGradient:ShowGradient);
	MainRectangleGradientAnimation->StopValue->Assign((Mode != TV_MODE)?ShowGradient:FilmGradient);
	ModeLabel->Text = GUITxt->GetString((Mode == TV_MODE)?"ModeLabel_Show":"ModeLabel_Film");
	StatusBarModeIcon->ImageIndex = (Mode == TV_MODE)?1:0;
	StatusBarLabel->Text = ModeLabel->Text;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ManageCandidateFound(String Searched, int SearchID, TList *Candidate){
	DEBUG_APP(INFO_DEBUG,"ManageCandidateFound()");
	DEBUG_APP(TOTAL_DEBUG,"Search: "+QUOTE_STRING(Searched)+(String)" - ID: "+
				IntToStr(SearchID)+(String)" - Candidate: "+IntToStr(Candidate->Count));
	int a;
	Candidate_Information *Info;
	MainGridRowInfo *Data;
	bool FoundMovie = false;
	if(ModeIcon->Tag == FILM_MODE){
		TDate DateTmp;
		int Year = 0;
		for(a=0;a<MainGridRows->Count;a++){
			Data = (MainGridRowInfo*)MainGridRows->Items[a];
			if(Data->SearchID == SearchID){
				Year = Data->SuggestedYear;
				break;
			}
		}
		for(a=0;a<Candidate->Count;a++){
			Info = (Candidate_Information*)Candidate->Items[0];
			if(Info->Release != ""){
				if(Info->Release.LowerCase() != "null"){
					DateTmp = ISO8601ToDate(Info->Release+(String)"T00:00:00");
					if(YearOf(DateTmp) == Year){
						FoundMovie = true;
						MovieSelectCandidate(NULL, Info->Name, Info->ID, SearchID, Info->Release);
						break;
					}
				}
			}
		}
	}
	if(FoundMovie == false){
		if(Candidate->Count > 1){
			CandidateForm->Frame->Source = Grabber->LastSourceUsed;
			if(ModeIcon->Tag == FILM_MODE)
				CandidateForm->Frame->NoPhotoImage = new TResourceStream((int)HInstance,"NoPoster_Film",RT_RCDATA);
			else
				CandidateForm->Frame->NoPhotoImage = new TResourceStream((int)HInstance,"NoPoster_TV",RT_RCDATA);
			DEBUG_APP(TOTAL_DEBUG,"WorkMode: "+IntToStr(ModeIcon->Tag));
			CandidateForm->Frame->OnRefuseCandidate = UserRefuseCandidate;
			if(ModeIcon->Tag == TV_MODE){
				CandidateForm->Frame->OnSelectCandidate = ShowSelectCandidate;
				CandidateForm->TVShowInfo = true;
			}
			else{
				CandidateForm->Frame->OnSelectMovie = MovieSelectCandidate;
				CandidateForm->TVShowInfo = false;
			}
			CandidateForm->ManageCandidateInfo(Searched, SearchID,Candidate);
			//
			if(CandidateForm->ModalResult == mrOk){
				for(int b=0;b<MainGridRows->Count;b++){
					Data = (MainGridRowInfo*)MainGridRows->Items[b];
					if(Data->SearchID == SearchID){
						Data->ImageIndex = WAIT_ICON;
						StatusColumn->UpdateCell(b);
						break;
					}
				}
			}
			//
		}
		else{
			if(Candidate->Count == 1){
				Info = (Candidate_Information*)Candidate->Items[0];
				if(ModeIcon->Tag == TV_MODE)
					ShowSelectCandidate(NULL,Info->Name,Info->ID,SearchID);
				else{
					MovieSelectCandidate(NULL, Info->Name, Info->ID, SearchID, Info->Release);
				}
			}
			else{
				
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MovieSelectCandidate(TObject *Sender, String Candidate, String ID, int SearchID, String Release){
	DEBUG_APP(INFO_DEBUG,"MovieSelectCandidate()");
	DEBUG_APP(TOTAL_DEBUG,"Candidate: "+QUOTE_STRING(Candidate)+(String)" - ID: "+
						QUOTE_STRING(ID)+" - SearchID: "+IntToStr(SearchID));
	int a;
	String Format = "<<Moviename>> (<<year>>)";
	String Result;
	int ImageIndex;
	TDateTime ReleaseDate;
	MainGridRowInfo *Info;
	MovieNamedetails Details;
	Details.Title = Candidate;
	if(Release != ""){
		if(Release.LowerCase() != "null"){
			ReleaseDate = ISO8601ToDate(Release+(String)"T00:00:00");
			Details.Year = YearOf(ReleaseDate);
		}
	}
	a = Config->GetInt("MovieOutFormatIndex");
	if(a != STRING_INVALID_NAME){
		Result = Config->GetString("MovieOutFormat_"+IntToStr(a));
		if(Result != "")
			Format = Result;
	}
	ImageIndex = -1;
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->SearchID == SearchID){
            Details.Disc = Info->DiscNumber;
			Result = Translator->CreateMovieName(Format,Details);
			Result += ExtractFileExt(Info->SourceFile);
			Info->FinalValue = Result;
			Info->ID = "0";
			FinalNameColumn->UpdateCell(a);
			if(Config->GetBool("AutoRenameFile")){
				RenameRow(a);
			}
			else
				Info->ImageIndex = WAIT_ICON;
			StatusColumn->UpdateCell(a);
			break;
		}
	}
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->ID == ""){
			Grabber->QueryMovieCandidate(Info->SearchName, Info->SearchID);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ShowSelectCandidate(TObject *Sender, String Candidate, String ID, int SearchID){
	DEBUG_APP(INFO_DEBUG,"ShowSelectCandidate()");
	DEBUG_APP(TOTAL_DEBUG,"Candidate: "+QUOTE_STRING(Candidate)+(String)" - ID: "+
						QUOTE_STRING(ID)+" - SearchID: "+IntToStr(SearchID));
	int a;
	MainGridRowInfo *Info;
	String OriginalSearch;
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->SearchID == SearchID){
			Info->ID = ID;
			OriginalSearch = Info->SearchName;
			Grabber->QueryShowDetail(Candidate, ID, Info->SuggestSeason, Info->SuggestEpisode,SearchID);
			break;
		}
	}
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->SearchName == OriginalSearch){
			if(Info->ID == ""){
				Info->ID = ID;
				Grabber->QueryShowDetail(Candidate, ID, Info->SuggestSeason, Info->SuggestEpisode,Info->SearchID);
			}
		}
	}
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->ID == ""){
			Grabber->QueryShowCandidate(Info->SearchName, Info->SearchID);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ShowFoundData(String ShowName, int Season, int Episode, int SearchID, ShowResultDetails Details){
	DEBUG_APP(INFO_DEBUG,"ShowFoundData()");
	DEBUG_APP(TOTAL_DEBUG,"ShowName: "+QUOTE_STRING(ShowName)+(String)" - Search: "+IntToStr(SearchID)+
				(String)" - Ep.: "+IntToStr(Season*100+Episode)+(String)" - Title: "+QUOTE_STRING(Details.EpisodeTitle));
	TVShowNameDetails TVShow;
	int a;
	int ImageIndex;
	String Result;
	String Format = "<<ShowName>> - <<season2>>x<<episode2>> - <<EpisodeTitle>>";
	String OutName;
	MainGridRowInfo *Info;
	TVShow.ShowName = ShowName;
	TVShow.Season = Season;
	TVShow.Episode = Episode;
	TVShow.EpisodeTitle = Details.EpisodeTitle;
	a = Config->GetInt("ShowOutFormatIndex");
	if(a != STRING_INVALID_NAME){
		Result = Config->GetString("ShowOutFormat_"+IntToStr(a));
		if(Result != "")
			Format = Result;
	}
	Result = Translator->CreateTVShowName(Format,TVShow);
	ImageIndex = -1;
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->SearchID == SearchID){
			Result += ExtractFileExt(Info->SourceFile);
			Info->FinalValue = Result;
			Info->FindName = ShowName;
			Info->FindTitle = Details.EpisodeTitle;
			FinalNameColumn->UpdateCell(a);
			if(Config->GetBool("AutoRenameFile")){
				RenameRow(a);
			}
			else
				Info->ImageIndex = WAIT_ICON;
			StatusColumn->UpdateCell(a);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void TForm1::RenameRow(int Row){
	if(Row > -1 && Row < MainGridRows->Count){
		MainGridRowInfo *Info = (MainGridRowInfo*)MainGridRows->Items[Row];
		String Result = ExtractFilePath(Info->SourceFile)+Info->FinalValue;
		Conf_Dialog->HistoryFrame->History->AddOperation(Conf_Dialog->HistoryFrame->History->GetNumRecord()-1,
					ExtractFileName(Info->SourceFile),Info->FinalValue);
		if(FileExists(Result)){
			Info->ImageIndex = ATTENTION_ICON;
		}
		else{
			if(RenameFile(Info->SourceFile, Result)){
				DEBUG_APP(TOTAL_DEBUG,"Correct renamed "+QUOTE_STRING(Info->FinalValue));
				Info->ImageIndex = OK_ICON;
				Info->ActualValue = Info->FinalValue;
			}
			else{
				DEBUG_APP(ERR_DEBUG,"Error renaming "+QUOTE_STRING(Info->FinalValue));
				Info->ImageIndex = ERROR_ICON;
			}
		}
		FinalNameColumn->UpdateCell(Row);
		StatusColumn->UpdateCell(Row);
		TWebSource *Src = Grabber->LastSourceUsed;
		if(Src){
			if(Src->Name.Pos("TVDB")>0)
				ShowCopyrightPanel(THE_TVDB_SOURCE);
			else
				ShowCopyrightPanel(THE_MOVIEDB_SOURCE);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UndoRename(TObject *Sender){
	if(MainGrid->Selected > -1){
		UndoRenameRow(MainGrid->Selected);
	}
}
//---------------------------------------------------------------------------
void TForm1::UndoRenameRow(int Row){
	if(Row > -1 && Row < MainGridRows->Count){
		MainGridRowInfo *Info = (MainGridRowInfo*)MainGridRows->Items[Row];
		String Result = ExtractFilePath(Info->SourceFile)+Info->FinalValue;
		RenameFile(Result, Info->SourceFile);
		Info->ImageIndex = UNDO_ICON;
		Info->ActualValue = ExtractFileName(Info->SourceFile);
		StatusColumn->UpdateCell(Row);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UndoSelected(TObject *Sender){
	MainGridRowInfo *Info;	
	for(int a=0;a<MainGridRows->Count;a++){	
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->Selected)
			UndoRenameRow(a);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UndoAll(TObject *Sender){
	for(int a=0;a<MainGridRows->Count;a++){	
		UndoRenameRow(a);
	}	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Rename(TObject *Sender){
	if(MainGrid->Selected > -1){
		RenameRow(MainGrid->Selected);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RenameSelected(TObject *Sender){
	MainGridRowInfo *Info;
	for(int a=0;a<MainGridRows->Count;a++){	
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->Selected)
			RenameRow(a);
	}	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RenameAll(TObject *Sender){
	for(int a=0;a<MainGridRows->Count;a++){	
		RenameRow(a);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainGridSetValue(TObject* Sender, const int ACol, const int ARow, const TValue &Value){
	bool AutoRename = Config->GetBool("AutoRenameFile");
	TValue Val = Value;
	switch(ACol){
		case 1:{
			if(AutoRename == false){
				MainGridRowInfo *Info = (MainGridRowInfo*)MainGridRows->Items[ARow];
				Info->Selected = Val.AsBoolean();
			}
		}break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ConnectionError(TNetHTTPClient *Client,TNetHTTPRequest *Request,
						CommandList *Cmd, int CommandIndex, int ErrCode, String ErrDesc){
	DEBUG_APP(INFO_DEBUG,"ConnectionError()");
	DEBUG_APP(TOTAL_DEBUG,"CommandList: "+QUOTED(Cmd)+(String)" - CmdIndex: "+IntToStr(CommandIndex)+
					(String)" - Err: 0x"+IntToHex(ErrCode)+(String)" - Desc: "+QUOTE_STRING(ErrDesc));
	String Msg = GUITxt->GetString("ConnErrorCode")+IntToHex(ErrCode)+(String)"\r\n";
	Msg = Msg + ErrDesc;
//	int Res = TDialogServiceSync::MessageDialog(Msg,TMsgDlgType::mtError,DIALOG_OK,TMsgDlgBtn(),THelpContext());
	int Res = MyShowDialog("",Msg,TMsgDlgType::mtError,DIALOG_OK,TMsgDlgBtn(),GUITxt);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MainGridPopupPopup(TObject *Sender)
{
	bool AutoRename = Config->GetBool("AutoRenameFile");
	Rename_Popup->Enabled = !AutoRename;
	Undo_Selected->Enabled = !AutoRename;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ManualRenameClick(TObject *Sender)
{
	MainGridRowInfo *Info;
	if(ModeIcon->Tag == TV_MODE){
		if(MainGrid->Selected > -1){
			Info = (MainGridRowInfo*)MainGridRows->Items[MainGrid->Selected];
			//TRenameShowForm *RenameForm = new TRenameShowForm(this);
			Episode_Info Episode;
			Episode = Translator->TranslateEpisode(ExtractFileName(Info->SourceFile));
			//RenameForm->CreateGUITxt(GUITxt);
			//RenameForm->ApplyLanguage(GUITxt);
			RenameForm->ShowEdit->Text = Info->FindName;
			RenameForm->TitleEdit->Text = Info->FindTitle;
			RenameForm->SeasonSpin->Value = Episode.Order.Season;
			RenameForm->EpisodeSpin->Value = Episode.Order.Episode;
			RenameForm->FormatComboBox->Items =Conf_Dialog->OutputNameFrame->FormatComboBox->Items;
			RenameForm->FormatComboBox->ItemIndex =Conf_Dialog->OutputNameFrame->FormatComboBox->ItemIndex;
			if(RenameForm->ShowModal() == mrOk){
				Info->FinalValue = RenameForm->OutputEdit->Text+ExtractFileExt(Info->SourceFile);
				Info->FindName = RenameForm->ShowEdit->Text;
				Info->FindTitle = RenameForm->TitleEdit->Text;
				FinalNameColumn->UpdateCell(MainGrid->Selected);
				RenameRow(MainGrid->Selected);
				Info->ImageIndex = OK_ICON;
				StatusColumn->UpdateCell(MainGrid->Selected);
			}
		}
	}
	else{
		if(MainGrid->Selected > -1){
			Info = (MainGridRowInfo*)MainGridRows->Items[MainGrid->Selected];
			//TRenameMovieForm *RenameForm = new TRenameMovieForm(this);
			Movie_Info MovieInfo;
			MovieInfo = Translator->TranslateMovie(ExtractFileName(Info->SourceFile));
			//RenameForm->CreateGUITxt(GUITxt);
			//RenameForm->ApplyLanguage(GUITxt);
			RenameForm2->MovieEdit->Text = Info->SearchName;
			RenameForm2->YearBox->Value = MovieInfo.Year;
            RenameForm2->DiscBox->Value = MovieInfo.Disc;
			RenameForm2->FormatComboBox->Items =Conf_Dialog->OutputNameFrame->MovieFormatComboBox->Items;
			RenameForm2->FormatComboBox->ItemIndex =Conf_Dialog->OutputNameFrame->MovieFormatComboBox->ItemIndex;
			if(RenameForm2->ShowModal() == mrOk){
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UserRefuseCandidate(TObject *Sender, String Candidate, int SearchID){
	int a;
	if(ModeIcon->Tag == FILM_MODE){//Movie...
		Grabber->QueryMovieCandidate(Candidate, SearchID);
	}
	else{// TV SHOW...
		Grabber->QueryShowCandidate(Candidate, SearchID);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CompleteSource(String Searched,int ID){
	String Mess = GUITxt->GetString("NoSourceMess")+QUOTE_STRING(Searched);
	int a;
	int b;
	int ImageIndex;
	MainGridRowInfo *Info;
	b = 0;
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->ID == "" && Info->SearchID != ID){
			a = -1;
			break;
		}
	}
	if(a>-1)
		b = MyShowDialog("",Mess,TMsgDlgType::mtError,mbOKCancel,TMsgDlgBtn(),GUITxt);
	else
		b = MyShowDialog("",Mess,TMsgDlgType::mtError,DIALOG_OK,TMsgDlgBtn(),GUITxt);
	if(b == mrCancel){
		Mess = GUITxt->GetString("StopScan");
		if(a>-1){
			b = MyShowDialog("",Mess,TMsgDlgType::mtConfirmation,mbYesNo,TMsgDlgBtn(),GUITxt);
			if(b != mrYes)
				b = mrOk;
		}
	}
	for(a=0;a<MainGridRows->Count;a++){
		Info = (MainGridRowInfo*)MainGridRows->Items[a];
		if(Info->SearchID == ID){
			Info->ImageIndex = QUESTION_ICON;
			StatusColumn->UpdateCell(a);
			if(a+1<MainGridRows->Count){
				Info->ID = "123";
				if(b == mrOk){
					if(a + 1 <MainGridRows->Count){
						Info = (MainGridRowInfo*)MainGridRows->Items[a+1];
						if(ModeIcon->Tag == FILM_MODE)
							Grabber->QueryMovieCandidate(Info->SearchName, Info->SearchID);
						else
							Grabber->QueryShowCandidate(Info->SearchName, Info->SearchID);
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ManualSearchClick(TObject *Sender)
{
	MainGridRowInfo *Info = NULL;
	TWebSource *Source;
	if(MainGrid->Selected > -1)
		Info = (MainGridRowInfo*)MainGridRows->Items[MainGrid->Selected];
	if(ModeIcon->Tag == FILM_MODE){//Movie...
		//TMovieSearchForm *SearchForm = new TMovieSearchForm(this);
		//SearchForm2->CreateGUITxt(GUITxt);
		//SearchForm2->ApplyLanguage(GUITxt);
		if(Info){
			SearchForm2->TitleEdit->Text = Info->SearchName;
			SearchForm2->YearSpin->Value = Info->SuggestedYear;
			SearchForm2->DiscSpin->Value = Info->DiscNumber;
			SearchForm2->SourceCombo->Items->Clear();
			for(int a=0;a<Grabber->GetNumInfoSource();a++){
				Source = Grabber->GetSourceByIndex(a);
				if(Source->Type == MOVIE_SOURCE_INFO){
					SearchForm2->SourceCombo->Items->Add(Source->Name);
					SearchForm2->SourceCombo->ListItems[SearchForm2->SourceCombo->Count-1]->Tag = Source->RememberPreferences;
				}
			}
			SearchForm2->SourceCombo->ItemIndex = 0;
			SearchForm2->FormatCombo->Items->Clear();
			SearchForm2->FormatCombo->Items->Text = Conf_Dialog->OutputNameFrame->MovieFormatComboBox->Items->Text;
			SearchForm2->FormatCombo->ItemIndex = Conf_Dialog->OutputNameFrame->MovieFormatComboBox->ItemIndex;
			SearchForm2->Grabber = Grabber;
		}
		if(SearchForm2->ShowModal() == mrOk){
			Info->FinalValue = SearchForm2->ResultValue->Text + ExtractFileExt(Info->SourceFile);
			RenameRow(MainGrid->Selected);
		}
	}
	else{// TV SHOW...
		//TShowSearchForm *SearchForm = new TShowSearchForm(this);
		//SearchForm->CreateGUITxt(GUITxt);
		//SearchForm->ApplyLanguage(GUITxt);
		if(Info){
			SearchForm->TitleEdit->Text = Info->SuggestedShow;
			SearchForm->SeasonSpin->Value = Info->SuggestSeason;
			SearchForm->EpisodeSpin->Value = Info->SuggestEpisode;
			SearchForm->SourceCombo->Items->Clear();
			for(int a=0;a<Grabber->GetNumInfoSource();a++){
				Source = Grabber->GetSourceByIndex(a);
				if(Source->Type == SHOW_SOURCE_INFO){
					SearchForm->SourceCombo->Items->Add(Source->Name);
					SearchForm->SourceCombo->ListItems[SearchForm->SourceCombo->Count-1]->Tag =	Source->RememberPreferences;
				}
			}
			SearchForm->SourceCombo->ItemIndex = 0;
			SearchForm->FormatCombo->Items->Clear();
			SearchForm->FormatCombo->Items->Text = Conf_Dialog->OutputNameFrame->FormatComboBox->Items->Text;
			SearchForm->FormatCombo->ItemIndex = Conf_Dialog->OutputNameFrame->FormatComboBox->ItemIndex;
			SearchForm->Grabber = Grabber;
		}
		if(SearchForm->ShowModal() == mrOk){
			Info->FinalValue = SearchForm->ResultValue->Text + ExtractFileExt(Info->SourceFile);
			RenameRow(MainGrid->Selected);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ColumnResize(TObject *Sender){
	TColumn *Column = (TColumn*)Sender;
	Column->Width = Column->Tag;
}
//---------------------------------------------------------------------------
void TForm1::ShowCopyrightPanel(int Type){
	if(CopyrightAnimation->Running == false){
		bool StartMe = false;
		TResourceStream *Res;
		switch(Type){
			case THE_TVDB_SOURCE:{
				StartMe = true;
				CopyrightLabel->Text = "TV information and images are provided by TheTVDB.com, but we are not endorsed or certified by TheTVDB.com or its affiliates.";
				Res = new TResourceStream((int)HInstance,"TVDB",RT_RCDATA);
			}break;
			case THE_MOVIEDB_SOURCE:{
				StartMe = true;
				CopyrightLabel->Text = "This product uses the TMDb API but is not endorsed or certified by TMDb.";
				Res = new TResourceStream((int)HInstance,"MovieDB",RT_RCDATA);
			}break;
		}
		CopyrightImage->Bitmap->LoadFromStream(Res);
		BottomLayout->Height = 0;
		BottomLayout->Visible = true;
		CopyrightAnimation->Enabled = false;
		CopyrightAnimation->Delay = 0;
		CopyrightAnimation->StartValue = 0;
		CopyrightAnimation->StopValue = 100;
		if(StartMe)
			CopyrightAnimation->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CopyrightAnimationFinish(TObject *Sender)
{
	if(BottomLayout->Height > 5){
		CopyrightAnimation->Enabled = false;
		CopyrightAnimation->Delay = 3;
		CopyrightAnimation->StartValue = 100;
		CopyrightAnimation->StopValue = 0;
		CopyrightAnimation->Enabled = true;
	}
	else{
		BottomLayout->Visible = false;
	}
}
//---------------------------------------------------------------------------
void TForm1::SaveLanguage(){
	String Path = AppDirectory+"\\Language";
	String Lng = GUITxt->GetString("Short_Language");
	if(TDirectory::Exists(Path) == false)
		TDirectory::CreateDirectory(Path);
	GUITxt->SetString("Short_Language","en");
	GUITxt->SaveToXML(Path+"\\Default.lng");
	GUITxt->SetString("Short_Language",Lng);	
}
//---------------------------------------------------------------------------
