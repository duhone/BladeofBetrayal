// EnemyPrisoner.h: interface for the EnemyPrisoner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYPRISONER_H__C019447E_BDD4_4B2C_B651_4E38E00ABD48__INCLUDED_)
#define AFX_ENEMYPRISONER_H__C019447E_BDD4_4B2C_B651_4E38E00ABD48__INCLUDED_


#include "Enemy.h"

class EnemyPrisoner : public Enemy  
{
public:
	EnemyPrisoner(Level *curLevel);
	virtual ~EnemyPrisoner();
	
	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();
	virtual void stop();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	void processUpdate();
};

#endif // !defined(AFX_ENEMYPRISONER_H__C019447E_BDD4_4B2C_B651_4E38E00ABD48__INCLUDED_)
