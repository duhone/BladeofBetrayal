// EnergyObject.cpp: implementation of the EnergyObject class.
//
//////////////////////////////////////////////////////////////////////


#include "Beacon.h"
#include "AssetList.h"
#include "Game.h"

extern Game* game_class;

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Beacon::Beacon()
{
	InitObject(0);
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::breakglass::ID);
}

Beacon::~Beacon()
{

}

void Beacon::InitObject(int type)
{
	state = 0;
	draw = true;
	
	sprite->SetImage(CR::AssetList::Beacon);
	sprite->SetAutoAnimate(true);
		
	sprite->SetFrame(0);
	sprite->SetFrameRate(15);	
	
	sprite2->SetImage(CR::AssetList::BeaconExplosion);
	//sprite2->SetAutoAnimate(true);
		
	sprite2->SetFrame(0);
	sprite2->SetFrameRate(15);	
}

bool Beacon::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype)
{
	int tempy;
	switch(state)
	{
	case 0:
		arg->AddLife(20);
		game_class->AddBeacon();
		draw = false;
		draw2 = true;
		state = 1;
		sprite2->SetAutoAnimate(true);
		sprite2->AutoStopAnimate();
		m_soundFX->Play();
		break;
	};
	return false;
}

void Beacon::Update()
{
	if(state == 1)
	{
		if(!sprite2->IsAnimating())
			state = 2;
	}
}

void Beacon::SetState(int _value)
{
	state = _value;
	
	if(state == 0)
	{
		draw = true;
		draw2 = false;
	}
	else if(state == 1)
	{
		draw = false;
		draw2 = true;
		sprite2->SetAutoAnimate(true);
		sprite2->AutoStopAnimate();
	}
	else
	{
		draw = false;
		draw2 = false;
	}
}
