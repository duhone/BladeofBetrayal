using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using iPhone_Tools.Custom;
using System.Drawing;

namespace iPhone_Tools.FileFormat
{
    public class HFFFile
    {
        #region Fields
        Font _font;
        string _fontName;
        //TFont *font;
        int _keyred;
        int _keygreen;
        int _keyblue;
        int _colorred;
        int _colorgreen;
        int _colorblue;
        int _fringred;
        int _fringgreen;
        int _fringblue;
        
        //Graphics::TBitmap *tbitmap;
        //Graphics::TPicture *tpic;
        //unsigned char *bits;
        //BITMAPINFOHEADER binfo;
        //int charwidths[95];
        int _bwidth;
        int _bheight;
        
        string _full_path_name;
        string _filename;
        
        //HFFFile();
        //SaveProj(FILE * fp);
        //LoadProj(FILE * fp);
       // ~HFFFile();

        #endregion

        #region Constructor(s)

        public HFFFile()
        {
        }

        #endregion

        #region Methods
        
        public void LoadFromProject(BinaryReader br)
        {
            string fontName = string.Empty;
            int bold, italic, underline, strike, size;
            FontStyle fontStyle = FontStyle.Regular;

            _full_path_name = HPTFileHelper.GetString(br);
            _filename = Path.GetFileName(_full_path_name);

            fontName = HPTFileHelper.GetString(br);
            size = br.ReadInt32();
            bold = br.ReadInt32();
            italic = br.ReadInt32();
            underline = br.ReadInt32();
            strike = br.ReadInt32();

            if (bold != 0 || underline != 0 || italic != 0 || strike != 0)
                fontStyle &= ~FontStyle.Regular;

            if (bold != 0) fontStyle |= FontStyle.Bold;
            if (underline != 0) fontStyle |= FontStyle.Underline;
            if (italic != 0) fontStyle |= FontStyle.Italic;
            if (strike != 0) fontStyle |= FontStyle.Strikeout;
            
            _font = new Font(fontName, size, fontStyle);
            _fontName = fontName;
            
            if (_font.Name != fontName)
            {
                //LogManager.OnLogMessage(this, string.Format("Font name did not work: {0}, changed to: {1}", fontName, _font.Name));
            }


            _keyred = br.ReadInt32();
            _keygreen = br.ReadInt32();
            _keyblue = br.ReadInt32();
            _colorred = br.ReadInt32();
            _colorgreen = br.ReadInt32();
            _colorblue = br.ReadInt32();
            _fringred = br.ReadInt32();
            _fringgreen = br.ReadInt32();
            _fringblue = br.ReadInt32();

        }

        public void SaveToProject(BinaryWriter bw)
        {
            int bold, italic, underline, strike;

            bw.Write(_full_path_name.Length);
            bw.Write(_full_path_name.ToCharArray());

            bold = ((int)_font.Style & (int)FontStyle.Bold);
            italic = ((int)_font.Style & (int)FontStyle.Italic);
            underline = ((int)_font.Style & (int)FontStyle.Underline);
            strike = ((int)_font.Style & (int)FontStyle.Strikeout);

            //bw.Write(_font.Name.Length);
            //bw.Write(_font.Name.ToCharArray());
            bw.Write(_fontName.Length);
            bw.Write(_fontName.ToCharArray());
            bw.Write((Int32)_font.Size);
            bw.Write(bold);
            bw.Write(italic);
            bw.Write(underline);
            bw.Write(strike);

            bw.Write(_keyred);
            bw.Write(_keygreen);
            bw.Write(_keyblue);

            bw.Write(_colorred);
            bw.Write(_colorgreen);
            bw.Write(_colorblue);

            bw.Write(_fringred);
            bw.Write(_fringgreen);
            bw.Write(_fringblue);

        }

        #endregion

        #region Properties

        #endregion
    }
}
