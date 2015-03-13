// EnemyGMonsterFire.h: interface for the EnemyGMonsterFire class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGMONSTERFIRE_H__BFF05288_8859_4374_9A56_563294C71E28__INCLUDED_)
#define AFX_ENEMYGMONSTERFIRE_H__BFF05288_8859_4374_9A56_563294C71E28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyGMonsterFire : public BaseEnemy  
{
public:
	float fire_time;
	float fire;
	void Wait();
	void Attack();
	AIEnemyGMonsterFire();
	virtual ~AIEnemyGMonsterFire();

};

#endif // !defined(AFX_ENEMYGMONSTERFIRE_H__BFF05288_8859_4374_9A56_563294C71E28__INCLUDED_)
