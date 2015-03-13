// EnemyBullDozer.h: interface for the EnemyBullDozer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBULLDOZER_H__749A9800_7B91_45E3_8C10_9DD2B2102CD5__INCLUDED_)
#define AFX_ENEMYBULLDOZER_H__749A9800_7B91_45E3_8C10_9DD2B2102CD5__INCLUDED_


#include "Enemy.h"

class EnemyBullDozer : public Enemy  
{
public:
	EnemyBullDozer(Level *curLevel);
	virtual ~EnemyBullDozer();

	virtual void stop();
	virtual void processAttack();
	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	void processUpdate();

	float btimer;
	float btimer2;
};

#endif // !defined(AFX_ENEMYBULLDOZER_H__749A9800_7B91_45E3_8C10_9DD2B2102CD5__INCLUDED_)
