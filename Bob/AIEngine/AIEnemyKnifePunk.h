// EnemyKnifePunk.h: interface for the EnemyKnifePunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYKNIFEPUNK_H__DB232754_EC65_4FDB_961C_67CCEEA3A8B3__INCLUDED_)
#define AFX_ENEMYKNIFEPUNK_H__DB232754_EC65_4FDB_961C_67CCEEA3A8B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyKnifePunk :  public BaseEnemy
{
public:
	AIEnemyKnifePunk();
	virtual ~AIEnemyKnifePunk();
	float throw_star;
	void Patrol();
	void Chase();
	void Attack();
	void Wait();
	float time_star;
	//bool  high_star;

};

#endif // !defined(AFX_ENEMYKNIFEPUNK_H__DB232754_EC65_4FDB_961C_67CCEEA3A8B3__INCLUDED_)
