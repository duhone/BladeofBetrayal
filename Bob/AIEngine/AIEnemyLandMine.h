// EnemyLandMine.h: interface for the EnemyLandMine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYLANDMINE_H__CAA34D13_AF4C_4FF0_A5F2_BEE0CF1F1C16__INCLUDED_)
#define AFX_ENEMYLANDMINE_H__CAA34D13_AF4C_4FF0_A5F2_BEE0CF1F1C16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyLandMine : public BaseEnemy  
{
public:
	void Patrol(){};
	void Chase(){};
	void Attack(){};
	void UseBrain();
	AIEnemyLandMine();
	virtual ~AIEnemyLandMine();

};

#endif // !defined(AFX_ENEMYLANDMINE_H__CAA34D13_AF4C_4FF0_A5F2_BEE0CF1F1C16__INCLUDED_)
