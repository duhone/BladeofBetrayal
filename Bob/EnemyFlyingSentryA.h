// EnemyFlyingSentryA.h: interface for the EnemyFlyingSentryA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYFLYINGSENTRYA_H__9BEE2A42_2EE2_4404_9E37_25722D695761__INCLUDED_)
#define AFX_ENEMYFLYINGSENTRYA_H__9BEE2A42_2EE2_4404_9E37_25722D695761__INCLUDED_


#include "Enemy.h"

class EnemyFlyingSentryA : public Enemy  
{
public:
	EnemyFlyingSentryA(Level *curLevel);
	virtual ~EnemyFlyingSentryA();

//	HPTRect &GetWeaponWorldLoc();
//	HPTRect &GetWorldLoc();

//	virtual void processLeft();
//	virtual void processRight();
	virtual void processUp();
	virtual void processDown();

	virtual void processAttack();
	virtual void processDamage();

	virtual void processDeath();

	virtual void stop();

	bool S_UP_DOWN;

	void processUpdate();
};

#endif // !defined(AFX_ENEMYFLYINGSENTRYA_H__9BEE2A42_2EE2_4404_9E37_25722D695761__INCLUDED_)
