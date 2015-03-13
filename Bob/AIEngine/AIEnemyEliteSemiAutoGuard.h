// EnemyEliteSemiAutoGuard.h: interface for the EnemyEliteSemiAutoGuard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYELITESEMIAUTOGUARD_H__9C43B1BB_F33C_4ADB_8A03_D41AB4BE54FE__INCLUDED_)
#define AFX_ENEMYELITESEMIAUTOGUARD_H__9C43B1BB_F33C_4ADB_8A03_D41AB4BE54FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"
#include "AIEnemyBaseEliteGaurd.h"

class AIEnemyEliteSemiAutoGuard : public AIEnemyBaseEliteGaurd
{
public:
	float fire_time;

	void Attack();
	void Patrol();
	void Chase();
	AIEnemyEliteSemiAutoGuard();
	virtual ~AIEnemyEliteSemiAutoGuard();

};

#endif // !defined(AFX_ENEMYELITESEMIAUTOGUARD_H__9C43B1BB_F33C_4ADB_8A03_D41AB4BE54FE__INCLUDED_)
