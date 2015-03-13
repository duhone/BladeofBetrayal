// EnemyGMonsterSpit.cpp: implementation of the EnemyGMonsterSpit class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyGMonsterSpit.h"
#include "ProjectileAGMSpit.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyGMonsterSpit::EnemyGMonsterSpit(Level *curLevel,IPlayer *_player)
{
	InitEnemy(base_enemy_type_3, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .4f,
			  0,
			  true);
	
	level_class = curLevel;	
	
	//SetCurLife(9);
	//SetNumLifeBars(2);

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;

	m_player = _player;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::firedeath::ID);
}

EnemyGMonsterSpit::~EnemyGMonsterSpit()
{

}

/*HPTRect &EnemyGMonsterSpit::GetWorldLoc()
{


	return rectWorldLoc;
}
*/
void EnemyGMonsterSpit::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);

		ipFlags.S_ATTACK = true;

		SetAnimation(ENEMY_SPIT_MONSTER_ATTACK, 0, true, true, 10, true);

			Projectile *temp;


			/* Create Ninja Star Projectile */
			if(ipFlags.S_DIRECTION)
			{
				//temp = new ProjectileGMonsterSpit(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 5), static_cast<int>(yLoc));
				//temp = new ProjectileAGMSpit(false, static_cast<int>(xLoc-20 + nOffSet), static_cast<int>(yLoc - 15),*projectile_list,m_player->GetXLoc());
				temp = new ProjectileAGMSpit(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 20), static_cast<int>(yLoc+15),*projectile_list,m_player->GetXLoc());
				temp->SetWeaponDamage(5);
			}
			else 
			{
				//temp = new ProjectileGMonsterSpit(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 5), static_cast<int>(yLoc));
				//temp = new ProjectileAGMSpit(false, static_cast<int>(xLoc-20 + nOffSet), static_cast<int>(yLoc - 15),*projectile_list,m_player->GetXLoc());
				temp = new ProjectileAGMSpit(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 20), static_cast<int>(yLoc+15),*projectile_list,m_player->GetXLoc());
				temp->SetWeaponDamage(5);				
			}
			(*projectile_list).push_back(temp);
	}
}

void EnemyGMonsterSpit::processDamage()
{	
	ipFlags.S_ATTACK = false;

//	velYModifier = -100;
	if(ipFlags.S_DAMAGED_DIRECTION) velMovement = 20;
	else velMovement = -20;
	
	/* Set Damage Animation */
	SetAnimation(0 /*ENEMY_FIRE_MONSTER_DAMAGE */, 0, true, false, 10, false);

}

void EnemyGMonsterSpit::processDeath()
{
	m_soundFX->Play();
//soundPlayer->PlaySound(firedeath);

	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_SPIT_MONSTER_DEATH, 0, true, true, 10, true);
}

void EnemyGMonsterSpit::stop()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Frame 0 of Attack Animation */
	if(ipFlags.PrevMState != move_stop) SetAnimation(ENEMY_SPIT_MONSTER_ATTACK, 0, false, false, 15, true);
	else SetAnimation(ENEMY_SPIT_MONSTER_ATTACK, 0, false, false, 15, false);
}

void EnemyGMonsterSpit::processUpdate()
{
//	BelowFeetLadderCheck();

	/* Stop All Directional Movement */
	if(!ipFlags.S_ON_GROUND) ApplyGravity();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_SPIT_MONSTER_DEATH) && !player_spr->IsAnimating())
		Die();

	/* Check for end of an attack state */
	if(ipFlags.S_ATTACK)
		if((player_spr->GetFrameSet() == ENEMY_SPIT_MONSTER_ATTACK) && !player_spr->IsAnimating())
		{
			SetAnimation(ENEMY_FIRE_MONSTER_ATTACK, 0, false, false, 0, true);
			ipFlags.S_ATTACK = false;
		}
	
	if(!ipFlags.S_DAMAGED && !ipFlags.S_ATTACK)
		switch(ipFlags.CurMState)
		{
			case move_stop:
				stop();
				break;

			default:
				break;
		}
		
	/* Center (0,0), offset by Render Offset */
//	SetRectangle(rectWorldLoc, 15, 45, -nOffSet, -15);
}