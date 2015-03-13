/*
 *  AIRunToPlayer.h
 *  BoB
 *
 *  Created by Eric Duhon on 3/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "IPlayer.h"

template<int NextState>
class AIRunToPlayer : public CR::Utility::IState
{
public:
	AIRunToPlayer(BaseEnemy &_enemy,int _dist) : m_enemy(_enemy), m_dist(_dist) {}
	virtual bool Begin()
	{ 
		float playerfx = m_enemy.aio->player_input->GetXLoc();
		m_left = (m_enemy.aiinput->GetXLoc() - playerfx) > 0;
		//m_enemy.aioutput->SetDirection(m_left);
		
		if(m_left)
			m_enemy.aioutput->moveLeft();
		else
			m_enemy.aioutput->moveRight();
		
		return false;
	}
	virtual int Process()
	{
		float playerfx = m_enemy.aio->player_input->GetXLoc();
		if(m_left)
			m_enemy.aioutput->moveLeft();
		else
			m_enemy.aioutput->moveRight();
		
		if(m_left && m_enemy.aiinput->GetXLoc() <= playerfx+m_dist)
			return NextState;
		if(!m_left && m_enemy.aiinput->GetXLoc() >= playerfx-m_dist)
			return NextState;
		return IState::UNCHANGED;
	}
	virtual void End()
	{
		m_enemy.aioutput->moveStop();
	}
private:
	BaseEnemy &m_enemy;
	int m_dist;
	bool m_left;
};





