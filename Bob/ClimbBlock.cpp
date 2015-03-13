// ClimbBlock.cpp: implementation of the ClimbBlock class.
//
//////////////////////////////////////////////////////////////////////


#include "ClimbBlock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ClimbBlock::ClimbBlock()
{

}

ClimbBlock::~ClimbBlock()
{

}

bool ClimbBlock::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype)
{
	ladder = true;
	ltype = block_type;
	return false;
}

void ClimbBlock::SetBlockType(int arg)
{
	block_type = arg;
}
