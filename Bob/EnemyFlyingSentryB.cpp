// EnemyFlyingSentryB.cpp: implementation of the EnemyFlyingSentryB class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyFlyingSentryB.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyFlyingSentryB::EnemyFlyingSentryB(Level *curLevel)
{
	SetRenderOffset(-3);

	SetCurLife(3);
	SetNumLifeBars((int)(3 * .2f + 1));

	walkAcceleration = 10.0; // Pixels Per Second Per Second
	maxWalkSpeed = 30.00;   // Pixels Per Second
	
	ipFlags.S_NO_GRAVITY = true;

	level_class = curLevel;

	ipFlags.S_RENDER_DIRECTION = false;	

	rectDX = 20;
	rectDY = 20;
	rectXOffset = -nOffSet-10;
	rectYOffset = -10;
	HPTSprite1 *temps;
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::sentry_bullet);
	
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::laser::ID);
}

EnemyFlyingSentryB::~EnemyFlyingSentryB()
{

}

/*HPTRect &EnemyFlyingSentryB::GetWorldLoc()
{

	return rectWorldLoc;
}*/
void EnemyFlyingSentryB::processDeath()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_FLYING_SENTRY_B_ANIM_DEATH, 0, true, true, 10, true);
	
//	soundPlayer->PlaySound(explode02);
}


void EnemyFlyingSentryB::processLeft()
{
	SetAnimation(ENEMY_FLYING_SENTRY_B_ANIM_MOVE, 0, true, false, .2f, false);
//	if (ipFlags.S_DIRECTION && ipFlags.S_ACTIVE) soundPlayer->PlaySound(electronic);
	//Accelerate Left Velocity
//	velMovement -= walkAcceleration;
//	if(velMovement < -maxWalkSpeed)
		velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyFlyingSentryB::processRight()
{

	SetAnimation(ENEMY_FLYING_SENTRY_B_ANIM_MOVE, 0, true, false, .2f, false);
//	if (!ipFlags.S_DIRECTION && ipFlags.S_ACTIVE) soundPlayer->PlaySound(electronic);
	//Accelerate Right Velocity
//	velMovement += walkAcceleration;
//	if(velMovement > maxWalkSpeed)
		velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

/*void EnemyFlyingSentryB::processUp()
{
	SetAnimation(ENEMY_FLYING_SENTRY_B_ANIM_MOVE, 0, true, false, 10, true);

	//Accelerate Up Velocity
	velYModifier -= walkAcceleration;
	if(velYModifier <= -maxWalkSpeed)
		velYModifier = -maxWalkSpeed;
}

void EnemyFlyingSentryB::processDown()
{
	SetAnimation(ENEMY_FLYING_SENTRY_B_ANIM_MOVE, 0, true, false, 10, true);

	//Accelerate Down Velocity
	velYModifier += walkAcceleration;
	if(velYModifier >= maxWalkSpeed)
		velYModifier = maxWalkSpeed;
}*/

void EnemyFlyingSentryB::processAttack()
{
	if(ipFlags.S_DIRECTION)
	{	Projectile *temp;
		temp = new ProjectileSentryBullet(static_cast<int>(xLoc + 15), static_cast<int>(yLoc+3), 80, 0);
		
		(*projectile_list).push_back(temp);
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser01);
	}
	else
	{	Projectile *temp;
		temp = new ProjectileSentryBullet(static_cast<int>(xLoc - 15), static_cast<int>(yLoc+3), -80, 0);
		
		(*projectile_list).push_back(temp);
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser01);
	}
	m_soundFX->Play();
}

void EnemyFlyingSentryB::processUpdate()
{
//	BelowFeetLadderCheck();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_FLYING_SENTRY_B_ANIM_DEATH) && !player_spr->IsAnimating())
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
//	SetRectangle(rectWorldLoc, 20, 20, -nOffSet-10, -10);
}

void EnemyFlyingSentryB::stop()
{
	velYModifier = 0;
	velMovement = 0;
}

void EnemyFlyingSentryB::processDamage()
{
	ipFlags.S_ATTACK = false;

	SetAnimation(ENEMY_FLYING_SENTRY_B_ANIM_MOVE, 0, true, false, 10, false);
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}
