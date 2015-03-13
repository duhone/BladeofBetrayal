// EnemyNinja.h: interface for the EnemyNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYNINJA_H__EB830887_F958_4563_8ABD_61B38BDAB1CB__INCLUDED_)
#define AFX_ENEMYNINJA_H__EB830887_F958_4563_8ABD_61B38BDAB1CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyNinja : public BaseEnemy  
{
public:
	void Chase();
	//void MoveRight();
	//void MoveLeft();
	//void Patrol();
	void UseBrain();
	//void Chase();
	void Attack();
	AIEnemyNinja();
	virtual ~AIEnemyNinja();
	float swing_sword;

};

#endif // !defined(AFX_ENEMYNINJA_H__EB830887_F958_4563_8ABD_61B38BDAB1CB__INCLUDED_)
