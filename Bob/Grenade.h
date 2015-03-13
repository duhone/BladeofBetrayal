// Grenade.h: interface for the Grenade class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRENADE_H__63DC1738_7C6E_4AE1_BF47_3C7F3B582E73__INCLUDED_)
#define AFX_GRENADE_H__63DC1738_7C6E_4AE1_BF47_3C7F3B582E73__INCLUDED_


#include "Object.h"

class Grenade : public Object  
{
public:
	Grenade(int arg);
	virtual ~Grenade();
	void InitObject(int arg);
	virtual bool WeaponCollideCheck(IPlayer* arg);
	virtual void Update();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype);
	virtual bool ProjectileCollideCheck(IPlayer *arg0, Projectile* arg);
	int GetState() const {return state;}
	void SetState(int _value);
	void Reinitialize(){InitObject(type);}
private:

	int type;
	int state;
	int amount;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFXBlip;
};

#endif // !defined(AFX_GRENADE_H__63DC1738_7C6E_4AE1_BF47_3C7F3B582E73__INCLUDED_)
