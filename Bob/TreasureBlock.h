#ifndef TREASURE_BLOCK_H
#define TREASURE_BLOCK_H

#include "Object.h"


class TreasureBlock : public Object  
{
public:
	TreasureBlock(int arg);
	virtual ~TreasureBlock();
	virtual bool WeaponCollideCheck(IPlayer* arg);
	virtual void Update();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype);
	virtual bool ProjectileCollideCheck(IPlayer *arg0, Projectile* arg);
	int GetState() const {return state;}
	void SetState(int _value);
	
	int GetUpgradeType()
	{
		if (type == 6)
			return LEVELSTATETYPE_ATTACK;
		else
			return LEVELSTATETYPE_NOTUPGRADE;
	}
	
	void SetUpgradeState(bool hasUpgrade);
	bool GetUpgradeState() { return hasUpgrade; }
	void InitObject();
	void Reinitialize(){InitObject();}
private:
	int type;
	int state;
	int point_amount;
	bool hasUpgrade;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFXBlip;
};

#endif