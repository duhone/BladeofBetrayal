// EnemyPunk.h: interface for the EnemyPunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYPUNK_H__A6798559_DC33_475F_B615_AE995B6FDD10__INCLUDED_)
#define AFX_ENEMYPUNK_H__A6798559_DC33_475F_B615_AE995B6FDD10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyPunk : public BaseEnemy  
{
public:
	void UseBrain();
	bool IsStopBlock();
	float punch_time;
	float punch;
	void Patrol();
	void Chase();
	void Attack();
	AIEnemyPunk();
	virtual ~AIEnemyPunk();

};

#endif // !defined(AFX_ENEMYPUNK_H__A6798559_DC33_475F_B615_AE995B6FDD10__INCLUDED_)
