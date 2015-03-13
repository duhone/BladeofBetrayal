using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace iPhone_Tools.FileFormat
{
    public class HGFHeader
    {
        char[] _hgf;
        int _version = 0;
        int _number_of_images = 0;

        public HGFHeader()
        {
            _hgf = new char[3];
            _version = 0;
            _number_of_images = 0;
        }

        public char[] HGF
        {
            get { return HGF; }
            set { HGF = value; }
        }

        public int Version
        {
            get { return _version; }
            set { _version = value; }
        }

        public int NumberOfImages
        {
            get { return _number_of_images; }
            set { _number_of_images = value; }
        }
    }
}
