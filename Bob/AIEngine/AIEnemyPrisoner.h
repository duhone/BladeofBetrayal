// EnemyPrisoner.h: interface for the EnemyPrisoner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYPRISONER_H__BF4A0790_61F2_4B5D_998A_C235940C43B8__INCLUDED_)
#define AFX_ENEMYPRISONER_H__BF4A0790_61F2_4B5D_998A_C235940C43B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyPrisoner : public BaseEnemy  
{
public:
	void UseBrain();
	bool IsStopBlock();
	float punch_time;
	float punch;
	void Patrol();
	void Chase();
	void Attack();
	AIEnemyPrisoner();
	virtual ~AIEnemyPrisoner();

};

#endif // !defined(AFX_ENEMYPRISONER_H__BF4A0790_61F2_4B5D_998A_C235940C43B8__INCLUDED_)
