// EnemyMrThomas.cpp: implementation of the EnemyMrThomas class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyMrThomas.h"
#include "../AIPause.h"
#include "../AIAttack.h"
#include "../AIRunTo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyMrThomas::AIEnemyMrThomas()
{
	
}

void AIEnemyMrThomas::Init()
{	
	for(int y = 0;y < aio->aimap_height;++y)
	{
		for(int x = 0;x < aio->aimap_width;++x)
		{
			int mapData = aio->ai_map[y*aio->aimap_width+x];
			//cout << mapData << " / ";
			switch (mapData)
			{
				case BLK_JUMP_LEFT:
					m_left = x*16;
					break;
				case BLK_RUN_LEFT1:
					m_left1 = x*16;
					break;
				case BLK_RUN_LEFT2:
					m_left2 = x*16;
					break;
				case BLK_JUMP_RIGHT:
					m_right = x*16;
					break;
				case BLK_RUN_RIGHT1:
					m_right1 = x*16;
					break;
				case BLK_RUN_RIGHT2:
					m_right2 = x*16;
					break;
				default:
					break;
			}
		}
	}		
	aioutput->SetEnds(m_left,m_right);
	m_stateMachine << new AIPause<1>(*this,1.0f,false) << new AIAttack<2,0>(*this) << new AIRunTo<3>(*this,m_right1);
	m_stateMachine << new AIAttack<4,1>(*this) << new AIRunTo<5>(*this,m_right2) << new AIAttack<6,2>(*this);
	m_stateMachine << new AIAttack<7,3>(*this,AIAttack<7,3>::FACE_LEFT) << new AIPause<8>(*this,0.25f,true) << new AIRunTo<9>(*this,m_left1);
	m_stateMachine << new AIAttack<10,1>(*this) << new AIRunTo<11>(*this,m_left2) << new AIAttack<12,2>(*this);
	m_stateMachine << new AIAttack<13,3>(*this,AIAttack<13,3>::FACE_RIGHT)<< new AIPause<2>(*this,0.25f,true);

	
	aioutput->SetDirection(false);
}

AIEnemyMrThomas::~AIEnemyMrThomas()
{

}

void AIEnemyMrThomas::UseBrain()
{	
	if(m_stateMachine.State == -1)
		m_stateMachine.State = 0;
	if(!aiinput->ipFlags.S_DEAD)
		m_stateMachine();
		
}

