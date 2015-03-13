using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using iPhone_Tools.Custom;

namespace iPhone_Tools.FileFormat
{
    public class HSFFile
    {
        #region Fields

        string _filename;
        string _full_path_name;
        List<HPTWav> wavs;

        #endregion

        #region Constructor(s)

        public HSFFile()
        {
            wavs = new List<HPTWav>();
        }

        #endregion

        #region Methods

        public void LoadFromProject(BinaryReader br)
        {
            int size = 0;
            
            _full_path_name = HPTFileHelper.GetString(br);
            _filename = Path.GetFileName(_full_path_name);

            size = br.ReadInt32();
            for (int i = 0; i < size; i++)
            {
                HPTWav hptWav = new HPTWav();
                hptWav.LoadFromProject(br);
                wavs.Add(hptWav);
            }
        }

        public void SaveToProject(BinaryWriter bw)
        {
            bw.Write(_full_path_name.Length);
            bw.Write(_full_path_name.ToCharArray());

            bw.Write(wavs.Count);
            for (int i = 0; i < wavs.Count; i++)
            {
                wavs[i].SaveToProject(bw);
            }
        }

        #endregion
    }
}
