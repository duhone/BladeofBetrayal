// EnemyZombie.h: interface for the EnemyZombie class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYZOMBIE_H__0172CEC2_76E7_466E_B2BD_9B5C76A1DBBE__INCLUDED_)
#define AFX_ENEMYZOMBIE_H__0172CEC2_76E7_466E_B2BD_9B5C76A1DBBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"


class AIEnemyZombie : public BaseEnemy  
{
public:
	void UseBrain();
	bool IsStopBlock();
	void Patrol();
	void Chase();
	void Attack();
	AIEnemyZombie();
	virtual ~AIEnemyZombie();

};

#endif // !defined(AFX_ENEMYZOMBIE_H__0172CEC2_76E7_466E_B2BD_9B5C76A1DBBE__INCLUDED_)
