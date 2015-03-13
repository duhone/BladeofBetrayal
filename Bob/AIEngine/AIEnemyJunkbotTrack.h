// EnemyJunkbotTrack.h: interface for the EnemyJunkbotTrack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJUNKBOTTRACK_H__46811158_3D5E_4996_AD8A_784221FDD1ED__INCLUDED_)
#define AFX_ENEMYJUNKBOTTRACK_H__46811158_3D5E_4996_AD8A_784221FDD1ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyJunkbotTrack : public BaseEnemy  
{
public:
	bool IsStopBlock();
	void UseBrain();
	void Patrol();
	void Attack();
	void Chase();
	AIEnemyJunkbotTrack();
	virtual ~AIEnemyJunkbotTrack();

};

#endif // !defined(AFX_ENEMYJUNKBOTTRACK_H__46811158_3D5E_4996_AD8A_784221FDD1ED__INCLUDED_)
