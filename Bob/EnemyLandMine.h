// EnemyLandMine.h: interface for the EnemyLandMine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYLANDMINE_H__6C4B708F_FE62_4938_B2EB_6E187EC53781__INCLUDED_)
#define AFX_ENEMYLANDMINE_H__6C4B708F_FE62_4938_B2EB_6E187EC53781__INCLUDED_


#include "Enemy.h"

class EnemyLandMine : public Enemy  
{
public:
	EnemyLandMine(Level *curLevel);
	virtual ~EnemyLandMine();

	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	void StartMine();

	void processUpdate();
	bool IsEnemy() const { return false; }
};

#endif // !defined(AFX_ENEMYLANDMINE_H__6C4B708F_FE62_4938_B2EB_6E187EC53781__INCLUDED_)
