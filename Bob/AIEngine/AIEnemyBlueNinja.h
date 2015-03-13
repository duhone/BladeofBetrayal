// EnemyBlueNinja.h: interface for the EnemyBlueNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBLUENINJA_H__5B697DCA_E742_43AA_9406_6E5F95FB93D0__INCLUDED_)
#define AFX_ENEMYBLUENINJA_H__5B697DCA_E742_43AA_9406_6E5F95FB93D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"
#include "AIEnemyBaseNinja.h"

class AIEnemyBlueNinja: public AIEnemyBaseNinja
{
public:
	void Wait();
	float swing_sword;
	void Chase();
	void Attack();
	//void UseBrain();
	void Patrol();
	float throw_star;
	float time_sword;
	float time_star;

	
	AIEnemyBlueNinja();
	virtual ~AIEnemyBlueNinja();

};

#endif // !defined(AFX_ENEMYBLUENINJA_H__5B697DCA_E742_43AA_9406_6E5F95FB93D0__INCLUDED_)
