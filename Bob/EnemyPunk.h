// EnemyPunk.h: interface for the EnemyPunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYPUNK_H__FF56452A_9CFC_4A04_A4C6_865272DBA37F__INCLUDED_)
#define AFX_ENEMYPUNK_H__FF56452A_9CFC_4A04_A4C6_865272DBA37F__INCLUDED_


#include "Enemy.h"

class EnemyPunk : public Enemy  
{
public:
	EnemyPunk(Level *curLevel);
	virtual ~EnemyPunk();

	virtual void setJumpVelocity();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
	void processUpdate();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
};

#endif // !defined(AFX_ENEMYPUNK_H__FF56452A_9CFC_4A04_A4C6_865272DBA37F__INCLUDED_)
