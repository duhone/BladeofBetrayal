// EnemyGreenNinja.h: interface for the EnemyGreenNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGREENNINJA_H__8D54E62D_E6CE_4E5C_812C_873F5F22BF6F__INCLUDED_)
#define AFX_ENEMYGREENNINJA_H__8D54E62D_E6CE_4E5C_812C_873F5F22BF6F__INCLUDED_


#include "EnemyNinja.h"

class EnemyGreenNinja : public EnemyNinja  
{
public:
	EnemyGreenNinja(Level *curLevel);
	virtual ~EnemyGreenNinja();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();
	virtual void stop();

	HPTRect &GetWeaponWorldLoc();
	//virtual HPTRect &GetWorldLoc();

	virtual void Reset();

	void processUpdate();
};

#endif // !defined(AFX_ENEMYGREENNINJA_H__8D54E62D_E6CE_4E5C_812C_873F5F22BF6F__INCLUDED_)
