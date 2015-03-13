/*
 *  AIRunTo.h
 *  BoB
 *
 *  Created by Eric Duhon on 2/28/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "IPlayer.h"

template<int NextState>
class AIRunTo : public CR::Utility::IState
{
public:
	AIRunTo(BaseEnemy &_enemy,int _dest) : m_enemy(_enemy), m_dest(_dest) {}
	virtual bool Begin()
	{ 
		m_left = (m_enemy.aiinput->GetXLoc() - m_dest) > 0;
		//m_enemy.aioutput->SetDirection(m_left);
		
		if(m_left)
			m_enemy.aioutput->moveLeft();
		else
			m_enemy.aioutput->moveRight();
		
		return false;
	}
	virtual int Process()
	{
		if(m_left)
			m_enemy.aioutput->moveLeft();
		else
			m_enemy.aioutput->moveRight();
		
		if(m_left && m_enemy.aiinput->GetXLoc() <= m_dest)
			return NextState;
		if(!m_left && m_enemy.aiinput->GetXLoc() >= m_dest)
			return NextState;
		return IState::UNCHANGED;
	}
	virtual void End()
	{
		m_enemy.aioutput->moveStop();
	}
private:
	BaseEnemy &m_enemy;
	int m_dest;
	bool m_left;
};



