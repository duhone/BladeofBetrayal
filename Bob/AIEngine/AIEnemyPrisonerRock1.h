// EnemyPrisonerRock1.h: interface for the EnemyPrisonerRock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYPRISONERROCK1_H__5A8C791D_DBC2_4C5F_868E_E828B759A378__INCLUDED_)
#define AFX_ENEMYPRISONERROCK1_H__5A8C791D_DBC2_4C5F_868E_E828B759A378__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyPrisonerRock : public BaseEnemy  
{
public:
	float rock_time;
	float throw_rock;
	void Wait();
	void Attack();
	AIEnemyPrisonerRock();
	virtual ~AIEnemyPrisonerRock();

};

#endif // !defined(AFX_ENEMYPRISONERROCK1_H__5A8C791D_DBC2_4C5F_868E_E828B759A378__INCLUDED_)
