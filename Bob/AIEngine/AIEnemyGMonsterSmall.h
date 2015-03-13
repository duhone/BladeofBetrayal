// EnemyGMonsterSmall.h: interface for the EnemyGMonsterSmall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGMONSTERSMALL_H__1E47088B_661C_4519_9140_D195F70A6899__INCLUDED_)
#define AFX_ENEMYGMONSTERSMALL_H__1E47088B_661C_4519_9140_D195F70A6899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseenemy.h"

class AIEnemyGMonsterSmall : public BaseEnemy
{
public:
	float hop_time;
	float jump_attack_time;
	float jump_time;
	float jump_attack;
	float jump;
	float hop;
	void Wait();
	void Attack();
	AIEnemyGMonsterSmall();
	virtual ~AIEnemyGMonsterSmall();

};

#endif // !defined(AFX_ENEMYGMONSTERSMALL_H__1E47088B_661C_4519_9140_D195F70A6899__INCLUDED_)
