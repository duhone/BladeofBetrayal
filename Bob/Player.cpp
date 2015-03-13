// Player.cpp: implementation of the Player class.
//
//////////////////////////////////////////////////////////////////////


#include "Player.h"
#include "game.h"
#include "ProjectileStephPistol.h"
#include "ProjectileStephRifle.h"
#include "Sound.h"
#include "AssetListNew.h"
#include "TutorialManager.h"
#include "AppConfig.h"

using namespace std;
using namespace CR::Sound;
extern Game* game_class;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int CollidableBlocks[] = {
 BASICBLOCK,
 DESTROYABLEBLOCK,
 CONVEYORBLOCKLEFT ,
 CONVEYORBLOCKRIGHT,
 NONTOPBASICBLOCK,
 SMALLHEALTH,
 LARGEHEALTH,
 FREELIFE,
 SMALLENERGY,
 LARGEENERGY,
ATTACK1NKEY,
ATTACK1BKEY,
ATTACK1OKEY,
ATTACK1GKEY,
ATTACK1RKEY,
ATTACK2NKEY,
ATTACK2BKEY,
ATTACK2OKEY,
ATTACK2GKEY,
ATTACK2RKEY,
ATTACK3NKEY,
ATTACK3BKEY,
ATTACK3OKEY,
ATTACK3GKEY,
ATTACK3RKEY,
ATTACK4NKEY,
ATTACK4BKEY,
ATTACK4OKEY,
ATTACK4GKEY,
ATTACK4RKEY,
HEALTHUPGRADENKEY,
HEALTHUPGRADEBKEY,
HEALTHUPGRADEOKEY,
HEALTHUPGRADEGKEY,
HEALTHUPGRADERKEY,
ENERGYUPGRADENKEY,
ENERGYUPGRADEBKEY,
ENERGYUPGRADEOKEY,
ENERGYUPGRADEGKEY,
ENERGYUPGRADERKEY
}; 

int NonCollidableBlocks[] = {
 0,
 BOUNCEBLOCK, 
 NONSIDEBASICBLOCK,
 CLIMBBLOCKLEFT, 
 CLIMBBLOCKRIGHT,
 CLIMBLADDER,
 CLIMBROPE,
 ENDLEVEL,
 FIREBLOCK
};

int ClimbBlocks[] = {
 CLIMBBLOCKLEFT, 
 CLIMBBLOCKRIGHT,
 CLIMBLADDER,
 CLIMBROPE
};

Player::Player():xWorldOffset(0),yWorldOffset(0), steph(false)
{
	number_grenades = 0;
	memset(weapons,0,7);
	weapons[0] = true;
/*CollidableBlocks[0] = BASICBLOCK;
CollidableBlocks[1] =  DESTROYABLEBLOCK;
 CollidableBlocks[2] = CONVEYORBLOCKLEFT ;
 CollidableBlocks[3] = CONVEYORBLOCKRIGHT;
 CollidableBlocks[4] = NONTOPBASICBLOCK;
 CollidableBlocks[5] = SMALLHEALTH;
 CollidableBlocks[6] = LARGEHEALTH;
 CollidableBlocks[7] = FREELIFE;
 CollidableBlocks[8] = SMALLENERGY;
 CollidableBlocks[9] = LARGEENERGY;
 CollidableBlocks[10] = ATTACK1;
 CollidableBlocks[11] = ATTACK2;
 CollidableBlocks[12] = ATTACK3;
 CollidableBlocks[13] = ATTACK4;
 CollidableBlocks[14] = ATTACK5;
 CollidableBlocks[15] = HEALTHUPGRADE;
 CollidableBlocks[16] = ENERGYUPGRADE;*/


 NonCollidableBlocks[0] =  0;
 NonCollidableBlocks[1] = BOUNCEBLOCK;
 NonCollidableBlocks[2] = NONSIDEBASICBLOCK;
 NonCollidableBlocks[3] = CLIMBBLOCKLEFT; 
 NonCollidableBlocks[4] = CLIMBBLOCKRIGHT;
 NonCollidableBlocks[5] = CLIMBLADDER;
 NonCollidableBlocks[6] = CLIMBROPE;
 NonCollidableBlocks[7] = ENDLEVEL;
 NonCollidableBlocks[8] = FIREBLOCK;


ClimbBlocks[0] =  CLIMBBLOCKLEFT;
ClimbBlocks[1] =   CLIMBBLOCKRIGHT;
ClimbBlocks[2] =   CLIMBLADDER;
 ClimbBlocks[3] =  CLIMBROPE;
	
	S_JACOB_INVIS = false;

	bubbletimer = static_cast<float>(rand()%2);

	basic_weapon_damage_amount = 3;
	xQuakeAttackModifier = 0;
	yQuakeAttackModifier = 0;

	deathtimer = 2.5;

	attacks[0] = 0;
	attacks[1] = 1;
	attacks[2] = 2;
	attacks[3] = 3;
	attacks[4] = 4;
	attacks[5] = 5;

	nCurLife = MaxLife;

	//Create Spencer Sprite
	player_spr = graphics_engine->CreateSprite1();	
	player_spr->SetImage(spencer_sprite);
	blades_sprite = graphics_engine->CreateSprite1();	
	blades_sprite->SetImage(CR::AssetList::Spencer_Blades);
	bladescrouch_sprite = graphics_engine->CreateSprite1();	
	bladescrouch_sprite->SetImage(CR::AssetList::blade_set_crouch);
	steph_top = NULL;//graphics_engine->CreateSprite1();	
	//steph_top->SetImage(182);
	
/*	gashelm_spr = graphics_engine->CreateSprite1();
	gashelm_spr->SetImage(71);
*/
	// Acceleration Constants -- Used for calculation during update
	walkAcceleration = 20.0; // Pixels Per Second Per Second
	maxWalkSpeed = 90.00;   // Pixels Per Second	
	climbVelocity = 72.0;
	jumpMaxVelocity = -185.0;
	MaxYVelocity = 14.0;
	MaxPixelDisplacement = 14.0; // Pixels Per Frame

	ipFlags.S_IS_PLAYER = true;
	ipFlags.S_PROCESS_DEATH = false;

	S_ROPE_PULL = false;

	underWaterTimer = 10;

	S_BARRIER_SHIELD = false;
	nBarrierOrbs = 0;

	SetDifficultyLevel(1); //Set Normal Difficutly Default

	for(int i = 0; i < 4; i++)
	{
		bshield_spr[i] = graphics_engine->CreateSprite1();
		bshield_spr[i]->SetImage(CR::AssetList::Barrier_Shield);
		bshield_spr[i]->SetFrame(i*4);
		bshield_spr[i]->SetAutoAnimate(true);
		bshield_spr[i]->SetFrameRate(15);
	}

	quaketimer = 9;

	analog_mod_x = 0;

	analog_mod_y = 0;

	HPTSprite1 *temps;
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::Electric_Spike);
	hold_sprites.push_back(temps);
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::Flame_Attack);
	hold_sprites.push_back(temps);
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::Spencer_Projectile_Attack);
	hold_sprites.push_back(temps);
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::Spencer_Grenade_Attack);
	hold_sprites.push_back(temps);
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::Spencer_Grenade_Explosion);
	hold_sprites.push_back(temps);
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::Spencer_Grenade_Flak);
	hold_sprites.push_back(temps);
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::Bubbles);
	hold_sprites.push_back(temps);
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::Barrier_Shield);
	hold_sprites.push_back(temps);

	inBossBattle = false;
	bossUsedOnlyBasicAttack = false;
	bossNoDamageTaken = false;

	m_swingSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::swing::ID);
	m_shockSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::shock::ID);
	m_flameSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::flame::ID);
	m_waveSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::wave::ID);
	m_quakeSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::quake::ID);
	m_splashSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::watersplash::ID);
	m_jumpSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::jump::ID);

	/*if(AppConfig::Instance().IsIpad())
	{
		graphics_engine->CacheTexture(CR::AssetList::SpencerOrange);
		graphics_engine->CacheTexture(CR::AssetList::SpencerRed);
		graphics_engine->CacheTexture(CR::AssetList::SpencerGreen);
		graphics_engine->CacheTexture(CR::AssetList::Player_Spencer);
	}
	else*/
	{
		m_orangeHolder = graphics_engine->CreateSprite1();
		m_orangeHolder->SetImage(CR::AssetList::SpencerOrange);
		m_greenHolder = graphics_engine->CreateSprite1();
		m_greenHolder->SetImage(CR::AssetList::SpencerGreen);
		m_redHolder = graphics_engine->CreateSprite1();
		m_redHolder->SetImage(CR::AssetList::SpencerRed);
		m_playerHolder = graphics_engine->CreateSprite1();
		m_playerHolder->SetImage(CR::AssetList::Player_Spencer);
	}
}

Player::~Player()
{
	blades_sprite->Release();
	bladescrouch_sprite->Release();
	
	//if(!AppConfig::Instance().IsIpad())
	{
		m_orangeHolder->Release();
		m_greenHolder->Release();
		m_redHolder->Release();
		m_playerHolder->Release();
	}
}

void Player::FallingCheck()
{
	if(!ipFlags.S_ON_LADDER && !ipFlags.S_UNDER_WATER)
	{
		float x, y;
	
		GetVelocityVector(&x, &y);

		if(y > 0)
		{
			if(!ipFlags.S_FALLING)
			{
				xFallBegin = GetXTilePos();
				yFallBegin = GetYTilePos();
				ipFlags.S_FALLING = true;
			}
			
			// IF NOT jumping - switch to fall animation
			if(!ipFlags.S_JUMP && ((abs(GetYTilePos() - yFallBegin)) <= 8))
				SetAnimation(PLAYER_ANIM_JUMP, 10, false, false, 0, true);
		
			if((abs(GetYTilePos() - yFallBegin)) > 20)
			{
				if(player_spr->GetFrameSet() != PLAYER_ANIM_LONG_FALL)
				SetAnimation(PLAYER_ANIM_FALL_TRANSITION, 0, true, true, 12, false);

				if((player_spr->GetFrameSet() == PLAYER_ANIM_FALL_TRANSITION))
				{
					if(player_spr->IsAnimating())
						SetAnimation(PLAYER_ANIM_LONG_FALL, 0, true, false, 8, true);
				}
			}

			// Check for Ladder Tile Under Feet && NOT above feet
			if(((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()  ) == CLIMBBLOCKRIGHT)  ||
			    (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()  ) == CLIMBBLOCKLEFT )  ||
				(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()  ) == CLIMBROPE      )  ||
				(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()  ) == CLIMBLADDER)   )  && 
			  !((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) == CLIMBBLOCKRIGHT)  ||
			    (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) == CLIMBBLOCKLEFT )  ||
				(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) == CLIMBROPE      )  ||
				(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) == CLIMBLADDER)   )    )
			{
				//yLoc = static_cast<float>((GetYTilePos() * 16) - 29);
				AddTransformationQueue(0, ((GetYTilePos() * 16) - 29) - yLoc);

				ipFlags.S_NO_GRAVITY = true;	
				ipFlags.S_ON_GROUND = true;
				ipFlags.S_JUMP = false;
				velYJumpModifier = 0;
				velModifier = 0;
				velYModifier = 0;
			}
		}
		else
		{
			if(ipFlags.S_FALLING)
			{
				int temp1 = abs(GetYTilePos() - yFallBegin);

				if(temp1 > 18 && !ipFlags.S_ON_LADDER)
				{
					doDamage(5, ipFlags.S_DIRECTION,0);

					if(temp1 > 28) 
					{
						doDamage(20, ipFlags.S_DIRECTION,0);
//						nCurLife = 0;
///						ipFlags.CurMState = move_0;
//						ipFlags.S_PROCESS_DEATH = true;
//						SetAnimation(PLAYER_ANIM_DEATH, 0, true, true, 5, false);
					}
				}

				ipFlags.S_FALLING = false;
				
				xFallBegin = 0;
				yFallBegin = 0;

				if(ipFlags.S_ON_GROUND && !ipFlags.S_JUMP && !(ipFlags.S_CROUCH || ipFlags.S_CRAWL))
				{	
					ipFlags.S_CRAWL = false;
					ipFlags.S_CROUCH = false;
				}
				
				// if player was crouching or crawling, return to that state
				if (ipFlags.S_CRAWL)
				{
					ipFlags.S_CROUCH = true;
					ipFlags.S_CROUCH_TOGGLE = false; //true;
					ipFlags.S_CRAWL = true;
					SetAnimation(PLAYER_ANIM_CRAWL, 0, false, false, 15, false);
				}
				else if (ipFlags.S_CROUCH)
				{
					ipFlags.S_CROUCH = true;
					ipFlags.S_CROUCH_TOGGLE = false;
					SetAnimation(PLAYER_ANIM_CROUCH, 2, false, false, 15, false);
				}
				else if (!ipFlags.S_DEAD && !ipFlags.S_PROCESS_DEATH) // player was walking
				{
					if (velMovement > 0)
					{
						processRight();
						ipFlags.S_ATTACK = false;
					}
					else if (velMovement < 0)
					{
						processLeft();
						ipFlags.S_ATTACK = false;
					}
					else
					{
						SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);	
						ipFlags.S_ATTACK = false;
					}
				}
				
			}
			else ipFlags.S_FALLING = false;
		}
	}
	else if(!ipFlags.S_ON_LADDER && ipFlags.S_UNDER_WATER)
	{
		float x, y;
	
		GetVelocityVector(&x, &y);

		if(y > 0)
		{
			if(!ipFlags.S_FALLING)
			{
				xFallBegin = GetXTilePos();
				yFallBegin = GetYTilePos();
				ipFlags.S_FALLING = true;
			}

			// IF NOT jumping - switch to fall animation
			if(/*!ipFlags.S_JUMP && */ ((abs(GetYTilePos() - yFallBegin)) <= 8) && !ipFlags.S_ATTACK)
				SetAnimation(PLAYER_ANIM_JUMP, 10, false, false, 0, true);
		}
		else ipFlags.S_FALLING = false;
	}
	else
		ipFlags.S_FALLING = false;

}

void Player::doWaterDamage(int num)
{
	/*
	if(ipFlags.nCurrAttack != 5)
	{
		if(underWaterTimer < 0)
		{
			doDamage(num, ipFlags.S_DIRECTION,0);
		}
	}
	 */
}

void Player::doChemicalDamage(int num)
{
	/*
	if(ipFlags.nCurrAttack != 5)
	{
		doDamage(num, ipFlags.S_DIRECTION,0);
	}
	 */
}

void Player::doDamage(int nDamageAmount, bool sDirection,int damage_type,bool silent/* = false*/)
{
	if(player_spr->GetFrameSet() == PLAYER_ANIM_ATTACK_QUAKE)
		return;

	if (inBossBattle)
		bossNoDamageTaken = false;
	
	if(nCurLife > 0)
	{
	if(!ipFlags.S_DAMAGED && !S_BARRIER_SHIELD)
	{
		if(!ipFlags.S_INVULNERABLE)
		{
			if(game_class->GetCurrentLevel() != 10)
				m_soundFXDamage->Play();
			//soundPlayer->PlaySound(damage00);
			if(!silent)
			{
				ipFlags.nDamageAmount = nDamageAmount;
				ipFlags.S_DAMAGED = true;
				ipFlags.fDmgTimer = fDmgTimer;//.25;
				ipFlags.S_DAMAGED_DIRECTION = sDirection;
			}

			int dmgAmt =  static_cast<int>(nDamageAmount*difficultyDamageModifier);

			if(dmgAmt < 1) dmgAmt = 1;

			nCurLife -= dmgAmt;
	
			if(!ipFlags.S_DEAD && !silent)
				processDamage();

			if(nCurLife <= 0)
			{
				ipFlags.CurMState = move_0;
				ipFlags.S_PROCESS_DEATH = true;
				
				if(!ipFlags.S_DEAD)
					processDeath();
			}
		}
	}
	else if(S_BARRIER_SHIELD && !ipFlags.S_DAMAGED)
	{
		ipFlags.S_DAMAGED = true;
		ipFlags.fDmgTimer = fDmgTimer;//.25;

		nBarrierOrbs--;
		if(nBarrierOrbs <= 0)
		{
			S_BARRIER_SHIELD = false;
			nBarrierOrbs = 0;
		}
	}
	}
}

/*
void Player::AddScore(int nPoints)
{
	nScore += static_cast<int>(nPoints * difficultyScoreModifier);
}
*/
 
void Player::ActivateBarrierShield()
{
	barrier_shield_timer = 3;
	S_BARRIER_SHIELD = true;
	nBarrierOrbs = 4;

	for(int i = 0; i < 4; i++)
	{
		bshield_spr[i]->SetFrame(i*4);
		bshield_spr[i]->SetAutoAnimate(true);
		bshield_spr[i]->SetFrameRate(15);
	}
}

void Player::AutoGrabLadder()
{
	if(!ipFlags.S_ATTACK)
	/* Left Facing Ladder */
	if((ipFlags.S_LADDER_TYPE == CLIMBBLOCKRIGHT) && (ipFlags.PrevMState != move_left))
	{	
		ipFlags.S_FALLING = false;
		ipFlags.S_JUMP = false;
		ipFlags.S_DIRECTION = true;

		/* Check for left facing ladder block type */
		if(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) == CLIMBBLOCKRIGHT)
		{
			velMovement = 0;
			velYJumpModifier = 0;

			/* Calculate Offset Into Climb Block */
			SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, false, false, 15, false);
			velYModifier = 0;
			ipFlags.S_ON_LADDER = true;
			ipFlags.S_FALLING = false;
		}
	}
	/* Right Facing Ladder */
	else if((ipFlags.S_LADDER_TYPE == CLIMBBLOCKLEFT) && (ipFlags.PrevMState != move_right))
	{	
		ipFlags.S_FALLING = false;
		ipFlags.S_JUMP = false;
		ipFlags.S_DIRECTION = false;

		/* Check for right facing ladder block type */
		if(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) == CLIMBBLOCKLEFT)
		{
			velMovement = 0;
			velYJumpModifier = 0;

			SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, false, false, 15, false);
			velYModifier = 0;
			ipFlags.S_ON_LADDER = true;
			ipFlags.S_FALLING = false;
		}
	}
}

void Player::BelowFeetLadderCheck()
{
	/* Check for Back Ladder OR Rope Block Below (When NOT Jumping) */
	if(!ipFlags.S_JUMP)
	{
		/* check for noncollidable ground tile */
		if((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBLADDER) ||
		   ((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBROPE) &&
		    (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) != CLIMBROPE)) ||
		   (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBBLOCKRIGHT) ||
		   (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBBLOCKLEFT))
		{
			/* Set Location to Top of Tile */
			ipFlags.S_NO_GRAVITY = true;
		}
		/* reset gravity if BACK on the 'collidable' ground */
		else
		{
			ipFlags.S_NO_GRAVITY = false;
		}
	}
}

void Player::CalcWorldOffset()
{


	// Check Player Bounding Rect
	HPTRect hptRectTemp = curLevel->GetWorldBounds();

	if(xLoc < 5)
		xLoc = 5;
	else if(xLoc > (hptRectTemp.p2.x + 235))
		xLoc = static_cast<float>(hptRectTemp.p2.x + 235);
	
	if(xLoc < 240)
		xWorldOffset = static_cast<float>(-(240-xLoc+xTransformOffset+xQuakeAttackModifier));
	else if (xLoc > (hptRectTemp.p2.x))
		xWorldOffset = static_cast<float>(-((hptRectTemp.p2.x)-xLoc+xTransformOffset+xQuakeAttackModifier));
	else 
		xWorldOffset = 0;

	if(yLoc < 160)
		yWorldOffset = static_cast<float>(-(160-yLoc+yTransformOffset+yQuakeAttackModifier));
	else if(yLoc > (hptRectTemp.p2.y)) 
		yWorldOffset = static_cast<float>(-(hptRectTemp.p2.y-yLoc+yTransformOffset+yQuakeAttackModifier));
	else
		yWorldOffset = 0;

	if(yWorldOffset > 160) ipFlags.S_DEAD = true;
}

Level *Player::GetCurLevel()
{
	return curLevel;
}

void Player::getViewTransform(float *x, float *y)
{
	*x = static_cast<float>(xLevelPos+xQuakeAttackModifier);
	*y = static_cast<float>(yLevelPos+yQuakeAttackModifier);
}

bool Player::isTileAboveHead()
{
	int tempxloc;
	int tempyloc;
	int templdata;

	for(int i = 0; i < 1; i++)
	{
		/* Check for Tiles Above Head */
		tempxloc = GetXTilePos();
		tempyloc = (static_cast<int>(GetYLoc())>>4)-i-1;
		templdata = curLevel->GetLevelData(tempxloc, tempyloc);	
		
		/*
		if(!(templdata == 0) &&
		   !((templdata == CLIMBBLOCKRIGHT) ||
		     (templdata == CLIMBBLOCKLEFT) ||
		     (templdata == CLIMBLADDER) ||
			 (templdata == CLIMBROPE) ||
			 (templdata == 26) ||
			 (templdata == 28) ||
		     (templdata == WATERMINE) ||
			 (templdata == FLAMETHROWEROBSTACLEVERTICLE) ||
			 (templdata == FLAMETHROWEROBSTACLERIGHT) ||
			 (templdata == SHOCKOBSTICLEVERTICAL) ||
			 (templdata == SHOCKOBSTICLEHORIZONTAL) ||
			 (templdata == FLAMETHROWEROBSTACLELEFT)) &&
			 (templdata < ENEMYFIRST || templdata > ENEMYLAST))
		{
			return true;
		}*/
		
		// These blocks are not collidable
		if (templdata == 0 ||
			templdata == CLIMBBLOCKRIGHT ||
			templdata == CLIMBBLOCKLEFT ||
			templdata == CLIMBLADDER ||
			templdata == CLIMBROPE ||
			templdata == WATERBLOCK ||
			templdata == GASBLOCK ||
			templdata == WATERMINE ||
			templdata == FLAMETHROWEROBSTACLEVERTICLE ||
			templdata == FLAMETHROWEROBSTACLERIGHT ||
			templdata == SHOCKOBSTICLEVERTICAL ||
			templdata == SHOCKOBSTICLEHORIZONTAL ||
			templdata == FLAMETHROWEROBSTACLELEFT ||
			(templdata > ENEMYFIRST && templdata < ENEMYLAST))
		{
			return false;
		}
			else return curLevel->IsCollidable(tempxloc, tempyloc);
	}	

/*	templdata = curLevel->GetLevelData(GetXTilePos(), (static_cast<int>(GetYLoc())>>4)-1);	

	if(ipFlags.S_CROUCH && !((templdata == CLIMBBLOCKRIGHT) ||
		     (templdata == CLIMBBLOCKLEFT) ||
		     (templdata == CLIMBLADDER) ||
			 (templdata == CLIMBROPE) ||
			 (templdata == 26) ||
			 (templdata == 28)))
	{
	
		if(ipFlags.S_DIRECTION)
		{
			if(xLoc <= (tempxloc*16)+8)
				return true;
		}
		else
		{
			if(xLoc >= (tempxloc*16)+8)
				return true;
		}
	}*/

	return false;
}

HPTRect &Player::GetWeaponWorldLoc()
{
	switch(player_spr->GetFrameSet())
	{
	case PLAYER_ANIM_ATTACK_STANDARD:
		if(player_spr->GetFrame() != 4 && player_spr->GetFrame() != 5)
			SetRectangle(rectWeaponWorldLoc, 29, 4, 0, -2);
		else
			SetRectangle(rectWeaponWorldLoc, 39, 4, 0, -2);
		break;
	case PLAYER_ANIM_ATTACK_JUMP:
			SetRectangle(rectWeaponWorldLoc, 23, 8, 0, 10);
		break;
	case PLAYER_ANIM_ATTACK_CROUCH:
		if(player_spr->GetFrame() != 4 && player_spr->GetFrame() != 5)
			SetRectangle(rectWeaponWorldLoc, 29, 4, 0, 12);
		else
			SetRectangle(rectWeaponWorldLoc, 39, 4, 0, 12);
		break;
	case PLAYER_ANIM_ATTACK_FLAME:
			SetRectangle(rectWeaponWorldLoc, 40, 40, -20, -10);
		break;
	default:
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);
		break;
	}

	return rectWeaponWorldLoc;
}

void Player::updateWorldLoc()
{
	switch(player_spr->GetFrameSet())
	{
	case PLAYER_ANIM_CLIMB_LADDER_TRANSITION:
	case PLAYER_ANIM_CRAWL:
	case PLAYER_ANIM_CROUCH:
	case PLAYER_ANIM_ATTACK_CROUCH:
			rectDX = 14;
			rectDY = 30;
			rectXOffset = -7;
			rectYOffset = 0;
			//SetRectangle(rectWorldLoc, 14, 30, -7, 0);
		break;
	default:
			rectDX = 14;
			rectDY = 45;
			rectXOffset = -7;
			rectYOffset = -15;
			//SetRectangle(rectWorldLoc, 14, 45, -7, -15);
		break;
	}
}

/*HPTRect &Player::GetWorldLoc()
{
	switch(player_spr->GetFrameSet())
	{
	case PLAYER_ANIM_CLIMB_LADDER_TRANSITION:
	case PLAYER_ANIM_CRAWL:
	//	if(ipFlags.S_DIRECTION)
//			SetRectangle(rectWorldLoc, 14, 25, 0, 5);
	//	else
	//		SetRectangle(rectWorldLoc, 15, 25, -15, 5);
//		break;
	case PLAYER_ANIM_CROUCH:
	//	if(ipFlags.S_DIRECTION)
			SetRectangle(rectWorldLoc, 14, 30, -7, 0);
	//	else
	//		SetRectangle(rectWorldLoc, 14, 30, -7, 0);
		break;
	case PLAYER_ANIM_ATTACK_CROUCH:
	//	if(ipFlags.S_DIRECTION)
			SetRectangle(rectWorldLoc, 14, 30, -7, 0);
	//	else
	//		SetRectangle(rectWorldLoc, 15, 30, -15 , 0);
		break;
	default:	
	//	if(ipFlags.S_DIRECTION)
			SetRectangle(rectWorldLoc, 14, 45, -7, -15);
	//	else
	//		SetRectangle(rectWorldLoc, 14, 45, -7, -15);
		break;
	}

	return rectWorldLoc;
}*/

void Player::LadderCompensate()
{
	/* Calculate Ladder Adjustments */
	if(ipFlags.S_NEXT_TO_LADDER)
	{
		/* Check for LEFT facing ladder block type */
		for(int i = 0; i <= 1; i++)
			if(curLevel->GetLevelData(GetXTilePos()-i, GetYTilePos() - 1) == CLIMBBLOCKRIGHT)
		   	{	
				if(ipFlags.S_DIRECTION)
				{
					/* Calculate Offset Into Climb Block */
					AddTransformationQueue((((GetXTilePos()-i) * 16)) - xLoc, 0);
					/* Check for Jump State - Auto Grab Ladder */
					if(ipFlags.S_JUMP || ipFlags.S_FALLING)
						AutoGrabLadder();
					break;
				}
			}
			/* Check for RIGHT facing ladder block type */
			else if(curLevel->GetLevelData(GetXTilePos()+i, GetYTilePos() - 1) == CLIMBBLOCKLEFT)
		   	{
				if(!ipFlags.S_DIRECTION)
				{
					/* Calculate Offset Into Climb Block */
					AddTransformationQueue((((GetXTilePos()+i) * 16)+15) - xLoc, 0);
					/* Check for Jump State - Auto Grab Ladder */
					if(ipFlags.S_JUMP || ipFlags.S_FALLING)
						AutoGrabLadder();
					break;
				}
			}
	}

	if(ipFlags.S_ON_LADDER)
	{
		ipFlags.S_FALLING = false;

		if((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) != CLIMBBLOCKRIGHT) && 
		   (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) != CLIMBBLOCKLEFT) &&
		   ((player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_LADDER_TRANSITION) && (!player_spr->IsAnimating())))
		{	
			AddTransformationQueue(0, ((((GetYTilePos()-1) * 16) + 17) - 30) - yLoc);

			SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);

#ifdef _DEBUG
//OutputDebugString("[SPENCER] Stand 1 - laderCompensate()");
#endif

			ipFlags.S_ON_LADDER = false;
			ipFlags.S_NO_GRAVITY = true;
			ipFlags.S_ON_GROUND = true;
		}
		
		
	}

	if(player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_ROPE_TRANSITION)
	{
		if(ropePullUp != player_spr->GetFrame())
		{
			switch(player_spr->GetFrame())
			{
				case 1:
					AddTransformationQueue(0, -13);
					break;
				case 2:
					AddTransformationQueue(0, -10);
					break;
				default:
					break;
			}
		}

		ropePullUp = player_spr->GetFrame();

		if(!player_spr->IsAnimating())
		{
#ifdef _DEBUG
			char temp[255];
			sprintf(temp, "[SPENCER] xLoc = %f, yLoc = %f", xLoc, yLoc);
//			OutputDebugString(temp);
//OutputDebugString("[SPENCER] Stand 2 - ladderCompensate()");
#endif
			SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);

		//	yLoc = 659;
			AddTransformationQueue(0,((((GetYTilePos()-1) * 16) + 17) - 46) - yLoc);
			AddTransformationQueue((((GetXTilePos()+1) * 16) - 8) - xLoc, 0);
			ipFlags.S_ON_LADDER = false;
			ipFlags.S_NO_GRAVITY = true;	
			ipFlags.S_ON_GROUND = true;
			ipFlags.S_JUMP = false;
			velYJumpModifier = 0;
			velModifier = 0;
			velYModifier = 0;
			S_ROPE_PULL = false;

#ifdef _DEBUG
			sprintf(temp, "[SPENCER] xLoc = %f, yLoc = %f", xLoc, yLoc);
//			OutputDebugString(temp);
//OutputDebugString("[SPENCER] Stand 2 - ladderCompensate()");
#endif
		}
	}
	else if(player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_ROPE_TRANSITION_DOWN)
	{
		if(ropePullDown != player_spr->GetFrame())
		{
			switch(player_spr->GetFrame())
			{
				case 6:	
					AddTransformationQueue(0, 13);
					break;
				case 7:	
					AddTransformationQueue(0, 10);
					break;
				default:
					break;
			}
		}

		ropePullDown = player_spr->GetFrame();

		if(!player_spr->IsAnimating())
		{
			SetAnimation(PLAYER_ANIM_CLIMB_ROPE, 0, false, false, 9, false);
				
//			AddTransformationQueue(0,((((GetYTilePos()-1) * 16) + 17) - 50) - yLoc);
		//	yLoc = static_cast<float>((((GetYTilePos()-1) * 16) +17) - 48);
		//	AddTransformationQueue((((GetXTilePos()+1) * 16) - 8) - xLoc, 0);
		//	xLoc = static_cast<float>(((GetXTilePos()+1) * 16)+ 4);
		//	ipFlags.S_ON_LADDER = false;
		//	ipFlags.S_NO_GRAVITY = true;	
		//	ipFlags.S_ON_GROUND = true;
			ipFlags.S_JUMP = false;
			ipFlags.S_ON_LADDER = true;
			velYJumpModifier = 0;
			velModifier = 0;
			velYModifier = 0;
			S_ROPE_PULL = false;
		}
	}
}

void Player::LadderDown()
{
		/* Check Ladder Type and Set Direction */
		/* Left Facing Ladder */
		if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKRIGHT)
		{
			/* Under Water Check */
			if(!ipFlags.S_UNDER_WATER)
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, true, false, 15*analog_mod_y, false);
				velYModifier = climbVelocity*analog_mod_y;
			}
			else
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, true, false, 10*analog_mod_y, false);
				velYModifier = climbVelocity * velWaterModifier*analog_mod_y;
			}

			ipFlags.S_DIRECTION = true;
			ipFlags.S_ON_LADDER = true;
			ipFlags.S_JUMP = false;
			velYJumpModifier = 0;	
		}
		/* Right Facing Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKLEFT)
		{
			/* Under Water Check */
			if(!ipFlags.S_UNDER_WATER)
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, true, false, 15*analog_mod_y, false);
				velYModifier = climbVelocity*analog_mod_y;
			}
			else
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, true, false, 7*analog_mod_y, false);
				velYModifier = climbVelocity * velWaterModifier*analog_mod_y;
			}

			ipFlags.S_DIRECTION = false;
			ipFlags.S_ON_LADDER = true;
			ipFlags.S_JUMP = false;
			velYJumpModifier = 0;	
		}
		/* Back Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBLADDER)
		{
			ipFlags.S_DIRECTION = true;

			/* Determine Location Offset - Scan 4 Tiles under feet, left to right
			   Set Spencer's Location to Right of Leftmost Back Facing Ladder Tile
			*/
			for(int i = -2; i < 2; i++)
			{
				if(curLevel->GetLevelData(GetXTilePos() + i, GetYTilePos()) == CLIMBLADDER)
				{
//					xLoc = static_cast<float>(((GetXTilePos()+i)<<4) + 16 - 3);
					AddTransformationQueue((((GetXTilePos()+i)<<4) + 16 - 3) - xLoc, 0);
					break;
				}
			}
	
			ipFlags.S_ON_LADDER = true;

			/* Under Water Check */
			if(!ipFlags.S_UNDER_WATER)
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_BACK, 0, true, false, 15*analog_mod_y, false);
				velYModifier = climbVelocity*analog_mod_y;
			}
			else
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_BACK, 0, true, false, 7*analog_mod_y, false);
				velYModifier = climbVelocity * velWaterModifier*analog_mod_y;
			}

			ipFlags.S_JUMP = false;
			velYJumpModifier = 0;	

			/* Check for Back Ladder block type */
			if((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) != CLIMBLADDER) &&
				curLevel->GetLevelData(GetXTilePos(), GetYTilePos()) != CLIMBLADDER)
			{
//				OutputDebugString("ON LADDER FALSE 3");
				ipFlags.S_ON_LADDER = false;
				ipFlags.S_NO_GRAVITY = true;
				ipFlags.S_ON_GROUND = true;

			//	yLoc = static_cast<float>((((GetYTilePos()-1) * 16) + 17));// - 30);

				SetAnimation(PLAYER_ANIM_STAND, 0, false, false, 3, true);

//				OutputDebugString("STAND 2");

				velYModifier = 0;
			}
		}
		/* Rope Climb */
		else if(ipFlags.S_LADDER_TYPE == CLIMBROPE)
		{
			if(!S_ROPE_PULL)
			{
				if((player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_ROPE_TRANSITION_DOWN) ||
				   (player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_ROPE))
				if(!(player_spr->IsAnimating()))
					SetAnimation(PLAYER_ANIM_CLIMB_ROPE_DOWN, 0, true, false, 15, false);

				if(player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_ROPE_DOWN)
				{
					SetAnimation(PLAYER_ANIM_CLIMB_ROPE_DOWN, 0, true, false, 15*analog_mod_y, false);
					ipFlags.S_JUMP = false;
					ipFlags.S_DIRECTION = true;
					velYModifier = climbVelocity*analog_mod_y;
				}
			}
		}
}

void Player::LadderDownGrab()
{
	ipFlags.S_JUMP = false;

	/* Left Facing Ladder */
	if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKRIGHT)
	{
		ipFlags.S_DIRECTION = true;

		/* Check for left facing ladder block type */
		for(int i = 0; i <= 1; i++)
			if(curLevel->GetLevelData(GetXTilePos()+i, GetYTilePos()) == CLIMBBLOCKRIGHT)
			{
				/* Calculate Offset Into Climb Block */
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, false, false, 15, true);
				AddTransformationQueue(0, ((((GetYTilePos()) * 16) + 17) - 30) - yLoc);
				AddTransformationQueue((((GetXTilePos()+i) * 16)) - xLoc, 0);
				StopMovement();
				ipFlags.S_ON_LADDER = true;
			}
	}
	/* Right Facing Ladder */
	else if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKLEFT)
	{
		ipFlags.S_DIRECTION = false;

		for(int i = 0; i >= -1; i--)
			if(curLevel->GetLevelData(GetXTilePos()+i, GetYTilePos()) == CLIMBBLOCKLEFT) 
			{
				/* Calculate Offset Into Climb Block */
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, false, false, 15, true);
				AddTransformationQueue(0, ((((GetYTilePos()) * 16) + 17) - 30) - yLoc);
				AddTransformationQueue((((GetXTilePos()+i) * 16)+15) - xLoc, 0);
				StopMovement();
				ipFlags.S_ON_LADDER = true;
			}
	}
	/* Back Ladder */
	else if(ipFlags.S_LADDER_TYPE == CLIMBLADDER)
	{
		/* Check that Ladder Tile is Atleast AT feet or higher */
		if(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBLADDER)
		{
			StopMovement();
			ipFlags.S_DIRECTION = true;
			ipFlags.S_ON_LADDER = true;
			SetAnimation(PLAYER_ANIM_CLIMB_LADDER_BACK, 0, true, false, 15, false);
			/* Determine Location Offset - Scan 4 Tiles under feet, left to right
			   Set Spencer's Location to Right of Leftmost Back Facing Ladder Tile
			*/
			for(int i = -2; i < 2; i++)
			{
				if(curLevel->GetLevelData(GetXTilePos() + i, GetYTilePos()) == CLIMBLADDER)
				{
					AddTransformationQueue((((GetXTilePos()+i)<<4) + 16 - 3) - xLoc, ((GetYTilePos() - 1)* 16) - yLoc);
					break;
				}
			}
		}
		else
		{
			StopMovement();
			ipFlags.S_ON_LADDER = false;
		}
	}
	/* Rope Climb */
	else if(ipFlags.S_LADDER_TYPE == CLIMBROPE)
	{	
		if(!S_ROPE_PULL)
			if((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBROPE) &&
			   (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) != CLIMBROPE))
			{	
				velYJumpModifier = 0;
				StopMovement();
				
				AddTransformationQueue(((GetXTilePos() * 16)+8) - xLoc, 0);
				AddTransformationQueue(0, ((GetYTilePos() * 16) - 7) - yLoc);
				ipFlags.S_JUMP = false;

				ipFlags.S_ON_LADDER = true;
				SetAnimation(PLAYER_ANIM_CLIMB_ROPE_TRANSITION_DOWN, 0, true, true, 9, false);

				S_ROPE_PULL = true;
			}
			else if(curLevel->GetLevelData(GetXTilePos(), GetYTilePos() - GetTileHeight()) == CLIMBROPE)
				{	
					velYJumpModifier = 0;
					velMovement = 0;
			
					AddTransformationQueue(((GetXTilePos() * 16)+8 - xLoc), 0);

					ipFlags.S_JUMP = false ;
					ipFlags.S_ON_GROUND = false;
					ipFlags.S_ON_LADDER = true;

					SetAnimation(PLAYER_ANIM_CLIMB_ROPE_DOWN, 0, true, false, 15, false);

				//	break;
				}
	}
}

void Player::LadderUp()
{
			/* Left Facing Ladder */
		if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKRIGHT)
		{
			/* Check for left facing ladder block type */
			if((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) != CLIMBBLOCKRIGHT))// && (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBBLOCKRIGHT) )
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_TRANSITION, 0, true, true, 10, false);
				velYModifier = 0;
			}
			else
			{
				/* Under Water Check */
				if(!ipFlags.S_UNDER_WATER)
				{
					SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, true, false, 15*analog_mod_y, false);
					velYModifier = -climbVelocity*analog_mod_y;
				}
				else
				{
					SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, true, false, 10*analog_mod_y, false);
					velYModifier = -climbVelocity * velWaterModifier*analog_mod_y;
				}

				ipFlags.S_DIRECTION = true;	
				ipFlags.S_ON_LADDER = true;
				velYJumpModifier = 0;
			}
		}
		/* Right Facing Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKLEFT)
		{		
			/* Check for Right facing ladder block type */
			if(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-1) != CLIMBBLOCKLEFT)
			{	
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_TRANSITION, 0, true, true, 10, false);
				velYModifier = 0;
			}
			else
			{
				/* Under Water Check */
				if(!ipFlags.S_UNDER_WATER)
				{
					SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, true, false, 15*analog_mod_y, false);
					velYModifier = -climbVelocity*analog_mod_y;
				}
				else
				{
					SetAnimation(PLAYER_ANIM_CLIMB_LADDER_SIDE, 0, true, false, 7*analog_mod_y, false);
					velYModifier = -climbVelocity * velWaterModifier*analog_mod_y;
				}

				ipFlags.S_DIRECTION = false;
				ipFlags.S_ON_LADDER = true;
				velYJumpModifier = 0;
			}
		}
		/* Back Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBLADDER)
		{
			/* Determine Location Offset - Scan 4 Tiles under feet, left to right
			   Set Spencer's Location to Right of Leftmost Back Facing Ladder Tile
			*/
			for(int i = -2; i < 2; i++)
			{
				if(curLevel->GetLevelData(GetXTilePos() + i, GetYTilePos() - 1) == CLIMBLADDER)
				{
//					xLoc = static_cast<float>(((GetXTilePos()+i)<<4) + 16 - 3);
					AddTransformationQueue((((GetXTilePos()+i)<<4) + 16 - 3) - xLoc, 0);
					break;
				}
			}

			ipFlags.S_DIRECTION = true;
			ipFlags.S_ON_LADDER = true;

			/* Under Water Check */
			if(!ipFlags.S_UNDER_WATER)
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_BACK, 0, true, false, 15*analog_mod_y, false);
				velYModifier = -climbVelocity*analog_mod_y;
			}
			else
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_BACK, 0, true, false, 7*analog_mod_y, false);
				velYModifier = -climbVelocity * velWaterModifier*analog_mod_y;
			}

			ipFlags.S_JUMP = false;
			velYJumpModifier = 0;

			/* Check for Back Ladder block type */
			if((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-(GetTileHeight())/*1*/) != CLIMBLADDER) &&
			   (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-(GetTileHeight()-1)/*1*/) != CLIMBLADDER) &&
   		       (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-(GetTileHeight()-2)/*2*/) != CLIMBLADDER))
			{
				ipFlags.S_ON_LADDER = false;
				ipFlags.S_NO_GRAVITY = true;
				ipFlags.S_ON_GROUND = true;

//				yLoc = static_cast<float>((((GetYTilePos()-1) * 16) + 17) - 30);
				AddTransformationQueue(0, ((((GetYTilePos()-1) * 16) + 17) - 30) - yLoc);

				SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);

//				OutputDebugString("STAND 3");
	
				velYModifier = 0;
			}
		}
		/* Rope Climb */
		else if(ipFlags.S_LADDER_TYPE == CLIMBROPE)
		{
			if(!S_ROPE_PULL)
			{
				/* Check for Rope block type */
				if((curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-GetTileHeight()) != CLIMBROPE) &&
					(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-GetTileHeight()) == 0))// &&
			       //(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-GetTileHeight()) == CLIMBROPE))
				{
					//ipFlags.S_ON_LADDER = false;
					//ipFlags.S_NO_GRAVITY = true;
					//ipFlags.S_ON_GROUND = true;	

					if((curLevel->GetLevelData(GetXTilePos()+1, GetYTilePos()-GetTileHeight()) != 0))
						ipFlags.S_DIRECTION = true;
					else if((curLevel->GetLevelData(GetXTilePos()-1, GetYTilePos()-GetTileHeight()-1) != 0))
						ipFlags.S_DIRECTION = false;
	
					SetAnimation(PLAYER_ANIM_CLIMB_ROPE_TRANSITION, 0, true, true, 9, false);
		
					S_ROPE_PULL = true;	

					velYModifier = 0;
				}
				else
				{
					SetAnimation(PLAYER_ANIM_CLIMB_ROPE, 0, true, false, 15*analog_mod_y, false);
			
				//	for(int i = -1; i <= 1; i++)
				//		if(curLevel->GetLevelData(GetXTilePos() + i, GetYTilePos()) == CLIMBLADDER)
				//			AddTransformationQueue((((GetXTilePos() + i) * 16)+8 - xLoc), 0);

					ipFlags.S_DIRECTION = true;
					ipFlags.S_ON_LADDER = true;
					velYModifier = -climbVelocity*analog_mod_y;
				}		
			}
		}
}

void Player::LadderUpGrab()
{
	//		ipFlags.S_JUMP = false;

		/* Left Facing Ladder */
		if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKRIGHT)
		{
			/* Check for left facing ladder block type */
			for(int i = 0; i <= 1; i++)
				if(curLevel->GetLevelData(GetXTilePos()+i, GetYTilePos()-1) == CLIMBBLOCKRIGHT)
				{
					velMovement = 0;
					velYJumpModifier = 0;

					/* Calculate Offset Into Climb Block */
//					xLoc = static_cast<float>(((GetXTilePos()+i) * 16) + 1);
					AddTransformationQueue((((GetXTilePos()+i) * 16) + 1) - xLoc, 0);
//					velYModifier = 0;
					
					ipFlags.S_ON_LADDER = true;
					ipFlags.S_DIRECTION = true;
					break;
				}
		}
		/* Right Facing Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKLEFT)
		{
			/* Check for right facing ladder block type */
			for(int i = 0; i <= 1; i++)
				if(curLevel->GetLevelData(GetXTilePos()-i, GetYTilePos()-1) == CLIMBBLOCKLEFT) 
				{
					velMovement = 0;
					velYJumpModifier = 0;

					/* Calculate Offset Into Climb Block */
//					xLoc = static_cast<float>(((GetXTilePos()-i) * 16)+15);
					AddTransformationQueue((((GetXTilePos()-i) * 16)+15) - xLoc, 0);
//					velYModifier = 0;
					
					ipFlags.S_ON_LADDER = true;	
					ipFlags.S_DIRECTION = false;
					break;
				}
		}
//	}
//	else if(ipFlags.S_NEXT_TO_LADDER && !ipFlags.S_ON_LADDER)
//	{
		/* Back Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBLADDER)
		{
//			OutputDebugString("GRAB CLIMB LADDER");
			/* Check that Ladder Tile is Atleast AT feet or higher */
			if((curLevel->GetLevelData(GetXTilePos(), GetYTilePos() - 3) == CLIMBLADDER) ||
   			   (curLevel->GetLevelData(GetXTilePos(), GetYTilePos() - 4) == CLIMBLADDER))
			{
				velMovement = 0;
				velYJumpModifier = 0;
				velYModifier = 0;
				ipFlags.S_ON_LADDER = true;
				ipFlags.S_JUMP = false;
				ipFlags.S_DIRECTION = true;

				/* Determine Location Offset - Scan 4 Tiles under feet, left to right
				   Set Spencer's Location to Right of Leftmost Back Facing Ladder Tile
				*/
				for(int i = -2; i < 2; i++)
				{
					if(curLevel->GetLevelData(GetXTilePos() + i, GetYTilePos() - 3) == CLIMBLADDER)
					{
//						xLoc = static_cast<float>(((GetXTilePos()+i)<<4) + 16 - 3);
						AddTransformationQueue((((GetXTilePos()+i)<<4) + 16 - 3) - xLoc, 0);
						break;
					}
				}	
				
				/* Under Water Check */
				if(!ipFlags.S_UNDER_WATER)
				{
					SetAnimation(PLAYER_ANIM_CLIMB_LADDER_BACK, 0, true, false, 15, false);
					velYModifier = -climbVelocity;
				}
				else
				{
					SetAnimation(PLAYER_ANIM_CLIMB_LADDER_BACK, 0, true, false, 7, false);
					velYModifier = -climbVelocity * velWaterModifier;
				}
			}
			else
			{
//				OutputDebugString("ON LADDER FALSE 4");
				velYJumpModifier = 0;
				velYModifier = 0;
				ipFlags.S_ON_LADDER = false;
			}


		}
		/* Rope Climb */
		else if(ipFlags.S_LADDER_TYPE == CLIMBROPE)
		{	
			/* Check for Rope block type */
			//if(!(curLevel->GetLevelData(GetXTilePos(), GetYTilePos()-GetTileHeight()-1) != CLIMBROPE))
			//for(int i = 3; i >= 2; i--)
			//if(player_spr->GetFrameSet() != PLAYER_ANIM_CLIMB_ROPE_TRANSITION)
			if(!S_ROPE_PULL)
			//	if(ipFlags.S_ON_GROUND)
					if(curLevel->GetLevelData(GetXTilePos(), GetYTilePos() - GetTileHeight()) == CLIMBROPE)
					{	
						velYJumpModifier = 0;
						velMovement = 0;
			
						//xLoc = static_cast<float>(GetXTilePos() * 16)+8 ;
						AddTransformationQueue(((GetXTilePos() * 16)+8 - xLoc), -3);

						ipFlags.S_JUMP = false ;
						ipFlags.S_ON_GROUND = false;
						ipFlags.S_ON_LADDER = true;

						SetAnimation(PLAYER_ANIM_CLIMB_ROPE, 0, true, false, 15, false);
					}
		}
}

void Player::processAttack()
{
	if(!ipFlags.S_JUMP)
	{
		velMovement = 0;
		velModifier = 0;
	}
	if(!ipFlags.S_ATTACK)
	{
		if(ipFlags.S_CROUCH || ipFlags.S_CRAWL)// && 	SetAnimation(PLAYER_ANIM_ATTACK_CROUCH, 0, true, true, 15, true))
		{
	//		SetAttack(0);
//		soundPlayer->PlaySound(swing00);
			m_swingSound->Play();
			SetAnimation(PLAYER_ANIM_ATTACK_CROUCH, 0, true, true, 25, true);
			SetWeaponDamage(static_cast<int>(basic_weapon_damage_amount*difficultyHitModifier));
			ipFlags.S_ATTACK = true;
			switch(ipFlags.nCurrAttack)
			{
				case 0:
						current_weapon = 0;
						break;
				/*case 5:
					{
						current_weapon = 5;
					}
					break;*/
				case 1:
					{
						current_weapon = 1;

					}
					break;
				case 2:
					{	
						current_weapon = 2;

					}
					break;
				case 3:
					{
						current_weapon = 4;

					}
					break;
				case 4:
					{
						current_weapon = 5;

					}
					break;	

				default:
					break;
			}
		}
		else if(ipFlags.S_JUMP && (player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_JUMP))
		{
	//		SetAttack(0);
//		soundPlayer->PlaySound(swoosh00);
			SetAnimation(PLAYER_ANIM_ATTACK_JUMP, 0, true, true, 13, true);
			//SetWeaponDamage(static_cast<int>(basic_weapon_damage_amount*(difficultyHitModifier*.5)));
			SetWeaponDamage(static_cast<int>(basic_weapon_damage_amount*(difficultyHitModifier)));
			ipFlags.S_ATTACK = true;
			current_weapon = 0;

		}
//		else if(ipFlags.S_ON_GROUND && ipFlags.CurMState == move_up)
//		{
//			CycleAttack();
//		}
		else if(!ipFlags.S_ON_LADDER && !ipFlags.S_FALLING)// if(ipFlags.S_ON_GROUND)
		{
/*			int tempa;
			if(ipFlags.CurMState != move_up)
			{
				tempa = GetAttack();
				SetAttack(0);
			}
*/				

		//	ipFlags.nCurrAttack = 6;
//		soundPlayer->PlaySound(swing00);
			m_swingSound->Play();
			SetAnimation(PLAYER_ANIM_ATTACK_STANDARD, 0, true, true, 25, true);
			SetWeaponDamage(static_cast<int>(basic_weapon_damage_amount*difficultyHitModifier));
			ipFlags.S_ATTACK = true;

			switch(ipFlags.nCurrAttack)
			{
				case 0:
						current_weapon = 0;
						break;
				/*case 5:
					{
						current_weapon = 5;
					}
					break;*/
				case 1:
					{
						current_weapon = 1;

					}
					break;
				case 2:
					{	
						current_weapon = 2;

					}
					break;
				case 3:
					{
						current_weapon = 4;

					}
					break;
				case 4:
					{
						current_weapon = 5;

					}
					break;	

				default:
					break;
			}
		}
//	else if(ipFlags.S_ON_GROUND && player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_STANDARD)
//	{
//		sound_processor->PlaySound(game_sounds->swing00);

//		SetAnimation(PLAYER_ANIM_ATTACK_STANDARD, 0, true, true, 25, true);
//		weapon.SetWeaponDamage(3);
//			ipFlags.S_ATTACK = true;
//	}
	}
}

void Player::processAttack2()
{
	if(!ipFlags.S_JUMP)
	{
		velMovement = 0;
		velModifier = 0;
	}
	if(!ipFlags.S_ATTACK)
	{
		if(ipFlags.S_CROUCH || ipFlags.S_CRAWL)// && 	SetAnimation(PLAYER_ANIM_ATTACK_CROUCH, 0, true, true, 15, true))
		{
	//		SetAttack(0);
//		soundPlayer->PlaySound(swing00);
			m_swingSound->Play();
			SetAnimation(PLAYER_ANIM_ATTACK_CROUCH, 0, true, true, 25, true);
			SetWeaponDamage(static_cast<int>(basic_weapon_damage_amount*difficultyHitModifier));
			ipFlags.S_ATTACK = true;
			current_weapon = 0;
			
		}
		else if(ipFlags.S_JUMP && (player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_JUMP))
		{
	//		SetAttack(0);
//		soundPlayer->PlaySound(swing00);
			m_swingSound->Play();
			SetAnimation(PLAYER_ANIM_ATTACK_JUMP, 0, true, true, 13, true);
			//SetWeaponDamage(static_cast<int>(basic_weapon_damage_amount*(difficultyHitModifier*.5)));
			SetWeaponDamage(static_cast<int>(basic_weapon_damage_amount*(difficultyHitModifier)));
			ipFlags.S_ATTACK = true;
			current_weapon = 0;
			
		}
//		else if(ipFlags.S_ON_GROUND && ipFlags.CurMState == move_up)
//		{
//			CycleAttack();
//		}
		else if(!ipFlags.S_ON_LADDER && !ipFlags.S_FALLING)// if(ipFlags.S_ON_GROUND)
		{
			if(steph)
			{
				if(steph_top->IsAnimating()) return;
				if((ipFlags.nCurrAttack != steph_top->GetFrameSet()) && ((6+ipFlags.nCurrAttack) != steph_top->GetFrameSet())  && ((12+ipFlags.nCurrAttack) != steph_top->GetFrameSet()))
					return;
			}
			int tempa;
/*			if(ipFlags.CurMState != move_up)
			{
				tempa = GetAttack();
				SetAttack(0);
			}*/
				

		//	ipFlags.nCurrAttack = 6;

			switch(ipFlags.nCurrAttack)
			{
//				case 0:
/*				case 5:
					{
						SetAnimation(PLAYER_ANIM_ATTACK_STANDARD, 0, true, true, 25, true);
						SetWeaponDamage(static_cast<int>(basic_weapon_damage_amount*difficultyHitModifier));
						ipFlags.S_ATTACK = true;

					}
					break;
*/				case 1:
					{
						/*
						if(steph)
						{
							steph_top->SetFrame(0);
							steph_top->SetFrameRate(8);
							steph_top->SetAutoAnimate(true);
							steph_top->AutoStopAnimate();

								Projectile *temp;
								float xveladd,yveladd;
								//GetVelocityVector(&xveladd,&yveladd);
								xveladd = analog_mod_x*90;
								//if(fabs(xveladd) < 10) xveladd = 0;
								yveladd = 0;

								if(ipFlags.S_DIRECTION)
								{
									if(game_class->twCurKeyStates.twkInputNavX > (-3*game_class->twCurKeyStates.twkInputNavY))  temp = new ProjectileStephPistol(0, static_cast<int>(xLoc+7)+nOffSet, static_cast<int>(yLoc-8),xveladd,yveladd,this,nOffSet+7,-8);
									else if((-game_class->twCurKeyStates.twkInputNavY) > (3*game_class->twCurKeyStates.twkInputNavX)) temp = new ProjectileStephPistol(90, static_cast<int>(xLoc -18)+nOffSet, static_cast<int>(yLoc -24 ),xveladd,yveladd,this,nOffSet-18,-24);
									else temp = new ProjectileStephPistol(45, static_cast<int>(xLoc -5)+nOffSet, static_cast<int>(yLoc -17 ),xveladd,yveladd,this,nOffSet-5,-17);
//									temp = new ProjectileStephPistol(ipFlags.S_DIRECTION, static_cast<int>(xLoc + 40), static_cast<int>(yLoc -5 ));
									
									
									temp->SetWeaponDamage(4);
								}
								else
								{
									xveladd = -xveladd;
									if((-game_class->twCurKeyStates.twkInputNavX) > (-3*game_class->twCurKeyStates.twkInputNavY))  temp = new ProjectileStephPistol(180, static_cast<int>(xLoc - 7)-nOffSet, static_cast<int>(yLoc -8 ),xveladd,yveladd,this,nOffSet-7,-8);
									else if((-game_class->twCurKeyStates.twkInputNavY) > (-3*game_class->twCurKeyStates.twkInputNavX)) temp = new ProjectileStephPistol(90, static_cast<int>(xLoc +18)-nOffSet, static_cast<int>(yLoc -24 ),xveladd,yveladd,this,18-nOffSet,-24);
									else temp = new ProjectileStephPistol(135, static_cast<int>(xLoc +5)-nOffSet, static_cast<int>(yLoc -17 ),xveladd,yveladd,this,5-nOffSet,-17);
									//temp = new ProjectileStephPistol(ipFlags.S_DIRECTION, static_cast<int>(xLoc - 40), static_cast<int>(yLoc -5 ));
									
									temp->SetWeaponDamage(4);
								}
								temp->SetSource(true);
								(*projectile_list).push_back(temp);
								//ipFlags.S_ATTACK = true;
								current_weapon = 6;
						}
						else*/
						{
							if(UseEnergy(SHOCK_ATTACK_ENERGY))
							{			
								if (inBossBattle)
									bossUsedOnlyBasicAttack = false;
								m_shockSound->Play();
//							soundPlayer->PlaySound(shockattack);
								SetAnimation(PLAYER_ANIM_ATTACK_ELECTRIC, 0, true, true, 20, false);	
								
								Projectile *temp;
								if(ipFlags.S_DIRECTION)
								{
									temp = new ProjectileShockAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc + 48), static_cast<int>(yLoc - 3));
								}
								else
								{
									temp = new ProjectileShockAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc - 48), static_cast<int>(yLoc - 3));
								}
						
								(*projectile_list).push_back(temp);
								ipFlags.S_ATTACK = true;
								current_weapon = 6;
							}
						}
					}
					break;
				case 2:
					/*
						if(steph)
						{
							steph_top->SetFrame(0);
							steph_top->SetFrameRate(8);
							steph_top->SetAutoAnimate(true);
							steph_top->AutoStopAnimate();
							float xveladd,yveladd;
								//GetVelocityVector(&xveladd,&yveladd);
								xveladd = analog_mod_x*90;
								//if(fabs(xveladd) < 10) xveladd = 0;
								yveladd = 0;

							Projectile *temp;

							if(ipFlags.S_DIRECTION)
							{
								int angle = 0;
								int xoff,yoff;
								if(game_class->twCurKeyStates.twkInputNavX > (-3*game_class->twCurKeyStates.twkInputNavY))
								{
									angle = 0;
									xoff = nOffSet+10;
									yoff = -2;
									//temp = new ProjectileStephPistol(0, static_cast<int>(xLoc+7)+nOffSet, static_cast<int>(yLoc-8),xveladd,yveladd,this,nOffSet+7,-8);
								}
								else if((-game_class->twCurKeyStates.twkInputNavY) > (3*game_class->twCurKeyStates.twkInputNavX))
								{
									angle = 90;
									xoff = nOffSet-10;
									yoff = -26;
									//temp = new ProjectileStephPistol(90, static_cast<int>(xLoc -18)+nOffSet, static_cast<int>(yLoc -24 ),xveladd,yveladd,this,nOffSet-18,-24);
								}
								else
								{
								
									xoff = nOffSet-2;
									yoff = -17;
									angle = 45;
									//temp = new ProjectileStephPistol(45, static_cast<int>(xLoc -5)+nOffSet, static_cast<int>(yLoc -17 ),xveladd,yveladd,this,nOffSet-5,-17);
								}
//									
								
								
								temp = new ProjectileStephRifle(angle,.10f,xveladd,yveladd,this,xoff,yoff);
								
								(*projectile_list).push_back(temp);

								temp = new ProjectileStephRifle(angle,.20f,xveladd,yveladd,this,xoff,yoff);
								
								(*projectile_list).push_back(temp);

								temp = new ProjectileStephRifle(angle,.30f,xveladd,yveladd,this,xoff,yoff);
								
								(*projectile_list).push_back(temp);
							}

							else
							{
								xveladd = -xveladd;
								int angle = 0;
								int xoff,yoff;
								
								if((-game_class->twCurKeyStates.twkInputNavX) > (-3*game_class->twCurKeyStates.twkInputNavY)) 
								{
									angle = 180;
									xoff = nOffSet-24;
									yoff = -2;
									//temp = new ProjectileStephPistol(180, static_cast<int>(xLoc - 7)-nOffSet, static_cast<int>(yLoc -8 ),xveladd,yveladd,this,nOffSet-7,-8);
								}
								else if((-game_class->twCurKeyStates.twkInputNavY) > (-3*game_class->twCurKeyStates.twkInputNavX))
								{
									angle = 90;
									xoff = 14-nOffSet;
									yoff = -26;
									//temp = new ProjectileStephPistol(90, static_cast<int>(xLoc +18)-nOffSet, static_cast<int>(yLoc -24 ),xveladd,yveladd,this,18-nOffSet,-24);
								}
								else 
								{
									angle = 135;
									xoff = 2-nOffSet;
									yoff = -17;
									//temp = new ProjectileStephPistol(135, static_cast<int>(xLoc +5)-nOffSet, static_cast<int>(yLoc -17 ),xveladd,yveladd,this,5-nOffSet,-17);
								}
								
								
								temp = new ProjectileStephRifle(angle,.10f,xveladd,yveladd,this,xoff,yoff);
								
								(*projectile_list).push_back(temp);
								
								temp = new ProjectileStephRifle(angle,.20f,xveladd,yveladd,this,xoff,yoff);
								
								(*projectile_list).push_back(temp);

								temp = new ProjectileStephRifle(angle,.30f,xveladd,yveladd,this,xoff,yoff);
								
								(*projectile_list).push_back(temp);
							}
							//(*projectile_list).push_back(temp);
							//ipFlags.S_ATTACK = true;
							current_weapon = 7;


						}
						else*/
						{	
							if(UseEnergy(FLAME_ATTACK_ENERGY))
							{
								if (inBossBattle)
									bossUsedOnlyBasicAttack = false;
								
								m_flameSound->Play();
//							soundPlayer->PlaySound(flame);
								SetAnimation(PLAYER_ANIM_ATTACK_FLAME, 0, true, true, 20, false);

								Projectile *temp;		
								if(ipFlags.S_DIRECTION)
								{
									temp = new ProjectileFlameAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc), static_cast<int>(yLoc), projectile_list);
								}
								else
								{
									temp = new ProjectileFlameAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc), static_cast<int>(yLoc), projectile_list);
								}
						
								SetWeaponDamage(static_cast<int>(10*difficultyHitModifier));

								(*projectile_list).push_back(temp);
								ipFlags.S_ATTACK = true;
								current_weapon = 7;
							}
						}
				
					break;
					/*
				case 3:
						if(steph)
						{
							steph_top->SetFrame(0);
							steph_top->SetFrameRate(8);
							steph_top->SetAutoAnimate(true);
							steph_top->AutoStopAnimate();

						}
						else
					{
					if(UseEnergy(SHIELD_ATTACK_ENERGY))
						{
//							sound_processor->PlaySound(game_sounds->swing00);
							//shield_sound->Play();
							ActivateBarrierShield();
							/*SetAnimation(PLAYER_ANIM_ATTACK_GRENADE, 0, true, true, 25, false);
							Projectile *temp;	

							if(ipFlags.S_DIRECTION)
							{
								temp = new ProjectileGrenadeAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc+15), static_cast<int>(yLoc), projectile_list);
								
							}
							else
							{
								temp = new ProjectileGrenadeAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc-15), static_cast<int>(yLoc), projectile_list);
								
							}
					
							(*projectile_list).push_back(temp);
							ipFlags.S_ATTACK = true;*//*
							current_weapon = 8;
						}
					}
					break;*/
				case 3:
						if(steph)
						{
							steph_top->SetFrame(0);
							steph_top->SetFrameRate(8);
							steph_top->SetAutoAnimate(true);
							steph_top->AutoStopAnimate();

						}
						else
					{
						if(UseEnergy(PROJECTILE_ATTACK_ENERGY))
						{	
							if (inBossBattle)
								bossUsedOnlyBasicAttack = false;
							
								m_waveSound->Play();
//						soundPlayer->PlaySound(laser02);
							SetAnimation(PLAYER_ANIM_ATTACK_PROJECTILE, 0, true, true, 20, false);
							Projectile *temp;	

							if(ipFlags.S_DIRECTION)
							{
								temp = new ProjectileProjectileAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc+5), static_cast<int>(yLoc));
							}
							else
							{
								temp = new ProjectileProjectileAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc-5), static_cast<int>(yLoc));
							}
					
							(*projectile_list).push_back(temp);
							ipFlags.S_ATTACK = true;
							current_weapon = 9;
						}
					}
					break;	
				case 4:
						if(steph)
						{
							steph_top->SetFrame(0);
							steph_top->SetFrameRate(8);
							steph_top->SetAutoAnimate(true);
							steph_top->AutoStopAnimate();

						}
						else
					{
						if(UseEnergy(QUAKE_ATTACK_ENERGY))
						{
							if (inBossBattle)
								bossUsedOnlyBasicAttack = false;
							
								m_quakeSound->Play();
//						soundPlayer->PlaySound(earthquake);
							quaketimer = 9;
							ipFlags.S_INVULNERABLE = true;
							SetAnimation(PLAYER_ANIM_ATTACK_QUAKE, 0, true, true, 15, false);

							Projectile *temp;	
							temp = new ProjectileQuakeAttack(&xQuakeAttackModifier, &yQuakeAttackModifier,static_cast<int>(xLoc), static_cast<int>(yLoc),projectile_list, &xLoc, &yLoc,&ipFlags);
							(*projectile_list).push_back(temp);
	
							ipFlags.S_ATTACK = true;
							current_weapon = 10;
						}					
					}
					break;
				default:
					break;
			}
		}
//	else if(ipFlags.S_ON_GROUND && player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_STANDARD)
//	{
//		sound_processor->PlaySound(game_sounds->swing00);

//		SetAnimation(PLAYER_ANIM_ATTACK_STANDARD, 0, true, true, 25, true);
//		weapon.SetWeaponDamage(3);
//			ipFlags.S_ATTACK = true;
//	}
	}
}


void Player::processDamage()
{
	ipFlags.S_ATTACK = false;

	m_soundFXDamage->Play();
//soundPlayer->PlaySound(damage00);

	StopMovement();

	if(!(ipFlags.S_CRAWL || ipFlags.S_CROUCH || ipFlags.S_ON_LADDER) &&
		(player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_ELECTRIC) &&
		(player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_FLAME) &&
		(player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_GRENADE) &&
		(player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_PROJECTILE) &&
		(player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_QUAKE))
	{
		SetAnimation(PLAYER_ANIM_DAMAGE, 0, true, false, 10, false);
	
		if(ipFlags.S_DAMAGED_DIRECTION)
			velMovement = 40;
		else
			velMovement = -40;
	}
	else if(ipFlags.S_ON_LADDER)
		velYModifier = 0;
}

void Player::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(PLAYER_ANIM_DEATH, 0, true, true, 5, false);
}

void Player::processDown()
{
	/* State - Climb Ladder */
	if(ipFlags.S_NEXT_TO_LADDER && ipFlags.S_ON_LADDER && !ipFlags.S_JUMP && !ipFlags.S_ON_GROUND)	
		LadderDown();
	/* State - Grab Ladder */
	else if(ipFlags.S_NEXT_TO_LADDER && !ipFlags.S_ON_LADDER && !ipFlags.S_ON_GROUND)
		LadderDownGrab();
	else if(!ipFlags.S_CROUCH && !ipFlags.S_CRAWL && ipFlags.S_ON_GROUND)
	{	
		/*if(ipFlags.PrevMState != move_left && ipFlags.PrevMState != move_right)*/
		{
			ipFlags.S_CROUCH = true;
			ipFlags.S_CRAWL = false;
			SetAnimation(PLAYER_ANIM_CROUCH, 2, false, false, 15, false);
			velMovement = 0;
		}
	}
	else if(ipFlags.S_CROUCH && !ipFlags.S_CRAWL && ipFlags.S_ON_GROUND && ipFlags.S_CROUCH_TOGGLE)
	{
		ipFlags.S_CROUCH_TOGGLE = false;
		ipFlags.S_CRAWL = true;
		
		SetAnimation(PLAYER_ANIM_CRAWL, 0, false, false, 15, false);
	}
}

void Player::processLeft()
{
	if(ipFlags.S_ON_LADDER) /* do nothing */
	{
		/* Check Ladder Type */
		/* Left Facing Ladder */
		if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKRIGHT)
		{
			/* Do nothing for Bottom of Ladder */
			/* Check for Top of Ladder */
		}
		/* Right Facing Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKLEFT)
		{
			/* Do nothing for Bottom of Ladder */	
			ipFlags.S_DIRECTION = false;
		}
		/* Back Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBLADDER)
		{
		}
		/* Rope Climb */
		else if(ipFlags.S_LADDER_TYPE == CLIMBROPE)
		{
		}

		stop();
		
		return;
	}
	else if(!ipFlags.S_JUMP)
	{
		ipFlags.S_DIRECTION = false;

		if(!ipFlags.S_CRAWL)
		{
			ipFlags.S_CROUCH = false;
			ipFlags.S_CROUCH_TOGGLE = false;

			/* Underwater Check */
			if(!ipFlags.S_UNDER_WATER)
			{	
				//if(!ipFlags.S_FALLING)  SetAnimation(PLAYER_ANIM_MOVE, 0, true, false, 23*analog_mod_x, false);
				velMovement = -maxWalkSpeed*analog_mod_x;
				if(!steph)
				{
					//velMovement = static_cast<float>(-maxWalkSpeed * .25*analog_mod_x);
					if(!ipFlags.S_FALLING) SetAnimation(PLAYER_ANIM_MOVE, 0, true, false, 23*analog_mod_x, false);
				}
				else
				{
					//velMovement = static_cast<float>(-maxWalkSpeed * .25*analog_mod_x);
					if(velMovement > -0.8*maxWalkSpeed)
					{
						if(!ipFlags.S_FALLING)  SetAnimation(PLAYER_ANIM_MOVE, 0, true, false, 20*analog_mod_x, false);
					}
					else
					{
						if(!ipFlags.S_FALLING)  SetAnimation(24, 0, true, false, 15*analog_mod_x, false);
					}

				}
			}
			else
			{
				if(!ipFlags.S_FALLING) SetAnimation(PLAYER_ANIM_MOVE, 0, true, false, 12*analog_mod_x, false);
				velMovement = -(maxWalkSpeed * velWaterModifier*analog_mod_x);
			}
		}
		else if(ipFlags.S_CRAWL)
		{
			if(!ipFlags.S_UNDER_WATER)
			{
					velMovement = static_cast<float>(-maxWalkSpeed * .35*analog_mod_x);
					SetAnimation(PLAYER_ANIM_CRAWL, 0, true, false, 15*analog_mod_x, false);
			}
			else
			{
				SetAnimation(PLAYER_ANIM_CRAWL, 0, true, false, 7*analog_mod_x, false);
				velMovement = static_cast<float>(-maxWalkSpeed * .35 * velWaterModifier * 2*analog_mod_x);
			}
		}
	}
	else
	{
		ipFlags.S_DIRECTION = false;

		/* Underwater Check */
		if(!ipFlags.S_UNDER_WATER)
		{	
			velMovement = -maxWalkSpeed*analog_mod_x;
		}
		else
		{
			velMovement = -(maxWalkSpeed * velWaterModifier*analog_mod_x);
		}
	}	
}

void Player::ProcessPreCalculations()
{
	/* Check for Falling State */

	
	//Apply Gravity Constant Modifier
	if(ipFlags.S_ON_GROUND)// || ipFlags.S_NEXT_TO_LADDER)// || (ipFlags.S_NEXT_TO_LADDER && !ipFlags.S_DAMAGED))
	{
		velYJumpModifier = 0;
		velModifier = 0;
		velYModifier = 0;
		ipFlags.S_JUMP = false;
	}
	else if((!ipFlags.S_NO_GRAVITY) && !(ipFlags.S_NEXT_TO_LADDER && ipFlags.S_ON_LADDER))// || ipFlags.S_NEXT_TO_LADDER)
	{
		if(!ipFlags.S_UNDER_WATER)
			velYModifier += static_cast<float>((gravityConstant * 1.5 * time));
		else
			velYModifier += static_cast<float>(((gravityConstant*.25) * velWaterModifier * 1.5 * time));
	}
}

void Player::processRight()
{
	if(ipFlags.S_ON_LADDER) /* do nothing */
	{
		/* Check Ladder Type */
		/* Left Facing Ladder */
		if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKRIGHT)
		{
			/* Do nothing for Bottom of Ladder */
			/* Check for Top of Ladder */
			ipFlags.S_DIRECTION = true;
		}
		/* Right Facing Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBBLOCKLEFT)
		{
			/* Do nothing for Bottom of Ladder */
			/* Check for Top of Ladder */
		}
		/* Back Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBLADDER)
		{
		}
		/* Rope Climb */
		else if(ipFlags.S_LADDER_TYPE == CLIMBROPE)
		{
		}

		stop();
		
		return;
	}
	else if(!ipFlags.S_JUMP)
	{
		ipFlags.S_DIRECTION = true;

		if(!ipFlags.S_CRAWL)
		{
			ipFlags.S_CROUCH = false;
			ipFlags.S_CROUCH_TOGGLE = false;

			/* Underwater Check */
			if(!ipFlags.S_UNDER_WATER)
			{
				//if(!ipFlags.S_FALLING) SetAnimation(PLAYER_ANIM_MOVE, 0, true, false, 23*analog_mod_x, false);
				velMovement = maxWalkSpeed*analog_mod_x;
				if(!steph)
				{
					//velMovement = static_cast<float>(-maxWalkSpeed * .25*analog_mod_x);
					if(!ipFlags.S_FALLING) SetAnimation(PLAYER_ANIM_MOVE, 0, true, false, 23*analog_mod_x, false);
				}
				else
				{
					//velMovement = static_cast<float>(-maxWalkSpeed * .25*analog_mod_x);
					if(velMovement < 0.8*maxWalkSpeed)
					{
						if(!ipFlags.S_FALLING)  SetAnimation(PLAYER_ANIM_MOVE, 0, true, false, 20*analog_mod_x, false);
					}
					else
					{
						if(!ipFlags.S_FALLING)  SetAnimation(24, 0, true, false, 15*analog_mod_x, false);
					}

				}
			}
			else
			{
				if(!ipFlags.S_FALLING) SetAnimation(PLAYER_ANIM_MOVE, 0, true, false, 12*analog_mod_x, false);
				velMovement = (maxWalkSpeed * velWaterModifier*analog_mod_x);
			}
		}
		else if(ipFlags.S_CRAWL)
		{
			if(!ipFlags.S_UNDER_WATER)
			{
				SetAnimation(PLAYER_ANIM_CRAWL, 0, true, false, 15*analog_mod_x, false);
				velMovement = static_cast<float>(maxWalkSpeed * .35 *analog_mod_x);
			}
			else
			{
				SetAnimation(PLAYER_ANIM_CRAWL, 0, true, false, 7*analog_mod_x, false);
				velMovement = static_cast<float>(maxWalkSpeed * .35 * velWaterModifier * 2*analog_mod_x);
			}
		}
	}
	else
	{
		ipFlags.S_DIRECTION = true;

		/* Underwater Check */
		if(!ipFlags.S_UNDER_WATER) velMovement = maxWalkSpeed*analog_mod_x;
		else velMovement = (maxWalkSpeed * velWaterModifier*analog_mod_x);
	}
}

void Player::processUp()
{
	/* State - Climb Ladder */
	if(ipFlags.S_NEXT_TO_LADDER && ipFlags.S_ON_LADDER && !ipFlags.S_JUMP)
	{
		LadderUp();
	}
	/* State - Grab Ladder */
	else if(ipFlags.S_NEXT_TO_LADDER && !ipFlags.S_ON_LADDER && !ipFlags.S_CROUCH && !ipFlags.S_CRAWL)
	{
		LadderUpGrab();
	}
	else if(!ipFlags.S_ON_LADDER && ipFlags.S_CROUCH)
	{
		UnCrouch();
		
		velMovement = 0;
	}
}

void Player::processUpdate()
{
	/* final animation check */
	/*if(ipFlags.S_FINAL_ANIM)
		if((GetYTilePos() > 13) && ipFlags.S_ON_GROUND)
		{
			S_JACOB_INVIS = true;
			ipFlags.S_FINAL_ANIM = false;
			SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);
			return;
		}*/

	UnderWaterCheck();

	/* Begin Calculate Ladder Adjustments */
	LadderCompensate();
	BelowFeetLadderCheck();
	/* End Calculate Ladder Adjustments */

	FallingCheck();

	if(ipFlags.S_JUMP && ipFlags.S_UNDER_WATER)
	{
		if(curLevel->GetLevelData(GetXTilePos(), GetYTilePos() - (GetTileHeight())) == 0 ||//!= 26)
			isTileAboveHead())
		{
			velYJumpModifier += (gravityConstant * time);
			if(velYJumpModifier >= 0)
			{
				ipFlags.S_JUMP = false;
				velYJumpModifier = 0;
			}
		}	
	}

	if(!ipFlags.S_NEXT_TO_LADDER)
	{
//		ipFlags.S_ON_LADDER = false; /* Tuesday Edit */
	}

	if(ipFlags.S_ON_GROUND && ipFlags.S_ON_LADDER && ipFlags.CurMState != move_up)
	{
		ipFlags.S_ON_LADDER = false;
	}


	if(((player_spr->GetFrameSet() == PLAYER_ANIM_DEATH) && !player_spr->IsAnimating() || ipFlags.S_PROCESS_DEATH))
	{
		deathtimer -= time;

		if(deathtimer < 0)
		{
			deathtimer = 2.5;
			Die();
		}
	}

	/* Begin Process Loop */
	if(!ipFlags.S_DAMAGED /*&& !ipFlags.S_PROCESS_DEATH*/)
	{
		if(ipFlags.S_ATTACK)
		{
			if(!player_spr->IsAnimating() && player_spr->GetFrameSet() != PLAYER_ANIM_ATTACK_QUAKE)
			{
					ipFlags.S_ATTACK = false;

					if(!(ipFlags.S_CRAWL || ipFlags.S_CROUCH || ipFlags.S_ON_LADDER) && !ipFlags.S_UNDER_WATER)
					{
						SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);

					}
					else if(!(ipFlags.S_CRAWL || ipFlags.S_CROUCH || ipFlags.S_ON_LADDER))
					{
						SetAnimation(PLAYER_ANIM_JUMP, 10, false, false, 0, true);
					}
			}
			else if(!player_spr->IsAnimating() && player_spr->GetFrameSet() == PLAYER_ANIM_ATTACK_QUAKE)
			{

				quaketimer -= time;

				if(quaketimer <= 0)
				{
					ipFlags.S_INVULNERABLE = false;
					SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);
					quaketimer = 9;
				}
			}
		}
		else
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
				break;

			default:
				break;	
			}
		}
	}



	updateWorldLoc();
	CalcWorldOffset();

#ifdef _DEBUG
			char temp[255];
			sprintf(temp, "[SPENCER] End Update xLoc = %f, yLoc = %f", xLoc, yLoc);
//			OutputDebugString(temp);
#endif
}
void Player::Render()
{
	if(steph) RenderSteph();
	else 
		RenderSpencer();
}

void Player::RenderSteph()
{
	player_spr->SetImage(181);
	if(S_JACOB_INVIS)
		return;

	if(ipFlags.S_DAMAGED || ipFlags.S_INVULNERABLE)
	{
		flashtimer -= time;

		if(flashtimer < 0)
			flashtimer = .04f;

		ipFlags.S_RENDER = !ipFlags.S_RENDER;
	}
	else
	{
		ipFlags.S_RENDER = true;
	}

	if(ipFlags.S_RENDER)
	{
			//steph_top->SetFrameSet(0);
			//steph_top->SetFrameRate(20*analog_mod_x);
		if(ipFlags.S_DIRECTION)
		{
			//Calculate Screen Coordinates & Update
			if(steph)
				steph_top->SetPositionAbsalute(static_cast<int>(240 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			if(((player_spr->GetFrameSet() >= 0) && (player_spr->GetFrameSet() <= 6)) || (player_spr->GetFrameSet() == 24))
			{
				//if(!steph_top->IsAnimating())
				{
					/*int desiredframe = ipFlags.nCurrAttack;
					if(game_class->twCurKeyStates.twkInputNavX > (-3*game_class->twCurKeyStates.twkInputNavY)) ;
					else if((-game_class->twCurKeyStates.twkInputNavY) > (3*game_class->twCurKeyStates.twkInputNavX)) desiredframe+=12;
					else desiredframe+=6;
					if(steph_top->GetFrameSet() != desiredframe)
					{
						steph_top->SetAutoAnimate(false);
						steph_top->SetFrame(0);
						steph_top->SetFrameSet(desiredframe);
					}*/
				}
				if(steph)
					steph_top->Render();
			}
			player_spr->SetPositionAbsalute(static_cast<int>(240 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			player_spr->Render();
		/*	if((player_spr->GetFrameSet() == 9) && (current_weapon != 0))
			{
				blades_sprite->SetFrameSet(current_weapon-1);
				blades_sprite->SetFrame(player_spr->GetFrame());
				blades_sprite->SetPositionAbsalute(static_cast<int>(240 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
				blades_sprite->Render();
			}
			if((player_spr->GetFrameSet() == 5) && (current_weapon != 0))
			{
				blades_sprite->SetFrameSet(current_weapon-1);
				blades_sprite->SetFrame(player_spr->GetFrame());
				blades_sprite->SetPositionAbsalute(static_cast<int>(240 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(142 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
				blades_sprite->Render();
			}*/
			/*RenderHealthBar();
			RenderEnergyBar();

	//	RenderGasHelm();

			if(ipFlags.S_UNDER_WATER)
			{
				RenderAirBar();

		//		if(ipFlags.nCurrAttack == 5)
		//			RenderGasHelm();
			}*/
		}
		else
		{
			//Calculate Screen Coordinates & Update
			if(steph)
				steph_top->SetPositionAbsalute(static_cast<int>(240 - nOffSet  + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			if(((player_spr->GetFrameSet() >= 0) && (player_spr->GetFrameSet() <= 6)) || (player_spr->GetFrameSet() == 24))
			{
				{
					/*int desiredframe = ipFlags.nCurrAttack;
					if((-game_class->twCurKeyStates.twkInputNavX) > (-3*game_class->twCurKeyStates.twkInputNavY)) ;
					else if((-game_class->twCurKeyStates.twkInputNavY) > (-3*game_class->twCurKeyStates.twkInputNavX)) desiredframe+=12;
					else desiredframe+=6;
					if(steph_top->GetFrameSet() != desiredframe)
					{
						steph_top->SetAutoAnimate(false);
						steph_top->SetFrame(0);
						steph_top->SetFrameSet(desiredframe);
					}*/
				}
				if(steph)
					steph_top->RenderHFlip();
			}
			player_spr->SetPositionAbsalute(static_cast<int>(240 - nOffSet  + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			player_spr->RenderHFlip();
			/*if((player_spr->GetFrameSet() == 9) && (current_weapon != 0))
			{
				blades_sprite->SetFrameSet(current_weapon-1);
				blades_sprite->SetFrame(player_spr->GetFrame());
				blades_sprite->SetPositionAbsalute(static_cast<int>(240 - nOffSet  + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
				blades_sprite->RenderHFlip();
			}
			if((player_spr->GetFrameSet() == 5) && (current_weapon != 0))
			{
				blades_sprite->SetFrameSet(current_weapon-1);
				blades_sprite->SetFrame(player_spr->GetFrame());
				blades_sprite->SetPositionAbsalute(static_cast<int>(240 - nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(172 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
				blades_sprite->RenderHFlip();
			}*/
			/*RenderHealthBar();
			RenderEnergyBar();

	//		RenderGasHelm();

			if(ipFlags.S_UNDER_WATER)
			{
				RenderAirBar();

			//	if(ipFlags.nCurrAttack == 5)
		//			RenderGasHelm();
			}*/
		}

		/*if(S_BARRIER_SHIELD)
		{
			for(int i = 0; i < nBarrierOrbs; i++)
			{
				bshield_spr[i]->SetPositionAbsalute(static_cast<int>(240  + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
				bshield_spr[i]->Render();
			}
		}*/

	}
}

void Player::RenderSpencer()
{	
	SetupSprite();
	if(S_JACOB_INVIS)
		return;

	if(ipFlags.S_DAMAGED || ipFlags.S_INVULNERABLE)
	{
		flashtimer -= time;

		if(flashtimer < 0)
			flashtimer = .04f;

		ipFlags.S_RENDER = !ipFlags.S_RENDER;
	}
	else
	{
		ipFlags.S_RENDER = true;
	}

	if(ipFlags.S_RENDER)
	{
		if(ipFlags.S_DIRECTION)
		{
			//Calculate Screen Coordinates & Update
			player_spr->SetPositionAbsalute(static_cast<int>(240 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			player_spr->Render();
		//	if(!ipFlags.S_CROUCH)
		//	{
				if((player_spr->GetFrameSet() == 9)/* && (current_weapon != 0)*/)
				{
					//blades_sprite->SetFrameSet(current_weapon);
					//if (current_weapon == 4)
					//	blades_sprite->SetFrameSet(3);
					//else if (current_weapon == 5)
					//	blades_sprite->SetFrameSet(4);
					
					if (current_weapon >= 4)
						blades_sprite->SetFrameSet(current_weapon-1);
					else	
						blades_sprite->SetFrameSet(current_weapon);
					
					blades_sprite->SetFrame(player_spr->GetFrame());
					blades_sprite->SetPositionAbsalute(static_cast<int>(242 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(165 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
					graphics_engine->DisableAlphaTest();
					blades_sprite->Render();
					graphics_engine->EnableAlphaTest();					
				}
				if((player_spr->GetFrameSet() == 5)/* && (current_weapon != 0)*/)
				{
					if (current_weapon >= 4)
						bladescrouch_sprite->SetFrameSet(current_weapon-1);
					else	
						bladescrouch_sprite->SetFrameSet(current_weapon);
					
					
					bladescrouch_sprite->SetFrame(player_spr->GetFrame());
					bladescrouch_sprite->SetPositionAbsalute(static_cast<int>(242 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(165 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
					graphics_engine->DisableAlphaTest();
					bladescrouch_sprite->Render();
					graphics_engine->EnableAlphaTest();
				}
		/*	}
			else
			{
				if((player_spr->GetFrameSet() == 9) && (current_weapon != 0))
				{
					bladescrouch_sprite->SetFrameSet(current_weapon-1);
					bladescrouch_sprite->SetFrame(player_spr->GetFrame());
					bladescrouch_sprite->SetPositionAbsalute(static_cast<int>(240 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
					bladescrouch_sprite->Render();
				}
				if((player_spr->GetFrameSet() == 5) && (current_weapon != 0))
				{
					bladescrouch_sprite->SetFrameSet(current_weapon-1);
					bladescrouch_sprite->SetFrame(player_spr->GetFrame());
					bladescrouch_sprite->SetPositionAbsalute(static_cast<int>(240 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(142 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
					bladescrouch_sprite->Render();
				}
			}*/
			//RenderHealthBar();
			//RenderEnergyBar();

	//	RenderGasHelm();

			if(ipFlags.S_UNDER_WATER)
			{
				RenderAirBar();

		//		if(ipFlags.nCurrAttack == 5)
		//			RenderGasHelm();
			}
		}
		else
		{
			//Calculate Screen Coordinates & Update
			player_spr->SetPositionAbsalute(static_cast<int>(240 - nOffSet  + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			player_spr->RenderHFlip();
			//if(!ipFlags.S_CROUCH)
			//{
				if((player_spr->GetFrameSet() == 9)/* && (current_weapon != 0)*/)
				{
					if (current_weapon >= 4)
						blades_sprite->SetFrameSet(current_weapon-1);
					else	
						blades_sprite->SetFrameSet(current_weapon);
					
					blades_sprite->SetFrame(player_spr->GetFrame());
					blades_sprite->SetPositionAbsalute(static_cast<int>(238 - nOffSet  + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(165 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
					graphics_engine->DisableAlphaTest();
					blades_sprite->RenderHFlip();
					graphics_engine->EnableAlphaTest();
				}
				if((player_spr->GetFrameSet() == 5)/* && (current_weapon != 0)*/)
				{
					if (current_weapon >= 4)
						bladescrouch_sprite->SetFrameSet(current_weapon-1);
					else	
						bladescrouch_sprite->SetFrameSet(current_weapon);
					
					
					bladescrouch_sprite->SetFrame(player_spr->GetFrame());
					bladescrouch_sprite->SetPositionAbsalute(static_cast<int>(238 - nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(165 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
					graphics_engine->DisableAlphaTest();
					bladescrouch_sprite->RenderHFlip();
					graphics_engine->EnableAlphaTest();
				}
		/*	}
			else
			{
				if((player_spr->GetFrameSet() == 9) && (current_weapon != 0))
				{
					bladescrouch_sprite->SetFrameSet(current_weapon-1);
					bladescrouch_sprite->SetFrame(player_spr->GetFrame());
					bladescrouch_sprite->SetPositionAbsalute(static_cast<int>(240 - nOffSet  + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
					bladescrouch_sprite->RenderHFlip();
				}
				if((player_spr->GetFrameSet() == 5) && (current_weapon != 0))
				{
					bladescrouch_sprite->SetFrameSet(current_weapon-1);
					bladescrouch_sprite->SetFrame(player_spr->GetFrame());
					bladescrouch_sprite->SetPositionAbsalute(static_cast<int>(240 - nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(172 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
					bladescrouch_sprite->RenderHFlip();
				}
			}*/
			RenderHealthBar();
			RenderEnergyBar();

	//		RenderGasHelm();

			if(ipFlags.S_UNDER_WATER)
			{
				RenderAirBar();

			//	if(ipFlags.nCurrAttack == 5)
		//			RenderGasHelm();
			}
		}

		if(S_BARRIER_SHIELD)
		{
			for(int i = 0; i < nBarrierOrbs; i++)
			{
				bshield_spr[i]->SetPositionAbsalute(static_cast<int>(240  + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
				bshield_spr[i]->Render();
			}
		}

	}

/*	HPTRect &temp00 = GetWorldLoc();

	//Calculate Screen Coordinates & Update
	pixel_spr->SetPositionAbsalute(static_cast<int>(temp00.p1.x - xLoc + 120), static_cast<int>(temp00.p1.y - yLoc + 160));
	pixel_spr->Render();
	pixel_spr->SetPositionAbsalute(static_cast<int>(temp00.p2.x - xLoc + 120), static_cast<int>(temp00.p2.y - yLoc + 160));
	pixel_spr->Render();
	pixel_spr->SetPositionAbsalute(static_cast<int>(120), static_cast<int>(160));
	pixel_spr->Render();

	HPTRect &temp01 = GetWeaponWorldLoc();

	//Calculate Screen Coordinates & Update
	pixel_spr->SetPositionAbsalute(static_cast<int>(temp01.p1.x - xLoc + 120), static_cast<int>(temp01.p1.y - yLoc + 160));
	pixel_spr->Render();
	pixel_spr->SetPositionAbsalute(static_cast<int>(temp01.p2.x - xLoc + 120), static_cast<int>(temp01.p2.y - yLoc + 160));
	pixel_spr->Render();*/

/*#if defined _DEBUG

	for(int j = 0; j < 240; j++)
	{
		pixel_spr->SetPositionAbsalute(j, 160);
		pixel_spr->Render();
	}

	for(int s = 0; s < 320; s++)
	{
		pixel_spr->SetPositionAbsalute(120, s);
		pixel_spr->Render();
	}

	HPTRect &temp00 = GetWorldLoc();

	//Calculate Screen Coordinates & Update
	for(int i = temp00.p1.x; i <= temp00.p2.x; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(i - xLoc + 120  + xWorldOffset + xQuakeAttackModifier), static_cast<int>(temp00.p1.y - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
			pixel_spr->Render();
	}

	for(i = temp00.p1.y; i <= temp00.p2.y; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(temp00.p1.x - xLoc + 120  + xWorldOffset + xQuakeAttackModifier), static_cast<int>(i - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
			pixel_spr->Render();
	}

	for(i = temp00.p1.y; i <= temp00.p2.y; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(temp00.p2.x - xLoc + 120  + xWorldOffset + xQuakeAttackModifier), static_cast<int>(i - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
			pixel_spr->Render();
	}

	for(i = temp00.p1.x; i <= temp00.p2.x; i++)
	{
			pixel_spr->SetPositionAbsalute(static_cast<int>(i - xLoc + 120  + xWorldOffset + xQuakeAttackModifier), static_cast<int>(temp00.p2.y - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
			pixel_spr->Render();
	}

	pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp00.p1.x - xLoc + 120  + xWorldOffset + xQuakeAttackModifier), static_cast<int>(temp00.p1.y - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
	pixel_red_spr->Render();
	pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp00.p2.x  - xLoc + 120  + xWorldOffset + xQuakeAttackModifier), static_cast<int>(temp00.p2.y - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
	pixel_red_spr->Render();

	if(ipFlags.S_ATTACK)
	{

	HPTRect &temp01 = GetWeaponWorldLoc();

	//Calculate Screen Coordinates & Update
	for(i = temp01.p1.x; i <= temp01.p2.x; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(i - xLoc + 120 + xWorldOffset + xQuakeAttackModifier), static_cast<int>(temp01.p1.y - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
			pixel_red_spr->Render();
	}

	for(i = temp01.p1.y; i <= temp01.p2.y; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp01.p1.x - xLoc + 120 + xWorldOffset + xQuakeAttackModifier), static_cast<int>(i - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
			pixel_red_spr->Render();
	}

	for(i = temp01.p1.y; i <= temp01.p2.y; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(temp01.p2.x - xLoc + 120 + xWorldOffset + xQuakeAttackModifier), static_cast<int>(i - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
			pixel_red_spr->Render();
	}

	for(i = temp01.p1.x; i <= temp01.p2.x; i++)
	{
			pixel_red_spr->SetPositionAbsalute(static_cast<int>(i - xLoc + 120 + xWorldOffset + xQuakeAttackModifier), static_cast<int>(temp01.p2.y - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
			pixel_red_spr->Render();
	}

	//Calculate Screen Coordinates & Update
	pixel_spr->SetPositionAbsalute(static_cast<int>(temp01.p1.x - xLoc + 120 + xWorldOffset + xQuakeAttackModifier), static_cast<int>(temp01.p1.y - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
	pixel_spr->Render();
	pixel_spr->SetPositionAbsalute(static_cast<int>(temp01.p2.x - xLoc + 120 + xWorldOffset + xQuakeAttackModifier), static_cast<int>(temp01.p2.y - yLoc + 160+ yWorldOffset + yQuakeAttackModifier));
	pixel_spr->Render();
	}
#endif*/
}

void Player::RenderGasHelm()
{
	int tempxoffset;
	int tempyoffset;

	switch(player_spr->GetFrameSet())
	{
	case PLAYER_ANIM_ATTACK_CROUCH:
	case PLAYER_ANIM_CROUCH:
		tempxoffset = 6;
		tempyoffset = 4;
		break;
	case PLAYER_ANIM_CRAWL:
		tempxoffset = 9;
		tempyoffset = 9;
		break;
	default:
		tempxoffset = 4;
		tempyoffset = -10;
		break;
	}

	if(ipFlags.S_DIRECTION)
	{
		gashelm_spr->SetPositionAbsalute(static_cast<int>(120 + tempxoffset + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + tempyoffset + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
		gashelm_spr->Render();
	}
	else
	{
		gashelm_spr->SetPositionAbsalute(static_cast<int>(120 - tempxoffset + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + tempyoffset + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
		gashelm_spr->RenderHFlip();
	}
}

void Player::RenderAirBar()
{
	if(game_class->GetEnableStatus()) return;

	int offSet = (int)(10 * 2 * .5f);

	int curAirLevel = static_cast<int>(underWaterTimer);
	int greenStart = (int)(curAirLevel) + 1;

	for(int i = 0; i <= (10 * 2); i++)
	{
		if((i % 2) == 0)
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (125 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (126 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (127 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (128 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();

			continue;
		}

		if(i * .5 < greenStart - 1)
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (125 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_blue_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (126 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_blue_spr->Render();
			pixel_blue_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (127 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_blue_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (128 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
		}
		
		else if(i * .5 < greenStart)
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (125 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_yellow_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (126 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_yellow_spr->Render();
			pixel_yellow_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (127 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_yellow_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (128 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
		}
		else
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (125 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (126 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_spr->Render();
			pixel_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (127 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (128 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
		}
	}
}

void Player::RenderEnergyBar()
{
	if(game_class->GetEnableStatus()) return;
	int offSet = (int)(GetMaxEnergyLevel() * .20f * 2 * .5f);

	int curEnergy = GetEnergyLevel();
	int greenStart = (int)(curEnergy * .20f) + 1;

	for(int i = 0; i <= (GetMaxEnergyLevel() * .20 * 2); i++)
	{
		if((i % 2) == 0)
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (135 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (136 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (137 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (138 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();

			continue;
		}

		if(i * .5 < greenStart - 1)
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (135 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_green_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (136 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_green_spr->Render();
			pixel_green_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (137 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_green_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (138 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
		}
		
		else if(i * .5 < greenStart)
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (135 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_yellow_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (136 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_yellow_spr->Render();
			pixel_yellow_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (137 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_yellow_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (138 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
		}
		else
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (135 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (136 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_spr->Render();
			pixel_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (137 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (138 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
		}
	}
}

void Player::RenderHealthBar()
{
	if(game_class->GetEnableStatus()) return;
	int offSet = (int)(GetNumLifeBars() * 2 * .5f);

	int curLife = GetCurLife();
//	int yellowStart = (curLife * .20)+1;
	int redStart = (int)(curLife * .20f) + 1;
//	int yellowStart = (curLife * .20) * .66;

	for(int i = 0; i <= (GetNumLifeBars() * 2); i++)
	{
		if((i % 2) == 0)
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (130 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (131 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (132 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (133 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();

			continue;
		}

		if(i * .5 < redStart-1)
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (130 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_red_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (131 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_red_spr->Render();
			pixel_red_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (132 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_red_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (133 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
		}
		else if(i * .5 < redStart)
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (130 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_yellow_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (131 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_yellow_spr->Render();
			pixel_yellow_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (132 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_yellow_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (133 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
		}
		else
		{
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (130 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
			pixel_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (131 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_spr->Render();
			pixel_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (132 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_spr->Render();
			pixel_black_spr->SetPositionAbsalute((120 + i + xWorldOffset - offSet + xTransformOffset + xQuakeAttackModifier), (133 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
			pixel_black_spr->Render();
		}
	}
}

void Player::ResetIPlayer()
{
	IPlayer::ResetIPlayer();

	//nCurLife = MaxLife;

	xWorldOffset = 0;
	yWorldOffset = 0;
	xLevelPos = 0;
	yLevelPos = 0;
	xFallBegin = 0;
	yFallBegin = 0;

	xTransformOffset = 0;
	yTransformOffset = 0;

	ResetTransformQueue();

	SetCurLife(nCurLifeBars * 5);
	SetEnergyLevel(MaxELevel);

	// Acceleration Constants -- Used for calculation during update
	walkAcceleration = 20.0; // Pixels Per Second Per Second
	maxWalkSpeed = 90.00;   // Pixels Per Second	
	climbVelocity = 72.0;
	jumpMaxVelocity = -185.0;
	MaxYVelocity = 14.0;
	MaxPixelDisplacement = 14.0; // Pixels Per Frame

//	S_UNDER_WATER_PREV = false;
//	ipFlags.S_UNDER_WATER = false;
	
	ipFlags.S_ON_LADDER = false;
	ipFlags.S_PROCESS_DEATH = false;
	ipFlags.S_IS_PLAYER = true;
	S_JACOB_INVIS = false;
	ipFlags.S_FINAL_ANIM = false;
	
	SetAttack(0);
}

void Player::ResetIPlayerFlags()
{
	IPlayer::ResetIPlayer();
	
	//nCurLife = MaxLife;
	
	xWorldOffset = 0;
	yWorldOffset = 0;
	xLevelPos = 0;
	yLevelPos = 0;
	xFallBegin = 0;
	yFallBegin = 0;
	
	xTransformOffset = 0;
	yTransformOffset = 0;
	
	ResetTransformQueue();
	
	//SetCurLife(nCurLifeBars * 5);
	//SetEnergyLevel(MaxELevel);
	
	// Acceleration Constants -- Used for calculation during update
	walkAcceleration = 20.0; // Pixels Per Second Per Second
	maxWalkSpeed = 90.00;   // Pixels Per Second	
	climbVelocity = 72.0;
	jumpMaxVelocity = -185.0;
	MaxYVelocity = 14.0;
	MaxPixelDisplacement = 14.0; // Pixels Per Frame
	
	//	S_UNDER_WATER_PREV = false;
	//	ipFlags.S_UNDER_WATER = false;
	
	ipFlags.S_ON_LADDER = false;
	ipFlags.S_PROCESS_DEATH = false;
	ipFlags.S_IS_PLAYER = true;
	S_JACOB_INVIS = false;
	ipFlags.S_FINAL_ANIM = false;
	
	SetAttack(0);	
}

void Player::SetDifficultyLevel(int arg0)
{
	switch(arg0)
	{
	case 0: // EASY
		difficultyDamageModifier = .75;
		difficultyHitModifier  = 2;
		difficultyScoreModifier = .5;
		break;
	case 1: // MEDIUM
		difficultyDamageModifier = 1;
		difficultyHitModifier = 1;
		difficultyScoreModifier = 1;
		break;
	case 2: // BETRAYED
		difficultyDamageModifier = 2;
		difficultyHitModifier = .75;
		difficultyScoreModifier = 2;
		break;
	default:
		break;
	}
}

/*void Player::SetAnimation(int frameset, bool bAutoAnim, bool bAutoStop, bool bReset)
{
	switch(frameset)
	{
	case PLAYER_ANIM_MOVE:
		break;
	case PLAYER_ANIM_STAND:
		break;
	case PLAYER_ANIM_STAND:
		break:
	case PLAYER_ANIM_IDLE:
		break;
	case PLAYER_ANIM_JUMP:
		break;
	case PLAYER_ANIM_ATTACK_JUMP:
		break;
	case PLAYER_ANIM_CROUCH:
		break;
	case PLAYER_ANIM_ATTACK_CROUCH:
		break:
	case PLAYER_ANIM_CRAWL:
		break;
	case PLAYER_ANIM_CLIMB_LADDER_SIDE:
		break;
	case PLAYER_ANIM_CLIMB_LADDER_BACK:
		break;
	case PLAYER_ANIM_ATTACK_STANDARD:
		break;
	case PLAYER_ANIM_ATTACK_ELECTRIC:
		break;
	case PLAYER_ANIM_DAMAGE:
		break;
	case PLAYER_ANIM_ATTACK_FLAME:
		break;
	case PLAYER_ANIM_ATTACK_GRENADE:
		break;
	case PLAYER_ANIM_ATTACK_PROJECTILE:
		break;
	case PLAYER_ANIM_ATTACK_QUAKE:
		break;
	case PLAYER_ANIM_CLIMB_ROPE:
		break;
	default:
		break;
	};
}*/

void Player::setTime(float time)
{
	IPlayer::time = time;
	freeze_for_intro_time -= time;
	if(freeze_for_intro_time < 0) freeze_for_intro = false;

	if(ipFlags.S_DAMAGED)
	{
		ipFlags.fDmgTimer-=time;

		if(ipFlags.fDmgTimer < 0)
		{
			//if(!ipFlags.S_ATTACK && !ipFlags.S_ATTACK)
				ResetStates();
			ipFlags.S_INVULNERABLE = true;
			ipFlags.fInvulnerableTimer = .5;
		}
	}
	else if(ipFlags.S_INVULNERABLE)
	{
		ipFlags.fInvulnerableTimer -= time;

		if(ipFlags.fInvulnerableTimer < 0)
			ipFlags.S_INVULNERABLE = false;
	}
	if(S_BARRIER_SHIELD)
	{
		barrier_shield_timer -= time;
		if(barrier_shield_timer <= 0)
		{
			nBarrierOrbs--;
			if(nBarrierOrbs <= 0)
			{
				S_BARRIER_SHIELD = false;
				nBarrierOrbs = 0;
			}
			else barrier_shield_timer = 3;
		}
	}
}

void Player::SetSpencerVictory()
{
	SetAnimation(PLAYER_ANIM_VICTORY, 0, false, false, 1, true);
}

void Player::setJumpVelocity()
{
	m_jumpSound->Play();
//soundPlayer->PlaySound(jump00);

	/* final animation check */
	if(ipFlags.S_FINAL_ANIM)
		if((GetYTilePos() > 16) && ipFlags.S_ON_GROUND)
		{
			SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);
			return;
		}

	if(player_spr->GetFrameSet() == PLAYER_ANIM_ATTACK_QUAKE)
		return;

	if(ipFlags.S_PROCESS_DEATH)
		return;

	/* Check Ladder Type */
	if(ipFlags.S_ON_LADDER)
	{
		/* Left Facing Ladder */
		if((ipFlags.S_LADDER_TYPE == CLIMBBLOCKRIGHT) && (ipFlags.PrevMState == move_left))
		{
			ipFlags.S_DIRECTION = false;
		}
		/* Right Facing Ladder */
		else if((ipFlags.S_LADDER_TYPE == CLIMBBLOCKLEFT) && (ipFlags.PrevMState == move_right))
		{
			ipFlags.S_DIRECTION = true;
		}
		/* Back Ladder */
		else if(ipFlags.S_LADDER_TYPE == CLIMBLADDER)
		{
		}
		/* Rope Climb */
		else if(ipFlags.S_LADDER_TYPE == CLIMBROPE)
		{
			if(S_ROPE_PULL)
				return;
		}
		else
			return;
	}
	
	if(ipFlags.S_CROUCH)
		if(isTileAboveHead()) return;

	if(isSpecialAttack()) return;

	yLoc -= 1;	
	velYModifier = 0;
	ipFlags.S_ON_GROUND = false;
	ipFlags.S_ON_LADDER = false;
	ipFlags.S_NEXT_TO_LADDER = false;
	ipFlags.S_NO_GRAVITY = false;
	ipFlags.S_JUMP = true;
	ipFlags.S_CROUCH = false;
	ipFlags.S_CRAWL = false;
	ipFlags.S_CROUCH_TOGGLE = false;

	if(!ipFlags.S_UNDER_WATER)
	{
		velYJumpModifier = jumpMaxVelocity;
		SetAnimation(PLAYER_ANIM_JUMP, 0, true, true, 15, true);
	}
	else 
	{
		velYJumpModifier = jumpMaxVelocity * velWaterJumpModifier;
		SetAnimation(PLAYER_ANIM_JUMP, 0, true, true, 9, true);
	}
}

bool Player::isSpecialAttack()
{
	if((player_spr->GetFrameSet() == PLAYER_ANIM_ATTACK_ELECTRIC) ||
	   (player_spr->GetFrameSet() == PLAYER_ANIM_ATTACK_FLAME) ||
	   (player_spr->GetFrameSet() == PLAYER_ANIM_ATTACK_GRENADE) ||
	   (player_spr->GetFrameSet() == PLAYER_ANIM_ATTACK_PROJECTILE) ||
	   (player_spr->GetFrameSet() == PLAYER_ANIM_ATTACK_QUAKE))
	   return true;

	return false;
}

void Player::stop()
{

	if(!ipFlags.S_DAMAGED)
		velMovement = 0;
	/* On Ladder & Next To Ladder */
	if(ipFlags.S_NEXT_TO_LADDER && ipFlags.S_ON_LADDER && !ipFlags.S_JUMP)
	{
		velYModifier = 0;
		if(!((player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_LADDER_TRANSITION) ||
		     (player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_ROPE_TRANSITION)   ||
			 (player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_ROPE_TRANSITION_DOWN)))
		{
			if(player_spr->GetFrameSet() == PLAYER_ANIM_CLIMB_ROPE)
				player_spr->SetFrame(0);
			player_spr->SetAutoAnimate(false);
		}
	}
	else if(ipFlags.S_NEXT_TO_LADDER && !ipFlags.S_JUMP && !ipFlags.S_DAMAGED && !ipFlags.S_INVULNERABLE)
	{
		if(!(ipFlags.S_CROUCH || ipFlags.S_CRAWL) && !ipFlags.S_ON_LADDER)
		{
			SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);

		}
		else if(ipFlags.S_CROUCH)
			SetAnimation(PLAYER_ANIM_CROUCH, 2, false, false, 15, false);
		else if(ipFlags.S_CRAWL)
			SetAnimation(PLAYER_ANIM_CRAWL, 0, true, false, 15, false);

	}

	if(!ipFlags.S_JUMP && !(ipFlags.S_CROUCH || ipFlags.S_CRAWL) && !ipFlags.S_ON_LADDER)
	{
		velMovement = 0;

		if(ipFlags.S_ON_GROUND)
		{
			SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);
		}
	}

	if(ipFlags.S_CROUCH)
		ipFlags.S_CROUCH_TOGGLE = true;
	else 
		ipFlags.S_CROUCH_TOGGLE = false;

	if(ipFlags.S_CRAWL)
		player_spr->SetAutoAnimate(false);
}

void Player::UnCrouch()
{
	/* State - UnCrouch */
	if(ipFlags.S_CROUCH)
	{
		if(isTileAboveHead())
			return;

		ipFlags.S_CROUCH = false;
		ipFlags.S_CRAWL = false;
		ipFlags.S_CROUCH_TOGGLE = false;

		if(ipFlags.S_ON_GROUND)
		{
			SetAnimation(PLAYER_ANIM_STAND, 0, true, false, 3, false);
		}
	}
}

void Player::UnderWaterCheck()
{
	if(S_UNDER_WATER_PREV != ipFlags.S_UNDER_WATER && (curLevel->GetLevelData(GetXTilePos(), GetYTilePos()) == 26))
	{
		S_UNDER_WATER_PREV = ipFlags.S_UNDER_WATER;
		velYModifier = 40;
		velYJumpModifier = 0;

		m_splashSound->Play();
//	soundPlayer->PlaySound(watersplash);
		
		if(ipFlags.S_ON_LADDER && (ipFlags.S_LADDER_TYPE == CLIMBLADDER))
			if(ipFlags.S_UNDER_WATER)
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_BACK, 0, true, false, 7, true);
				velYModifier = climbVelocity * velWaterModifier;
			}
			else
			{
				SetAnimation(PLAYER_ANIM_CLIMB_LADDER_BACK, 0, true, false, 15, true);
				velYModifier = climbVelocity;
			}
	}
	

	if(ipFlags.S_UNDER_WATER)
	{
		//if(ipFlags.nCurrAttack == 5)
		{

			bubbletimer -= time;

			if(bubbletimer < 0)
			{
				Projectile *temp;
				temp = new ProjectileBubble(static_cast<int>(xLoc), static_cast<int>(yLoc - 15));
				(*projectile_list).push_back(temp);
				bubbletimer = static_cast<float>(rand()%2+.5f);
			}
		}
	}

	/*Check for underwater*/
	/*
	if(ipFlags.S_UNDER_WATER && (ipFlags.nCurrAttack != 5))
	{
		underWaterTimer -= time;
		if(underWaterTimer < 0)
			doWaterDamage(1);
	}
	else
		underWaterTimer = 10;
	 */
}

void Player::UpdateLevel()
{
	// Check Player Bounding Rect
	HPTRect hptRectTemp = curLevel->GetWorldBounds();

	xTransformOffset = GetXTransformQueue();
	yTransformOffset = GetYTransformQueue();

	xLevelPos = static_cast<float>(240-xLoc+xTransformOffset);
	yLevelPos = static_cast<float>(160-yLoc+yTransformOffset);
	
	if(xLoc < 240) xLevelPos = 0;
	else if(xLoc > hptRectTemp.p2.x) xLevelPos = -(hptRectTemp.p2.x - 240);
	if(yLoc < 160) yLevelPos = 0;
	else if(yLoc > hptRectTemp.p2.y) yLevelPos = -(hptRectTemp.p2.y - 160);

	curLevel->SetLevelPosition(static_cast<float>(xLevelPos+xQuakeAttackModifier), static_cast<float>(yLevelPos+yQuakeAttackModifier));
}



float Player::GetModifier()
{
	return difficultyScoreModifier;
}

int Player::GetBasicAttackDamage()
{
	return basic_weapon_damage_amount;
}

void Player::SetBasicAttackDamage(int arg)
{
	basic_weapon_damage_amount = arg;
}

void Player::AddBasicAttackUpgrade()
{
	basic_weapon_damage_amount *= 2;
}

void Player::FreezeForIntro()
{
	
	moveStop();
	ResetStates();
	Update();

	freeze_for_intro = true;
	freeze_for_intro_time = 3.5f;


}


void Player::SetAnalogX(float arg)
{
	if(steph) analog_mod_x = arg*1.8;
	else if(game_class->GetSaveGameManager()->IsUnlockEnabled(SaveGameManager::SpencerBoost))
		analog_mod_x = arg*1.5;
	else
		analog_mod_x = arg*1.3;
}

void Player::SetAnalogModY(float arg)
{
	analog_mod_y = arg;
}

void Player::SetAnalogMods()
{
//	velMovement *= analog_mod_x;
//	velYModifier *= analog_mod_y;

}

void Player::AddWeapon(int arg)
{
	if(arg != 0)
	{
		bool anyAlready = false;
		for (int i = 1; i < 6; i++)
		{
			if(weapons[i])
				anyAlready = true;
		}
		if(anyAlready)
			TutorialManager::Instance().Trigger(TutorialManager::TWEAPON2);
		else if (weapons[arg] != true)
			TutorialManager::Instance().Trigger(TutorialManager::TWEAPON);
	}

	weapons[arg] = true;
	if(ipFlags.nCurrAttack == 0) SetAttack(arg);
}

void Player::ResetWeapons()
{
	for (int i = 0; i < 6; i++)
		weapons[i] = false;
}

bool Player::IsWeaponAvailable(int arg)
{
	return weapons[arg];
}

void Player::NextAttack()
{
	do
	{
		ipFlags.nCurrAttack++;
		if(ipFlags.nCurrAttack >= 6)
			if(AnyWeapons()) ipFlags.nCurrAttack = 0;
			else ipFlags.nCurrAttack = 0;
	}
	while(!weapons[ipFlags.nCurrAttack]);
}

void Player::PrevAttack()
{
	do
	{
		ipFlags.nCurrAttack--;
		if(AnyWeapons()) if(ipFlags.nCurrAttack < 0) ipFlags.nCurrAttack = 5;
		else if(ipFlags.nCurrAttack < 0) ipFlags.nCurrAttack = 5;
	}
	while(!weapons[ipFlags.nCurrAttack]);

}

void Player::ClearWeapons()
{
	memset(weapons,1,7);
	weapons[0] = true;
//	weapons[1] = true;
//	weapons[3] = true;
	ipFlags.nCurrAttack = 0;
}

void Player::SetAttack(int nAttack)
{
	ipFlags.nCurrAttack = nAttack;
	
	if(nAttack <= 0 || nAttack >= 6) ipFlags.nCurrAttack = 1;
	if(!weapons[ipFlags.nCurrAttack])
	{
		do
		{
			ipFlags.nCurrAttack++;
			if(ipFlags.nCurrAttack >= 6)
			{
				ipFlags.nCurrAttack = 0;
			
				for (int i = 1; i <= 6; i++) // attempt to set a non-knife weaopon (iPhone)
				{
					if (weapons[i])
					{
						ipFlags.nCurrAttack = i;
						break;
					}
				}
			}
		}
		while(!weapons[ipFlags.nCurrAttack]);
	}
}

void Player::SetupSprite()
{
	switch(ipFlags.nCurrAttack)
	{
	case 2:
		player_spr->SetImage(CR::AssetList::SpencerOrange,false);
		break;
	case 3:
		player_spr->SetImage(CR::AssetList::SpencerGreen,false);
		break;
	case 4:
		player_spr->SetImage(CR::AssetList::SpencerRed,false);
		break;
	default:
		player_spr->SetImage(CR::AssetList::Player_Spencer,false);
		break;
	};
}

bool Player::AnyWeapons()
{
	/*if((!weapons[1]) && (!weapons[2]) && (!weapons[3]) && (!weapons[4]) && (!weapons[5]) && (!weapons[6]))
		return false;
	else*/ return true;
}

void Player::AddGrenades(int arg)
{
	TutorialManager::Instance().Trigger(TutorialManager::TGRENADES);

	number_grenades += arg;
	
	if (number_grenades > 5)
		number_grenades = MAX_GRENADES;
}

void Player::ThrowGrenade()
{


	if(ipFlags.S_JUMP || ipFlags.S_ATTACK || ipFlags.S_CROUCH || ipFlags.S_CRAWL || ipFlags.S_ON_LADDER || ipFlags.S_FALLING)
		return;

	velMovement = 0;
	velModifier = 0;
	if(number_grenades > 0)
		{
		number_grenades--;

		m_swingSound->Play();
//		soundPlayer->PlaySound(swing00);
			m_swingSound->Play();
			SetAnimation(PLAYER_ANIM_ATTACK_GRENADE, 0, true, true, 25, false);
			Projectile *temp;	

			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileGrenadeAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc+15), static_cast<int>(yLoc), projectile_list);
			}
			else
			{
				temp = new ProjectileGrenadeAttack(ipFlags.S_DIRECTION, static_cast<int>(xLoc-15), static_cast<int>(yLoc), projectile_list);
			}
	
			(*projectile_list).push_back(temp);
			ipFlags.S_ATTACK = true;
		}
}

int Player::GetGrenades()
{
	return number_grenades;
}

void Player::SetGremades(int arg)
{
	number_grenades = arg;
	
	if (number_grenades > 5)
		number_grenades = MAX_GRENADES;
}

void Player::ResetStates()
{
	//ipFlags.S_ATTACK = false;
	ipFlags.S_JUMP = false;
	//ipFlags.S_CROUCH = false;
	ipFlags.S_HEAD_COLLISION = false;
	ipFlags.S_ON_GROUND = false;
	ipFlags.S_NEXT_TO_LADDER = false;
	ipFlags.S_DAMAGED = false;
	ipFlags.nDamageAmount = 0;
	ipFlags.fDmgTimer = 0;
}