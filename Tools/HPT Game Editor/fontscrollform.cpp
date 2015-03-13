//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fontscrollform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfontscroll *fontscroll;
//---------------------------------------------------------------------------
__fastcall Tfontscroll::Tfontscroll(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
