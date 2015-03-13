using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using iPhone_Tools.Custom;

namespace iPhone_Tools.FileFormat
{
    public class Level
    {
        #region Fields

        string _map_data = string.Empty;
        string _tileimage_layer1 = string.Empty;
        string _tiledata_layer1 = string.Empty;
        string _tileimage_layer2 = string.Empty;
        string _tiledata_layer2 = string.Empty;
        string _file_name = string.Empty;
        string _full_path_name = string.Empty;
        int _num_frontlayer_tiles = 0;
        int _num_backlayer_tiles = 0;

        //Level();
        //WriteHLF();
        //WriteLayer1HTF();
        //WriteLayer2HTF();
        //void SavePrj(FILE *fp);
        //void LoadPrj(FILE *fp);

        #endregion

        #region Constructor(s)

        public Level()
        {
        }

        #endregion

        #region Methods

        public void LoadFromProject(BinaryReader br)
        {
            _full_path_name = HPTFileHelper.GetString(br);
            _file_name = Path.GetFileName(_full_path_name);
            _map_data = HPTFileHelper.GetString(br);
            _tileimage_layer1 = HPTFileHelper.GetString(br);
            _tiledata_layer1 = HPTFileHelper.GetString(br);
            _tileimage_layer2 = HPTFileHelper.GetString(br);
            _tiledata_layer2 = HPTFileHelper.GetString(br);
            _num_frontlayer_tiles = br.ReadInt32();
            _num_backlayer_tiles = br.ReadInt32();
        }

        public void SaveToProject(BinaryWriter bw)
        {
            bw.Write(_full_path_name.Length);
            bw.Write(_full_path_name.ToCharArray());

            bw.Write(_map_data.Length);
            bw.Write(_map_data.ToCharArray());

            bw.Write(_tileimage_layer1.Length);
            bw.Write(_tileimage_layer1.ToCharArray());

            bw.Write(_tiledata_layer1.Length);
            bw.Write(_tiledata_layer1.ToCharArray());

            bw.Write(_tileimage_layer2.Length);
            bw.Write(_tileimage_layer2.ToCharArray());

            bw.Write(_tiledata_layer2.Length);
            bw.Write(_tiledata_layer2.ToCharArray());

            bw.Write(_num_frontlayer_tiles);
            bw.Write(_num_backlayer_tiles);
        }

        #endregion

        #region Properties

        public string Map_data
        {
            get { return _map_data; }
            set { _map_data = value; }
        }

        public string Tileimage_layer1
        {
            get { return _tileimage_layer1; }
            set { _tileimage_layer1 = value; }
        }

        public string Tiledata_layer1
        {
            get { return _tiledata_layer1; }
            set { _tiledata_layer1 = value; }
        }

        public string Tileimage_layer2
        {
            get { return _tileimage_layer2; }
            set { _tileimage_layer2 = value; }
        }

        public string Tiledata_layer2
        {
            get { return _tiledata_layer2; }
            set { _tiledata_layer2 = value; }
        }

        //public string Level_name
        //{
        //    get { return _level_name; }
        //    set { _level_name = value; }
        //}

        public int Num_frontlayer_tiles
        {
            get { return _num_frontlayer_tiles; }
            set { _num_frontlayer_tiles = value; }
        }

        public int Num_backlayer_tiles
        {
            get { return _num_backlayer_tiles; }
            set { _num_backlayer_tiles = value; }
        }

        public string File_name
        {
            get { return _file_name; }
            set { _file_name = value; }
        }

        public string Full_path_name
        {
            get { return _full_path_name; }
            set
            {
                _full_path_name = value;
                _file_name = Path.GetFileName(_full_path_name);
            }
        }

        public string HLF_file_path
        {
            get
            {
                if (_full_path_name == string.Empty || _file_name == string.Empty ||
                    _full_path_name == null || _file_name == null)
                    return string.Empty;

                try
                {
                    //string hlfFile = _full_path_name;//.Remove(_full_path_name.Length - _file_name.Length, _file_name.Length);
                    //string fileName = _file_name;//.Remove(_file_name.Length - 3, 3);
                    //fileName = fileName + ".htf";
                    //return hlfFile + fileName;
                    return _full_path_name + ".hlf";
                }
                catch
                {
                    return "";
                }
            }
        }

        public string Front_HTF_file_path
        {
            get
            {
                if (_full_path_name == string.Empty || _file_name == string.Empty ||
                    _full_path_name == null || _file_name == null)
                    return string.Empty;

                try
                {
                    return _full_path_name + "f.htf";
                }
                catch
                {
                    return "";
                }
            }
        }

        public string Back_HTF_file_path
        {
            get
            {
                if (_full_path_name == string.Empty || _file_name == string.Empty ||
                    _full_path_name == null || _file_name == null)
                    return string.Empty;

                try
                {
                    return _full_path_name + "b.htf";
                }
                catch
                {
                    return "";
                }
            }
        }

        #endregion
    }
}
