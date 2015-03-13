// EnemyAdvancedGeneticMonster.h: interface for the EnemyAdvancedGeneticMonster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYADVANCEDGENETICMONSTER_H__7C05DA9A_D2C2_4A87_9BB6_AE42D712709F__INCLUDED_)
#define AFX_ENEMYADVANCEDGENETICMONSTER_H__7C05DA9A_D2C2_4A87_9BB6_AE42D712709F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "baseenemy.h"
#include "../../Engines/Utility/FSM.h"

class AIEnemyAdvancedGeneticMonster  : public BaseEnemy
{
public:
	void UseBrain();
	const HPTPoint& JumpBlockLeft() const {return m_jumpBlockLeft;}
	const HPTPoint& JumpBlockRight() const {return m_jumpBlockRight;}
	AIEnemyAdvancedGeneticMonster();
	virtual ~AIEnemyAdvancedGeneticMonster();
	virtual void Init();
private:
	CR::Utility::FSM m_stateMachine;
	HPTPoint m_jumpBlockLeft;
	HPTPoint m_jumpBlockRight;
};

#endif // !defined(AFX_ENEMYADVANCEDGENETICMONSTER_H__7C05DA9A_D2C2_4A87_9BB6_AE42D712709F__INCLUDED_)
