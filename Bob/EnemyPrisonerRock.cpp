// EnemyPrisonerRock.cpp: implementation of the EnemyPrisonerRock class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyPrisonerRock.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyPrisonerRock::EnemyPrisonerRock(Level *curLevel)
{
	SetRenderOffset(enemy_ninja_render_offset);

	SetCurLife(3);
//	SetSprite(1, 8);

	level_class = curLevel;	

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	HPTSprite1 *temps;
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::prisoner_rock);
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::knifethrow::ID);

}

EnemyPrisonerRock::~EnemyPrisonerRock()
{
}

/*HPTRect &EnemyPrisonerRock::GetWorldLoc()
{
//	rectWorldLoc.p1.x = static_cast<int>(xLoc - 20 + nOffSet); 
//	rectWorldLoc.p2.x = static_cast<int>(xLoc - 5 + nOffSet);
//	rectWorldLoc.p1.y = static_cast<int>(yLoc - 15);
//	rectWorldLoc.p2.y = static_cast<int>(yLoc + 30);




	return rectWorldLoc;
}*/

void EnemyPrisonerRock::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{
		case 0:
			break;

		case 1: /* Rock Throw */

			SetAnimation(ENEMY_PRISONER_ANIM_THROW, 0, true, true, 20, true);
			m_soundFX->Play();
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);

			Projectile *temp;

			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectilePrisonerRock(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc - 15));
				
			}
			else
			{
				temp = new ProjectilePrisonerRock(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc - 15));
				
			}
			
			(*projectile_list).push_back(temp);

			ipFlags.S_ATTACK = true;
				
			//Stop All Directional Movement
			velMovement = 0;
			velModifier = 0;
			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyPrisonerRock::processDamage()
{
	ipFlags.S_ATTACK = false;

	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);


	SetAnimation(ENEMY_PRISONER_ANIM_DAMAGE, 0, true, false, 10, false);

	velYModifier = -100;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 20;
	else
		velMovement = -20;
}

void EnemyPrisonerRock::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_PRISONER_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyPrisonerRock::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_PRISONER_ANIM_THROW, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_PRISONER_ANIM_THROW, 0, false, false, 22, false);
}

void EnemyPrisonerRock::processUpdate()
{
//	BelowFeetLadderCheck();

	if(ipFlags.S_ON_GROUND)
	{
		velModifier = 0;
		velYModifier = 0;
	}
	else
	{
//		velYModifier += (gravityConstant * time);
	}

	if((player_spr->GetFrameSet() == ENEMY_PRISONER_ANIM_DEATH)&& !player_spr->IsAnimating())
		Die();

	if(ipFlags.S_ATTACK)
	{
		if((player_spr->GetFrameSet() == ENEMY_PRISONER_ANIM_THROW) && !player_spr->IsAnimating())
			ipFlags.S_ATTACK = false;
	}

	//Transition Movement State
//	TransitionMovement(ipFlags.CurMState);

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