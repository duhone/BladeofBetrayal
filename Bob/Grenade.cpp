// Grenade.cpp: implementation of the Grenade class.
//
//////////////////////////////////////////////////////////////////////

#include "Grenade.h"
#include "AssetList.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Grenade::Grenade(int arg)
{
	InitObject(arg);
	m_soundFXBlip = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::blip::ID);
}

Grenade::~Grenade()
{
}

void Grenade::InitObject(int arg)
{
	isCollidable = true;
	gotObject = false;
	type = arg;
	sprite->SetImage(CR::AssetList::Regular_crate);
	sprite->SetAutoAnimate(false);
	sprite->SetFrameSet(0);
	sprite->SetFrame(0);
	sprite->SetFrameRate(2);
	draw = true;
	
	if(type == 1)
	{
		amount = 1;
		sprite2->SetImage(CR::AssetList::Single_grenade);
	}
	if((type == 2))
	{
		amount = 5;
		sprite2->SetImage(CR::AssetList::Multiple_grenade);
	}
	
	sprite2->SetAutoAnimate(true);
	sprite2->SetFrameSet(0);
	sprite2->SetFrame(0);
	sprite2->SetFrameRate(5);
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::breakcrate::ID);
	state = 0;
	draw2 = false;
}

bool Grenade::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype)
{
	//if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
	int tempy;
	switch(state)
	{
	case 0:case 1:
		tempy = y;
			
		if(tempy < 0) tempy++;
		arg->SetWorldLoc(x,tempy);
		if(y != 0) y = -100;
		if(x != 0) x = -100;
		

		break;
	case 2:
		if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
		m_soundFXBlip->Play();
		//	soundPlayer->PlaySound(blip);
		arg->AddGrenades(amount);
		state = 3;
		draw2 = false;
		gotObject = true;
		//return true;
		break;
	};
	return false;
}

void Grenade::Update()
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
/*			if(type == 1) sprite->SetImage(10);
			if(type == 2) sprite->SetImage(11);
			sprite->SetFrameSet(0);
			sprite->SetFrame(0);
			sprite->SetAutoAnimate(true);*/
		}

		break;
	};
}

bool Grenade::WeaponCollideCheck(IPlayer* arg)
{
	if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
	switch(state)
	{
	case 0:
		state = 1;
		//	soundPlayer->PlaySound(cratebreak);
		sprite->SetFrameSet(1);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(10);
		draw2 = true;
		m_soundFX->Play();
			
		SetPointValue(P_DEST_BLOCK_RED);
		isCollidable = false;
		break;
	};
	return false;
}

bool Grenade::ProjectileCollideCheck(IPlayer *arg0, Projectile* arg)
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
		//	soundPlayer->PlaySound(cratebreak);
			sprite->SetFrameSet(1);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(10);
		draw2 = true;
		ProjectileFlags& proj_flags = arg->GetProjectileFlags();
		m_soundFX->Play();

		SetPointValue(P_DEST_BLOCK_RED);

		if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
			isCollidable = false;
		//return false;
		break;
	};
//	ProjectileFlags& proj_flags = arg->GetProjectileFlags();

//	if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
	return false;
}

void Grenade::SetState(int _value)
{
	//TODO: This code has not been verified to work!
	state = _value;
	
	if (state == 1)// crate in process of opening, just open it
		state = 2;
	
	// open the crate, if it was in an open state
	if (state == 1 || state == 2 || state == 3)
	{
		sprite->SetFrameSet(1);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(5);
		draw2 = true;
	}
	
	switch (state)
	{
		case 0:
			// do nothing
			break;
		case 1: // in process of opening
			break;
		case 2: // crate was open w/item floating on it
			break;
		case 3: // crate states complete
			gotObject = true;
			draw2 = false;
			break;
	}	
}