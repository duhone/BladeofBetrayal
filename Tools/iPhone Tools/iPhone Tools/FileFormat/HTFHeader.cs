using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace iPhone_Tools.FileFormat
{
    public class HTFHeader
    {
        #region Fields

        //virtual void VFlip(unsigned char *arg) = 0;
        //virtual void HFlip(unsigned char* arg) = 0;
        //void RemoveHDuplicates();
        //void RemoveVDuplicates();
        //void RemoveHVDuplicates();
        //void ReplaceTileMapKey(int old,int newt);
        //bool CompareTiles(unsigned char *arg1,unsigned char *arg2);
        //void RemoveDuplicates();
        //int FindEntry(int arg);
        //void GenerateNewEntrys();
        //int GetNumbKeys();
        //bool FindKey(int key);
        //void GenerateKeys();
        //int GenerateKey(unsigned short *arg);
        //void CreateTiles();
        //virtual void write_file(FILE *fp)=0;
        //virtual void load_image_data(FILE *&fp)=0;
        
        //unsigned short* matrix_data;
        //unsigned int* matrix_keys;
        //Tile *tiles;
        //vector<FlatTile> flat_tiles;
        //int matrix_height;
        //int matrix_width;
        //int image_type;
        //int num_tiles;
        //int color_key_green;
        //int color_key_blue;
        //int color_key_red;
        //unsigned int total_width;
        //unsigned int total_height;
        //int height;
        //int width;
        //int version;
        //char HTF[4];

        ushort[] matrix_data;
        uint[] matrix_keys;
        Tile[] tiles;
        List<FlatTile> flat_tiles;
        int matrix_height;
        int matrix_width;
        int image_type;
        int num_tiles;
        int color_key_green;
        int color_key_blue;
        int color_key_red;
        uint total_width;
        uint total_height;
        int height;
        int width;
        int version;
        byte[] htf;

        //HTFHeader();
        //virtual ~HTFHeader();
        //virtual void CheckKeyVisibility(int &key,int arg1,int arg2) = 0;
        //virtual void CheckKeyVisibility(int &key,int arg1) = 0;

        #endregion
    }

    public class Tile
    {
	    public ushort layer;
    }

    public class FlatTile
    {
    }
}
