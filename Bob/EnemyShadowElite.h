// EnemyShadowElite.h: interface for the EnemyShadowElite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYSHADOWELITE_H__22CA79D7_7FEC_4DAD_ACF8_B48B466C7B7D__INCLUDED_)
#define AFX_ENEMYSHADOWELITE_H__22CA79D7_7FEC_4DAD_ACF8_B48B466C7B7D__INCLUDED_


#include "Enemy.h"

class EnemyShadowElite : public Enemy  
{
public:
	EnemyShadowElite(Level *curLevel);
	virtual ~EnemyShadowElite();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();
	virtual void stop();

	void processUpdate();
};

#endif // !defined(AFX_ENEMYSHADOWELITE_H__22CA79D7_7FEC_4DAD_ACF8_B48B466C7B7D__INCLUDED_)
