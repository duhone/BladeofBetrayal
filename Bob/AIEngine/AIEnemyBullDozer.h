// EnemyBullDozer.h: interface for the EnemyBullDozer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBULLDOZER_H__8BC76F42_7C22_4D92_BDCE_891C743B2FB1__INCLUDED_)
#define AFX_ENEMYBULLDOZER_H__8BC76F42_7C22_4D92_BDCE_891C743B2FB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyBullDozer : public BaseEnemy  
{
public:
	bool first_move;
	virtual void UseBrain();
	AIEnemyBullDozer();
	virtual ~AIEnemyBullDozer();

};

#endif // !defined(AFX_ENEMYBULLDOZER_H__8BC76F42_7C22_4D92_BDCE_891C743B2FB1__INCLUDED_)
