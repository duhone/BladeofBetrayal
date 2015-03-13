// EnemyBaseEliteGaurd.h: interface for the EnemyBaseEliteGaurd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBASEELITEGAURD_H__58EEAC7B_764C_4819_9C22_8427ADD0D1B2__INCLUDED_)
#define AFX_ENEMYBASEELITEGAURD_H__58EEAC7B_764C_4819_9C22_8427ADD0D1B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyBaseEliteGaurd: public BaseEnemy 
{
public:
	
	virtual bool IsStopBlock();
	void UseBrain();
	AIEnemyBaseEliteGaurd();
	virtual ~AIEnemyBaseEliteGaurd();

	float fire;

};

#endif // !defined(AFX_ENEMYBASEELITEGAURD_H__58EEAC7B_764C_4819_9C22_8427ADD0D1B2__INCLUDED_)
