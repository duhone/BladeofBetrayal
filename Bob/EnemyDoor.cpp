// EnemyDoor.cpp: implementation of the EnemyDoor class.
//
//////////////////////////////////////////////////////////////////////

#include "EnemyDoor.h"
#include "Game.h"
#include "TutorialManager.h"

extern Game* game_class;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyDoor::EnemyDoor(Level *curLevel,int arg,Object** obj,Object** obj1,Object** obj2,unsigned char *ld)
{
	level_data = ld;
	SetRenderHealthBar(false);
	ipFlags.S_NO_GRAVITY = true;
	level_class = curLevel;
	nOffSet = 0;
	nyOffSet = 32;
	rectDX = 32;
	rectDY = 48;
	rectXOffset = 0;
	rectYOffset = 0;
	isDead = false;
	type = arg;
	this->SetCurLife(1);
	take_all_damage = false;
	for(int count = 0;count < 12;count++)
	{
		damage_resistance[count] = 10;
	}
	/*switch(type)
	{
	case 0:
		damage_resistance[1] = 0;
		break;
	case 1:
		damage_resistance[2] = 0;
		break;
	case 2:
		damage_resistance[3] = 0;
		break;
	case 3:
		damage_resistance[4] = 0;
		break;
	case 4:
		damage_resistance[5] = 0;
		break;

	};*/
	object = obj;
	object1 = obj1;
	object2 = obj2;
	ipFlags.door = true;
	
}

EnemyDoor::~EnemyDoor()
{

}

HPTRect &EnemyDoor::GetWeaponWorldLoc()
{
	SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyDoor::processUpdate()
{
	if(!player_spr->IsAnimating() && isDead && ipFlags.S_VISIBLE)
	{
		ipFlags.S_VISIBLE = false;
		ipFlags.S_ATTACK = false;
		
		delete (*object);
		(*object) = NULL;
		delete (*object1);
		(*object1) = NULL;
		delete (*object2);
		(*object2) = NULL;
		
		(*(level_data-1)) = 0;
		(*(level_data+1)) = 0;
	}
}

void EnemyDoor::processDeath()
{

	SetAnimation(type, 0, true, true, 8, true);
	//ipFlags.S_DEAD = true;
	isDead = true;
}

void EnemyDoor::doDoor(int type)
{
	//ipFlags.fInvulnerableTimer = 1000;

	//ipFlags.S_INVULNERABLE = true;
	ipFlags.door = true;

	if(type >= 3)
		type += 1;
	if(isDead)
		return;
	if(this->type == (type-1))
	{
		SetCurLife(-1);
		ipFlags.door = false;
	}
	else
	{
		if(game_class->player->IsWeaponAvailable(type+1))
			TutorialManager::Instance().Trigger(TutorialManager::TDOOR2);
		else
			TutorialManager::Instance().Trigger(TutorialManager::TDOOR);
	}
}

bool EnemyDoor::forceOpenDoor()
{
	doDoor(this->type+1);
	
	return true;
}

void EnemyDoor::SetSprite(int nSet, int nSprite)
{
	Enemy::SetSprite(nSet,nSprite);
	
	SetAnimation(type, 0, false, false, 8, true);
}

