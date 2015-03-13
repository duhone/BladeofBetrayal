// EnemyFlyingSentryB.h: interface for the EnemyFlyingSentryB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYFLYINGSENTRYB_H__32E85400_5A2B_4E80_B89E_1781FC811CED__INCLUDED_)
#define AFX_ENEMYFLYINGSENTRYB_H__32E85400_5A2B_4E80_B89E_1781FC811CED__INCLUDED_


#include "Enemy.h"

class EnemyFlyingSentryB : public Enemy  
{
public:
	EnemyFlyingSentryB(Level *curLevel);
	virtual ~EnemyFlyingSentryB();

//	HPTRect &GetWorldLoc();

	virtual void processLeft();
	virtual void processRight();
//	virtual void processUp();
//	virtual void processDown();

	virtual void processDeath();

	virtual void processAttack();
	virtual void processDamage();

	virtual void stop();

	void processUpdate();
};

#endif // !defined(AFX_ENEMYFLYINGSENTRYB_H__32E85400_5A2B_4E80_B89E_1781FC811CED__INCLUDED_)
