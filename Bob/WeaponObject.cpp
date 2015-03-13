// WeaponObject.cpp: implementation of the WeaponObject class.
//
//////////////////////////////////////////////////////////////////////


#include "WeaponObject.h"
#include "AssetList.h"
#include "Game.h"
#include "TutorialManager.h"

extern Game* game_class;

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WeaponObject::~WeaponObject()
{

}

WeaponObject::WeaponObject(int arg,int _key)
{
	type = arg;
	m_key = _key;
	hasUpgrade = false;
	InitObject();
	m_soundFXBlip = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::blip::ID);
}

void WeaponObject::InitObject()
{
	isCollidable = true;
	gotObject = false;
	state = 0;
	draw = true;
	
	sprite->SetImage(CR::AssetList::Item_Chest);
	sprite->SetAutoAnimate(true);
	if(m_key < 3)
		sprite->SetFrameSet(m_key);
	else
		sprite->SetFrameSet(m_key+1);
	sprite->SetFrame(0);
	sprite->SetFrameRate(2);
	
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::openchest::ID);
	if(!hasUpgrade)
	{
		
		sprite3->SetImage(CR::AssetList::weapon_pickup_icons);
		if(type == 1) sprite3->SetFrameSet(0);//sprite3->SetImage(CR::AssetList::Spike_icon_Status_Bar);
		else if(type == 2) sprite3->SetFrameSet(1);//sprite3->SetImage(CR::AssetList::Flame_Weapon_Icon);
		//else if(type == 3) sprite3->SetImage(CR::AssetList::Grenade_icon);
		else if(type == 3) sprite3->SetFrameSet(2);//sprite3->SetImage(CR::AssetList::Wave_Attack);
		//else if(type == 5) sprite3->SetImage(CR::AssetList::Respirator_icon);
		else if(type == 4) sprite3->SetFrameSet(3);//sprite3->SetImage(CR::AssetList::Quake_attack_icon);
		
		
		/*
		if(type == 1) sprite3->SetImage(CR::AssetList::Spike_icon_Status_Bar);
		else if(type == 2) sprite3->SetImage(CR::AssetList::Flame_Weapon_Icon);
		//else if(type == 3) sprite3->SetImage(CR::AssetList::Grenade_icon);
		else if(type == 3) sprite3->SetImage(CR::AssetList::Wave_Attack);
		//else if(type == 5) sprite3->SetImage(CR::AssetList::Respirator_icon);
		else if(type == 4) sprite3->SetImage(CR::AssetList::Quake_attack_icon);
		 */
	}
	else
	{
		sprite3->SetImage(CR::AssetList::Multiple_grenade);
		sprite3->SetFrameSet(0);
	}
		
	sprite3->SetAutoAnimate(true);
	//sprite3->SetFrameSet(0);
	sprite3->SetFrame(0);
	sprite3->SetFrameRate(5);
	draw3 = false;	
}

bool WeaponObject::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype)
{	
	Projectile *tempp;
	
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
		//soundPlayer->PlaySound(blip);
		if(!hasUpgrade)
		{
			arg->AddWeapon(type);
			
			switch (type)
			{
				case 1:
					tempp = new ProjectileUpgrade("FOUND THE ENERGY BLADE ... CAN OPEN BLUE DOORS");
					(*arg->GetProjectileList()).push_back(tempp);
					break;
				case 2:
					tempp = new ProjectileUpgrade("FOUND THE FIRE BLADE ... CAN OPEN ORANGE DOORS");
					(*arg->GetProjectileList()).push_back(tempp);
					break;
				case 3:
					tempp = new ProjectileUpgrade("FOUND THE WAVE BLADE ... CAN OPEN GREEN DOORS");
					(*arg->GetProjectileList()).push_back(tempp);
					break;
				case 4:
					tempp = new ProjectileUpgrade("FOUND THE QUAKE BLADE ... CAN OPEN RED DOORS");
					(*arg->GetProjectileList()).push_back(tempp);
					break;
				default:
					break;
			}
			
	//		arg->SetMaxAttacks(arg->GetMaxAttacks() + 1);
	//		arg->SetAttack(arg->GetMaxAttacks() - 1);
			SetPointValue(P_DEST_BLOCK_YELLOW);
			arg->AddSpecialItems();
			hasUpgrade = true;
		}
		else
		{
			arg->AddGrenades(3);
		}
	
		state = 3;
		draw3 = false;
		gotObject = true;
		//return true;
		break;
	};
	return false;
}

void WeaponObject::Update()
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
/*			if(type == 1) sprite->SetImage(23);
			if(type == 2) sprite->SetImage(6);
			if(type == 3) sprite->SetImage(37);
			if(type == 4) sprite->SetImage(38);
			if(type == 5) sprite->SetImage(62);
			if(type == 6) sprite->SetImage(39);
			sprite->SetFrameSet(0);
			sprite->SetFrame(0);
			sprite->SetAutoAnimate(true);*/
		}

		break;
	};
}

bool WeaponObject::WeaponCollideCheck(IPlayer* arg)
{
	if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
	if(m_key != 0 && arg->GetAttack() != m_key)
	{
		if(state == 0)
		{
			if(game_class->player->IsWeaponAvailable(m_key))
				TutorialManager::Instance().Trigger(TutorialManager::TDOOR2);
			else
				TutorialManager::Instance().Trigger(TutorialManager::TDOOR);
		}
		return false;
	}
	switch(state)
	{
	case 0:
//			soundPlayer->PlaySound(cratebreak);
		state = 1;
		sprite->SetFrameSet(6);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(10);
		m_soundFX->Play();
		draw3 = true;
		SetPointValue(P_DEST_BLOCK_YELLOW);
			isCollidable = false;
		break;
	};
	return false;
}

bool WeaponObject::ProjectileCollideCheck(IPlayer *arg0, Projectile* arg)
{
	if(!arg->GetSource())
	{
		arg->DeActivate();
		return false;
	}
	if(m_key != 0)
		return false;
	switch(state)
	{
	case 0:
//			soundPlayer->PlaySound(cratebreak);
		state = 1;
		sprite->SetFrameSet(6);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(10);
		m_soundFX->Play();
		draw3 = true;
		ProjectileFlags& proj_flags = arg->GetProjectileFlags();
		SetPointValue(P_DEST_BLOCK_YELLOW);
		if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
			isCollidable = false;
		return false;
		break;
	};
	ProjectileFlags& proj_flags = arg->GetProjectileFlags();

	if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
	return false;
}

void WeaponObject::SetState(int _value)
{
	state = _value;
	
	if (state == 1)// crate in process of opening, just open it
		state = 2;
	
	// open the crate, if it was in an open state
	if (state == 1 || state == 2 || state == 3)
	{
		sprite->SetFrameSet(6);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(5);
		draw3 = true;
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
			draw2 = false;
			draw3 = false;
			gotObject = true;
			break;
	}
	
}


void WeaponObject::SetUpgradeState(bool hasUpgrade)
{
	if (GetUpgradeType() != LEVELSTATETYPE_WEAPON)
		return;
	
	int tState = state;
	this->hasUpgrade = hasUpgrade;
	if (hasUpgrade)
	{
		// Initialize the object if it has not been used (check for resumeGame);
		InitObject();
	}
	SetState(tState);
}
