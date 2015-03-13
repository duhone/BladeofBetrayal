/*
 *  AGMJumpState.h
 *  BoB
 *
 *  Created by Eric Duhon on 2/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "EnemyAdvancedGeneticMonster.h"

template<int NextState>
class AGMJumpState : public CR::Utility::IState
{
public:
	AGMJumpState(AIEnemyAdvancedGeneticMonster &_agm,bool _left) : m_agm(_agm), m_left(_left) {}
	virtual bool Begin()
	{ 
		if(m_left)
			m_agm.aioutput->SuperJump(m_agm.JumpBlockLeft().x* 16 ,1.6f,1,80);
		else
			m_agm.aioutput->SuperJump(m_agm.JumpBlockRight().x * 16 + 30,1.6f,1,80);
		return false;
	}
	virtual int Process()
	{
		if(m_agm.aiinput->FinishedSuperJump())
			return NextState;
		return IState::UNCHANGED;
	}
	/*virtual void End()
	{
		m_agm.aioutput->SetDirection(!m_left);
	}*/
private:
	AIEnemyAdvancedGeneticMonster &m_agm;
	bool m_left;
};

