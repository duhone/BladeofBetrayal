// BasicBlock.cpp: implementation of the BasicBlock class.
//
//////////////////////////////////////////////////////////////////////


#include "BasicBlock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BasicBlock::BasicBlock()
{
	side_collide = true;
	top_collide = true;
}

BasicBlock::~BasicBlock()
{

}

bool BasicBlock::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype)
{
	int tempy = y;
	if(top_collide)
	{
		if(side_collide)
		{
		
			if(tempy < 0) tempy++;
			arg->SetWorldLoc(x,tempy);
			if(y != 0) y = -100;
			if(x != 0) x = -100;
		}
		else
		{
		
			if(tempy < 0) tempy++;
			arg->SetWorldLoc(0,tempy);
			if(y != 0) y = -100;
		}
	}
	else
	{
		if(side_collide)
		{
	
			arg->SetWorldLoc(x,0);
			if(x != 0) x = -100;
		}
		else
		{
		
			arg->SetWorldLoc(0,0);
		}


	}
	return false;
}

bool BasicBlock::OnGround(int y)
{
	if(top_collide)
	{
		if(y == 0) return false;
		else return true;
	}
	else return false;
}

void BasicBlock::SetSideCollide(bool arg)
{
	side_collide = arg;
}

void BasicBlock::SetTopCollide(bool arg)
{
	top_collide = arg;
}

bool BasicBlock::ProjectileCollideCheck(IPlayer *arg0, Projectile* arg)
{
	ProjectileFlags& proj_flags = arg->GetProjectileFlags();

	if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
	return false;
}
