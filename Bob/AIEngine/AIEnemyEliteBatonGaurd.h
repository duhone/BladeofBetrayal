// EnemyEliteBatonGaurd.h: interface for the EnemyEliteBatonGaurd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYELITEBATONGAURD_H__2AD5D2A5_34A2_4161_B181_A2F55D7A24C6__INCLUDED_)
#define AFX_ENEMYELITEBATONGAURD_H__2AD5D2A5_34A2_4161_B181_A2F55D7A24C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"
#include "AIEnemyBaseNinja.h"

class AIEnemyEliteBatonGaurd : public AIEnemyBaseNinja
{
public:
	float time_sword;
	float swing_sword;
	void Wait();
	void Patrol();
	void Attack();
	void Chase();
	AIEnemyEliteBatonGaurd();
	virtual ~AIEnemyEliteBatonGaurd();

};

#endif // !defined(AFX_ENEMYELITEBATONGAURD_H__2AD5D2A5_34A2_4161_B181_A2F55D7A24C6__INCLUDED_)
