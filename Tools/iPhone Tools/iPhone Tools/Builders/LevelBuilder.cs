using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using iPhone_Tools.FileFormat;
using System.IO;
using iPhone_Tools.Custom;
using System.Drawing;
using System.IO.Compression;

namespace iPhone_Tools.Builders
{
    public class LevelBuilder
    {
        #region Fields

        HGPFileManager _hgpFileManager;

        #endregion

        #region Constructor(s)

        public LevelBuilder()
        {
        }

        #endregion

        #region Public Methods

        public void Build(Level level)
        {
            WriteHLF(level);
            WriteLayer1HTF(level);
        }

        public void BuildAll()
        {
        }

        private void WriteHLF(Level level)
        {
            FileStream output = new FileStream(level.HLF_file_path, FileMode.Create);            
            FileStream map_data = new FileStream(level.Map_data, FileMode.Open);

            // Read the map data
            int width;
            int height;
            byte[] mapdata;
            string[] tmp_mapdata;

            StreamReader sr = new StreamReader(map_data);
            width = int.Parse(sr.ReadLine());
            height = int.Parse(sr.ReadLine());
            
            // Convert map data to bytes
            mapdata = new byte[width * height];
            tmp_mapdata = sr.ReadLine().Split(new char[]{' '});
            for (int i = 0; i < (width * height); i++)
            {
                mapdata[i] = Byte.Parse(tmp_mapdata[i]);
            }
            sr.Close();

            // write the HLF file
            byte[] hlf = HPTFileHelper.convertStringToByteArray("HLF");
            Int32 version = 1;
            BinaryWriter bw = new BinaryWriter(output);
            bw.Write(hlf);
            bw.Write(version);
            bw.Write(width);
            bw.Write(height);
            bw.Write(mapdata);
            bw.Close();
        }

        public void WriteLayer1HTF(Level level)
        {
            FileStream tile_script = new FileStream(level.Tiledata_layer1, FileMode.Open);
            FileStream output = new FileStream(level.Front_HTF_file_path, FileMode.Create);

            HTFPng png = new HTFPng();
            
        }

        //public void ConvertHTFsToiPhone(Level level)
        //{
        //    FileStream file = new FileStream(level.Front_HTF_file_path, FileMode.Open);
        //    BinaryReader br = new BinaryReader(file);

        //    string HTF = HPTFileHelper.convertByteArrayToString(br.ReadBytes(3));
        //    int version = br.ReadInt32();
        //    int output_image_width = br.ReadInt32();
        //    int output_image_height = br.ReadInt32();
        //    int rows = br.ReadInt32();

        //    int[] columns = new int[rows - 1];
        //    for (int i = 0; i < rows - 1; i++)
        //    {
        //        columns[i] = br.ReadInt32();
        //    }
        //    int last_column = br.ReadInt32();

        //    int compressed_output_image_size = br.ReadInt32();
        //    byte[] compressed_output_image = br.ReadBytes(compressed_output_image_size);
        //    ///
        //    byte[] output_image = new byte[100];
        //    //MemoryStream ms = new MemoryStream(compressed_output_image);
            
        //    //DeflateStream ds = new DeflateStream(ms, CompressionMode.Decompress, false);

        //    //ReadAllBytesFromStream(ds, output_image);

        //    //ds.Close();
        //    //ms.Close();
            
        //   FileStream output = new FileStream("D:\\output.oop", FileMode.Create);
        //   BinaryWriter bw = new BinaryWriter(output);
        //   bw.Write(compressed_output_image);
        //   bw.Close();
        //    ///

        //    int matrix_width = br.ReadInt32();
        //    int matrix_height = br.ReadInt32();

        //    //fwrite(tiles, sizeof(Tile), matrix_width * matrix_height, fp);
        //}

        #endregion

        //public static int ReadAllBytesFromStream(Stream stream, byte[] buffer)
        //{
        //    // Use this method is used to read all bytes from a stream.
        //    int offset = 0;
        //    int totalCount = 0;
        //    while (true)
        //    {
        //        int bytesRead = stream.Read(buffer, offset, 100);
        //        if (bytesRead == 0)
        //        {
        //            break;
        //        }
        //        offset += bytesRead;
        //        totalCount += bytesRead;
        //    }
        //    return totalCount;
        //} 

        #region Properties

        public HGPFileManager HGPFileManager
        {
            set
            {
                _hgpFileManager = value;
            }
        }
        
        #endregion
    }
}
