// EnemyJacob.h: interface for the EnemyJacob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJACOB_H__ED6CF03D_3B46_411B_9FE2_09CF1D05537E__INCLUDED_)
#define AFX_ENEMYJACOB_H__ED6CF03D_3B46_411B_9FE2_09CF1D05537E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"
#include "../../Engines/Utility/FSM.h"
#include "../AIRunToPlayer.h"

class AIEnemyJacob : public BaseEnemy  
{
public:
	AIEnemyJacob();
	virtual ~AIEnemyJacob();
	virtual void UseBrain();
	virtual void Init();
	const HPTPoint& JumpBlockLeft() const {return m_jumpBlockLeft;}
	const HPTPoint& JumpBlockRight() const {return m_jumpBlockRight;}
	
private:	
	CR::Utility::FSM m_stateMachine;
	HPTPoint m_jumpBlockLeft;
	HPTPoint m_jumpBlockRight;
	AIRunToPlayer<0> *m_finalRun;
	bool m_fRun;
	bool m_grab;
};

#endif // !defined(AFX_ENEMYJACOB_H__ED6CF03D_3B46_411B_9FE2_09CF1D05537E__INCLUDED_)
