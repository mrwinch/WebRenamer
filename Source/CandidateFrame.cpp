//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "CandidateFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TCandidateListFrame *CandidateListFrame;
//---------------------------------------------------------------------------
#define UNIT_ID                                     "CDD_FR"
#define BUILD_ID(Name)                              UNIT_ID+(String)"_"+Name
#define DEFAULT_HEIGHT                              100
//---------------------------------------------------------------------------
bool IsEmpty(String Value){
	String Tmp;
	if(Value == "")
		return true;
	Tmp = Value.LowerCase();
	if(Tmp == "null")
		return true;
	return false;
}
//---------------------------------------------------------------------------
int __fastcall CompareCandidate(void *Item2, void *Item1){
	Candidate_Information *Info1, *Info2;
	Info1 = (Candidate_Information*)Item1;
	Info2 = (Candidate_Information*)Item2;
	if(Info1->Poster != ""){
		if(Info2->Poster == "")
		//if(IsEmpty(Info2->Poster))
			return 1;
		else{
			if(Info1->Summary != ""){
				if(Info2->Summary == "")
					return 1;
				else
					return 0;
			}
			else{
				if(Info2->Summary == "")
					return 0;
				else
					return -1;
			}
		}
	}
	else{
		if(Info2->Poster != "")
			return -1;
		else{
			if(Info1->Summary != ""){
				if(Info2->Summary == "")
					return 1;
				else
					return 0;
			}
			else{
				if(Info2->Summary == "")
					return 0;
				else
					return -1;
			}
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
__fastcall TCandidateFrameBox::TCandidateFrameBox(TComponent *Owner):TListBoxItem(Owner){
	ImageLayout = new TLayout(this);
	ImageLayout->Parent = this;
	ImageLayout->Width = 66;
	ImageLayout->Align = TAlignLayout::Left;
	Poster = new TImage(ImageLayout);
	Poster->Parent = ImageLayout;
	Poster->Align = TAlignLayout::Client;
	Poster->Margins->Left = 3;
	Poster->Margins->Right = 3;
	Poster->Margins->Top = 3;
	Poster->Margins->Bottom = 3;
	Poster->OnDblClick = ImgDblClick;
	Poster->OnMouseEnter = ImageEnter;
	Poster->OnMouseLeave = ImageLeave;
	MainLayout = new TLayout(this);
	MainLayout->Parent = this;
	MainLayout->Align = TAlignLayout::Client;
	TopLayout = new TLayout(MainLayout);
	TopLayout->Parent = MainLayout;
	TopLayout->Align = TAlignLayout::Top;
	TopLayout->Height = 25;
	TitleLabel = new TLabel(TopLayout);
	TitleLabel->Parent = TopLayout;
	TitleLabel->Align = TAlignLayout::Top;
	TitleLabel->Height = 24;
	CenterLayout = new TLayout(MainLayout);
	CenterLayout->Parent = MainLayout;
	CenterLayout->Height = 14;
	CenterLayout->Align = TAlignLayout::Top;
	BottomLayout = new TLayout(MainLayout);
	BottomLayout->Parent = MainLayout;
	BottomLayout->Align = TAlignLayout::Client;

	IDLabel = new TLabel(CenterLayout);
	IDLabel->Parent = CenterLayout;
	IDLabel->Align = TAlignLayout::Left;
	AerialLabel = new TLabel(CenterLayout);
	AerialLabel->Parent = CenterLayout;
	AerialLabel->Align = TAlignLayout::Left;
	SummaryLabel = new TLabel(BottomLayout);
	SummaryLabel->Parent = BottomLayout;
	SummaryLabel->Align = TAlignLayout::Client;
	SummaryLabel->TextSettings->Trimming = TTextTrimming::Word;

	OnResize = BoxResized;
	Height = DEFAULT_HEIGHT;
	PosterData = new TMemoryStream();
	Client = new TNetHTTPClient(Owner);
	Client->Asynchronous = true;
	Client->OnRequestCompleted =  PosterClientRequestCompleted;
	FInfo = NULL;
}
//---------------------------------------------------------------------------
__fastcall TCandidateFrameBox::~TCandidateFrameBox(){
}
//---------------------------------------------------------------------------
void __fastcall TCandidateFrameBox::BoxResized(TObject *Sender){
	if(BottomLayout)
		BottomLayout->Height = Height-(CenterLayout->Position->Y+CenterLayout->Height);
}
//---------------------------------------------------------------------------
void TCandidateFrameBox::SetTitle(String Title){
	TitleLabel->Text = Title;
	TitleLabel->ResultingTextSettings->Font->Size = 18;
}
//---------------------------------------------------------------------------
String TCandidateFrameBox::GetTitle(){
	return TitleLabel->Text;
}
//---------------------------------------------------------------------------
void TCandidateFrameBox::SetID(String ID){
	IDLabel->Text = ID;
	IDLabel->ResultingTextSettings->Font->Size = 9;
}
//---------------------------------------------------------------------------
String TCandidateFrameBox::GetID(){
	return IDLabel->Text;
}
//---------------------------------------------------------------------------
void TCandidateFrameBox::SetAired(String ID){
	AerialLabel->Text = ID;
	AerialLabel->ResultingTextSettings->Font->Size = 9;
}
//---------------------------------------------------------------------------
String TCandidateFrameBox::GetAired(){
	return AerialLabel->Text;
}
//---------------------------------------------------------------------------
void TCandidateFrameBox::SetSum(String ID){
	SummaryLabel->AutoSize = false;
	SummaryLabel->Text = ID;
	SummaryLabel->ResultingTextSettings->Font->Family = "Arial";
	SummaryLabel->ResultingTextSettings->Font->Size = 12;
	SummaryLabel->ResultingTextSettings->VertAlign = TTextAlign::Leading;
}
//---------------------------------------------------------------------------
String TCandidateFrameBox::GetSum(){
	return SummaryLabel->Text;
}
//---------------------------------------------------------------------------
void __fastcall TCandidateFrameBox::PosterClientRequestCompleted(TObject * const Sender, _di_IHTTPResponse AResponse)
{
	Poster->Bitmap->LoadFromStream(PosterData);
}
//---------------------------------------------------------------------------
void TCandidateFrameBox::DefaultPhoto(TStream *Stream){
	Poster->Bitmap->LoadFromStream(Stream);
	Poster->OnMouseEnter = NULL;
	Poster->OnMouseLeave = NULL;
}
//---------------------------------------------------------------------------
void TCandidateFrameBox::SetInfo(Candidate_Information *Info){
	FInfo = Info;
}
//---------------------------------------------------------------------------
Candidate_Information *TCandidateFrameBox::GetInfo(){
	return FInfo;
}
//---------------------------------------------------------------------------
void __fastcall TCandidateFrameBox::ImgDblClick(TObject *Sender){
	//((TListBox*)Owner)->OnDblClick(Sender);
	(((TCandidateListFrame*)Owner->Owner))->CandidateListBoxDblClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TCandidateFrameBox::ImageLeave(TObject *Sender){
	Height = DEFAULT_HEIGHT;
	ImageLayout->Width = 66;
}
//---------------------------------------------------------------------------
void __fastcall TCandidateFrameBox::ImageEnter(TObject *Sender){
	Height = DEFAULT_HEIGHT * 2;
	ImageLayout->Width = 132;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TCandidateListFrame::TCandidateListFrame(TComponent* Owner)
	: TFrame(Owner)
{
/*	IDLabelValue = "ID: ";
	AerialLabelValue = "Aired: ";
	SummaryLabelValue = "Summary:";
	SearchTitle = "Search for: ";*/
	NoPhotoImage = NULL;
	OnSelectCandidate = NULL;
    OnSelectMovie = NULL;
	OnRefuseCandidate = NULL;
	S_ID = -1;
	Source = NULL;
	FInfo = true;	
}
//---------------------------------------------------------------------------
void __fastcall TCandidateListFrame::ManageCandidateInfo(String Candidate, int SearchID, TList *CandidateList){
	Candidate_Information *Info;
	int a;
	String Txt;
	TCandidateFrameBox *BoxItem;
	TDate Aerial;
	CandidateList->Sort(CompareCandidate);
	CandidateListBox->Clear();
	for(a=0;a<CandidateList->Count;a++){
		Info = (Candidate_Information*)CandidateList->Items[a];
		//Txt = Info->Poster;
		//Txt = "";
		BoxItem = new TCandidateFrameBox(CandidateListBox);
		BoxItem->Parent = CandidateListBox;
		BoxItem->Title = Info->Name;
		BoxItem->ID = IDLabelValue+Info->ID;
		if(FInfo)
			Txt = Info->Aerial;
		else
			Txt = Info->Release;
		if(Txt != ""){
			if(Txt != "null"){
				Aerial = ISO8601ToDate(Txt+(String)"T00:00:00");
				BoxItem->Aired = AerialLabelValue + Aerial.DateString();
			}
			else
				BoxItem->Aired = AerialLabelValue+(String)" - ";
		}
		else
			BoxItem->Aired = AerialLabelValue+Txt;
		BoxItem->Summary = Info->Summary;
		BoxItem->PosterData->Clear();
		if(Info->Poster != ""){
			if(Info->Poster != "null"){
				BoxItem->PosterURL = Info->Poster;
				BoxItem->Client->Get(Info->Poster,BoxItem->PosterData);
			}else{
				if(NoPhotoImage){
					BoxItem->DefaultPhoto(NoPhotoImage);
				}
			}
		}
		else{
			if(NoPhotoImage){
				BoxItem->DefaultPhoto(NoPhotoImage);
			}
        }
		BoxItem->DataInfo = Info;
	}
	if(Form){
		Txt = SearchTitle+Candidate;
		if(Source)
			Txt +=" - Source: "+Source->Name;
		Form->Caption = Txt;
	}
	S_ID = SearchID;
	FCandidate = Candidate;
	/*if(Form)
		Form->ShowModal();*/
}
//---------------------------------------------------------------------------
void __fastcall TCandidateListFrame::CandidateListBoxDblClick(TObject *Sender)
{
	TCandidateFrameBox *Box = NULL;;
	if(CandidateListBox->Selected)
		Box = (TCandidateFrameBox*)CandidateListBox->Selected;
	else{
		Box = (TCandidateFrameBox*)Sender;
		if(Box){
			if(Box->ClassName() != "TCandidateFrameBox")
				Box = NULL;
		}
	}
	if(Box){
		String ID = Box->ID.SubString(IDLabelValue.Length() + 1,Box->ID.Length());
		if(FInfo){
			if(OnSelectCandidate)
				OnSelectCandidate(this, Box->Title, ID, S_ID);
		}
		else{
			if(OnSelectMovie)
				OnSelectMovie(this,Box->Title, ID, S_ID, Box->DataInfo->Release);
		}
		if(Form)
			Form->ModalResult = mrOk;
	}
}
//---------------------------------------------------------------------------
void TCandidateListFrame::CreateGUITxt(TNameValue *Txt){
	if(Txt->ValueExist(BUILD_ID("IDLabelValue")) == false)
		Txt->AddString(BUILD_ID("IDLabelValue"),"ID: ","Text for ID label");
	if(Txt->ValueExist(BUILD_ID("AerialLabelValue")) == false)
		Txt->AddString(BUILD_ID("AerialLabelValue"),"Aired: ","Text for aired label");
	if(Txt->ValueExist(BUILD_ID("ReleaseLabelValue")) == false)
		Txt->AddString(BUILD_ID("ReleaseLabelValue"),"Release: ","Text for release label");
	if(Txt->ValueExist(BUILD_ID("SummaryLabelValue")) == false)
		Txt->AddString(BUILD_ID("SummaryLabelValue"),"Summary: ","Text for summary label");
	if(Txt->ValueExist(BUILD_ID("SearchTitle")) == false)
		Txt->AddString(BUILD_ID("SearchTitle"),"Search for: ","Text for search label");
	if(Txt->ValueExist(BUILD_ID("RefuseButton")) == false)
		Txt->AddString(BUILD_ID("RefuseButton"),"Refuse","Text for refuse label");
}
//---------------------------------------------------------------------------
void TCandidateListFrame::ApplyLanguage(TNameValue *Txt){
	IDLabelValue = Txt->GetString(BUILD_ID("IDLabelValue"));
	if(FInfo)
		AerialLabelValue = Txt->GetString(BUILD_ID("AerialLabelValue"));
	else
		AerialLabelValue = Txt->GetString(BUILD_ID("ReleaseLabelValue"));
	SummaryLabelValue = Txt->GetString(BUILD_ID("SummaryLabelValue"));
	SearchTitle = Txt->GetString(BUILD_ID("SearchTitle"));
	RefuseButton->Text = Txt->GetString(BUILD_ID("RefuseButton"));
}
//---------------------------------------------------------------------------
bool TCandidateListFrame::GetInfo(){
	return FInfo;
}
//---------------------------------------------------------------------------
void TCandidateListFrame::SetInfo(bool Value){
	FInfo = Value;
}
//---------------------------------------------------------------------------
void __fastcall TCandidateListFrame::RefuseButtonClick(TObject *Sender)
{
	if(Form)
		Form->ModalResult = mrIgnore;
	if(OnRefuseCandidate)
		OnRefuseCandidate(this, FCandidate, S_ID);
}
//---------------------------------------------------------------------------
void __fastcall TCandidateListFrame::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(Form){
		if(Form->ModalResult == mrCancel){    //Userclick the close button...
			Form->Close();
			if(OnRefuseCandidate)
				OnRefuseCandidate(this, FCandidate, S_ID);
		}
	}
}
//---------------------------------------------------------------------------



