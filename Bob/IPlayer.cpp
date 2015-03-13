// IPlayer.cpp: implementation of the IPlayer class.
//
//////////////////////////////////////////////////////////////////////


#include "IPlayer.h"
#include <iostream>
#include "AssetListNew.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IPlayer::IPlayer() : m_attackWhenDamaged(false)
{
	stunned = false;
	take_all_damage = true;
	analog_mod_x = 1;

	analog_mod_y = 1;
	freeze_for_intro = false;
	rectDX = 0;
	rectDY = 0;
	rectXOffset = 0;
	rectYOffset = 0;

	SetWeaponDamage(1);

	flashtimer = .04f;

	fDmgTimer = .25f;

	xLoc = 0;
	xLocPrev = 0;
	xTilePos = 0;
	yLoc = 0;
	yLocPrev = 0;
	yTilePos = 0;

	velYJumpModifier = 0;
	velGravityModifier = 0;
	velModifier = 0;
	velYModifier = 0;
	velMovement = 0;
	velWaterJumpModifier = .75f;
	velWaterModifier = .5f;

	/* Rendering Offsets */
	nOffSet = 0;
	nyOffSet = 0;

	//Load Sprite Images
	player_spr = 0;

	/* Constant Variables */
	LifePerBar = 5;
	MaxLifeBars = 15;
	MaxLife = MaxLifeBars * LifePerBar;

	nLives = 3;

	// Acceleration Constants -- Used for calculation during update
	walkAcceleration = 15.0; // Pixels Per Second Per Second
	maxWalkSpeed = 60.00;   // Pixels Per Second	
	climbVelocity = 50.0;
	jumpMaxVelocity = -200.0;
	MaxYVelocity = 14.0;
	MaxPixelDisplacement = 14.0; // Pixels Per Frame
	gravityConstant = 0;

	CurELevel = 20;

	time = 0;

	nWeaponDamage = 0;

//	SetRenderOffset(0);
//	SetMaxWalkVelocity(enemy_ninja_max_walk_velocity);
//	SetWalkAcceleration(enemy_ninja_walk_acceleration);
	SetPlayerRectangle(15, 45);
//	InitializeCriticalSection(&InputCriticalSection);

	SetRectangle(rectWorldLoc, 0, 0, 0, 0);
	
	x_transform_queue = 0;
	y_transform_queue = 0;
	xTransformOffset = 0;
	yTransformOffset = 0;

	nMaxAttacks = 20;

	m_soundFXDamage = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::damage::ID);
//	InitializeCriticalSection(&cs);
}

IPlayer::~IPlayer()
{
/*	pixel_spr->Release();
	pixel_red_spr->Release();
	pixel_yellow_spr->Release();
	pixel_black_spr->Release();
	pixel_green_spr->Release();
	pixel_blue_spr->Release();*/
	if(player_spr != 0)
		player_spr->Release();

	ipFlags.InputQueue.clear();

	for(int count = 0;count < hold_sprites.size();count++)
	{
		HPTSprite1 *temp = hold_sprites[count];
		temp->Release();
	}
	hold_sprites.clear();
//	DeleteCriticalSection(&cs);
}

void IPlayer::AddEnergy(int nEnergy)
{
	CurELevel += nEnergy;
	
	if(CurELevel > MaxELevel) CurELevel = MaxELevel;
	if(CurELevel <0) CurELevel = 0;
}

void IPlayer::AddExtraLife()
{
	nLives++;
}

void IPlayer::AddLife(int nLife)
{
	nCurLife += nLife; 
	if(nCurLife > (nCurLifeBars * health_per_life_bar))
		nCurLife = (nCurLifeBars * health_per_life_bar);
}

void IPlayer::ApplyGravity()
{
	velYModifier += (gravityConstant * time);
}

void IPlayer::CycleAttack()
{
	ipFlags.nCurrAttack++;
	
	if(ipFlags.nCurrAttack >= nMaxAttacks) ipFlags.nCurrAttack = 0;
}

void IPlayer::doDamage(int nDamageAmount, bool sDirection,int damage_type,bool silent/* = false*/)
{

	doDoor(damage_type);
	
	/*if(!stunned)
	{
		if(damage_type == 1)
		{
			if((take_all_damage) || (damage_resistance[damage_type] != 10))
			{
				player_spr->PauseAnimation(true);
				stunned = true;
				if(!take_all_damage) stunned_time = 3-(damage_resistance[damage_type]*0.3f);
				else stunned_time = 3;
			}
		}
	}*/
	
	if(!take_all_damage)
	{
		int resistance = damage_resistance[damage_type];
		if(resistance == 10)
			nDamageAmount = 0;
		else
		{
			float fresist = 1.0f-((float)resistance/10.0f);
			nDamageAmount *= fresist;
		}
	}

	if(!ipFlags.S_DAMAGED && !ipFlags.S_INVULNERABLE && !ipFlags.S_PROCESS_DEATH && !ipFlags.door)
	{
		ipFlags.nDamageAmount = nDamageAmount;
		ipFlags.S_DAMAGED = true;
		ipFlags.fDmgTimer = fDmgTimer;	
		ipFlags.S_DAMAGED_DIRECTION = sDirection;
		nCurLife -= nDamageAmount;

		if(!ipFlags.S_DEAD)
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

void IPlayer::forceDeath()
{
	int nDamageAmount = nCurLife + 1;
	bool sDirection = false;
	
	forceOpenDoor();
	
	if(!ipFlags.S_DAMAGED && !ipFlags.S_INVULNERABLE && !ipFlags.S_PROCESS_DEATH && !ipFlags.door)
	{
		ipFlags.nDamageAmount = nDamageAmount;
		ipFlags.S_DAMAGED = true;
		ipFlags.fDmgTimer = fDmgTimer;	
		ipFlags.S_DAMAGED_DIRECTION = sDirection;
		nCurLife -= nDamageAmount;
		
		if(!ipFlags.S_DEAD)
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

int IPlayer::GetXTransformQueue()
{
	if(x_transform_queue > 0)
	{
		x_transform_queue -= (300 * time);

		if(x_transform_queue < 0)
			x_transform_queue = 0;
	}
	else if(x_transform_queue < 0)
	{
		x_transform_queue += (300 * time);

		if(x_transform_queue > 0)
			x_transform_queue = 0;
	}

	return static_cast<int>(x_transform_queue);
}

int IPlayer::GetYTransformQueue()
{
	if(y_transform_queue > 0)
	{
		y_transform_queue -= (300 * time);

		if(y_transform_queue < 0)
			y_transform_queue = 0;
	}
	else if(y_transform_queue < 0)
	{
		y_transform_queue += (300 * time);

		if(y_transform_queue > 0)
			y_transform_queue = 0;
	}

	return static_cast<int>(y_transform_queue);
}

void IPlayer::ProcessPreCalculations()
{
	if(ipFlags.S_ON_GROUND)
	{
		if(ipFlags.S_IS_PLAYER)
			velMovement = 0;
		
		velYJumpModifier = 0;
		velModifier = 0;
		velYModifier = 0;
		ipFlags.S_JUMP = false;
	}
	else if((!ipFlags.S_NO_GRAVITY))
	{
		velYModifier += (gravityConstant * time);
	}
}

void IPlayer::ProcessPostCalculations()
{
	//Store Location
	xLocPrev = xLoc;
	yLocPrev = yLoc;
	
	//Calculate Displacement
	yDisplacement = (velYModifier + velYJumpModifier) * time;
	xDisplacement = (velModifier + velMovement) * time;

	if((yDisplacement > 0) && (yDisplacement > MaxPixelDisplacement))
		yDisplacement = MaxPixelDisplacement;
	else if((yDisplacement < 0) && (yDisplacement < -MaxPixelDisplacement))
		yDisplacement = -MaxPixelDisplacement;

	if((xDisplacement > 0) && (xDisplacement > MaxPixelDisplacement))
		xDisplacement = MaxPixelDisplacement;
	else if((xDisplacement < 0) && (xDisplacement < -MaxPixelDisplacement))
		xDisplacement = -MaxPixelDisplacement;

	if(ipFlags.S_CONVEYOR)
	{
		if(ipFlags.S_CONVEYOR_TYPE)	xDisplacement += (50*time);
		else xDisplacement -= (50*time);
	}
	
	yLoc += yDisplacement;
	xLoc += xDisplacement;

	/* Reset Level Check Flags */
	if(ipFlags.S_NEXT_TO_LADDER)
		ipFlags.S_NEXT_TO_LADDER = false;

	if(!ipFlags.S_LADDER_TYPE)
		ipFlags.S_LADDER_TYPE = 0;

	if(ipFlags.S_DIRECTION)
	{
		rectWorldLoc.p1.x = static_cast<int>(xLoc) + 0 + rectXOffset + xTransformOffset;
		rectWorldLoc.p2.x = static_cast<int>(xLoc) + rectDX + rectXOffset + xTransformOffset;
		rectWorldLoc.p1.y = static_cast<int>(yLoc) + 0 + rectYOffset + yTransformOffset;
		rectWorldLoc.p2.y = static_cast<int>(yLoc) + rectDY + rectYOffset + yTransformOffset;
	}
	else
	{
		rectWorldLoc.p1.x = static_cast<int>(xLoc) - rectDX - rectXOffset + xTransformOffset;
		rectWorldLoc.p2.x = static_cast<int>(xLoc) - 0 - rectXOffset + xTransformOffset;
		rectWorldLoc.p1.y = static_cast<int>(yLoc) + 0 + rectYOffset + yTransformOffset;
		rectWorldLoc.p2.y = static_cast<int>(yLoc) + rectDY + rectYOffset + yTransformOffset;	
	}
}

void IPlayer::ResetIPlayer()
{
	ipFlags.S_ACTIVE = true;
	ipFlags.S_ATTACK = false;
	ipFlags.S_ATTACK_COLLISION = false;
	ipFlags.S_CONVEYOR = false;
	ipFlags.S_CONVEYOR_TYPE = false;
	ipFlags.S_CRAWL = false;
	ipFlags.S_CROUCH = false;
	ipFlags.S_CROUCH_TOGGLE = false;
	ipFlags.S_DAMAGED = false;
	ipFlags.S_DAMAGED_DIRECTION = false;
	ipFlags.S_DEAD = false;
	ipFlags.S_DIRECTION = true;
	ipFlags.S_FALLING = false;
	ipFlags.S_HEAD_COLLISION = false;
	ipFlags.S_INVULNERABLE = false;
	ipFlags.S_JUMP = false;
	ipFlags.S_LADDER_TYPE = false;
	ipFlags.S_NEXT_TO_LADDER = false;
	ipFlags.S_NO_GRAVITY = false;
	ipFlags.S_ON_GROUND = false;
	ipFlags.S_POINTS = false;
	ipFlags.S_PROCESS_DEATH = false;
	ipFlags.S_RENDER = true;
	ipFlags.S_RENDER_DIRECTION = true;
	ipFlags.S_RENDER_HEALTH_BAR = true;
	ipFlags.S_UNDER_WATER = false;
	ipFlags.S_VISIBLE = true;
	ipFlags.S_FINAL_ANIM = false;
	ipFlags.S_FREEZE_INPUT = false;

	ipFlags.CurMState = move_stop;
	ipFlags.ReqIState = input_0;
	ipFlags.PrevMState = move_0;
	ipFlags.CurAState = anim_0;

	ipFlags.nDamageAmount = 0;
	ipFlags.nCurrAttack = 0;
	ipFlags.fDmgTimer = 0;

	velModifier=0;
	velMovement=0;
	velYModifier=0;
	velYJumpModifier=0;
	velGravityModifier=0;
	gravityConstant=0;	
}

void IPlayer::ResetStates()
{
	//ipFlags.S_ATTACK = false;
	ipFlags.S_JUMP = false;
	ipFlags.S_CROUCH = false;
	ipFlags.S_HEAD_COLLISION = false;
	ipFlags.S_ON_GROUND = false;
	ipFlags.S_NEXT_TO_LADDER = false;
	ipFlags.S_DAMAGED = false;
	ipFlags.nDamageAmount = 0;
	ipFlags.fDmgTimer = 0;
}

void IPlayer::ResetTransformQueue()
{
	x_transform_queue = 0;
	y_transform_queue = 0;
}

// Time Since Last Frame
void IPlayer::setTime(float time)
{
	if(stunned)
	{
		stunned_time -= time;
		if(stunned_time <= 0)
		{
			stunned = false;
			player_spr->PauseAnimation(false);
		}
		IPlayer::time = 0;

	}
	else IPlayer::time = time;

	if(ipFlags.S_DAMAGED)
	{
		ipFlags.fDmgTimer-=time;

		if(ipFlags.fDmgTimer < 0)
		{
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
}

void IPlayer::SetDirection(bool bDirection)
{
	//cout << "setdir " << bDirection << endl;
	ipFlags.S_DIRECTION = bDirection;
}

bool IPlayer::UseEnergy(int nEnergy)
{
	if((CurELevel - nEnergy) < 0)
	{
		return false;
	}
	else
	{
		CurELevel -= nEnergy;

	//	if(CurELevel < nEnergy)
	//	{
			//set default attack
	//		ipFlags.nCurrAttack = 0;
	//	}
		return true;
	}
}

void IPlayer::SetCurLife(int nLife)
{
	nCurLife = nLife;
}

void IPlayer::SetNumLifeBars(int nBars)
{
	nCurLifeBars = nBars;
}

void IPlayer::SetProjectileList(list<Projectile *> *list)
{
	projectile_list = list;
}

void IPlayer::SetRenderHealthBar(bool arg)
{
	ipFlags.S_RENDER_HEALTH_BAR = arg;
}

void IPlayer::SetMaxWalkVelocity(float fVel)
{
	maxWalkSpeed = fVel;
}

void IPlayer::SetWalkAcceleration(float fAcc)
{
	walkAcceleration = fAcc;
}

void IPlayer::SetWorldLoc(int dx, int dy)
{
	xLoc += dx;
	yLoc += dy;
}

void IPlayer::SetWorldLocAbsolute(int x, int y)
{
	xLoc = static_cast<float>(x);
	yLoc = static_cast<float>(y);
}

void IPlayer::SetWorldLocAbsoluteT(int x, int y, int dx, int dy)
{
	xLoc = static_cast<float>((x*16) + 8 + dx);
	yLoc = static_cast<float>((y*16) - 8 + dy);
	
	
}

// **************************** STATE TRIGGERS *********************************
bool IPlayer::TransitionMovement(M_STATE state)
{
	if(ipFlags.ReqIState != input_0 && !ipFlags.S_PROCESS_DEATH)
	{
		ipFlags.PrevMState = ipFlags.CurMState; //Store Previous Movement State
		
		//Transition Movement State
		switch(ipFlags.ReqIState)
		{
		case input_stop:
			if(ipFlags.CurMState == move_left || ipFlags.CurMState == move_right || ipFlags.CurMState == move_up || ipFlags.CurMState == move_down)
			{
				moveStop();
				ipFlags.CurMState = move_stop;
			}
			break;

		case input_left:
				if((ipFlags.S_FINAL_ANIM || ipFlags.CurMState == move_stop || ipFlags.CurMState == move_right || ipFlags.CurMState == move_down || ipFlags.CurMState == move_up))// && !ipFlags.S_ON_LADDER)
			{
				ipFlags.CurMState = move_left;
			}
			break;

		case input_right:
			if((ipFlags.S_FINAL_ANIM || ipFlags.CurMState == move_stop || ipFlags.CurMState == move_left || ipFlags.CurMState == move_down || ipFlags.CurMState == move_up))// && !ipFlags.S_ON_LADDER)
			{
				ipFlags.CurMState = move_right;
			}
			break;

		case input_up:
			if((ipFlags.CurMState == move_stop || ipFlags.CurMState == move_left || ipFlags.CurMState == move_right || ipFlags.CurMState == move_down))// && !ipFlags.S_JUMP)
			{
				ipFlags.CurMState = move_up; //Transition State To Move Up
			}
			break;

		case input_down:
			if((ipFlags.CurMState == move_stop || ipFlags.CurMState == move_left || ipFlags.CurMState == move_right || ipFlags.CurMState == move_up))// && !ipFlags.S_JUMP)
			{
				ipFlags.CurMState = move_down; //Transition State To Move Down
			}
			break;

		case input_button1: //Special 1 - Reserved Custom Action
			{
				ipFlags.CurMState = move_reserved_action_1;
			}
			break;

		case input_button2: //Special 2 - Reserved Custom Action
			{
				ipFlags.CurMState = move_reserved_action_2;
			}
			break;

		case input_button3:
			if((ipFlags.S_ON_GROUND || ipFlags.S_NEXT_TO_LADDER) && !ipFlags.S_ON_LADDER && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD && !ipFlags.S_JUMP)
			{
				setJumpVelocity();
		//		ipFlags.S_JUMP = true;
		//		ipFlags.S_ON_GROUND = false;
		//		ipFlags.S_CROUCH = false;
			}
			else if((ipFlags.S_ON_GROUND || ipFlags.S_NEXT_TO_LADDER) && ipFlags.S_ON_LADDER && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD && !ipFlags.S_JUMP)
			{
			//	if(ipFlags.S_ON_LADDER && (ipFlags.CurMState == move_left || ipFlags.CurMState == move_right))

				if(!(ipFlags.CurMState == move_up || ipFlags.CurMState == move_down))
					setJumpVelocity();
				
		//		ipFlags.S_JUMP = true;
		//		ipFlags.S_ON_GROUND = false;

			}
			break;

		case input_button4:
			{
				if((!ipFlags.S_DAMAGED || m_attackWhenDamaged) && !ipFlags.S_ATTACK && !ipFlags.S_ON_LADDER && (nCurLife > 0)) //Disable Attack During Damaged State
					processAttack();
			}
			break;
		case input_button5:
			{
				if(!ipFlags.S_DAMAGED && !ipFlags.S_ATTACK && !ipFlags.S_ON_LADDER && (nCurLife > 0)) //Disable Attack During Damaged State
					processAttack2();
			}
			break;
		case FACE_LEFT:
			{
				ipFlags.S_DIRECTION = false;
			}
			break;
		case FACE_RIGHT:
			{
				ipFlags.S_DIRECTION = true;
			}
			break;
		default:
			StopMovement();
			break;
		};
	};

	ipFlags.ReqIState = input_0;

	return true;
}

//************************** END STATE TRIGGERS ********************************

void IPlayer::SetRenderOffset(int argx, int argy)
{
	nOffSet = argx;
	nyOffSet = argy;
}

void IPlayer::SetSprite(int nSet, int nSprite)
{
	if(player_spr != 0)
		player_spr->Release();

	player_spr = graphics_engine->CreateSprite1();	
	player_spr->SetImage(nSprite);
	SetAnimation(0, 0, true, true, 0, true);
}

void IPlayer::SetPlayerRectangle(int dx, int dy)
{
	nPlayerWidth = dx;
	nPlayerHeight = dy;
	nHalfPlayerWidth = dx>>2;
	nHalfPlayerHeight = dy>>2;
}

void IPlayer::velocityModify(int pixSec)
{
	velModifier = static_cast<float>(pixSec);
}

void IPlayer::SetAttack(int nAttack)
{
	if(nAttack < nMaxAttacks)
		ipFlags.nCurrAttack = nAttack;
	else if(nAttack >= nMaxAttacks)
		ipFlags.nCurrAttack = 1;
}

void IPlayer::StandingOnGround(bool val)
{
	ipFlags.S_ON_GROUND = val;
}

void IPlayer::NextToLadder(bool val, int arg2)
{
	ipFlags.S_NEXT_TO_LADDER = val;
	ipFlags.S_LADDER_TYPE = arg2;
}

void IPlayer::setGravityConstant(float gravConst)
{
	gravityConstant = gravConst;
}

void IPlayer::Update()
{	
	if(!ipFlags.S_PROCESS_DEATH)
		ProcessPreCalculations();
	
//	EnterCriticalSection(&cs);
	if(!ipFlags.S_FREEZE_INPUT)
	{
		do
		{
			if(!ipFlags.InputQueue.empty())
			{
				//HPTListIterator<I_STATE> val;

				//Transition Movement State
				ipFlags.ReqIState = (*ipFlags.InputQueue.begin());
				ipFlags.InputQueue.pop_front();
				if(!freeze_for_intro)
					TransitionMovement(ipFlags.CurMState);
			}
		
			processUpdate();
		}
		while(!ipFlags.InputQueue.empty());
	}
//		SetAnalogMods();
//	LeaveCriticalSection(&cs);

/*	while(!ipFlags.InputQueue.empty())
	{
		HPTListIterator<I_STATE> val;
		ipFlags.ReqIState = (*ipFlags.InputQueue.begin());
		ipFlags.InputQueue.pop_front();
		TransitionMovement(ipFlags.CurMState);

		processUpdate();
	}*/

	if(!ipFlags.S_PROCESS_DEATH)
		ProcessPostCalculations();
}



void IPlayer::SetSpawnPoint()
{
	x_spawn = (int)GetXLoc();
	y_spawn = (int)GetYLoc();

}

void IPlayer::SetSpawnPoint(int xarg, int yarg)
{
	x_spawn = xarg;
	y_spawn = yarg;
}

void IPlayer::ReSpawn()
{
	SetWorldLocAbsoluteT(x_spawn>>4,y_spawn>>4);
	
	SetRectangle(rectWorldLoc, 0, 0, 0, 0);
	xLocPrev = x_spawn;
	yLocPrev = y_spawn;
}

void IPlayer::SubtractLife()
{
	//nLives--;
}

void IPlayer::ResetItems()
{
	n_basic_items = 0;
	n_treasure_items = 0;
	n_special_items = 0;
}

void IPlayer::AddBasicItem()
{
	n_basic_items++;
}

void IPlayer::AddTreasureItem()
{
	n_treasure_items++;
}

void IPlayer::AddSpecialItems()
{
	n_special_items++;
}

void IPlayer::AddTransformationQueue(float dx, float dy)
{
	xLoc += dx;
	yLoc += dy;

	x_transform_queue+=dx;
	y_transform_queue+=dy;
}

void IPlayer::AddBasicAttackUpgrade()
{
}

void IPlayer::SetAnalogMods()
{

}

bool IPlayer::GetDead()
{
	if (ipFlags.S_DEAD)
		return true;
	else if (ipFlags.S_PROCESS_DEATH)
		return true;
	else
		return false;
}