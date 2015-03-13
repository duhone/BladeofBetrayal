// ProjectilePoints.cpp: implementation of the ProjectilePoints class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectilePoints.h"
#include "game.h"
extern Game* game_class;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
float ProjectilePoints::modifier = 1;

ProjectilePoints::ProjectilePoints(int xPos, int yPos, int nPoints, int fnt, bool type)
{
	this->nPoints = static_cast<int>(nPoints*modifier);

	S_FLICKER = false;

	/* Set Activate & Delay Timer */
	SetActiveTime(3);
	SetDelayTime(0);

	/* Set Start Position */
	SetPosition(xPos, yPos);
	
	SetVelocityVector(0, -20);

	SetSource(true);
	proj_flags.S_NON_PROJECTILE = true;

	bType = type;

	switch(fnt)
	{
	case 0:
		this->fnt = fnt_yellow;
		break;
	case 1:
		this->fnt = fnt_red;
		break;
	case 2:
		this->fnt = fnt_green;
		break;
	case 3:
		this->fnt = fnt_blue;
		break;
	case 4:
		this->fnt = fnt_blue;
		S_FLICKER = true;
		break;
	}
}

ProjectilePoints::~ProjectilePoints()
{

}

void ProjectilePoints::Update()
{
	if(S_FLICKER)
	{
		int i = rand()%4;

		switch(i)
		{
		case 0:
			this->fnt = fnt_yellow;
			break;
		case 1:
			this->fnt = fnt_red;
			break;
		case 2:
			this->fnt = fnt_green;
			break;
		case 3:
			this->fnt = fnt_blue;
			break;
		}
	}

	/* Initialize Sprite */
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
	
		if(proj_params.timeActive <= 0)
			DeActivate();

		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}

void ProjectilePoints::Render()
{
	//if(game_class->GetEnableScore()) return;
	if(bType){
		graphics_engine->Position((int)(proj_params.xLoc  + nOffset + xViewLoc) ,(int)(proj_params.yLoc + nOffset + yViewLoc));
		(*graphics_engine) << fnt << "+" << nPoints;
	}
	else{
		graphics_engine->Position((int)(proj_params.xLoc  + nOffset + xViewLoc) ,(int)(proj_params.yLoc + nOffset + yViewLoc));
		(*graphics_engine) << fnt << "-" << nPoints;
	}
}

void ProjectilePoints::SetModifier(float arg)
{
	modifier = arg;
}
