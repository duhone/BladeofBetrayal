// EnergyObject.h: interface for the EnergyObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENERGYOBJECT_H__1AD0D387_B065_4D4F_848D_B31351327043__INCLUDED_)
#define AFX_ENERGYOBJECT_H__1AD0D387_B065_4D4F_848D_B31351327043__INCLUDED_


#include "Object.h"

class EnergyObject : public Object  
{
public:
	EnergyObject(int arg,int _key = 0);
	virtual ~EnergyObject();
	virtual bool WeaponCollideCheck(IPlayer* arg);
	virtual void Update();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype);
	virtual bool ProjectileCollideCheck(IPlayer *arg0, Projectile* arg);
	int GetState() const {return state;}
	void SetState(int _value);
	
	int GetUpgradeType();
	void SetUpgradeState(bool hasUpgrade);
	bool GetUpgradeState() { return hasUpgrade; }
	void InitObject(int type);
	void Reinitialize(){InitObject(type);}
private:
	int type;
	int state;
	int m_key;
	int energy_amount;
	
	int levelStateType;
	bool hasUpgrade;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFXBlip;
};

#endif // !defined(AFX_ENERGYOBJECT_H__1AD0D387_B065_4D4F_848D_B31351327043__INCLUDED_)
