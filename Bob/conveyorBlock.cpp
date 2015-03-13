// onveyorBlock.cpp: implementation of the ConveyorBlock class.
//
//////////////////////////////////////////////////////////////////////


#include "conveyorBlock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConveyorBlock::ConveyorBlock()
{
/*	sprite->SetImage(1,0);
	sprite->SetAutoAnimate(true);
	sprite->SetFrameSet(0);
	sprite->SetFrame(0);

*/
	sprite->SetAutoAnimate(true);

}

ConveyorBlock::~ConveyorBlock()
{

}

bool ConveyorBlock::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype)
{
	if(y > 0) 
	{
		arg->SetWorldLoc(0,y);
		if(y != 0) y = -100;

		return false;
	}
	arg->GetStateFlags()->S_CONVEYOR = true;
	arg->GetStateFlags()->S_CONVEYOR_TYPE = direction;

	int xVel = 10;

	if(direction == LEFT) xVel = -xVel;
		
//		arg->velocityModify(-20);
//	else arg->velocityModify(20);
//	arg->SetWorldLoc(x,y+1);
//	m = true;
//	return false;
	int tempy = y;
//	if(top_collide)
//	{
//		if(side_collide)
//		{
//		
//			if(tempy < 0) tempy++;
//			arg->SetWorldLoc(x,tempy);
//			if(y != 0) y = -100;
//			if(x != 0) x = -100;
//		}
//		else
//		{
	if(tempy < 0) tempy++;
	arg->SetWorldLoc(0/*xVel*time*/,tempy);
	if(y != 0) y = -100;
//		}
//	}
//	else
//	{
//		if(side_collide)
//		{
	
//			arg->SetWorldLoc(x,0);
//			if(x != 0) x = -100;
//		}
//		else
//		{
		
//			arg->SetWorldLoc(0,0);
//		}


//	}
	return false;
}

void ConveyorBlock::SetDirection(int arg)
{
	direction = arg;
}

bool ConveyorBlock::ProjectileCollideCheck(Projectile* arg)
{
	ProjectileFlags& proj_flags = arg->GetProjectileFlags();

	if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
	return false;
}
