// EnemyPistolEliteGuard.h: interface for the EnemyPistolEliteGuard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYPISTOLELITEGUARD_H__1FD8E57D_6470_4FF1_A045_D696E53A6707__INCLUDED_)
#define AFX_ENEMYPISTOLELITEGUARD_H__1FD8E57D_6470_4FF1_A045_D696E53A6707__INCLUDED_


#include "EnemyEliteGuard.h"

class EnemyPistolEliteGuard : public EnemyEliteGuard  
{
public:
	EnemyPistolEliteGuard(Level *curLevel);
	virtual ~EnemyPistolEliteGuard();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
};

#endif // !defined(AFX_ENEMYPISTOLELITEGUARD_H__1FD8E57D_6470_4FF1_A045_D696E53A6707__INCLUDED_)
