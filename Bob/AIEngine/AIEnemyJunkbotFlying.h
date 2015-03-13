// EnemyJunkbotFlying.h: interface for the EnemyJunkbotFlying class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJUNKBOTFLYING_H__67E18983_2CDA_4B0D_9996_01FD7CF09756__INCLUDED_)
#define AFX_ENEMYJUNKBOTFLYING_H__67E18983_2CDA_4B0D_9996_01FD7CF09756__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyJunkbotFlying : public BaseEnemy  
{
public:
	float time_bullet;
	float yLocPrev;
	float time_attack;
	void Attack();
	void Patrol();
	bool IsStopBlock();
	void UseBrain();

	AIEnemyJunkbotFlying();
	virtual ~AIEnemyJunkbotFlying();

};

#endif // !defined(AFX_ENEMYJUNKBOTFLYING_H__67E18983_2CDA_4B0D_9996_01FD7CF09756__INCLUDED_)
