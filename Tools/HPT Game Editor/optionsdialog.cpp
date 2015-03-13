//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "optionsdialog.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TDialogOptions *DialogOptions;
//--------------------------------------------------------------------- 
__fastcall TDialogOptions::TDialogOptions(TComponent* AOwner)
	: TOKBottomDlg(AOwner)
{
        autosavetime = 0;
        AnsiString temp;

        temp.sprintf("1");
        AutoSaveTimes->Items->Add(temp);

        temp.sprintf("5");
        AutoSaveTimes->Items->Add(temp);

        temp.sprintf("10");
        AutoSaveTimes->Items->Add(temp);

        temp.sprintf("15");
        AutoSaveTimes->Items->Add(temp);

        temp.sprintf("20");
        AutoSaveTimes->Items->Add(temp);

        AutoSaveTimes->ItemIndex = 1;

}
//--------------------------------------------------------------------- 
void __fastcall TDialogOptions::HelpBtnClick(TObject *Sender)
{
	Application->HelpContext(HelpContext);
}
//---------------------------------------------------------------------
void __fastcall TDialogOptions::AutoSaveTimesChange(TObject *Sender)
{
        if(AutoSaveTimes->ItemIndex == 0) autosavetime =1;
        else autosavetime = AutoSaveTimes->ItemIndex * 5;
}
//---------------------------------------------------------------------------


