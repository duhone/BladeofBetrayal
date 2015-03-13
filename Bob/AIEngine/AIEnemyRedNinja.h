// EnemyRedNinja.h: interface for the EnemyRedNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYREDNINJA_H__74B5657E_C1A1_45E5_BCF7_610BBDDFD8E2__INCLUDED_)
#define AFX_ENEMYREDNINJA_H__74B5657E_C1A1_45E5_BCF7_610BBDDFD8E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"
#include "AIEnemyBaseNinja.h"


class AIEnemyRedNinja : public AIEnemyBaseNinja
{
public:
	int high_count;
	bool low_star;
	bool high_star;
	float throw_star;
	void Patrol();
	void Chase();
	void Attack();
	void Wait();
	AIEnemyRedNinja();
	virtual ~AIEnemyRedNinja();

	float time_star;
	//bool  high_star;

};

#endif // !defined(AFX_ENEMYREDNINJA_H__74B5657E_C1A1_45E5_BCF7_610BBDDFD8E2__INCLUDED_)
