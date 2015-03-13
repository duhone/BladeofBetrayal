// EnemyBrownNinja.h: interface for the EnemyBrownNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBROWNNINJA_H__A89C1701_A066_47EB_A97A_A27022D2B9D2__INCLUDED_)
#define AFX_ENEMYBROWNNINJA_H__A89C1701_A066_47EB_A97A_A27022D2B9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"
#include "AIEnemyBaseNinja.h"

class AIEnemyBrownNinja : public AIEnemyBaseNinja
{
public:
	void Attack();
	//void UseBrain();
	void Chase();
	void Patrol();
	AIEnemyBrownNinja();
	virtual ~AIEnemyBrownNinja();

};

#endif // !defined(AFX_ENEMYBROWNNINJA_H__A89C1701_A066_47EB_A97A_A27022D2B9D2__INCLUDED_)
