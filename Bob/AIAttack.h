/*
 *  AIAttack.h
 *  BoB
 *
 *  Created by Eric Duhon on 2/26/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "IPlayer.h"

template<int NextState,int Attack>
class AIAttack : public CR::Utility::IState
{
public:
	enum Facing
	{
		FACE_NONE = 0,
		FACE_LEFT,
		FACE_RIGHT,
		FACE_PLAYER
	};
	AIAttack(BaseEnemy &_enemy,Facing _faceing=FACE_PLAYER) : m_enemy(_enemy), m_faceing(_faceing) {}
	virtual bool Begin()
	{ 
		switch (m_faceing)
		{
			case FACE_PLAYER:
				m_enemy.FacePlayer();
				break;
			case FACE_LEFT:
				m_enemy.aioutput->FaceLeft();
				break;				
			case FACE_RIGHT:
				m_enemy.aioutput->FaceRight();
				break;				
			default:
				break;
		}
		m_enemy.aioutput->SetAttack(Attack);
		m_enemy.aioutput->moveButton4();
		return false;
	}
	virtual int Process()
	{
		if(!m_enemy.aiinput->ipFlags.S_ATTACK)
			return NextState;
		return IState::UNCHANGED;
	}
	
private:
	BaseEnemy &m_enemy;
	Facing m_faceing;
};


