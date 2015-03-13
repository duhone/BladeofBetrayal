// EnemyZombiePrisoner.h: interface for the EnemyZombiePrisoner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYZOMBIEPRISONER_H__9CC4225D_9A2F_4693_9000_B2D817C95CDA__INCLUDED_)
#define AFX_ENEMYZOMBIEPRISONER_H__9CC4225D_9A2F_4693_9000_B2D817C95CDA__INCLUDED_


#include "Enemy.h"

class EnemyZombiePrisoner : public Enemy  
{
public:
	EnemyZombiePrisoner(Level *curLevel);
	virtual ~EnemyZombiePrisoner();

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

#endif // !defined(AFX_ENEMYZOMBIEPRISONER_H__9CC4225D_9A2F_4693_9000_B2D817C95CDA__INCLUDED_)
