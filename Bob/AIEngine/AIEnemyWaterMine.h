// EnemyWaterMine.h: interface for the EnemyWaterMine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYWATERMINE_H__870C3609_5C92_49AB_ABC1_3D418DE37796__INCLUDED_)
#define AFX_ENEMYWATERMINE_H__870C3609_5C92_49AB_ABC1_3D418DE37796__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyWaterMine : public BaseEnemy  
{
public:
	void UseBrain();
	AIEnemyWaterMine();
	virtual ~AIEnemyWaterMine();

};

#endif // !defined(AFX_ENEMYWATERMINE_H__870C3609_5C92_49AB_ABC1_3D418DE37796__INCLUDED_)
