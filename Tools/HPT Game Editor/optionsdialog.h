//----------------------------------------------------------------------------
#ifndef optionsdialogH
#define optionsdialogH
//----------------------------------------------------------------------------
#include <OKCANCL1.h>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
//----------------------------------------------------------------------------
class TDialogOptions : public TOKBottomDlg
{
__published:
	TButton *HelpBtn;
        TCheckBox *saveproject;
        TComboBox *AutoSaveTimes;
        TLabel *Label1;
	void __fastcall HelpBtnClick(TObject *Sender);
        void __fastcall AutoSaveTimesChange(TObject *Sender);
private:
public:
        int autosavetime;
	virtual __fastcall TDialogOptions(TComponent* AOwner);
        
};
//----------------------------------------------------------------------------
extern PACKAGE TDialogOptions *DialogOptions;
//----------------------------------------------------------------------------
#endif    
