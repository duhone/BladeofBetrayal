// EnemyJunkbotLarge.h: interface for the EnemyJunkbotLarge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJUNKBOTLARGE_H__AEF2138D_FC51_4642_BD65_1A7FC461394C__INCLUDED_)
#define AFX_ENEMYJUNKBOTLARGE_H__AEF2138D_FC51_4642_BD65_1A7FC461394C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyJunkbotLarge : public BaseEnemy  
{
public:
	float rock_time;
	float rock;
	void Wait();
	void Attack();
	AIEnemyJunkbotLarge();
	virtual ~AIEnemyJunkbotLarge();

};

#endif // !defined(AFX_ENEMYJUNKBOTLARGE_H__AEF2138D_FC51_4642_BD65_1A7FC461394C__INCLUDED_)
