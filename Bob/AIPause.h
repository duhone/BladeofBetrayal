/*
 *  AIPause.h
 *  BoB
 *
 *  Created by Eric Duhon on 2/25/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

template<int NextState>
class AIPause : public CR::Utility::IState
{
public:
	AIPause(BaseEnemy &_enemy,float _totalTime,bool _direction,bool _setDirection = true) :
		m_totalTime(_totalTime), m_enemy(_enemy), m_direction(_direction), m_setDirection(_setDirection) {}
	virtual bool Begin()
	{
		if(m_setDirection)
		{
			if(m_direction)
			{
				m_enemy.aioutput->SetDirection(true);
				m_enemy.aioutput->FaceRight();
			}
			else
			{
				m_enemy.aioutput->SetDirection(false);
				m_enemy.aioutput->FaceLeft();
			}
		}
		m_pauseTime = 0;
		return true;
	}
	virtual int Process()
	{
		if(m_setDirection)
		{
			if(m_direction)
				m_enemy.aioutput->FaceRight();
			else
				m_enemy.aioutput->FaceLeft();
		}
		m_enemy.aioutput->moveStop();
		m_pauseTime += m_enemy.time;
		if(m_pauseTime >= m_totalTime)
			return NextState;
		return UNCHANGED;
	}
private:
	float m_pauseTime;
	float m_totalTime;
	bool m_direction;
	BaseEnemy &m_enemy;
	bool m_setDirection;
};

