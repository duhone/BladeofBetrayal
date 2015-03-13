// EnemyBlueNinja.cpp: implementation of the EnemyBlueNinja class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyBlueNinja.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyBlueNinja::EnemyBlueNinja(Level *curLevel)
{
	InitEnemy(base_enemy_type_2, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .25,
			  0,
			  true);

	level_class = curLevel;

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	HPTSprite1 *temps;
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::ninja_star);

}

EnemyBlueNinja::~EnemyBlueNinja()
{
}

//HPTRect &EnemyBlueNinja::GetWorldLoc()
//{
	/* Center (0,0), offset by Render Offset */
	

//	return rectWorldLoc;
//}

HPTRect &EnemyBlueNinja::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_BLUE_NINJA_ANIM_SWORD_ATTACK) && (player_spr->GetFrame() == 4))	
	{
		SetWeaponDamage(2);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, 2);//, ipFlags.S_DIRECTION);
	}
	else if((player_spr->GetFrameSet() == ENEMY_BLUE_NINJA_ANIM_SWORD_ATTACK) && (player_spr->GetFrame() == 5))	
	{
		SetWeaponDamage(2);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, -2);//, ipFlags.S_DIRECTION);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyBlueNinja::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)	SetAnimation(ENEMY_BLUE_NINJA_ANIM_MOVE, 0, true, false, 22, true);
	else SetAnimation(ENEMY_BLUE_NINJA_ANIM_MOVE, 0, true, false, 22, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyBlueNinja::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right) SetAnimation(ENEMY_BLUE_NINJA_ANIM_MOVE, 0, true, false, 22, true);
	else SetAnimation(ENEMY_BLUE_NINJA_ANIM_MOVE, 0, true, false, 22, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyBlueNinja::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{
			Projectile *temp;
		
		case 0:

			if(!SetAnimation(ENEMY_BLUE_NINJA_ANIM_SWORD_ATTACK, 0, true, true, 30, false))
			{
//				if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);
				StopMovement();
			}
			break;

		case 1:

//			OutputDebugString("Blue: Ninja Star - Throw");
			SetAnimation(ENEMY_BLUE_NINJA_ANIM_STAR_ATTACK, 0, true, true, 20, false);
			
			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileNinjaStar(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc - 15));
			}
			else
			{
				temp = new ProjectileNinjaStar(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc - 15));
			}
			
			(*projectile_list).push_back(temp);
			
			StopMovement();
				
//			if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);
			ipFlags.S_ATTACK = true;
			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyBlueNinja::processDamage()
{
	ipFlags.S_ATTACK = false;

	SetAnimation(ENEMY_BLUE_NINJA_ANIM_DAMAGE, 0, true, false, 10, false);
	
	if(	ipFlags.S_DAMAGED_DIRECTION) velMovement = 60;
	else velMovement = -60;	
	
	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
}

void EnemyBlueNinja::processDeath()
{
	StopMovement();

	SetAnimation(ENEMY_BLUE_NINJA_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyBlueNinja::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)	SetAnimation(ENEMY_BLUE_NINJA_ANIM_MOVE, 0, false, false, 15, true);
	else SetAnimation(ENEMY_BLUE_NINJA_ANIM_MOVE, 0, false, false, 15, false);
}

void EnemyBlueNinja::processUpdate()
{
//	BelowFeetLadderCheck();

	if((player_spr->GetFrameSet() == ENEMY_BLUE_NINJA_ANIM_DEATH)&& !player_spr->IsAnimating())
		Die();

	if(ipFlags.S_ATTACK)
	{
		if(!player_spr->IsAnimating())
			ipFlags.S_ATTACK = false;
	}

	// Apply Velocity Modifier
	if(!ipFlags.S_DAMAGED)
	{
		if(!ipFlags.S_ATTACK)
			switch(ipFlags.CurMState)
			{
				case move_stop:
					stop();
					break;

				case move_left:
					processLeft();
					break;

				case move_right:
					processRight();
					break;

				default:
					break;
			}
	}
}
