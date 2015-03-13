// EnemyFlyingSentryA.h: interface for the EnemyFlyingSentryA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYFLYINGSENTRYA_H__0F1DFA3F_82E5_4A03_9241_3620A3DCF132__INCLUDED_)
#define AFX_ENEMYFLYINGSENTRYA_H__0F1DFA3F_82E5_4A03_9241_3620A3DCF132__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyFlyingSentryA : public BaseEnemy  
{
public:
	float attack_time;
	void UseBrain();
	float time_bullet;
	float time_flydown;
	float time_stopflydown;
	float range_patrol;
	float time_attack;

	int turret;

	void Attack();
	void Chase();
	void Patrol();
	
	//void UseBrain();
	bool IsStopBlock();
	AIEnemyFlyingSentryA();
	virtual ~AIEnemyFlyingSentryA();

	FILE *temp;

private:
	float yLocPrev;

};

#endif // !defined(AFX_ENEMYFLYINGSENTRYA_H__0F1DFA3F_82E5_4A03_9241_3620A3DCF132__INCLUDED_)
