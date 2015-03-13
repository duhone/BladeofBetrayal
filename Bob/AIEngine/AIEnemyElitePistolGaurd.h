// EnemyElitePistolGaurd.h: interface for the EnemyElitePistolGaurd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYELITEPISTOLGAURD_H__B6B60570_29C8_4D6C_99DF_1BD6B1143751__INCLUDED_)
#define AFX_ENEMYELITEPISTOLGAURD_H__B6B60570_29C8_4D6C_99DF_1BD6B1143751__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "AIEnemyBaseEliteGaurd.h"

class AIEnemyElitePistolGaurd : public AIEnemyBaseEliteGaurd  
{
public:
	
	float fire_time;
	void Patrol();
	void Chase();
	void Attack();
	AIEnemyElitePistolGaurd();
	virtual ~AIEnemyElitePistolGaurd();

};

#endif // !defined(AFX_ENEMYELITEPISTOLGAURD_H__B6B60570_29C8_4D6C_99DF_1BD6B1143751__INCLUDED_)
