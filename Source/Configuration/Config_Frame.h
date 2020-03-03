//---------------------------------------------------------------------------

#ifndef BasicConfigFrameH
#define BasicConfigFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.DialogService.Sync.hpp>
#include "Project_Const.h"
//---------------------------------------------------------------------------
class TConfig_Frame : public TFrame
{
__published:	// IDE-managed Components
private:	// User declarations
	TTreeViewItem *FTreeNode;
	TNameValue *FConfig;
	TNameValue *FLang;
	
	void SetTreeNode(TTreeViewItem *Item);
	TTreeViewItem *GetTreeNode();
	void SetConf(TNameValue *Conf);
	TNameValue *GetConf();
	void SetLang(TNameValue *Lang);
	TNameValue *GetLang();
	
public:		// User declarations
	__fastcall TConfig_Frame(TComponent* Owner);
	virtual void CreateGUITxt(TNameValue *GUITxt);
	virtual void ApplyLanguage(TNameValue *Src);
	virtual void LoadConfiguration(TNameValue *Conf);
	virtual void SaveConfiguration(TNameValue *Conf);
	virtual void CreateConfiguration(TNameValue *Conf);
	void ApplyLanguage(TNameValue *Src, String Prefix, TStringList *Components);
	virtual void ResizeComponents();
	TComponent *SearchComponent(String Name);

	__property TTreeViewItem *TreeNode = {read = GetTreeNode, write = SetTreeNode};
	__property TNameValue *Config = {read = GetConf, write = SetConf};
	__property TNameValue *Language = {read = GetLang, write = SetLang};	
};
//---------------------------------------------------------------------------
extern PACKAGE TConfig_Frame *ConfigFrame;
//---------------------------------------------------------------------------
#endif
