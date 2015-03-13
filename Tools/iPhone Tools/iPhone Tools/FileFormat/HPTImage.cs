using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;
using iPhone_Tools.Custom;

namespace iPhone_Tools.FileFormat
{
    public class HPTImage : IHPTImage
    {
        #region Fields

        //HPTImageHeader _imageHeader;
        string _file_name;
        string _full_path_name;
        string _desc;
        Image _image;

        int _width;  //of single frame image
        int _height; // of single frame image
        int _img_width;
        int _img_height;
        int _color_key_red;
        int _color_key_blue;
        int _color_key_green;
        float _default_frame_rate;
        bool _default_auto_animate;
        int _num_frame_sets;
        List<int> _frames_per_set;   //one integer for each frame set
        int _image_type;

        #endregion

        #region Constructor(s)

        public HPTImage()
        {
            _color_key_blue = 0;
            _color_key_red = 0;
            _color_key_green = 0;
            _height = 0;
            _width = 0;
            _img_height = 0;
            _img_width = 0;
            _num_frame_sets = 1;
            _default_frame_rate = 0f;
            _default_auto_animate = false;
            _frames_per_set = new List<int>();
            _frames_per_set.Add(0);
            _image_type = 0;
        }

        #endregion

        #region Methods

        public void LoadFromProject(BinaryReader br)
        {
            _full_path_name = HPTFileHelper.GetString(br);
            _file_name = Path.GetFileName(_full_path_name);
            _desc = HPTFileHelper.GetString(br);

            _width = br.ReadInt32();
            _height = br.ReadInt32();
            _color_key_red = br.ReadInt32();
            _color_key_blue = br.ReadInt32();
            _color_key_green = br.ReadInt32();

            _default_frame_rate = br.ReadSingle();
            _default_auto_animate = br.ReadBoolean();
            _num_frame_sets = br.ReadInt32();
            
            _frames_per_set.Clear();
            if (_num_frame_sets > 0)
            {
                int frames = 0;
                for (int i = 0; i < _num_frame_sets; i++)
                {
                    frames = br.ReadInt32();
                    _frames_per_set.Add(frames);
                }
            }

            // load the image
            try
            {
                FileStream fs = new FileStream(_full_path_name, FileMode.Open);
                _image = Bitmap.FromStream(fs);//.FromFile(_full_path_name);
                fs.Close();

                _img_width = _image.Width;
                _img_height = _image.Height;
            }
            catch
            {
                LogManager.OnLogMessage(this, string.Format("Error opening file, \"{0}\".", _full_path_name));
            }
        }

        public void SaveToProject(BinaryWriter bw)
        {
            bw.Write(_full_path_name.Length);
            bw.Write(_full_path_name.ToCharArray());

            bw.Write(_desc.Length);
            bw.Write(_desc.ToCharArray());

            bw.Write(_width);
            bw.Write(_height);

            bw.Write(_color_key_red);
            bw.Write(_color_key_blue);
            bw.Write(_color_key_green);

            bw.Write(_default_frame_rate);
            bw.Write(_default_auto_animate);

            bw.Write(_num_frame_sets);

            if (_num_frame_sets > 0)
            {
                for (int i = 0; i < _num_frame_sets; i++)
                {
                    bw.Write(_frames_per_set[i]);
                }
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

        public string Desc
        {
            get { return _desc; }
            set { _desc = value; }
        }

        public Image Image
        {
            get { return _image; }
            set { _image = value; }
        }

        public int Width
        {
            get { return _width; }
            set { _width = value; }
        }

        public int Height
        {
            get { return _height; }
            set { _height = value; }
        }

        public int Img_width
        {
            get { return _img_width; }
            set { _img_width = value; }
        }

        public int Img_height
        {
            get { return _img_height; }
            set { _img_height = value; }
        }

        public int Color_key_red
        {
            get { return _color_key_red; }
            set { _color_key_red = value; }
        }

        public int Color_key_blue
        {
            get { return _color_key_blue; }
            set { _color_key_blue = value; }
        }

        public int Color_key_green
        {
            get { return _color_key_green; }
            set { _color_key_green = value; }
        }

        public float Default_frame_rate
        {
            get { return _default_frame_rate; }
            set { _default_frame_rate = value; }
        }

        public bool Default_auto_animate
        {
            get { return _default_auto_animate; }
            set { _default_auto_animate = value; }
        }

        public int Num_frame_sets
        {
            get { return _num_frame_sets; }
            set
            {
                _num_frame_sets = value;

                if (_frames_per_set.Count < _num_frame_sets)
                {
                    for (int i = _frames_per_set.Count; i < _num_frame_sets; i++)
                        _frames_per_set.Add(0);
                }
                else
                {
                    _frames_per_set.RemoveRange(_num_frame_sets, _frames_per_set.Count - _num_frame_sets);
                }
            }
        }

        public List<int> Frames_per_set
        {
            get { return _frames_per_set; }
            set { _frames_per_set = value; }
        }

        public int Image_type
        {
            get { return _image_type; }
            set { _image_type = value; }
        }

        public bool HighQuality
        {
            get { return _color_key_red == 0x0000000f0; }
            set
            {
                if (value) _color_key_red = 0x0000000f0;
                else _color_key_red = 0;
            }
        }
        #endregion

        #region IHPTImage Members

        public int ColorKeyBlue
        {
            get
            {
                return _color_key_blue;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public int ColorKeyGreen
        {
            get
            {
                return _color_key_green;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public int ColorKeyRed
        {
            get
            {
                return _color_key_red;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public bool DefaultAutoAnimate
        {
            get
            {
                return _default_auto_animate;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public float DefaultFrameRate
        {
            get
            {
                return _default_frame_rate;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public string FileName
        {
            get
            {
                return _full_path_name;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public List<int> FramesPerSet
        {
            get
            {
                return _frames_per_set;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public int ImageType
        {
            get
            {
                return _image_type;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public int NumFrameSets
        {
            get
            {
                return _num_frame_sets;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public int TotalHeight
        {
            get
            {
                return _img_height;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public int TotalWidth
        {
            get
            {
                return _img_width;
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        #endregion
    }
}
