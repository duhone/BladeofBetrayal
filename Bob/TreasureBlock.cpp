// TreasureBlock.cpp: implementation of the TreasureBlock class.
//
//////////////////////////////////////////////////////////////////////


#include "TreasureBlock.h"
#include "AssetList.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TreasureBlock::TreasureBlock(int arg)
{
	type = arg;
	hasUpgrade = false;
	InitObject();
	m_soundFXBlip = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::blip::ID);
}

void TreasureBlock::InitObject()
{	
	isCollidable = true;
	gotObject = false;
	sprite->SetImage(CR::AssetList::Item_Chest);
	sprite->SetAutoAnimate(true);
	sprite->SetFrameSet(0);
	sprite->SetFrame(0);
	state = 0;
	draw = true;
	if(hasUpgrade)
		sprite3->SetImage(CR::AssetList::Multiple_grenade);
	else				
		sprite3->SetImage(CR::AssetList::basic_weapon_upgrade);
}

TreasureBlock::~TreasureBlock()
{
}

bool TreasureBlock::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype)
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
		if(type == 6)
		{
			if(!hasUpgrade)
			{
				Projectile *temp = new ProjectileUpgrade("Found: 2X Basic Attack Strength!");
				(*arg->GetProjectileList()).push_back(temp);

//				soundPlayer->PlaySound(blip);
				m_soundFXBlip->Play();
				SetPointValue(P_TREASURE_6);
				arg->AddBasicAttackUpgrade();
				hasUpgrade = true;
			}
			else
			{
				arg->AddGrenades(3);
			}
		}
		if(!hasUpgrade) arg->AddSpecialItems();
		state = 3;
		//draw = false;
		draw3 = false;
		gotObject = true;
		//return true;
		break;
	};
	return false;
}

void TreasureBlock::Update()
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
			/*if(type == 1) sprite->SetImage(CR::AssetList::Document);
			else if(type == 2) sprite->SetImage(CR::AssetList::Folder);
			else if(type == 5) sprite->SetImage(CR::AssetList::Briefcase);
			else if(type == 4) sprite->SetImage(CR::AssetList::Microfilm);
			else if(type == 3) sprite->SetImage(CR::AssetList::ODD);
			else if(type == 6) sprite->SetImage(CR::AssetList::Short_White_Box);
			sprite->SetFrameSet(0);
			sprite->SetFrame(0);
			sprite->SetAutoAnimate(true);*/
		}

		break;
	};
}

bool TreasureBlock::WeaponCollideCheck(IPlayer* arg)
{
	if(!arg->GetStateFlags()->S_IS_PLAYER) return false;
	switch(state)
	{
	case 0:
		state = 1;
//			soundPlayer->PlaySound(cratebreak);
		sprite->SetFrameSet(6);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(10);
		draw3 = true;			
			
		SetPointValue(P_DEST_BLOCK_RED);
			isCollidable = false;
		break;
	};
	return false;
}

bool TreasureBlock::ProjectileCollideCheck(IPlayer *arg0, Projectile* arg)
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
		sprite->SetFrameSet(6);
		sprite->SetFrame(0);
		sprite->SetAutoAnimate(true);
		sprite->AutoStopAnimate();
		sprite->SetFrameRate(10);
		draw3 = true;
		ProjectileFlags& proj_flags = arg->GetProjectileFlags();

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

void TreasureBlock::SetState(int _value)
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
			state = 1; // update will change the sprite and switch back to state 2
			break;
		case 3: // crate states complete
			draw = false;
			draw2 = false;			
			draw3 = false;
			gotObject = true;
			break;
	}
}

void TreasureBlock::SetUpgradeState(bool hasUpgrade)
{
	if (GetUpgradeType() != LEVELSTATETYPE_ATTACK)
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
