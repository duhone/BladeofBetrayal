// ProjectileGrenadeAttack.cpp: implementation of the ProjectileGrenadeAttack class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileGrenadeAttack.h"
#include "ProjectileGrenadeFlak.h"
#include<math.h>
#include<stdlib.h>

#include "../Engines/Input/input_engine.h"

using namespace std;
using namespace CR::Sound;

extern void NEW(void *arg);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileGrenadeAttack::ProjectileGrenadeAttack(bool bDirection, int xPos, int yPos,list<Projectile*> *projectile_list)
{
	/* Set Sprite Number */
	SetSprite(0, CR::AssetList::Spencer_Grenade_Attack);



	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
//	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
//	SetActiveTime(4);
	SetDelayTime(.45f);

	proj_flags.S_DIRECTION = bDirection;

	/* Set Velocity Direction */
	if(bDirection) SetVelocityVector(180, -140);
	else SetVelocityVector(-180, -140);

	/* Set Acceleration Vector */
	SetAccelerationVector(0, 680);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	SetSource(true);
//	proj_flags.S_NON_PROJECTILE = ;

	/* Set Damage Value */
	SetWeaponDamage(6);

	this->projectile_list = projectile_list;

	IS_EXPLODING = false;
	
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 15, true);

	weapon_type = 11;
	m_sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::explosion::ID);

}

ProjectileGrenadeAttack::~ProjectileGrenadeAttack()
{
}

HPTRect &ProjectileGrenadeAttack::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileGrenadeAttack::Explode()
{
	m_sound->Play();
	//soundPlayer->PlaySound(explode02);
	/* Set Sprite Number */
	SetSprite(0, CR::AssetList::Spencer_Grenade_Explosion);
	//HPTGetInputEngine()->Rumble(HPT_RUMBLE_LOW);
	/* Initialize Sprite */
	SetAnimation(0, 0, true, true, 8, true);

	SetVelocityVector(0, 0);

	/* Set Acceleration Vector */
	SetAccelerationVector(0, 0);

	/* Spawn Flak Objects */
	for(int i = 0; i < 8; i++)
	{
		Projectile *temp;
		
	//	if(proj_flags.S_DIRECTION)
	//		temp = new ProjectileGrenadeFlak(static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc), rand()%200, rand()%150 - 200, 0, 5);
	//	else
			temp = new ProjectileGrenadeFlak(static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc),(float)( rand()%200 - 100),(float)(rand()%200 - 200), 0, 100);
			

		(*projectile_list).push_back(temp);
	}

//	proj_flags.S_ACTIVE = false;

	IS_EXPLODING = true;
}

void ProjectileGrenadeAttack::DeActivate()
{
	if(!IS_EXPLODING)
		Explode();
}

void ProjectileGrenadeAttack::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		if(IS_EXPLODING && (projectile_spr->GetFrame() == 6))
			proj_flags.S_ACTIVE = false;

		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);
	
		if(proj_params.xVel < proj_params.MaxXVel) proj_params.xVel+=proj_params.xAcc*time;
		if(proj_params.yVel < proj_params.MaxYVel) proj_params.yVel+=proj_params.yAcc*time;
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}