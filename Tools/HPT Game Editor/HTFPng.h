// HTFPng.h: interface for the HTFPng class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTFPNG_H__0104275F_326A_4FF1_97B8_21760692CFA2__INCLUDED_)
#define AFX_HTFPNG_H__0104275F_326A_4FF1_97B8_21760692CFA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "HTFHeader.h"
#include "PNGChunk.h"
#include "zlib.h"

using namespace std;

class HTFPng: public HTFHeader 
{
public:
	bool IsTransparent(int arg);
	virtual void VFlip(unsigned char *arg);
	virtual void HFlip(unsigned char* arg);
	void ExtractTile(unsigned char*arg, int numb);
	void FlattenTiles();
	void CompressImage();
	void GenerateOutputImage();
	void DecompressImage();
	void CombineImage();
	void ConvertIHDR();
	HTFPng();
	virtual ~HTFPng();

	vector<PNGChunk*> png_chunks;

	void load_image_data(FILE *&fp);
	void write_file(FILE *fp);
	char PNGSignature[8];
	int  data_length;
	unsigned char *combined_chunks;
	unsigned char *decompressed_image;
	unsigned int combined_chunk_size;
	unsigned char *output_image;
	unsigned char *compressed_output_image;
	unsigned long compressed_output_image_size;
	virtual void CheckKeyVisibility(int &key,int arg1,int arg2);
	virtual void CheckKeyVisibility(int &key,int arg1);
        int output_image_width;
        int output_image_height;
};

#endif // !defined(AFX_HTFPNG_H__0104275F_326A_4FF1_97B8_21760692CFA2__INCLUDED_)
