// EnemyJacob.cpp: implementation of the EnemyJacob class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyJacob.h"
#include "../AIPause.h"
#include "../AIAttack.h"
#include "../AIRunToPlayer.h"
#include "../JacobAIJump.h"
#include "../AIFacePlayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyJacob::AIEnemyJacob()
{

}

AIEnemyJacob::~AIEnemyJacob()
{
	delete m_finalRun;
}

void AIEnemyJacob::Init()
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
					m_jumpBlockLeft.Set(x, y);
					break;
				case BLK_JUMP_RIGHT:
					m_jumpBlockRight.Set(x, y);
					break;
				default:
					break;
			}
		}
	}
	
	m_stateMachine << new AIPause<1>(*this,1.0f,false) << new AIAttack<2,0>(*this) << new AIRunToPlayer<3>(*this,56);
	m_stateMachine << new AIAttack<4,1>(*this) << new JacobJumpState<5>(*this,true) << new AIAttack<6,2>(*this);
	m_stateMachine << new AIPause<7>(*this,1.5f,true) << new AIRunToPlayer<8>(*this,56) << new AIAttack<9,1>(*this);
	m_stateMachine << new JacobJumpState<10>(*this,false)  << new AIAttack<11,2>(*this) << new AIPause<12>(*this,1.5f,false);
	m_stateMachine << new AIAttack<13,3>(*this)  << new AIAttack<14,4>(*this) << new AIPause<15>(*this,2.5f,false);
	m_stateMachine << new AIAttack<16,5>(*this) << new JacobJumpState<2>(*this,false) ; 
	
	m_finalRun = new AIRunToPlayer<0>(*this,48);
	
	aioutput->SetDirection(false);
	m_fRun = false;
	m_grab = false;
}

void AIEnemyJacob::UseBrain()
{	
	if(aiinput->ipFlags.S_FINAL_ANIM)
	{
		float playerfx = aio->player_input->GetXLoc();
		if(fabs(playerfx-aiinput->GetXLoc()) < 48)
		{
			m_grab = true;
			FacePlayer();
			aioutput->SetAttack(6);
			aioutput->moveButton4();
		}
		if(!m_grab)
		{
			if(!m_fRun)
			{
				m_fRun = true;
				m_finalRun->Begin();
			}
			if(m_finalRun->Process() == 0)
			{
				m_grab = true;
				aioutput->SetAttack(6);
				aioutput->moveButton4();
			}
		}
		return;
	}
	if(aio->player_input->ipFlags.S_FINAL_ANIM)
		return;
	if(m_stateMachine.State == -1)
		m_stateMachine.State = 0;
	if(!aiinput->ipFlags.S_DEAD)
		m_stateMachine();	
}

