// EnemyBaseballPunk.h: interface for the EnemyBaseballPunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBASEBALLPUNK_H__26120D93_3BC0_4860_905E_C6E4C272DEC4__INCLUDED_)
#define AFX_ENEMYBASEBALLPUNK_H__26120D93_3BC0_4860_905E_C6E4C272DEC4__INCLUDED_


#include "Enemy.h"

class EnemyBaseballPunk : public Enemy  
{
public:
	EnemyBaseballPunk(Level *curLevel);
	virtual ~EnemyBaseballPunk();

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

#endif // !defined(AFX_ENEMYBASEBALLPUNK_H__26120D93_3BC0_4860_905E_C6E4C272DEC4__INCLUDED_)
