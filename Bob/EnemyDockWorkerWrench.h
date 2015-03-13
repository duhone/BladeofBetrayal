// EnemyDockWorkerWrench.h: interface for the EnemyDockWorkerWrench class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYDOCKWORKERWRENCH_H__E0E48DA6_380C_4F11_985E_99E92EF97280__INCLUDED_)
#define AFX_ENEMYDOCKWORKERWRENCH_H__E0E48DA6_380C_4F11_985E_99E92EF97280__INCLUDED_


#include "Enemy.h"

class EnemyDockWorkerWrench : public Enemy  
{
public:
	EnemyDockWorkerWrench(Level *curLevel);
	virtual ~EnemyDockWorkerWrench();

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

#endif // !defined(AFX_ENEMYDOCKWORKERWRENCH_H__E0E48DA6_380C_4F11_985E_99E92EF97280__INCLUDED_)
