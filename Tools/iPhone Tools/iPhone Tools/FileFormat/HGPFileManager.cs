using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace iPhone_Tools.FileFormat
{
    public class HGPFileManager
    {
        #region Fields

        string _fileName;

        List<HGFFile> _hgfFiles;
        List<HSFFile> _hsfFiles;
        List<HFFFile> _hffFiles;
        List<Level> _hlfFiles;

        #endregion

        #region Constructor(s)

        public HGPFileManager()
        {
            _hgfFiles = new List<HGFFile>();
            _hsfFiles = new List<HSFFile>();
            _hffFiles = new List<HFFFile>();
            _hlfFiles = new List<Level>();
        }

        #endregion

        #region Methods

        public void NewFile(string fileName)
        {
            _fileName = fileName;
            _hgfFiles.Clear();
            _hsfFiles.Clear();
            _hffFiles.Clear();
            _hlfFiles.Clear();
            SaveFile();
        }

        public void OpenFile(string fileName)
        {
            FileStream fstream = new FileStream(fileName, FileMode.Open);
            BinaryReader br = new BinaryReader(fstream);

            _fileName = fileName;

            //int str_len = 0;
            int size = 0;
            //char[] buffer = new char[512];
            //string ansi_buffer = string.Empty;

            // Amount of HGF Files
            size = br.ReadInt32();

            // Load ALL HGF Files
            for (int i = 0; i < size; i++)
            {
                // Load the associated HGF File info
                HGFFile hgfFile = new HGFFile();
                hgfFile.LoadFromProject(br);
                _hgfFiles.Add(hgfFile);
            }

            //Amount of HSF Files
            size = br.ReadInt32();
            
            // Load ALL HSF Files
            for (int i = 0; i < size; i++)
            {
                // Load the associated HSF file info
                HSFFile hsfFile = new HSFFile();
                hsfFile.LoadFromProject(br);
                _hsfFiles.Add(hsfFile);
            }

            // Amount of HFF Files
            size = br.ReadInt32();

            // Load ALL HFF Files
            for (int i = 0; i < size; i++)
            {
                HFFFile hffFile = new HFFFile();
                hffFile.LoadFromProject(br);
                _hffFiles.Add(hffFile);
            }

            // Amount of HLF / HTF Files
            size = br.ReadInt32();

            // Load ALL HLF / HTF Files
            for (int i = 0; i < size; i++)
            {
                Level level = new Level();
                level.LoadFromProject(br);
                _hlfFiles.Add(level);
            }

            // Close the Binary Reader
            br.Close();
        }

        public void SaveFile()
        {
            //FileStream fstream = new FileStream("D:\\" + "tmp-" + Path.GetFileName(_fileName), FileMode.Create);
            FileStream fstream = new FileStream(_fileName, FileMode.Create);
            BinaryWriter bw = new BinaryWriter(fstream);

            // Save ALL HGF Files
            bw.Write(_hgfFiles.Count);
            for (int i = 0; i < _hgfFiles.Count; i++)
            {
                _hgfFiles[i].SaveToProject(bw);
            }

            // Save ALL HSF Files
            bw.Write(_hsfFiles.Count);
            for (int i = 0; i < _hsfFiles.Count; i++)
            {
                _hsfFiles[i].SaveToProject(bw);
            }

            // Save ALL HFF Files
            bw.Write(_hffFiles.Count);
            for (int i = 0; i < _hffFiles.Count; i++)
            {
                _hffFiles[i].SaveToProject(bw);
            }

            // Save ALL HLF / HTF Files
            bw.Write(_hlfFiles.Count);
            for (int i = 0; i < _hlfFiles.Count; i++)
            {
                _hlfFiles[i].SaveToProject(bw);
            }

            // Close the Binary Writer
            bw.Flush();
            bw.Close();
        }

        public void CloseFile()
        {
            _fileName = "";
            _hgfFiles.Clear();
            _hsfFiles.Clear();
            _hffFiles.Clear();
            _hlfFiles.Clear();
        }

        #endregion

        #region Properties

        public List<HGFFile> HGFFiles
        {
            get { return _hgfFiles; }
            set { _hgfFiles = value; }
        }

        public List<HSFFile> HSFFiles
        {
            get { return _hsfFiles; }
            set { _hsfFiles = value; }
        }

        public List<HFFFile> HFFFiles
        {
            get { return _hffFiles; }
            set { _hffFiles = value; }
        }

        public List<Level> Levels
        {
            get { return _hlfFiles; }
            set { _hlfFiles = value; }
        }

        #endregion
    }
}
