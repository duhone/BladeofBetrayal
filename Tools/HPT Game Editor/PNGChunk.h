// PNGChunk.h: interface for the PNGChunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PNGCHUNK_H__BB2B366C_BD3C_4002_A191_B09796F56BE4__INCLUDED_)
#define AFX_PNGCHUNK_H__BB2B366C_BD3C_4002_A191_B09796F56BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>

class PNGChunk  
{
public:
	void LoadChunk(FILE* fp);
	PNGChunk();
	virtual ~PNGChunk();
	int Length;
    char Type[5];
    char* data;
    int CRC;

};

#endif // !defined(AFX_PNGCHUNK_H__BB2B366C_BD3C_4002_A191_B09796F56BE4__INCLUDED_)
