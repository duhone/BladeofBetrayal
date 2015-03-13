// WeaponObject.h: interface for the WeaponObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEAPONOBJECT_H__96C834FD_0256_4564_863E_6586746FEA6B__INCLUDED_)
#define AFX_WEAPONOBJECT_H__96C834FD_0256_4564_863E_6586746FEA6B__INCLUDED_


#include "Object.h"

class WeaponObject : public Object  
{
public:
	WeaponObject(int type,int _key);
	virtual ~WeaponObject();
	virtual bool WeaponCollideCheck(IPlayer* arg);
	virtual void Update();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype);
	virtual bool ProjectileCollideCheck(IPlayer *arg0, Projectile* arg);
	int GetState() const {return state;}
	void SetState(int _value);
	
	int GetUpgradeType()
	{
		return LEVELSTATETYPE_WEAPON;
	}
	
	void SetUpgradeState(bool hasUpgrade);
	bool GetUpgradeState() { return hasUpgrade; }
	void InitObject();
	void Reinitialize(){InitObject();}
private:
	int type;
	int state;
	int m_key;
	bool hasUpgrade;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFXBlip;
};

#endif // !defined(AFX_WEAPONOBJECT_H__96C834FD_0256_4564_863E_6586746FEA6B__INCLUDED_)
