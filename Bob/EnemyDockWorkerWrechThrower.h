// EnemyDockWorkerWrechThrower.h: interface for the EnemyDockWorkerWrechThrower class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYDOCKWORKERWRECHTHROWER_H__83501509_F333_48E7_A12C_66E700F078A9__INCLUDED_)
#define AFX_ENEMYDOCKWORKERWRECHTHROWER_H__83501509_F333_48E7_A12C_66E700F078A9__INCLUDED_


#include "Enemy.h"

class EnemyDockWorkerWrechThrower : public Enemy  
{
public:
	EnemyDockWorkerWrechThrower(Level *curLevel);
	virtual ~EnemyDockWorkerWrechThrower();

	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();

};

#endif // !defined(AFX_ENEMYDOCKWORKERWRECHTHROWER_H__83501509_F333_48E7_A12C_66E700F078A9__INCLUDED_)
