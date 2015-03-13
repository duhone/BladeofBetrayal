// EnemyBird.h: interface for the EnemyBird class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBIRD_H__7A2C3C58_78B2_457D_AB8D_02E4DA3478C8__INCLUDED_)
#define AFX_ENEMYBIRD_H__7A2C3C58_78B2_457D_AB8D_02E4DA3478C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyBird : public BaseEnemy  
{
public:
	float y_range;
	void Attack();
	AIEnemyBird();
	virtual ~AIEnemyBird();

};

#endif // !defined(AFX_ENEMYBIRD_H__7A2C3C58_78B2_457D_AB8D_02E4DA3478C8__INCLUDED_)
