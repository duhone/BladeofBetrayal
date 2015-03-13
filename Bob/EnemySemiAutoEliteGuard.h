// EnemySemiAutoEliteGuard.h: interface for the EnemySemiAutoEliteGuard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYSEMIAUTOELITEGUARD_H__4A23316E_D021_432B_ADF0_C37D17F76425__INCLUDED_)
#define AFX_ENEMYSEMIAUTOELITEGUARD_H__4A23316E_D021_432B_ADF0_C37D17F76425__INCLUDED_


#include "EnemyEliteGuard.h"

class EnemySemiAutoEliteGuard : public EnemyEliteGuard  
{
public:
	EnemySemiAutoEliteGuard(Level *curLevel);
	virtual ~EnemySemiAutoEliteGuard();

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

#endif // !defined(AFX_ENEMYSEMIAUTOELITEGUARD_H__4A23316E_D021_432B_ADF0_C37D17F76425__INCLUDED_)
