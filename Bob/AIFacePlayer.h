/*
 *  AIFacePlayer.h
 *  BoB
 *
 *  Created by Eric Duhon on 3/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

template<int NextState>
class AIFacePlayer : public CR::Utility::IState
{
public:
	AIFacePlayer(BaseEnemy &_enemy) : m_enemy(_enemy) {}
	virtual bool Begin()
	{
		m_enemy.FacePlayer();
		return true;
	}
	virtual int Process()
	{
		m_enemy.FacePlayer();
		return NextState;
	}
private:
	BaseEnemy &m_enemy;
};


