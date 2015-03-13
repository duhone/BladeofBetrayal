// EnemyShadowEliteRifle.h: interface for the EnemyShadowEliteRifle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYSHADOWELITERIFLE_H__A711B732_DCAC_4C9D_AEE0_68E4BCAF0F4F__INCLUDED_)
#define AFX_ENEMYSHADOWELITERIFLE_H__A711B732_DCAC_4C9D_AEE0_68E4BCAF0F4F__INCLUDED_


#include "Enemy.h"

class EnemyShadowEliteRifle : public Enemy  
{
public:
	EnemyShadowEliteRifle(Level *curLevel);
	virtual ~EnemyShadowEliteRifle();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
};

#endif // !defined(AFX_ENEMYSHADOWELITERIFLE_H__A711B732_DCAC_4C9D_AEE0_68E4BCAF0F4F__INCLUDED_)
