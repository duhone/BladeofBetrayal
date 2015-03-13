// PNGChunk.cpp: implementation of the PNGChunk class.
//
//////////////////////////////////////////////////////////////////////

#include "PNGChunk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PNGChunk::PNGChunk()
{

}

PNGChunk::~PNGChunk()
{

}

void PNGChunk::LoadChunk(FILE *fp)
{
	Length=0;
    int temp=0;

    fread(&temp, 1, 1,fp);
    Length += temp;
    Length = Length << 8;

    fread(&temp, 1, 1,fp);
    Length += temp;
    Length = Length << 8;

    fread(&temp, 1,1,fp);
    Length += temp;
    Length = Length << 8;

    fread(&temp, 1,1,fp);
    Length += temp;

    //set up memory for data of chunk
    data = new char[Length];

    //read in Type
    fread(Type, 4, 1, fp);
    Type[4]='\0';

    fread(data, Length, 1, fp);

    fread(&CRC, 4,1,fp);


}
