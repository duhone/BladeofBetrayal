// EnemyFlyingSentryB.h: interface for the EnemyFlyingSentryB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYFLYINGSENTRYB_H__8992A8F4_FCA0_4782_80F8_8C9F0C4D396A__INCLUDED_)
#define AFX_ENEMYFLYINGSENTRYB_H__8992A8F4_FCA0_4782_80F8_8C9F0C4D396A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AIEnemyFlyingSentryA.h"

class AIEnemyFlyingSentryB : public BaseEnemy 
{
public:
	float attack_time;
	void UseBrain();
	void Patrol();
	void Chase();
	void Attack();

	AIEnemyFlyingSentryB();
	virtual ~AIEnemyFlyingSentryB();

	bool IsStopBlock();

	float range_patrol;
	float time_attack;

	
	float xLocPrev;
};

#endif // !defined(AFX_ENEMYFLYINGSENTRYB_H__8992A8F4_FCA0_4782_80F8_8C9F0C4D396A__INCLUDED_)
