// EnemyDockWorkerRope.h: interface for the EnemyDockWorkerRope class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYDOCKWORKERROPE_H__2C5DEA20_5173_48E1_AE9E_2A3E15489B28__INCLUDED_)
#define AFX_ENEMYDOCKWORKERROPE_H__2C5DEA20_5173_48E1_AE9E_2A3E15489B28__INCLUDED_


#include "Enemy.h"

class EnemyDockWorkerRope : public Enemy  
{
public:
	EnemyDockWorkerRope(Level *curLevel);
	virtual ~EnemyDockWorkerRope();

	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	virtual HPTRect &GetWorldLoc();
	HPTRect &GetWeaponWorldLoc();
	void processUpdate();

	void StartDockWorkerRope();
};

#endif // !defined(AFX_ENEMYDOCKWORKERROPE_H__2C5DEA20_5173_48E1_AE9E_2A3E15489B28__INCLUDED_)
