// ProjectileBubble.cpp: implementation of the ProjectileBubble class.
//
//////////////////////////////////////////////////////////////////////


#include <math.h>
#include <stdlib.h>
#include "ProjectileBubble.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileBubble::ProjectileBubble(int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(0, CR::AssetList::Bubbles);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	SetDelayTime(.15f);

	/* Set Velocity Direction */
	SetVelocityVector(static_cast<float>(0), -(rand()%5 + 15));

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(0);	
	
	/* Initialize Sprite */
	SetAnimation(0, 0, true, true, 3, true);

	movetimer = .25;
}

ProjectileBubble::~ProjectileBubble()
{
}

HPTRect &ProjectileBubble::GetWeaponBounds()
{
	SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileBubble::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
	
		if(proj_params.timeActive <= 0)
			DeActivate();

		movetimer -= time;

		if(movetimer < 0)
		{
			proj_params.xLoc += (rand()%3-1);
			movetimer = .25;
		}

		proj_params.yLoc += (proj_params.yVel * time);
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}