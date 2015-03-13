// EnemyJunkbotWalking.h: interface for the EnemyJunkbotWalking class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJUNKBOTWALKING_H__AC09AA9F_E22F_49BD_B31D_A18C53D7656C__INCLUDED_)
#define AFX_ENEMYJUNKBOTWALKING_H__AC09AA9F_E22F_49BD_B31D_A18C53D7656C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyJunkbotWalking : public BaseEnemy  
{
public:
	int xwalk;
	bool no_move;
	float shoot_time;
	float shoot;
	float patrol_time;
	float patrol;
	bool IsStopBlock();
	void UseBrain();
	void Patrol();
	void Attack();
	void Chase();
	AIEnemyJunkbotWalking();
	virtual ~AIEnemyJunkbotWalking();

};

#endif // !defined(AFX_ENEMYJUNKBOTWALKING_H__AC09AA9F_E22F_49BD_B31D_A18C53D7656C__INCLUDED_)
