using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;
using iPhone_Tools.Custom;

namespace iPhone_Tools.FileFormat
{
    public class HGFFile : IHGFFile
    {
        #region Fields

        string _file_name = string.Empty;
        string _full_path_name = string.Empty;
        HGFHeader _hgfHeader;
        List<HPTImage> _hptImages;

        #endregion

        #region Constructor(s)

        public HGFFile()
        {
            _hgfHeader = new HGFHeader();
            _hptImages = new List<HPTImage>();
        }

        #endregion

        #region Methods

        public void LoadFromProject(BinaryReader br)
        {
            int size = 0;
            HPTImage hptImage;

            _full_path_name = HPTFileHelper.GetString(br);
            _file_name = Path.GetFileName(_full_path_name);

            size = br.ReadInt32();
            _hgfHeader.NumberOfImages = size;

            _hptImages.Clear();
            for (int i = 0; i < size; i++)
            {
                // get pngs
                hptImage = new HPTImage();
                hptImage.LoadFromProject(br);
                _hptImages.Add(hptImage);
            }
        }

        public void SaveToProject(BinaryWriter bw)
        {
            bw.Write(_full_path_name.Length);
            bw.Write(_full_path_name.ToCharArray());

            bw.Write(_hptImages.Count);
            for (int i = 0; i < _hptImages.Count; i++)
            {
                _hptImages[i].SaveToProject(bw);
            }
        }

        #endregion

        #region Properties

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

        public List<HPTImage> HPTImages
        {
            get { return _hptImages; }
            set { _hptImages = value; }
        }

        #endregion

        #region IHGFFile Members

        public string FileName
        {
            get
            {
                return Path.GetFullPath(_full_path_name);
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public List<IHPTImage> Images
        {
            get
            {
                List<IHPTImage> result = new List<IHPTImage>();
                _hptImages.ForEach(i => result.Add(i));
                return result;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        #endregion
    }
}
