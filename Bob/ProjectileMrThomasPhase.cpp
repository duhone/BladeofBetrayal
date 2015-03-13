// ProjectileMrThomasPhase.cpp: implementation of the ProjectileMrThomasPhase class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileMrThomasPhase.h"
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileMrThomasPhase::ProjectileMrThomasPhase(int xPos, int yPos, float xVel, 
			IPlayerFlags *ipFlags, float *xLoc, float *yLoc, int _leftBound,int _rightBound) :
			m_leftBound(_leftBound), m_rightBound(_rightBound)
{
	/* Set Sprite Number */	
	SetSprite(0, CR::AssetList::MrT_charge_loop);

	/* Set Sprite Direction */

	/* Set Weapon Bounding Box */
	SetWeaponBounds(60,60);

	/* Set Activate & Delay Timer */
//	SetActiveTime(1.5);
	SetDelayTime(0);

	/* Set Velocity Direction */
	SetVelocityVector(xVel, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(6);

	this->xLoc = xLoc;
	this->yLoc = yLoc;

	proj_flags.S_DIRECTION = ipFlags->S_DIRECTION;

	this->ipFlags = ipFlags;

	proj_flags.S_NON_PROJECTILE = true;
	SetAnimation(0, 0, true, false, 15, true);
}

ProjectileMrThomasPhase::~ProjectileMrThomasPhase()
{
}

HPTRect &ProjectileMrThomasPhase::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 20, 45, -15, -15);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);


	
	return hptrectBounds;
}

void ProjectileMrThomasPhase::DeActivate()
{
	if(proj_params.xLoc < m_leftBound) proj_params.xLoc = m_leftBound+1;
	else if(proj_params.xLoc > m_rightBound) proj_params.xLoc = m_rightBound-1;

	ipFlags->S_VISIBLE = true;
	ipFlags->S_ATTACK = false;
	*xLoc = proj_params.xLoc;
	*yLoc = proj_params.yLoc;

	proj_flags.S_ACTIVE = false;
}

void ProjectileMrThomasPhase::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		ipFlags->S_VISIBLE = false;

		if((proj_params.xLoc < m_leftBound) || (proj_params.xLoc > m_rightBound))
		{
			DeActivate();
		}

		proj_params.xLoc += (proj_params.xVel * time);
		//cout << "xloc " << proj_params.xLoc << "vel " << proj_params.xVel << endl;
	}
	else
	{
		proj_params.timeDelay -= time;

		if(proj_params.timeDelay < 0)
			SetAnimation(0, 0, true, false, 15, true);
	}
}