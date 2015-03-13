// EnemyLabScientist.h: interface for the EnemyLabScientist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYLABSCIENTIST_H__A429FA6E_508E_42CC_BF73_6AF278057B8F__INCLUDED_)
#define AFX_ENEMYLABSCIENTIST_H__A429FA6E_508E_42CC_BF73_6AF278057B8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "baseenemy.h"

class AIEnemyLabScientist  : public BaseEnemy
{
public:
	void UseBrain();
	bool IsStopBlock();
	void Chase();
	void Patrol();
	void Attack();
	AIEnemyLabScientist();
	virtual ~AIEnemyLabScientist();

};

#endif // !defined(AFX_ENEMYLABSCIENTIST_H__A429FA6E_508E_42CC_BF73_6AF278057B8F__INCLUDED_)
