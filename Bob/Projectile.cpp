// Projectile.cpp: implementation of the Projectile class.
//
//////////////////////////////////////////////////////////////////////


#include "Projectile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Projectile::Projectile():projectile_spr(0)
{
	weapon_type = 0;
	
	/* Create Projectile Sprite */
	projectile_spr = graphics_engine->CreateSprite1();	
	projectile_spr->SetImage(CR::AssetList::Pixel);

	pixel_spr = graphics_engine->CreateSprite1();	
	pixel_spr->SetImage(CR::AssetList::Pixel);

	/* Set Default Offset to 0 */
	nOffset = 0;	

	pixel_yellow_spr = graphics_engine->CreateSprite1();
	pixel_yellow_spr->SetImage(CR::AssetList::Yellow_Pixel);
	pixel_black_spr = graphics_engine->CreateSprite1();
	pixel_black_spr->SetImage(CR::AssetList::Black_Pixel);
	pixel_red_spr = graphics_engine->CreateSprite1();
	pixel_red_spr->SetImage(CR::AssetList::Red_Pixel);
	pixel_spr = graphics_engine->CreateSprite1();	
	pixel_spr->SetImage(CR::AssetList::Pixel);
	pixel_green_spr = graphics_engine->CreateSprite1();
	pixel_green_spr->SetImage(CR::AssetList::Green_Pixel);


	switch(difficulty_level)
	{
	case 0: // EASY
		difficultyHitModifier  = 1.4f;
		break;
	case 1: // MEDIUM
		difficultyHitModifier = 1;
		break;
	case 2: // BETRAYED
		difficultyHitModifier = .5f;
		break;
	default:
		break;
	}
	m_vflip = false;
}

Projectile::~Projectile()
{
	/* Release Projectile Sprite */
	pixel_spr->Release();
	pixel_red_spr->Release();
	pixel_yellow_spr->Release();
	pixel_black_spr->Release();
	pixel_green_spr->Release();
	projectile_spr->Release();
}

void Projectile::SetTime(float dt)
{
	this->time = dt;
}

void Projectile::setViewTransform(float x, float y)
{
	xViewLoc = x;
	yViewLoc = y;
}

void Projectile::SetWeaponBounds(int dx, int dy)
{
	dx_width = dx;
	dy_height = dy;
}

void Projectile::SetWeaponDamage(int  nDamage)
{
	nAmtDmg = static_cast<int>(nDamage * difficultyHitModifier);

	if(nAmtDmg < 1)
		nAmtDmg = 1;
}

bool Projectile::GetDirection()
{
	return proj_flags.S_DIRECTION;
}

bool Projectile::GetSource()
{
	return proj_flags.S_SOURCE;
}

void Projectile::SetSource(bool bSource)
{
	proj_flags.S_SOURCE = bSource;
}

void Projectile::Update()
{
	//update time

	//check activity state

	//process calculations
	
	//render new graphics

/*	if(delayTimer <= 0)
	{
		if(bIsDeActivateable)
		{
			params->ActiveTime -= params->time;
	
			if(params->ActiveTime <= 0)
				DeActivate();
		}

		params->xLoc += (params->xVel * params->time);
		params->yLoc += (params->yVel * params->time);
	
		if(params->xVel < params->MaxXVel) params->xVel+=params->xAcc;
		if(params->yVel < params->MaxYVel) params->yVel+=params->yAcc;
	}
	else
	{
		delayTimer -= params->time;
	}*/
}

HPTRect &Projectile::GetWeaponBounds()
{
	//finish this/

	return hptrectBounds;
}

ProjectileFlags &Projectile::GetProjectileFlags()
{
	return proj_flags;
}

void Projectile::DeActivate()
{
	proj_flags.S_ACTIVE = false;
}

bool Projectile::IsActive()
{
	return proj_flags.S_ACTIVE;
}

void Projectile::OnGround()
{
	proj_flags.S_ON_GROUND = true;
}

void Projectile::SetActiveTime(float timeActive)
{
	proj_params.timeActive = timeActive;
}

void Projectile::SetDelayTime(float timeDelay)
{
	proj_params.timeDelay = timeDelay;
}

void Projectile::SetDirection(bool bDirection)
{
	proj_flags.S_DIRECTION = bDirection;
}

void Projectile::SetPosition(int x, int y)
{
	proj_params.xLoc = static_cast<float>(x);
	proj_params.yLoc = static_cast<float>(y);
}

void Projectile::SetSprite(int nSet, int nSprite)
{
	if(projectile_spr != 0)
		projectile_spr->SetImage(nSprite);
}

void Projectile::SetSpriteOffset(int nOffset)
{
	this->nOffset = nOffset;
}

void Projectile::SetVelocityVector(float dx, float dy)
{
	proj_params.xVel = dx;
	proj_params.yVel = dy;
}

void Projectile::SetAccelerationVector(float dx, float dy)
{
	proj_params.xAcc = dx;
	proj_params.yAcc = dy;
}

void Projectile::Render()
{
	if(proj_params.timeDelay <= 0)
		if(projectile_spr != 0)
		{
			if(proj_flags.S_DIRECTION)
			{
				projectile_spr->SetPositionAbsalute(static_cast<int>(proj_params.xLoc + nOffset + xViewLoc ), static_cast<int>(proj_params.yLoc + yViewLoc));
				if(m_vflip)
					projectile_spr->RenderVFlip();
				else
					projectile_spr->Render();


				HPTRect &temp = GetWeaponBounds();
				//Calculate Screen Coordinates & Update
//				pixel_spr->SetPositionAbsalute(static_cast<int>(temp.p1.x + nOffset + xViewLoc ), static_cast<int>(temp.p1.y + yViewLoc));
//				pixel_spr->Render();
//				pixel_spr->SetPositionAbsalute(static_cast<int>(temp.p2.x + nOffset +xViewLoc ), static_cast<int>(temp.p2.y + yViewLoc));
//				pixel_spr->Render();
			}
			else
			{
				projectile_spr->SetPositionAbsalute(static_cast<int>(proj_params.xLoc - nOffset + xViewLoc), static_cast<int>(proj_params.yLoc + yViewLoc));
				if(m_vflip)
					projectile_spr->RenderHVFlip();
				else
					projectile_spr->RenderHFlip();

				HPTRect &temp = GetWeaponBounds();
				//Calculate Screen Coordinates & Update
//				pixel_spr->SetPositionAbsalute(static_cast<int>(temp.p1.x - nOffset + xViewLoc ), static_cast<int>(temp.p1.y + yViewLoc));
//				pixel_spr->Render();
//				pixel_spr->SetPositionAbsalute(static_cast<int>(temp.p2.x - nOffset +xViewLoc ), static_cast<int>(temp.p2.y + yViewLoc));
//				pixel_spr->Render();
			}


		}

/*#if defined _DEBUG

	HPTRect &temp00 = GetWeaponBounds();

	//Calculate Screen Coordinates & Update
	for(int i = temp00.p1.x; i <= temp00.p2.x; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(i + xViewLoc), static_cast<int>(temp00.p1.y + yViewLoc));
			pixel_red_spr->Render();
	}

	for(i = temp00.p1.y; i <= temp00.p2.y; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp00.p1.x + xViewLoc), static_cast<int>(i + yViewLoc));
			pixel_red_spr->Render();
	}

	for(i = temp00.p1.y; i <= temp00.p2.y; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp00.p2.x + xViewLoc), static_cast<int>(i + yViewLoc));
			pixel_red_spr->Render();
	}

	for(i = temp00.p1.x; i <= temp00.p2.x; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(i + xViewLoc), static_cast<int>(temp00.p2.y + yViewLoc));
			pixel_red_spr->Render();
	}

	pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp00.p1.x + xViewLoc), static_cast<int>(temp00.p1.y + yViewLoc));
	pixel_red_spr->Render();
	pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp00.p2.x + xViewLoc), static_cast<int>(temp00.p2.y + yViewLoc));
	pixel_red_spr->Render();

#endif*/

//	if(ipFlags.S_ATTACK)
//	{

/*	HPTRect &temp01 = GetWeaponWorldLoc();

	//Calculate Screen Coordinates & Update
	for(i = temp01.p1.x; i <= temp01.p2.x; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(i + xViewLoc), static_cast<int>(temp01.p1.y + yViewLoc));
			pixel_red_spr->Render();
	}

	for(i = temp01.p1.y; i <= temp01.p2.y; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp01.p1.x + xViewLoc), static_cast<int>(i + yViewLoc));
			pixel_red_spr->Render();
	}

	for(i = temp01.p1.y; i <= temp01.p2.y; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp01.p2.x + xViewLoc), static_cast<int>(i + yViewLoc));
			pixel_red_spr->Render();
	}

	for(i = temp01.p1.x; i <= temp01.p2.x; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(i + xViewLoc), static_cast<int>(temp01.p2.y + yViewLoc));
			pixel_red_spr->Render();
	}

	//Calculate Screen Coordinates & Update
	pixel_spr->SetPositionAbsalute(static_cast<int>(temp01.p1.x + xViewLoc), static_cast<int>(temp01.p1.y  + yViewLoc));
	pixel_spr->Render();
	pixel_spr->SetPositionAbsalute(static_cast<int>(temp01.p2.x + xViewLoc), static_cast<int>(temp01.p2.y  + yViewLoc));
	pixel_spr->Render();*/
//	}


}
