// FireBlock.cpp: implementation of the FireBlock class.
//
//////////////////////////////////////////////////////////////////////


#include "FireBlock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FireBlock::FireBlock(int arg)
{
	time_to_damage = 0;
	type = arg;
}

FireBlock::~FireBlock()
{

}

bool FireBlock::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype)
{
	int tempy = y;
	int tempx = x;		
	if(type == SPIKEBLOCK)
	{
		if(tempy < 0) tempy++;
		//if(tempx < 0) tempx++;
		//else if(tempx > 0) tempx--;
		arg->SetWorldLoc(tempx,tempy);
		if(y != 0) y = -100;
		if(x != 0) x = -100;
		if(time_to_damage <= 0)
		{

			arg->doDamage(3,!arg->GetStateFlags()->S_DIRECTION,0);
			time_to_damage = 1.0f;
		}
	}
	if(type == GASBLOCK)
	{

		arg->doChemicalDamage(5);
	}
	return false;
}

void FireBlock::Update()
{
	time_to_damage -= time;
	
}
