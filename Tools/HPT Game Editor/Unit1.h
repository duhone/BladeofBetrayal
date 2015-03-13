//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <vector.h>
#include <list.h>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "optionsdialog.h"
#include "fontscrollform.h"
#include "fontscrollform.h"
#include "htfpng.h"
#include "zlib.h"



//---------------------------------------------------------------------------
/*struct PNGChunk
{
        int Length;
        char Type[5];
        char* data;
        int CRC;
public:
        ~PNGChunk();
}; */

struct HGFHeader
{
public:
        char HGF[3];
        int  version;
        int  number_of_images;
        HGFHeader();



};

struct HPTImageHeader
{
public:
       int width;  //of single frame image
       int height; // of single frame image
       int img_width;
       int img_height;
       int color_key_red;
       int color_key_blue;
       int color_key_green;
       float default_frame_rate;
       bool default_auto_animate;
       int num_frame_sets;
       vector<int> frames_per_set;   //one integer for each frame set
       int image_type;

        HPTImageHeader();
        ~HPTImageHeader();
        SetFramesPerSet(TEdit* arg);
        GetFramesPerSet(TEdit* arg); // 1=bmp  2=png  3=jpg
};

class PNG
{
public:      

       char PNGSignature[8];
       vector<PNGChunk*> PNGChunks;

       char* image_data;

       AnsiString file_name;
       AnsiString full_path_name;
       AnsiString desc;
       HPTImageHeader image_header;

        PNG();
        ~PNG();
        LoadData(FILE* fp);

        int GetPNGWidth();
        

};

class HGFFile
{
public:        

        AnsiString file_name;
        AnsiString full_path_name;

        HGFHeader hgfheader;
        vector<PNG*> PNGS;

        //FILE *file;
        
        HGFFile();
        ~HGFFile();
        SavePrj(FILE *fp);
        LoadPrj(FILE* fp);

};

class HPTWav
{
public:
        HPTWav(){};
       
        AnsiString filename;
        AnsiString desc;
        unsigned int data_size;
        unsigned short *data;
        unsigned short *fil_data;
        unsigned char *zlib_data;
        void LoadData(FILE * fp);
        int zlib_size;
        
        SubtractionFilter();
        zlibCompress();
        void WriteData(FILE * fp);
        ~HPTWav();
};

class HSFFile
{
public:
        
        AnsiString filename;
        AnsiString full_path_name;
 //       FILE* file;
        vector<HPTWav*> wavs;
        HSFFile();
        ~HSFFile();
        SaveProj(FILE * fp);
        LoadProj(FILE * fp);


};

class HFFFile
{
public:
        TFont *font;
        int keyred;
        int keygreen;
        int keyblue;
        int colorred;
        int colorgreen;
        int colorblue;
        int fringred;
        int fringgreen;
        int fringblue;
        
        Graphics::TBitmap *tbitmap;
        Graphics::TPicture *tpic;
        unsigned char *bits;
        BITMAPINFOHEADER binfo;
        int charwidths[95];
        int bwidth;
        int bheight;
        AnsiString full_path_name;
        AnsiString filename;
        HFFFile();
        SaveProj(FILE * fp);
        LoadProj(FILE * fp);
        ~HFFFile();
};

class HLFFile
{

public:
        AnsiString full_path_name;
        AnsiString mapdata_filename;
        AnsiString fronttileimage_filename;
        AnsiString backtileimage_filename;
        AnsiString fronttiledata_filename;
        AnsiString backtiledata_filename;
        int colorred;
        int colorblue;
        int colorgreen;

};

class Level
{
public:
        AnsiString map_data;
        AnsiString tileimage_layer1;
        AnsiString tiledata_layer1;
        AnsiString tileimage_layer2;
        AnsiString tiledata_layer2;
        AnsiString level_name;

        int num_frontlayer_tiles;
        int num_backlayer_tiles;

        Level();
        WriteHLF();
        WriteLayer1HTF();
        WriteLayer2HTF();
        void SavePrj(FILE *fp);
        void LoadPrj(FILE *fp);
};

DispatchMessage(char* msg);
TListBox * MessageQue;

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPageControl *TabSheet;
        TTabSheet *HGF;
        TTabSheet *HLFHTF;
        TTabSheet *HSF;
        TMainMenu *MainMenu1;
        TMenuItem *MenuFile;
        TMenuItem *NewGame;
        TMenuItem *OpenGame;
        TMenuItem *Exit;
        TLabel *Label1;
        TListBox *LevelsList;
        TLabel *Levels;
        TListBox *HSFFiles;
        TLabel *SoundFiles;
        TEdit *framerate;
        TComboBox *HGFImages;
        TEdit *DescriptionEdit;
        TEdit *ImageLocEdit;
        TButton *imagelocbut;
        TOpenDialog *ImageLocationDialog;
        TEdit *red;
        TEdit *green;
        TEdit *blue;
        TEdit *frameset;
        TEdit *framesperset;
        TCheckBox *autoanimate;
        TButton *applysettingsbut;
        TEdit *height;
        TEdit *width;
        TButton *removeimagebut;
        TButton *addimagebut;
        TOpenDialog *AddImage;
        TLabel *Frame_Rate;
        TLabel *Label2;
        TLabel *FrameSets;
        TLabel *textHeight;
        TLabel *textWidth;
        TLabel *Label5;
        TLabel *Label4;
        TLabel *R;
        TLabel *G;
        TLabel *B;
        TLabel *Label3;
        TLabel *Label6;
        TMenuItem *MenuHGF;
        TMenuItem *NewHGF;
        TMenuItem *RemoveHGF;
        TMenuItem *SaveHGF;
        TEdit *hgflocname;
        TButton *hgflocbut;
        TLabel *Label7;
        TSaveDialog *DialogNewHGF;
        TListBox *HGFFiles;
        TMenuItem *SaveAllHGFS;
        TSaveDialog *DialogNewGame;
        TOpenDialog *DialogOpenGame;
        TMenuItem *CloseGame;
        TEdit *palletentry;
        TOpenDialog *DialogHGFLoc;
        TComboBox *HSFSounds;
        TSaveDialog *DialogSaveHSF;
        TMenuItem *MenuHSF;
        TMenuItem *NewHSF;
        TMenuItem *RemoveHSF;
        TMenuItem *SaveHSF;
        TMenuItem *SaveAllHSFS;
        TMenuItem *SaveGame;
        TMenuItem *MenuHLFHTF;
        TEdit *SDescriptionEdit;
        TEdit *spalletnumber;
        TEdit *SoundLocEdit;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *hsflocname;
        TMenuItem *CreateNewLevel;
        TMenuItem *RemoveLevel;
        TMenuItem *SaveLevel;
        TMenuItem *SaveAllLevels;
        TButton *addsoundbut;
        TOpenDialog *DialogAddSound;
        TButton *removesoundbut;
        TButton *sapplysettingbut;
        TButton *hsflocbut;
        TOpenDialog *DialogHSFLoc;
        TButton *soundlocbut;
        TOpenDialog *DialogSoundLocation;
        TTabSheet *HFF;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TButton *Button2;
        TEdit *KeyRedEdit;
        TEdit *KeyGreenEdit;
        TEdit *KeyBlueEdit;
        TEdit *ColorRedEdit;
        TEdit *ColorGreenEdit;
        TEdit *ColorBlueEdit;
        TFontDialog *FontDialog1;
        TSaveDialog *SaveDialog1;
        TLabel *Label17;
        TListBox *HFFFiles;
        TLabel *Label18;
        TMenuItem *HFF1;
        TMenuItem *AddFont1;
        TMenuItem *RemoveHFF1;
        TMenuItem *SaveHFF1;
        TMenuItem *SaveAllHFFs1;
        TButton *choosefontbut;
        TSaveDialog *DialogNewHFF;
        TEdit *hfflocedit;
        TButton *hfflocbut;
        TMenuItem *N1;
        TMenuItem *Options;
        TMenuItem *N2;
        TColorDialog *DialogBackGroundColor;
        TButton *backgroundcolorbut;
        TBitBtn *foregroundcolorbut;
        TColorDialog *DialogForegroundColor;
        TTimer *TimerAutoSave;
   //     Tfontscroll *fontscroll1;
        TCheckBox *fringingcheckbox;
        TButton *fringingcolorbut;
        TEdit *FringRedEdit;
        TEdit *FringGreenEdit;
        TEdit *FringBlueEdit;
        TColorDialog *DialogFringingColor;
        Tfontscroll *fontscroll1;
        TListBox *Messages;
        TSplitter *Splitter1;
        TTreeView *TreeView1;
        TSplitter *Splitter2;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *fronttiledataedit;
        TButton *fronttibut;
        TButton *fronttdbut;
        TLabel *Label16;
        TLabel *Label19;
        TEdit *backtileimageedit;
        TEdit *backtiledataedit;
        TButton *backtdbut;
        TButton *backtibut;
        TLabel *Label20;
        TEdit *mapdataedit;
        TButton *mapdatabut;
        TEdit *fronttileimageedit;
        TOpenDialog *DialogMapData;
        TOpenDialog *DialogTileData;
        TMenuItem *BuildProject1;
        TEdit *leveloutputedit;
        TLabel *Label23;
        TButton *leveloutputbut;
        TSaveDialog *NewLevelDialog;
        TEdit *frontlayernumbertiles;
        TEdit *scrollinglayernumbertiles;
        TLabel *Label21;
        TLabel *Label22;
        void __fastcall NewHGFClick(TObject *Sender);
        void __fastcall RemoveHGFClick(TObject *Sender);
        void __fastcall NewGameClick(TObject *Sender);
        void __fastcall OpenGameClick(TObject *Sender);
        void __fastcall CloseGameClick(TObject *Sender);
        void __fastcall addimagebutClick(TObject *Sender);
        void __fastcall HGFFilesClick(TObject *Sender);
        void __fastcall HGFImagesChange(TObject *Sender);
        void __fastcall removeimagebutClick(TObject *Sender);
        void __fastcall applysettingsbutClick(TObject *Sender);
        void __fastcall imagelocbutClick(TObject *Sender);
        void __fastcall SaveHGFClick(TObject *Sender);
        void __fastcall SaveAllHGFSClick(TObject *Sender);
        void __fastcall hgflocbutClick(TObject *Sender);
        void __fastcall NewHSFClick(TObject *Sender);
        void __fastcall RemoveHSFClick(TObject *Sender);
        void __fastcall ExitClick(TObject *Sender);
        void __fastcall addsoundbutClick(TObject *Sender);
        void __fastcall removesoundbutClick(TObject *Sender);
        void __fastcall HSFSoundsChange(TObject *Sender);
        void __fastcall HSFFilesClick(TObject *Sender);
        void __fastcall sapplysettingbutClick(TObject *Sender);
        void __fastcall hsflocbutClick(TObject *Sender);
        void __fastcall soundlocbutClick(TObject *Sender);
        void __fastcall SaveHSFClick(TObject *Sender);
        void __fastcall SaveAllHSFSClick(TObject *Sender);
        void __fastcall SaveGameClick(TObject *Sender);
        void __fastcall choosefontbutClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall AddFont1Click(TObject *Sender);
        void __fastcall SaveHFFClick(TObject *Sender);
       // void __fastcall choosefontbut(TObject * Sender);
       void __fastcall KeyRedEditChange(TObject *Sender);
       void __fastcall KeyRedEditExit(TObject *Sender);
       void __fastcall KeyGreenEditChange(TObject *Sender);
       void __fastcall KeyGreenEditExit(TObject *Sender);
       void __fastcall KeyBlueEditChange(TObject *Sender);
       void __fastcall ColorRedEditChange(TObject *Sender);
       void __fastcall ColorGreenEditChange(TObject *Sender);
       void __fastcall ColorBlueEditChange(TObject *Sender);
       void __fastcall KeyBlueEditExit(TObject *Sender);
       void __fastcall ColorRedEditExit(TObject *Sender);
       void __fastcall ColorGreenEditExit(TObject *Sender);
       void __fastcall ColorBlueEditExit(TObject *Sender);
        void __fastcall RemoveHFF1Click(TObject *Sender);
        void __fastcall coloreditClick(TObject * Sender);
        void __fastcall HFFFilesClick(TObject *Sender);
        void __fastcall SaveAllHFFs1Click(TObject *Sender);
        void __fastcall hfflocbutClick(TObject *Sender);
        void __fastcall backgroundcolorbutClick(TObject *Sender);
        void __fastcall foregroundcolorbutClick(TObject *Sender);
        void __fastcall OptionsClick(TObject *Sender);
        void __fastcall AutoSave(TObject *Sender);
        void __fastcall onClose(TObject *Sender, TCloseAction &Action);
        void __fastcall fringingcolorbutClick(TObject *Sender);
        void __fastcall fringcolorcheckOnClick(TObject *Sender);
        void __fastcall fronttibutClick(TObject *Sender);
        void __fastcall backtibutClick(TObject *Sender);
        void __fastcall mapdatabutClick(TObject *Sender);
        void __fastcall fronttdbutClick(TObject *Sender);
        void __fastcall backtdbutClick(TObject *Sender);
        void __fastcall BuildProject1Click(TObject *Sender);
        void __fastcall CreateNewLevelClick(TObject *Sender);
        void __fastcall LevelsListClick(TObject *Sender);
        void __fastcall SaveLevelClick(TObject *Sender);

private:	// User declarations
        vector<HGFFile*> hgfs;
        vector<HSFFile*> hsfs;
        vector<HFFFile*> hffs;
        vector<Level*> levels;
        //FILE *proj;
        AnsiString proj_file;
        float version;
        bool needtosave;
public:
        TDialogOptions *DialogOptions;
        
        __fastcall TForm1(TComponent* Owner);

        SaveProject();
        DisableFontEdit();
        EnableFontEdit();
        EnableLevels();

        



};




//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
