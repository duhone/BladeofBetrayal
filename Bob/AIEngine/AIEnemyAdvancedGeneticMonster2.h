// EnemyAdvancedGeneticMonster2.h: interface for the EnemyAdvancedGeneticMonster2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYADVANCEDGENETICMONSTER2_H__C49CDFDA_1BBA_453E_BCC1_575866E239A2__INCLUDED_)
#define AFX_ENEMYADVANCEDGENETICMONSTER2_H__C49CDFDA_1BBA_453E_BCC1_575866E239A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyAdvancedGeneticMonster2 : public BaseEnemy  
{
public:
	bool ignore_player;
	bool run_direction;
	bool IsStopBlock();
	int attack_height;
	bool temp;
	bool damaged;
	int prev_health;
	int cur_health;
	void UseBrain();
	int damage_count;
	bool was_damaged;
	void Chase();
	void Patrol();
	void Attack();
	AIEnemyAdvancedGeneticMonster2();
	virtual ~AIEnemyAdvancedGeneticMonster2();

};

#endif // !defined(AFX_ENEMYADVANCEDGENETICMONSTER2_H__C49CDFDA_1BBA_453E_BCC1_575866E239A2__INCLUDED_)
