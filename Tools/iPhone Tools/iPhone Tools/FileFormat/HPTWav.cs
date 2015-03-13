using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using iPhone_Tools.Custom;

namespace iPhone_Tools.FileFormat
{
    public class HPTWav
    {
        #region Fields

        //HPTWav(){};

        string _filename;
        string _desc;
        
        //uint data_size;
        //ushort[] *data;
        //ushort[] *fil_data;
        //byte[] *zlib_data;
        //void LoadData(FILE * fp);
        //int zlib_size;
        
        //SubtractionFilter();
        //zlibCompress();
        //void WriteData(FILE * fp);
        //~HPTWav();

        #endregion

        #region Constructor(s)

        public HPTWav()
        {
        }

        #endregion

        #region Methods

        public void LoadFromProject(BinaryReader br)
        {
            _filename = HPTFileHelper.GetString(br);
            _desc = HPTFileHelper.GetString(br);
        }

        public void SaveToProject(BinaryWriter bw)
        {
            bw.Write(_filename.Length);
            bw.Write(_filename.ToCharArray());

            bw.Write(_desc.Length);
            bw.Write(_desc.ToCharArray());
        }

        #endregion

        #region Properties

        public string Filename
        {
            get { return _filename; }
            set { _filename = value; }
        }

        public string Desc
        {
            get { return _desc; }
            set { _desc = value; }
        }

        #endregion
    }
}
