// DestroyableBlock.cpp: implementation of the DestroyableBlock class.
//
//////////////////////////////////////////////////////////////////////


#include "DestroyableBlock.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DestroyableBlock::DestroyableBlock()
{
	InitObject();
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::breakcrate::ID);
}

DestroyableBlock::~DestroyableBlock()
{
}

void DestroyableBlock::InitObject()
{
	isCollidable = true;
	sprite->SetImage(CR::AssetList::destrubtable_block_type_1);
	sprite->SetAutoAnimate(false);
	sprite->SetFrameSet(0);
	sprite->SetFrame(0);
	state = 0;
	
	time_to_hit = 0;
	draw = true;
}

bool DestroyableBlock::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype)
{
	//if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
	int tempy;
	switch(state)
	{
	case 0:
		tempy = y;
			
		if(tempy < 0) tempy++;
		arg->SetWorldLoc(x,tempy);
		if(y != 0) y = -100;
		if(x != 0) x = -100;

		break;
	
	};
	return false;
}

void DestroyableBlock::SetHitPoints(int arg)
{
	hit_points = arg;
}

void DestroyableBlock::SetTime(float time_passed)
{
	time_to_hit -= time_passed;

}

bool DestroyableBlock::WeaponCollideCheck(IPlayer* arg)
{
	if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
	if(state == 0)
	{
		if(time_to_hit <= 0)
		{
			hit_points--;
			time_to_hit = 1;
		}
		if(hit_points <= 0)
		{
			state = 1;
//		soundPlayer->PlaySound(cratebreak);
			sprite->SetAutoAnimate(true);
			sprite->AutoStopAnimate();
			m_soundFX->Play();
			//return true;
			isCollidable = false;
		}
	}
	return false;

}

bool DestroyableBlock::ProjectileCollideCheck(IPlayer *arg0, Projectile* arg)
{
	if(!arg->GetSource())
	{
		arg->DeActivate();
		return false;
	}
	if(state == 0)
	{
		if(time_to_hit <= 0)
		{
			hit_points--;
			time_to_hit = 1;
			ProjectileFlags& proj_flags = arg->GetProjectileFlags();
			if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
			return false;
		}
		if(hit_points <= 0)
		{
			state = 1;
			m_soundFX->Play();
//		soundPlayer->PlaySound(cratebreak);
			sprite->SetAutoAnimate(true);
			sprite->AutoStopAnimate();
			ProjectileFlags& proj_flags = arg->GetProjectileFlags();

			if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
			//return true;
			isCollidable = false;
		}
	}
//	ProjectileFlags& proj_flags = arg->GetProjectileFlags();

//	if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
	return false;
}

void DestroyableBlock::Update()
{
	switch(state)
	{
	case 0:
		draw = true;
		//time_to_hit -= time;
	break;
	case 1:
		draw = true;
		if(!sprite->IsAnimating()) state = 2;
		break;
	default:
		draw = false;
		break;
	}

}

void DestroyableBlock::SetState(int _value)
{
	state = _value;
	
	// open the crate, if it was in an open state
	if (state == 1 || state == 2)
	{
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		state = 1; // force animate to completion
	}
}