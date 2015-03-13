// ProjectileJacobRockQuake.cpp: implementation of the ProjectileJacobRockQuake class.
//
//////////////////////////////////////////////////////////////////////


#include <math.h>
#include <stdlib.h>
#include "ProjectileJacobRockQuake.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileJacobRockQuake::ProjectileJacobRockQuake(int *xOffset, int *yOffset, int xPos, int yPos,list<Projectile*> *projectile_list, float *xLoc, float *yLoc, IPlayerFlags *ipFlags)
{
	/* Set Activate & Delay Timer */
	//SetDelayTime(.25);

	/* Set Damage Value */
	//SetWeaponDamage(5);
	SetWeaponDamage(5);

	xLevelRenderOffset = xOffset;
	yLevelRenderOffset = yOffset;
	
	/* Set Start Position */
	SetPosition(xPos, yPos);

	SetSource(true);
	proj_flags.S_NON_PROJECTILE = true;
	shake = 10;
	S_SHAKE = true;

	this->ipFlags = ipFlags;
	this->xLoc = xLoc;
	this->yLoc = yLoc;
	this->projectile_list = projectile_list;
}

ProjectileJacobRockQuake::~ProjectileJacobRockQuake()
{
}

HPTRect &ProjectileJacobRockQuake::GetWeaponBounds()
{
	SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}


void ProjectileJacobRockQuake::Update()
{
	if(proj_params.timeDelay <= 0)
	{
//		if(S_SHAKE)
//		{
//			int temp = rand()%100;
//			shake += .05;
//			if(shake > 15)
//				S_SHAKE = false;
//		}
//		else
		{
			int temp = rand()%100;
			shake -= .1f;
			if(shake <= 1)
			{
			//	ipFlags->S_ATTACK = false;
				DeActivate();
				return;
			}
		}
		*xLevelRenderOffset = static_cast<int>(rand()%(static_cast<int>(shake))-(shake*.5));
		*yLevelRenderOffset = static_cast<int>(rand()%(static_cast<int>(shake))-(shake*.5));
	}
	else
	{
		proj_params.timeDelay -= time;

		if(proj_params.timeDelay <= 0)   ;
		//soundPlayer->PlaySound(explode01);
	}
}
