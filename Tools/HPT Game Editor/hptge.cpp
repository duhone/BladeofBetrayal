//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("hptge.res");
USEFORM("Unit1.cpp", Form1);
USE("zlib.h", File);
USEFORM("C:\PROGRAM FILES\BORLAND\CBUILDER5\OBJREPOS\OKCANCL1.cpp", OKBottomDlg);
USEFORM("fontscrollform.cpp", fontscroll); /* TFrame: File Type */
USEFORM("optionsdialog.cpp", DialogOptions);
USEUNIT("PNGChunk.cpp");
USEUNIT("HTFBitmap.cpp");
USEUNIT("HTFHeader.cpp");
USEUNIT("HTFPng.cpp");
USELIB("zlib_bor.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TDialogOptions), &DialogOptions);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------






