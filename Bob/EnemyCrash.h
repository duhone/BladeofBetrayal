// EnemyCrash.h: interface for the EnemyCrash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYCRASH_H__388EC748_C8E6_4D9E_A12C_4FDC9D60E62B__INCLUDED_)
#define AFX_ENEMYCRASH_H__388EC748_C8E6_4D9E_A12C_4FDC9D60E62B__INCLUDED_


#include "Enemy.h"

class EnemyCrash : public Enemy  
{
public:
	EnemyCrash(Level *curLevel);
	virtual ~EnemyCrash();

	virtual void setJumpVelocity();
	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void processUpdate();
	virtual void stop();

//	void updateWorldLoc();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	float jumpTimer;
	bool  S_TIMER;
};

#endif // !defined(AFX_ENEMYCRASH_H__388EC748_C8E6_4D9E_A12C_4FDC9D60E62B__INCLUDED_)
