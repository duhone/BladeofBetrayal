// EnemyFlyingSentryA.cpp: implementation of the EnemyFlyingSentryA class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyFlyingSentryA.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyFlyingSentryA::EnemyFlyingSentryA(Level *curLevel)
{
	SetRenderOffset(0);

	SetCurLife(3);
	SetNumLifeBars((int)(3 * .2f + 1));

	walkAcceleration = 4.0; // Pixels Per Second Per Second
	maxWalkSpeed = 20.00;    // Pixels Per Second	

	ipFlags.S_NO_GRAVITY = true;

	velMovement = 0;
	velYModifier =0;

	level_class = curLevel;

	rectDX = 15;
	rectDY = 15;
	rectXOffset = -8;
	rectYOffset = -10;
	HPTSprite1 *temps;
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::sentry_bullet);
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::laser::ID);

}

EnemyFlyingSentryA::~EnemyFlyingSentryA()
{

}

/*HPTRect &EnemyFlyingSentryA::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyFlyingSentryA::processDeath()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_FLYING_SENTRY_A_ANIM_DEATH, 0, true, true, 10, true);
	
//	soundPlayer->PlaySound(explode02);
}

/*void EnemyFlyingSentryA::processLeft()
{
	SetAnimation(ENEMY_FLYING_SENTRY_A_ANIM_MOVE, 0, true, false, 10, true);

	//Accelerate Left Velocity
	velMovement -= walkAcceleration;
	if(velMovement < -maxWalkSpeed)
		velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyFlyingSentryA::processRight()
{
	SetAnimation(ENEMY_FLYING_SENTRY_A_ANIM_MOVE, 0, true, false, 10, true);

	//Accelerate Right Velocity
	velMovement += walkAcceleration;
	if(velMovement >= maxWalkSpeed)
		velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}*/

void EnemyFlyingSentryA::processUp()
{
//	if (!S_UP_DOWN && ipFlags.S_ACTIVE) soundPlayer->PlaySound(electronic);
	SetAnimation(ENEMY_FLYING_SENTRY_A_ANIM_MOVE, 0, true, false, 0, false);

	//Accelerate Up Velocity
//	velYModifier -= walkAcceleration;
//	if(velYModifier <= -maxWalkSpeed)
		velYModifier = -maxWalkSpeed;

	S_UP_DOWN = true;
}

void EnemyFlyingSentryA::processDown()
{
//	if (S_UP_DOWN && ipFlags.S_ACTIVE) soundPlayer->PlaySound(electronic);
	SetAnimation(ENEMY_FLYING_SENTRY_A_ANIM_MOVE, 0, true, false, 0, false);

	//Accelerate Down Velocity
//	velYModifier += walkAcceleration;
//	if(velYModifier >= maxWalkSpeed)
		velYModifier = maxWalkSpeed;

	S_UP_DOWN = false;
}

void EnemyFlyingSentryA::processAttack()
{
	if(ipFlags.nCurrAttack == 0)
	{
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser00);
		Projectile *temp;
		temp = new ProjectileSentryBullet(static_cast<int>(xLoc - 10), static_cast<int>(yLoc + 10), -45, 45);
		
		(*projectile_list).push_back(temp);
	}
	else if(ipFlags.nCurrAttack == 1)
	{
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser00);
		Projectile *temp;
		temp = new ProjectileSentryBullet(static_cast<int>(xLoc + 10), static_cast<int>(yLoc + 10), 45, 45);
		
		(*projectile_list).push_back(temp);
	}
	else if(ipFlags.nCurrAttack == 2)
	{
		Projectile *temp;
		temp = new ProjectileSentryBullet(static_cast<int>(xLoc - 10), static_cast<int>(yLoc + 10), -45, 45);
		
		(*projectile_list).push_back(temp);
		
		temp = new ProjectileSentryBullet(static_cast<int>(xLoc + 10), static_cast<int>(yLoc + 10), 45, 45);
		
		(*projectile_list).push_back(temp);
	}	
	m_soundFX->Play();
}

void EnemyFlyingSentryA::processUpdate()
{
//	BelowFeetLadderCheck();

		/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_FLYING_SENTRY_A_ANIM_DEATH) && !player_spr->IsAnimating())
		Die();

	if(!ipFlags.S_DEAD)
	{
//		if(ipFlags.S_ON_GROUND)
///		{
//			velModifier = 0;
//			velYModifier = 0;
//		}
//		else
//		{
//			velYModifier += (gravityConstant * time);
//		}

		// Apply Velocity Modifier
		if(!ipFlags.S_DAMAGED)
		{
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

					case move_up:
						processUp();
						break;

					case move_down:
						processDown();

					default:
						break;
				}
		}
	}

	/* Center (0,0), offset by Render Offset */
//	SetRectangle(rectWorldLoc, 15, 15, -8/*-nOffSet*//*-10*/, -10);
}

void EnemyFlyingSentryA::stop()
{
	velYModifier = 0;
	velMovement = 0;
}

void EnemyFlyingSentryA::processDamage()
{
	ipFlags.S_ATTACK = false;

	SetAnimation(ENEMY_FLYING_SENTRY_A_ANIM_MOVE, 0, true, false, 10, false);

//	velYModifier = -100;
	
//	if(	ipFlags.S_DAMAGED_DIRECTION)
//		velMovement = 40;
//	else
//		velMovement = -40;
}
