// Enemy.cpp: implementation of the Enemy class.
//
//////////////////////////////////////////////////////////////////////


#include "Enemy.h"
#include "game.h"
extern Game* game_class;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Enemy::Enemy():xViewLoc(0), yViewLoc(0)
{
//	this->curLevel = curLevel;

	SetMaxAttacks(5);

	SetCurLife(enemy_blue_ninja_set_cur_life);
	SetNumLifeBars((int)(enemy_blue_ninja_set_cur_life * .2f + 1));
	SetDamageTimer(.5);

	introtimer = 3;

	m_rangeExtra = (rand()%6)*16;
	m_rangeExtra *= m_rangeExtra;

}

Enemy::~Enemy()
{ 

}

void Enemy::InitEnemy(int nHitPoints, int nMaxXVelocity, int nMaxYVelocity, float nMaxXAcceleration, float nRecoveryTime, int nPointValue, bool bRenderHBar)
{
	SetWeaponDamage(0);

	SetCurLife(nHitPoints);
	SetNumLifeBars(static_cast<int>(nHitPoints * .20));

	if(GetNumLifeBars() <= 0)
		SetNumLifeBars(1);

	SetWalkAcceleration(nMaxXAcceleration);
	SetMaxWalkVelocity(static_cast<float>(nMaxXVelocity));
//	SetMaxJumpVelocity(nMaxYVelocity);
	SetDamageTimer(nRecoveryTime);
	SetEnergyLevel(0);
	SetExtraLives(0);
//	SetMaxClimbVelocity(0);

	SetRenderHealthBar(bRenderHBar);
}

void Enemy::setViewTransform(float x, float y)
{
//	level_class = 0;
	xViewLoc = x;
	yViewLoc = y;
}

void Enemy::BelowFeetLadderCheck()
{
		/* Check for Back Ladder OR Rope Block Below (When NOT Jumping) */
	if(!ipFlags.S_JUMP)
	{
		/* check for noncollidable ground tile */
		if(level_class != 0)
		{
			if((level_class->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBLADDER) ||
			   (level_class->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBROPE) ||
			   (level_class->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBBLOCKRIGHT) ||
			   (level_class->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBBLOCKLEFT))
				ipFlags.S_NO_GRAVITY = true;
			/* reset gravity if BACK on the 'collidable' ground */
			else
			{
				ipFlags.S_NO_GRAVITY = false;
			}
		}
	}
}

void Enemy::Render()
{
	HPTRect hptRectTemp = level_class->GetWorldBounds();

	if(xLoc < (hptRectTemp.p1.x - 240)) xLoc = static_cast<float>(hptRectTemp.p1.x - 240);
	else if(xLoc > (hptRectTemp.p2.x + 240)) xLoc = static_cast<float>(hptRectTemp.p2.x + 240);

	if(yLoc < (hptRectTemp.p1.y - 160)) yLoc = static_cast<float>(hptRectTemp.p1.y - 160);
	else if(yLoc > (hptRectTemp.p2.y + 160)) yLoc = static_cast<float>(hptRectTemp.p2.y + 160);

	if(ipFlags.S_DAMAGED && !ipFlags.S_PROCESS_DEATH && ipFlags.S_RENDER_FLASH)
	{
		flashtimer -= time;

		if(flashtimer < 0)
		{
			flashtimer = .04f;
			ipFlags.S_RENDER = !ipFlags.S_RENDER;
		}
	}
	else
	{
		ipFlags.S_RENDER = true;
	}

	if(ipFlags.S_RENDER)
	{
		if(ipFlags.S_VISIBLE)
		{
			if(ipFlags.S_RENDER_DIRECTION)
			{
				if(ipFlags.S_DIRECTION)
				{
					//Calculate Screen Coordinates & Update
					player_spr->SetPositionAbsalute((xLoc + xViewLoc + nOffSet), (yLoc + yViewLoc + nyOffSet));
					player_spr->Render();
				}
				else
				{
					//Calculate Screen Coordinates & Update
					player_spr->SetPositionAbsalute((xLoc + xViewLoc - nOffSet), (yLoc + yViewLoc + nyOffSet));
					player_spr->RenderHFlip();
				}
			}
			else
			{
				if(!ipFlags.S_DIRECTION)
				{
					//Calculate Screen Coordinates & Update
					player_spr->SetPositionAbsalute((xLoc + xViewLoc + nOffSet), (yLoc + yViewLoc + nyOffSet));
					player_spr->Render();
				}
				else
				{
					//Calculate Screen Coordinates & Update
					player_spr->SetPositionAbsalute((xLoc + xViewLoc - nOffSet), (yLoc + yViewLoc + nyOffSet));
					player_spr->RenderHFlip();
		
				}
			}
		}
		
		//if(ipFlags.S_RENDER_HEALTH_BAR)
		//	RenderHealthBar();
	}

//#if defined _DEBUG


	if(ipFlags.S_ACTIVE)
	{
	/*for(int z = 0; z < 480; z++)
	{
		pixel_red_spr->SetPositionAbsalute(static_cast<int>(xLoc + xViewLoc), static_cast<int>(z));
		pixel_red_spr->Render();
	}

	for(int z = 0; z < 320; z++)
	{
		pixel_red_spr->SetPositionAbsalute(static_cast<int>(z), static_cast<int>(yLoc + yViewLoc));
		pixel_red_spr->Render();
	}*/
	}

	/*HPTRect &temp00 = GetWorldLoc();

	//Calculate Screen Coordinates & Update
	for(int i = temp00.p1.x; i <= temp00.p2.x; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(i + xViewLoc), static_cast<int>(temp00.p1.y + yViewLoc));
			pixel_spr->Render();
	}

	for(int i = temp00.p1.y; i <= temp00.p2.y; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(temp00.p1.x + xViewLoc), static_cast<int>(i + yViewLoc));
			pixel_spr->Render();
	}

	for(int i = temp00.p1.y; i <= temp00.p2.y; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(temp00.p2.x + xViewLoc), static_cast<int>(i + yViewLoc));
			pixel_spr->Render();
	}

	for(int i = temp00.p1.x; i <= temp00.p2.x; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(i + xViewLoc), static_cast<int>(temp00.p2.y + yViewLoc));
			pixel_spr->Render();
	}*/
/*
	pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp00.p1.x + xViewLoc), static_cast<int>(temp00.p1.y + yViewLoc));
	pixel_red_spr->Render();
	pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp00.p2.x + xViewLoc), static_cast<int>(temp00.p2.y + yViewLoc));
	pixel_red_spr->Render();
*/
	if((ipFlags.S_ATTACK || ipFlags.S_ALWAYS_ATTACK) && ipFlags.S_VISIBLE)
	{

		/*
	HPTRect &temp01 = GetWeaponWorldLoc();

	//Calculate Screen Coordinates & Update
	for(int i = temp01.p1.x; i <= temp01.p2.x; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(i + xViewLoc), static_cast<int>(temp01.p1.y + yViewLoc));
			pixel_spr->Render();
	}

	for(int i = temp01.p1.y; i <= temp01.p2.y; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(temp01.p1.x + xViewLoc), static_cast<int>(i + yViewLoc));
			pixel_spr->Render();
	}

	for(int i = temp01.p1.y; i <= temp01.p2.y; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(temp01.p2.x + xViewLoc), static_cast<int>(i + yViewLoc));
			pixel_spr->Render();
	}

	for(int i = temp01.p1.x; i <= temp01.p2.x; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(i + xViewLoc), static_cast<int>(temp01.p2.y + yViewLoc));
			pixel_spr->Render();
	}*/

	//Calculate Screen Coordinates & Update
	/*pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp01.p1.x + xViewLoc), static_cast<int>(temp01.p1.y  + yViewLoc));
	pixel_red_spr->Render();
	pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp01.p2.x + xViewLoc), static_cast<int>(temp01.p2.y  + yViewLoc));
	pixel_red_spr->Render();*/
	}
//#endif

}

void Enemy::RenderHealthBar()
{

	
	/*if(game_class->GetEnableStatus()) return;
	int x = (int)GetXLoc();// - 15;
	int y = (int)(GetYLoc() - player_spr->GetFrameHeight() * .5f - 3);// (GetTileHeight() * 16) - 3;
	int offSet = (int)(GetNumLifeBars() * 2 * .5f);

	int curLife = GetCurLife();
//	int yellowStart = (curLife * .20)+1;
	int redStart = (int)((curLife * .20f) + 1);
//	int yellowStart = (curLife * .20) * .66;

	for(int i = 0; i <= (GetNumLifeBars() * 2); i++)
	{
		if((i % 2) == 0)
		{
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 1));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 2));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 3));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 4));
			pixel_black_spr->Render();

			continue;
		}

		if(i * .5 < redStart - 1)
		{
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 1));
			pixel_black_spr->Render();
			pixel_red_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 2));
			pixel_red_spr->Render();
			pixel_red_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 3));
			pixel_red_spr->Render();
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 4));
			pixel_black_spr->Render();
		}
		else if(i * .5 < redStart)
		{
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 1));
			pixel_black_spr->Render();
			pixel_yellow_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 2));
			pixel_yellow_spr->Render();
			pixel_yellow_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 3));
			pixel_yellow_spr->Render();
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 4));
			pixel_black_spr->Render();
		}
		else
		{
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 1));
			pixel_black_spr->Render();
			pixel_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 2));
			pixel_spr->Render();
			pixel_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 3));
			pixel_spr->Render();
			pixel_black_spr->SetPositionAbsalute((x + i + xViewLoc - offSet), (y + yViewLoc + 4));
			pixel_black_spr->Render();
		}
	}*/
}