// HealthObject.h: interface for the HealthObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEALTHOBJECT_H__44CF5E4B_2AB5_4246_B667_EB19D9BEC528__INCLUDED_)
#define AFX_HEALTHOBJECT_H__44CF5E4B_2AB5_4246_B667_EB19D9BEC528__INCLUDED_


#include "Object.h"

class HealthObject : public Object  
{
public:
	virtual bool WeaponCollideCheck(IPlayer* arg);
	virtual void Update();
	HealthObject(int arg,int _key = 0);
	virtual ~HealthObject();
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
	int health_amount;
	int levelStateType;
	bool hasUpgrade;
	int m_key;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFXBlip;
};

#endif // !defined(AFX_HEALTHOBJECT_H__44CF5E4B_2AB5_4246_B667_EB19D9BEC528__INCLUDED_)
