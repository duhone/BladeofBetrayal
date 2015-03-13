// EnemyGMonsterFire.h: interface for the EnemyGMonsterFire class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGMONSTERFIRE_H__193381E0_F956_4CB3_9E5B_7CA6BE948706__INCLUDED_)
#define AFX_ENEMYGMONSTERFIRE_H__193381E0_F956_4CB3_9E5B_7CA6BE948706__INCLUDED_


#include "Enemy.h"

class EnemyGMonsterFire : public Enemy  
{
public:
	EnemyGMonsterFire(Level *curLevel);
	virtual ~EnemyGMonsterFire();

	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
};

#endif // !defined(AFX_ENEMYGMONSTERFIRE_H__193381E0_F956_4CB3_9E5B_7CA6BE948706__INCLUDED_)
