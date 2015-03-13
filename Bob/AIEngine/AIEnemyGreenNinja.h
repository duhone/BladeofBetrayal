// EnemyGreenNinja.h: interface for the EnemyGreenNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGREENNINJA_H__E3A57172_3C82_4881_900C_42D2D58338B5__INCLUDED_)
#define AFX_ENEMYGREENNINJA_H__E3A57172_3C82_4881_900C_42D2D58338B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"
#include "AIEnemyBaseNinja.h"

class AIEnemyGreenNinja : public AIEnemyBaseNinja
{
public:
	void Wait();
	float time_sword;
	float swing_sword;
	void Patrol();
	//void MoveRight();
	//void MoveLeft();
	//void UseBrain();
	void Chase();
	void Attack();
	AIEnemyGreenNinja();
	virtual ~AIEnemyGreenNinja();

};

#endif // !defined(AFX_ENEMYGREENNINJA_H__E3A57172_3C82_4881_900C_42D2D58338B5__INCLUDED_)
