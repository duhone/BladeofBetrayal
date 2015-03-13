// EnemyWolf.h: interface for the EnemyWolf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYWOLF_H__54F2DB7E_0C9E_4373_9682_98E5C10A4230__INCLUDED_)
#define AFX_ENEMYWOLF_H__54F2DB7E_0C9E_4373_9682_98E5C10A4230__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyWolf : public BaseEnemy  
{
public:
	void Patrol();
	void UseBrain();
	bool IsStopBlock();
	
	AIEnemyWolf();
	virtual ~AIEnemyWolf();

};

#endif // !defined(AFX_ENEMYWOLF_H__54F2DB7E_0C9E_4373_9682_98E5C10A4230__INCLUDED_)
