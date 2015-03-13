// HealthObject.cpp: implementation of the HealthObject class.
//
//////////////////////////////////////////////////////////////////////


#include "HealthObject.h"
#include "AssetList.h"
#include "Game.h"
#include "TutorialManager.h"

extern Game* game_class;

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HealthObject::HealthObject(int arg,int _key)
{
	levelStateType = arg;
	m_key = _key;
	hasUpgrade = false;
	InitObject(arg);
	m_soundFXBlip = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::blip::ID);
}

HealthObject::~HealthObject()
{
}

void HealthObject::InitObject(int type)
{
	gotObject = false;
	isCollidable = true;
	this->type = type;
	state = 0;
	draw = true;
	
	// Determine the type of health crate
	switch(type)
	{
		case 1: // small health crate
			health_amount = 5;
			sprite->SetImage(CR::AssetList::Regular_crate);
			sprite2->SetImage(CR::AssetList::Small_Health);
			m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::breakcrate::ID);
			break;
		case 2: // large health crate
			health_amount = 20;
			sprite->SetImage(CR::AssetList::Regular_crate);
			sprite2->SetImage(CR::AssetList::Large_Health);
			m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::breakcrate::ID);
			break;
		case 3: // health upgrade
			health_amount = 20;
			sprite->SetImage(CR::AssetList::Item_Chest);
			if(hasUpgrade)
				sprite3->SetImage(CR::AssetList::Large_Health);
			else
				sprite3->SetImage(CR::AssetList::Health_Upgrade);
			m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::openchest::ID);
			break;
		case 4: // extra life
			health_amount = 20;
			sprite->SetImage(CR::AssetList::Regular_crate);
			sprite2->SetImage(CR::AssetList::Free_life_Icon);
			m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::openchest::ID);
			break;
		default:
			break;
	}	
	
	if(type == 3)
	{
		if(m_key < 3)
			sprite->SetFrameSet(m_key);
		else
			sprite->SetFrameSet(m_key+1);
		sprite->SetAutoAnimate(true);
	}
	else
	{
		sprite->SetAutoAnimate(false);
		sprite->SetFrameSet(0);	
	}
		
	sprite->SetFrame(0);
	sprite->SetFrameRate(2);
	
	if(type == 3)
	{
		sprite3->SetAutoAnimate(true);
		sprite3->SetFrameSet(0);
		sprite3->SetFrame(0);
		sprite3->SetFrameRate(5);
	}
	else
	{
		sprite2->SetAutoAnimate(true);
		sprite2->SetFrameSet(0);
		sprite2->SetFrame(0);
		sprite2->SetFrameRate(5);
	}
	
	draw2 = false;
	draw3 = false;
}

bool HealthObject::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype)
{
	//if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
	int tempy;
	switch(state)
	{
		case 0:
		case 1:
			tempy = y;
			if(tempy < 0) tempy++;
			arg->SetWorldLoc(x,tempy);
			if(y != 0) y = -100;
			if(x != 0) x = -100;
			break;
		case 2:
			if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
			if(type == 3 && !hasUpgrade)
			{
				Projectile *temp = new ProjectileUpgrade("HEALTH UPGRADE +5");
				(*arg->GetProjectileList()).push_back(temp);
				m_soundFXBlip->Play();
//			soundPlayer->PlaySound(blip);
				arg->IncNumLifeBars();
				arg->AddSpecialItems();
				SetPointValue(P_HEALTH_UPGRADE);
				hasUpgrade = true;
				arg->AddLife(health_amount);
			}
			else if(type != 4)
			{
				m_soundFXBlip->Play();
//			soundPlayer->PlaySound(blip);
				arg->AddLife(health_amount);
				arg->AddBasicItem();
				if(type == 1) SetPointValue(P_HEALTH_A);
				else SetPointValue(P_HEALTH_B);
			}
			else if(type == 4)
			{
				m_soundFXBlip->Play();
//			soundPlayer->PlaySound(blip);
				arg->AddExtraLife();
				arg->AddSpecialItems();
				SetPointValue(P_FREELIFE);
			}
			state = 3;
			draw2 = false;
			draw3 = false;
			gotObject = true;
			//return true;
			//return false;
			break;
		}
	
	return false;
}

void HealthObject::Update()
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
			if(type == 3) draw3 = true;
		}

		break;
	};
}

bool HealthObject::WeaponCollideCheck(IPlayer* arg)
{
	if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
	if(type == 3 && m_key != 0 && arg->GetAttack() != m_key)
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
		state = 1;
//		soundPlayer->PlaySound(cratebreak);
		//sprite->SetFrameSet(1);
		if(type == 3)				
			sprite->SetFrameSet(6);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(10);
		m_soundFX->Play();
			
		SetPointValue(P_DEST_BLOCK_RED);
		if(type != 3) draw2 = true;
			isCollidable = false;
		break;
	};
	return false;
}

bool HealthObject::ProjectileCollideCheck(IPlayer *arg0, Projectile* arg)
{
	if(!arg->GetSource())
	{
		arg->DeActivate();
		return false;
	}
	if(type == 3 && m_key != 0)
		return false;
	switch(state)
	{
	case 0:
		state = 1;
//		soundPlayer->PlaySound(cratebreak);
		//sprite->SetFrameSet(1);
		if(type == 3)				
			sprite->SetFrameSet(6);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(10);
		m_soundFX->Play();
		ProjectileFlags& proj_flags = arg->GetProjectileFlags();

		SetPointValue(P_DEST_BLOCK_RED);

		if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
		if(type != 3) draw2 = true;
			isCollidable = false;
		//return false;
		break;
	};
//	ProjectileFlags& proj_flags = arg->GetProjectileFlags();

//	if(!proj_flags.S_NON_PROJECTILE) arg->DeActivate();
	return false;
}

void HealthObject::SetState(int _value)
{	
	state = _value;
	
	if (state == 1)// crate in process of opening, just open it
		state = 2;
	
	// open the crate, if it was in an open state
	/*if (state == 0 && type != 3)
	{
		sprite->SetFrameSet(0);	
		sprite->SetFrame(0);
		sprite->SetFrameRate(2);
	}
	else */if (state == 1 || state == 2 || state == 3)
	{
		//sprite->SetFrameSet(1);
		if(type == 3)				
			sprite->SetFrameSet(6);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(10);
		if(type != 3) draw2 = true;
	}
	
	switch (state)
	{
		case 0:
			// do nothing
			//draw = true;
			break;
		case 1: // in process of opening
			break;
		case 2: // crate was open w/item floating on it
			if(type == 3) draw3 = true;
			break;
		case 3: // crate states complete
			draw2 = false;
			draw3 = false;
			gotObject = true;
			break;
	}
}

int HealthObject::GetUpgradeType()
{
	if (levelStateType == 3)
		return LEVELSTATETYPE_HEALTH;
	else
		return LEVELSTATETYPE_NOTUPGRADE;
}

void HealthObject::SetUpgradeState(bool hasUpgrade)
{
	if (GetUpgradeType() != LEVELSTATETYPE_HEALTH)
		return;
	
	int tState = state;
	this->hasUpgrade = hasUpgrade;
	if (hasUpgrade)
	{
		// Initialize the object if it has not been used (check for resumeGame);
		//if (state < 3)
			InitObject(type);
		//sprite->SetImage(CR::AssetList::Item_Chest);
	}
	
	SetState(tState);
}