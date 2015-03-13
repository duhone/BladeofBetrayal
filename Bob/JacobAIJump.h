/*
 *  JacobAIJump.h
 *  BoB
 *
 *  Created by Eric Duhon on 3/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "EnemyJacob.h"

template<int NextState>
class JacobJumpState : public CR::Utility::IState
{
public:
	JacobJumpState(AIEnemyJacob &_jacob,bool _left) : m_jacob(_jacob), m_left(_left) {}
	virtual bool Begin()
	{ 
		if(m_left)
			m_jacob.aioutput->SuperJump(m_jacob.JumpBlockLeft().x,1,1,60);
		else
			m_jacob.aioutput->SuperJump(m_jacob.JumpBlockRight().x,1,1,60);
		return false;
	}
	virtual int Process()
	{
		if(m_jacob.aiinput->FinishedSuperJump())
			return NextState;
		return IState::UNCHANGED;
	}
	/*virtual void End()
	 {
	 m_agm.aioutput->SetDirection(!m_left);
	 }*/
private:
	AIEnemyJacob &m_jacob;
	bool m_left;
};



