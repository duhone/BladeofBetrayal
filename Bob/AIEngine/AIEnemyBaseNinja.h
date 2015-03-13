// EnemyBaseNinja.h: interface for the EnemyBaseNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBASENINJA_H__82D754EE_4D29_4471_8E58_CCA3A1F2B74A__INCLUDED_)
#define AFX_ENEMYBASENINJA_H__82D754EE_4D29_4471_8E58_CCA3A1F2B74A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyBaseNinja : public BaseEnemy  
{
public:
	float wait_time;
	float wait_timer;
	virtual bool IsStopBlock();
	void UseBrain();
	void ChangeState(int state);
	AIEnemyBaseNinja();
	virtual ~AIEnemyBaseNinja();

};

#endif // !defined(AFX_ENEMYBASENINJA_H__82D754EE_4D29_4471_8E58_CCA3A1F2B74A__INCLUDED_)
