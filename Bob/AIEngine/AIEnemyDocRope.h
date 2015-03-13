// EnemyDockRope.h: interface for the EnemyDockRope class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYDOCKROPE_H__468A1AC0_6F23_49E8_8430_DEA03909BF82__INCLUDED_)
#define AFX_ENEMYDOCKROPE_H__468A1AC0_6F23_49E8_8430_DEA03909BF82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyDocRope : public BaseEnemy  
{
public:
	float throw_star;
	void Patrol();
	void Chase();
	void Attack();
	void Wait();
	AIEnemyDocRope();
	virtual ~AIEnemyDocRope();

	float time_star;
	//bool  high_star;


};

#endif // !defined(AFX_ENEMYDOCKROPE_H__468A1AC0_6F23_49E8_8430_DEA03909BF82__INCLUDED_)
