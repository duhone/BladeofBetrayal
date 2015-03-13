// HTFHeader.h: interface for the HTFHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTFHEADER_H__D5454BDF_62F0_4099_8111_72793FB915B0__INCLUDED_)
#define AFX_HTFHEADER_H__D5454BDF_62F0_4099_8111_72793FB915B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define HFLIP 0x01
#define VFLIP 0x02
#include<vector>
#include<stdio.h>

using namespace std;

struct Tile
{
	unsigned short layer;
//	unsigned char flip;
//	char padding;
};



struct FlatTile
{
	unsigned int key;
	unsigned char image[16*16*3];
	unsigned short entry;
	FlatTile()
	{
		ClearTile();
		key = 0;
		entry = 0;
	};
	FlatTile(const FlatTile &arg)
	{
		memcpy(image,arg.image,16*16*3);
		key = arg.key;
		entry = arg.entry;
	};
	const FlatTile& operator=(const FlatTile &arg)
	{
		memcpy(image,arg.image,16*16*3);
		key = arg.key;
		entry = arg.entry;
		return *this;
	};
	int GetLayer1()
	{
		unsigned int temp = 0;
		temp = key;
		temp = temp >> 22;
		temp = temp & 255;
		return temp;
	};
	int GetLayer2()
	{
		unsigned int temp = 0;
		temp = key;
		temp = temp >> 12;
		temp = temp & 255;
		return temp;
	};
	int GetLayer3()
	{
		unsigned int temp = 0;
		temp = key;
		temp = temp >> 2;
		temp = temp & 255;
		return temp;
	};
	int GetLayer1H()
	{
		unsigned int temp = 0;
		temp = key;
		temp = temp >> 21;
		temp = temp & 1;
		return temp;
	};
	int GetLayer1V()
	{
		unsigned int temp = 0;
		temp = key;
		temp = temp >> 20;
		temp = temp & 1;
		return temp;
	};
	int GetLayer2H()
	{
		unsigned int temp = 0;
		temp = key;
		temp = temp >> 11;
		temp = temp & 1;
		return temp;
	};
	int GetLayer2V()
	{
		unsigned int temp = 0;
		temp = key;
		temp = temp >> 10;
		temp = temp & 1;
		return temp;
	};
	int GetLayer3H()
	{
		unsigned int temp = 0;
		temp = key;
		temp = temp >> 1;
		temp = temp & 1;
		return temp;
	};
	int GetLayer3V()
	{
		unsigned int temp = 0;
		temp = key;
		temp = temp & 1;
		return temp;
	};
	void RenderTile(unsigned char *arg,unsigned char red,unsigned char green,unsigned char blue)
	{
		for(int ycount = 0;ycount < 16;ycount++)
		{
			for(int xcount = 0;xcount < 16;xcount++)
			{
				if(!((arg[ycount*16*3 + xcount*3] == red) && (arg[ycount*3*16 + xcount*3+1] == green) && (arg[ycount*16*3 + xcount*3+2] == blue)))
				{
					image[ycount*3*16 + xcount*3] = arg[ycount*16*3 + xcount*3];	
					image[ycount*3*16 + xcount*3+1] = arg[ycount*16*3 + xcount*3+1];	
					image[ycount*3*16 + xcount*3+2] = arg[ycount*16*3 + xcount*3+2];	
				}
			}
		}
	}
	void ClearTile()
	{
		for(int ycount = 0;ycount < 16;ycount++)
		{
			for(int xcount = 0;xcount < 16;xcount++)
			{
				image[ycount*3*16 + xcount*3] = 255;	
				image[ycount*3*16 + xcount*3+1] = 0;	
				image[ycount*3*16 + xcount*3+2] = 255;	
			}
		}
	}

};

bool SortTile(FlatTile arg1,FlatTile arg2);
/*{
	if(arg1.key <= arg2.key) return true;
	else return false;
}
*/


class HTFHeader
{
public:
	virtual void VFlip(unsigned char *arg) = 0;
	virtual void HFlip(unsigned char* arg) = 0;
	void RemoveHDuplicates();
	void RemoveVDuplicates();
	void RemoveHVDuplicates();
	void ReplaceTileMapKey(int old,int newt);
	bool CompareTiles(unsigned char *arg1,unsigned char *arg2);
	void RemoveDuplicates();
	int FindEntry(int arg);
	void GenerateNewEntrys();
	int GetNumbKeys();
	bool FindKey(int key);
	void GenerateKeys();
	int GenerateKey(unsigned short *arg);
	void CreateTiles();
	virtual void write_file(FILE *fp)=0;
	virtual void load_image_data(FILE *&fp)=0;
	unsigned short* matrix_data;
	unsigned int* matrix_keys;
	Tile *tiles;
	vector<FlatTile> flat_tiles;
	int matrix_height;
	int matrix_width;
	int image_type;
	int num_tiles;
	int color_key_green;
	int color_key_blue;
	int color_key_red;
	unsigned int total_width;
	unsigned int total_height;
	int height;
	int width;
	int version;
	char HTF[4];
	HTFHeader();
	virtual ~HTFHeader();
	virtual void CheckKeyVisibility(int &key,int arg1,int arg2) = 0;
	virtual void CheckKeyVisibility(int &key,int arg1) = 0;


};

#endif // !defined(AFX_HTFHEADER_H__D5454BDF_62F0_4099_8111_72793FB915B0__INCLUDED_)
