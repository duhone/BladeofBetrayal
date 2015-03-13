// EnemyAdvancedGeneticMonster2.h: interface for the EnemyAdvancedGeneticMonster2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYADVANCEDGENETICMONSTER2_H__D9E91550_8246_4053_8F19_BB2852788C47__INCLUDED_)
#define AFX_ENEMYADVANCEDGENETICMONSTER2_H__D9E91550_8246_4053_8F19_BB2852788C47__INCLUDED_


#include "Enemy.h"

class EnemyAdvancedGeneticMonster2 : public Enemy  
{
public:
	EnemyAdvancedGeneticMonster2(Level *curLevel);
	virtual ~EnemyAdvancedGeneticMonster2();

	virtual void processDamage();
	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDeath();
	virtual void setJumpVelocity();
	virtual void stop();
	virtual void processUpdate();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
private:
	float deathtimer;
};

#endif // !defined(AFX_ENEMYADVANCEDGENETICMONSTER2_H__D9E91550_8246_4053_8F19_BB2852788C47__INCLUDED_)
