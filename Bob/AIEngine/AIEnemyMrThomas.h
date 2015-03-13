// EnemyMrThomas.h: interface for the EnemyMrThomas class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYMRTHOMAS_H__CE05B7A1_36CD_45F6_953F_7A685A405032__INCLUDED_)
#define AFX_ENEMYMRTHOMAS_H__CE05B7A1_36CD_45F6_953F_7A685A405032__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"
#include "../../Engines/Utility/FSM.h"

class AIEnemyMrThomas : public BaseEnemy  
{
public:
	AIEnemyMrThomas();
	virtual ~AIEnemyMrThomas();
	virtual void UseBrain();
	virtual void Init();

private:	
	CR::Utility::FSM m_stateMachine;
	int m_left;
	int m_left1;
	int m_left2;
	int m_right;
	int m_right1;
	int m_right2;
};

#endif // !defined(AFX_ENEMYMRTHOMAS_H__CE05B7A1_36CD_45F6_953F_7A685A405032__INCLUDED_)
