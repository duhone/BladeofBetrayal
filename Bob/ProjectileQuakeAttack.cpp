// ProjectileQuakeAttack.cpp: implementation of the ProjectileQuakeAttack class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileQuakeAttack.h"

extern void NEW(void *arg);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "ProjectileQuakeAttackRock.h"
#include<math.h>
#include<stdlib.h>

using namespace std;

ProjectileQuakeAttack::ProjectileQuakeAttack(int *xOffset, int *yOffset, int xPos, int yPos,list<Projectile*> *projectile_list, float *xLoc, float *yLoc, IPlayerFlags *ipFlags)
{
	/* Set Activate & Delay Timer */
	//SetDelayTime(1.5);
	SetDelayTime(0.5);
	
	/* Set Damage Value */
	SetWeaponDamage(5);

	xLevelRenderOffset = xOffset;
	yLevelRenderOffset = yOffset;
	
	/* Set Start Position */
	SetPosition(xPos, yPos);

	SetSource(true);
	proj_flags.S_NON_PROJECTILE = true;
	shake = 1;
	S_SHAKE = true;

	this->ipFlags = ipFlags;
	this->xLoc = xLoc;
	this->yLoc = yLoc;
	this->projectile_list = projectile_list;

	weapon_type = 10;
}

ProjectileQuakeAttack::~ProjectileQuakeAttack()
{
}

HPTRect &ProjectileQuakeAttack::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 400, 400, -200, -200);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}


void ProjectileQuakeAttack::Update()
{	
	if(proj_params.timeDelay <= 0)
	{
	if(S_SHAKE)
	{
		int temp = rand()%100;

		if(temp <= 25)
		{
			Projectile *temp;
			//temp = new ProjectileQuakeAttackRock(static_cast<int>(*xLoc) + rand()%480 - 240, static_cast<int>(*yLoc - 160),(float)(rand()%50 - 25),5, 0, 200);
			
			//iPhone
			temp = new ProjectileQuakeAttackRock(static_cast<int>(*xLoc) + rand()%480 - 240, static_cast<int>(*yLoc - 180),(float)(rand()%50 - 25),5, 0, 200);
			
			(*projectile_list).push_back(temp);
		}

		shake += .05f;

		/*if(shake > 1)
		{
			ipFlags->S_ATTACK = false;
		}
		*/
		
		if(shake > 6)
		{
			//S_SHAKE = false;
			
			ipFlags->S_ATTACK = false;
			DeActivate();
			return;
		}
	}
	/*else
	{
		int temp = rand()%100;

		if(temp <= 25)
		{
			Projectile *temp;
			temp = new ProjectileQuakeAttackRock(static_cast<int>(*xLoc) + rand()%480 - 240, static_cast<int>(*yLoc - 160),(float)(rand()%50 - 25),5, 0, 200);
			;
			(*projectile_list).push_back(temp);
		}

		shake -= .05f;

		if(shake <= 1)
		{
			ipFlags->S_ATTACK = false;
			DeActivate();
			return;
		}
	}*/

	*xLevelRenderOffset = static_cast<int>(rand()%(static_cast<int>(shake))-(shake*.5));
	*yLevelRenderOffset = static_cast<int>(rand()%(static_cast<int>(shake))-(shake*.5));

	}
	else
	{
		proj_params.timeDelay -= time;
	}
}