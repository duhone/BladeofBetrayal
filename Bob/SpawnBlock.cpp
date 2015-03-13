// SpawnBlock.cpp: implementation of the SpawnBlock class.
//
//////////////////////////////////////////////////////////////////////


#include "SpawnBlock.h"
#include "AssetList.h"
#include "Game.h"

extern Game* game_class;

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SpawnBlock::SpawnBlock()
{
	sprite->SetImage(CR::AssetList::Spawn_Flag);
	sprite->SetAutoAnimate(true);
	sprite->SetFrameSet(0);
	sprite->SetFrame(0);
	draw = true;
	state = 0;
	isCollidable = false;
	
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::breakglass::ID);
}

SpawnBlock::~SpawnBlock()
{
}

bool SpawnBlock::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype)
{

/*	if(arg->GetStateFlags()->S_IS_PLAYER)
	{
		draw = false;
		arg->SetSpawnPoint();
		return true;
	}
	else*/ return false;
}

bool SpawnBlock::WeaponCollideCheck(IPlayer* arg)
{
	if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
	switch(state)
	{
	case 0:
		state = 1;
			sprite->SetImage(CR::AssetList::spawn_flag_explosion);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		arg->SetSpawnPoint(worldx,worldy);
		game_class->CaptureSpawnPointInfo();
			
		m_soundFX->Play();
//		soundPlayer->PlaySound(breakwindow);
		break;
	};
	return false;
}

bool SpawnBlock::ProjectileCollideCheck(IPlayer *arg0, Projectile* arg)
{
	if(!arg->GetSource())
	{
		arg->DeActivate();
		return false;
	}
	switch(state)
	{
	case 0:
		state = 1;
			sprite->SetImage(CR::AssetList::spawn_flag_explosion);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		ProjectileFlags& proj_flags = arg->GetProjectileFlags();
		arg0->SetSpawnPoint(worldx,worldy);
		game_class->CaptureSpawnPointInfo();
		m_soundFX->Play();
//		soundPlayer->PlaySound(breakwindow);
			
		if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
		return false;
		break;
	};
//	ProjectileFlags& proj_flags = arg->GetProjectileFlags();

//	if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
	return false;
}

void SpawnBlock::Update()
{
	switch(state)
	{
	case 0:
		draw = true;
		break;
	case 1:
		if(!sprite->IsAnimating())
		{
			state = 2;
/*			if(type == 1) sprite->SetImage(0,42);
			if(type == 2) sprite->SetImage(0,43);
			if(type == 5) sprite->SetImage(0,44);
			if(type == 4) sprite->SetImage(0,45);
			if(type == 3) sprite->SetImage(0,46);
			if(type == 6) sprite->SetImage(0,47);
			sprite->SetFrameSet(0);
			sprite->SetFrame(0);
			sprite->SetAutoAnimate(true);
*/
//			draw = false;
		}

		break;
	};
}

void SpawnBlock::SetState(int _value)
{
	state = _value;
	
	// open the crate, if it was in an open state
	if (state == 1 || state == 2 || state == 3)
	{
		sprite->SetImage(CR::AssetList::spawn_flag_explosion);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		state = 1; // reset state to 1, so the animation runs to completion
	}
}