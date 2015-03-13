// EnemyCrash.h: interface for the EnemyCrash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYCRASH_H__CA67BD16_C010_4F65_9610_6FA893100597__INCLUDED_)
#define AFX_ENEMYCRASH_H__CA67BD16_C010_4F65_9610_6FA893100597__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyCrash : public BaseEnemy  
{
public:
	void Patrol();
	int mode3_count;
	float pause_time;
	float pause_timer;
	int mode;
	int lbound;
	int rbound;
	int step6_count;
	int walk_x;
	int rapidfire_count;
	void Chase();
	int hilow_count;
	float hilow_time;
	float hilow_timer;
	void Attack();
	AIEnemyCrash();
	virtual ~AIEnemyCrash();
	bool hilow_attack;
	void UseBrain();
	bool damaged;
	int prev_health;
	int cur_health;

};

#endif // !defined(AFX_ENEMYCRASH_H__CA67BD16_C010_4F65_9610_6FA893100597__INCLUDED_)
