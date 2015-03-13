// EnemyBatonEliteGuard.h: interface for the EnemyBatonEliteGuard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBATONELITEGUARD_H__388C0D45_2EAF_4610_AEA9_D0890FD68966__INCLUDED_)
#define AFX_ENEMYBATONELITEGUARD_H__388C0D45_2EAF_4610_AEA9_D0890FD68966__INCLUDED_


#include "EnemyEliteGuard.h"

class EnemyBatonEliteGuard : public EnemyEliteGuard  
{
public:
	EnemyBatonEliteGuard(Level *curLevel);
	virtual ~EnemyBatonEliteGuard();

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

#endif // !defined(AFX_ENEMYBATONELITEGUARD_H__388C0D45_2EAF_4610_AEA9_D0890FD68966__INCLUDED_)
