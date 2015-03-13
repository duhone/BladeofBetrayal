// EnemyWolf1.h: interface for the EnemyWolf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYWOLF1_H__373D1AE2_E7DE_4C26_9E9D_3E4DC0EB1ED8__INCLUDED_)
#define AFX_ENEMYWOLF1_H__373D1AE2_E7DE_4C26_9E9D_3E4DC0EB1ED8__INCLUDED_


#include "Enemy.h"

class EnemyWolf : public Enemy  
{
public:
	EnemyWolf(Level *curLevel, int Type);
	virtual ~EnemyWolf();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	virtual void processLeft();
	virtual void processRight();
	virtual void processDeath();
	virtual void processDamage();
	virtual void stop();
	void StartWolf();
	void processUpdate();

	int wolfType;
};

#endif // !defined(AFX_ENEMYWOLF1_H__373D1AE2_E7DE_4C26_9E9D_3E4DC0EB1ED8__INCLUDED_)
