//---------------------------------------------------------------------------


#ifndef fontscrollformH
#define fontscrollformH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfontscroll : public TFrame
{
__published:	// IDE-managed Components
        TImage *Image1;
private:	// User declarations
public:		// User declarations
        __fastcall Tfontscroll(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfontscroll *fontscroll;
//---------------------------------------------------------------------------
#endif
