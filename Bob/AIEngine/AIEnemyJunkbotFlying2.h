// EnemyJunkbotFlying2.h: interface for the EnemyJunkbotFlying2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJUNKBOTFLYING2_H__3267A5B2_129E_4116_B6D4_F87703868231__INCLUDED_)
#define AFX_ENEMYJUNKBOTFLYING2_H__3267A5B2_129E_4116_B6D4_F87703868231__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyJunkbotFlying2 : public BaseEnemy  
{
public:
	float attack_time;
	float attack_timer;
	void Patrol();
	AIEnemyJunkbotFlying2();
	virtual ~AIEnemyJunkbotFlying2();
	bool IsStopBlock();
	virtual void UseBrain();

	

};

#endif // !defined(AFX_ENEMYJUNKBOTFLYING2_H__3267A5B2_129E_4116_B6D4_F87703868231__INCLUDED_)
