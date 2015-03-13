// HTFHeader.cpp: implementation of the HTFHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "HTFHeader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool SortTile(FlatTile arg1,FlatTile arg2)
{
	if(arg1.key <= arg2.key) return true;
	else return false;
}


HTFHeader::HTFHeader():
version(1)
{
	sprintf(HTF, "HTF");
}

HTFHeader::~HTFHeader()
{

}

void HTFHeader::write_file(FILE *fp)
{
	
}

void HTFHeader::CreateTiles()
{
	tiles = new Tile[matrix_width*matrix_height];
	for(int ycount = 0;ycount < matrix_height;ycount++)
	{
		for(int xcount = 0;xcount < matrix_width;xcount++)
		{
		/*	(tiles+ycount*matrix_width+xcount)->layer = (*(matrix_data+ycount*9*matrix_width+xcount*9+3));
			(tiles+ycount*matrix_width+xcount)->flip = 0;
			if((*(matrix_data+ycount*9*matrix_width+xcount*9+4))) 
				(tiles+ycount*matrix_width+xcount)->flip = (tiles+ycount*matrix_width+xcount)->flip | HFLIP;
			if((*(matrix_data+ycount*9*matrix_width+xcount*9+5))) 
				(tiles+ycount*matrix_width+xcount)->flip = (tiles+ycount*matrix_width+xcount)->flip | VFLIP;
*/
			int temp;
			temp = FindEntry(matrix_keys[ycount*matrix_width+xcount] & 0x03fffffff);
			unsigned short temps = 0;
			temps = (unsigned short)((matrix_keys[ycount*matrix_width+xcount] >> 16) & 0x00000c000);
			tiles[ycount*matrix_width+xcount].layer = flat_tiles[temp].entry | temps;
		}
	}
}

int HTFHeader::GenerateKey(unsigned short *arg)
{
	int temp,temp2;
	temp = 0;
	temp2 = arg[0];
	CheckKeyVisibility(temp2,arg[3],arg[6]);
	temp += temp2;
	temp = temp << 1;
	if(arg[1]) temp++;
	temp = temp << 1;
	if(arg[2]) temp++;
	temp = temp << 8;
	
	temp2 = arg[3];
	CheckKeyVisibility(temp2,arg[6]);
	temp += temp2;
	temp = temp << 1;
	if(arg[4]) temp++;
	temp = temp << 1;
	if(arg[5]) temp++;
	temp = temp << 8;
	
	temp += arg[6];
	temp = temp << 1;
	if(arg[7]) temp++;
	temp = temp << 1;
	if(arg[8]) temp++;
//	temp = temp << 8;

	return temp;
	
}

void HTFHeader::GenerateKeys()
{
	matrix_keys = new unsigned int[matrix_width*matrix_height];
	FlatTile tempt;

	for(int ycount = 0;ycount < matrix_height;ycount++)
	{
		for(int xcount = 0;xcount < matrix_width;xcount++)
		{
 			tempt.key = GenerateKey(&(matrix_data[ycount*matrix_width*9 + xcount*9]));
 			if(!FindKey(tempt.key)) flat_tiles.push_back(tempt);
			matrix_keys[matrix_width*ycount + xcount] = tempt.key;
		}
	}
}

bool HTFHeader::FindKey(int key)
{
	for(int count = 0;count < flat_tiles.size();count++)
	{
		if(flat_tiles[count].key == key) return true;
	}
	return false;
}

int HTFHeader::GetNumbKeys()
{
	return flat_tiles.size();
}


void HTFHeader::GenerateNewEntrys()
{
	for(int count = 0;count < flat_tiles.size();count++)
	{
		flat_tiles[count].entry = count;
	}
}

int HTFHeader::FindEntry(int arg)
{
	for(int count = 0;count < flat_tiles.size();count++)
	{
		if(flat_tiles[count].key == arg) return count;
	}
	return 0;
}

void HTFHeader::RemoveDuplicates()
{
	for(int ocount = 1;ocount < flat_tiles.size();ocount++)
	{
		for(int icount = ocount-1;icount >=0;icount--)
		{
			if(CompareTiles(flat_tiles[ocount].image,flat_tiles[icount].image))
			{
				ReplaceTileMapKey(flat_tiles[ocount].key,flat_tiles[icount].key);
				flat_tiles.erase(&(flat_tiles[ocount]));
				//flat_tiles[ocount].key = 0;
				ocount--;
				icount = -1;
			}
		}
	}
}

bool HTFHeader::CompareTiles(unsigned char *arg1, unsigned char *arg2)
{
	bool tempb = true;
	for(int count = 0;count < 16*16*3;count++)
	{
		if(arg1[count] != arg2[count]) tempb = false;
	}
	return tempb;
}

void HTFHeader::ReplaceTileMapKey(int old, int newt)
{
	for(int ycount = 0;ycount < matrix_height;ycount++)
	{
		for(int xcount = 0;xcount < matrix_width;xcount++)
		{
			if(matrix_keys[ycount*matrix_width+xcount] == old)
			{
				matrix_keys[ycount*matrix_width+xcount] = newt;
			}
		}
	}
}

void HTFHeader::RemoveHDuplicates()
{
	unsigned char temptile[16*16*3];
	for(int ocount = 1;ocount < flat_tiles.size();ocount++)
	{
		for(int icount = ocount-1;icount >=0;icount--)
		{
			memcpy(temptile,flat_tiles[ocount].image,16*16*3);
			HFlip(temptile);
			if(CompareTiles(temptile,flat_tiles[icount].image))
			{
				ReplaceTileMapKey(flat_tiles[ocount].key,flat_tiles[icount].key | 0x080000000);
				flat_tiles.erase(&(flat_tiles[ocount]));
				//flat_tiles[ocount].key = 0;
				ocount--;
				icount = -1;
			}
			else
			{
				HFlip(temptile);
				VFlip(temptile);
				if(CompareTiles(temptile,flat_tiles[icount].image))
				{
					ReplaceTileMapKey(flat_tiles[ocount].key,flat_tiles[icount].key | 0x040000000);
					flat_tiles.erase(&(flat_tiles[ocount]));
					//flat_tiles[ocount].key = 0;
					ocount--;
					icount = -1;
				}
				else
				{
					HFlip(temptile);
					if(CompareTiles(temptile,flat_tiles[icount].image))
					{
						ReplaceTileMapKey(flat_tiles[ocount].key,flat_tiles[icount].key | 0x0c0000000);
						flat_tiles.erase(&(flat_tiles[ocount]));
						//flat_tiles[ocount].key = 0;
						ocount--;
						icount = -1;
					}

				}

			}
		}
	}
}

void HTFHeader::RemoveVDuplicates()
{
	unsigned char temptile[16*16*3];
	for(int ocount = 1;ocount < flat_tiles.size();ocount++)
	{
		if((flat_tiles[ocount].key & 0x0c0000000) != 0) continue;
		for(int icount = ocount-1;icount >=0;icount--)
		{
			if((flat_tiles[icount].key & 0x0c0000000) != 0) continue;
			memcpy(temptile,flat_tiles[ocount].image,16*16*3);
			VFlip(temptile);
			if(CompareTiles(temptile,flat_tiles[icount].image))
			{
				ReplaceTileMapKey(flat_tiles[ocount].key,flat_tiles[icount].key | 0x040000000);
				flat_tiles.erase(&(flat_tiles[ocount]));
				//flat_tiles[ocount].key = 0;
				ocount--;
				icount = -1;
			}
		}
	}
}

void HTFHeader::RemoveHVDuplicates()
{
	unsigned char temptile[16*16*3];
	for(int ocount = 1;ocount < flat_tiles.size();ocount++)
	{
		for(int icount = ocount-1;icount >=0;icount--)
		{
			memcpy(temptile,flat_tiles[ocount].image,16*16*3);
			VFlip(temptile);
			HFlip(temptile);
			if(CompareTiles(temptile,flat_tiles[icount].image))
			{
				ReplaceTileMapKey(flat_tiles[ocount].key,flat_tiles[icount].key | 0x0c0000000);
				flat_tiles.erase(&(flat_tiles[ocount]));
				//flat_tiles[ocount].key = 0;
				ocount--;
				icount = -1;
			}
		}
	}
}