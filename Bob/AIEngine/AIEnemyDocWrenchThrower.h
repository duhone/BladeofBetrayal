// EnemyDockWrenchThrower.h: interface for the EnemyDockWrenchThrower class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYDOCKWRENCHTHROWER_H__1F4AE269_EA0D_474E_96BC_A4E54CA7B40B__INCLUDED_)
#define AFX_ENEMYDOCKWRENCHTHROWER_H__1F4AE269_EA0D_474E_96BC_A4E54CA7B40B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyDocWrenchThrower  : public BaseEnemy
{
public:
	AIEnemyDocWrenchThrower();
	virtual ~AIEnemyDocWrenchThrower();
	
	float throw_star;
	void Patrol();
	void Chase();
	void Attack();
	void Wait();
	float time_star;
	//bool  high_star

};

#endif // !defined(AFX_ENEMYDOCKWRENCHTHROWER_H__1F4AE269_EA0D_474E_96BC_A4E54CA7B40B__INCLUDED_)
