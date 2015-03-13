// EnemyAdvancedGeneticMonster.cpp: implementation of the EnemyAdvancedGeneticMonster class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyAdvancedGeneticMonster.h"

#include "../AGMJumpState.h"
#include "../AIPause.h"
#include "../AIAttack.h"
#include "../AIRunTo.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyAdvancedGeneticMonster::AIEnemyAdvancedGeneticMonster()
{
	
}

void AIEnemyAdvancedGeneticMonster::Init()
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
	
	m_stateMachine << new AIPause<1>(*this,1.0f,false) << new AIAttack<2,0>(*this) << new AIAttack<3,1>(*this);
	m_stateMachine << new AGMJumpState<4>(*this,true) << new AIAttack<5,1>(*this) << new AGMJumpState<6>(*this,false);
	m_stateMachine << new AIAttack<7,2>(*this) << new AIPause<8>(*this,0.5f,false) << new AIAttack<9,3>(*this);
	m_stateMachine << new AIPause<10>(*this,1.0f,false) << new AIRunTo<11>(*this,m_jumpBlockLeft.x*16) << new AIRunTo<12>(*this,m_jumpBlockRight.x*16);
	m_stateMachine << new AIRunTo<13>(*this,m_jumpBlockLeft.x*16) << new AIPause<14>(*this,0.0f,true) << new AIAttack<15,4>(*this);
	m_stateMachine << new AIPause<16>(*this,1.0f,true) << new AGMJumpState<17>(*this,false) << new AIPause<2>(*this,0.0f,false);
	
	aioutput->SetDirection(false);	
}

AIEnemyAdvancedGeneticMonster::~AIEnemyAdvancedGeneticMonster()
{

}

void AIEnemyAdvancedGeneticMonster::UseBrain()
{	
	if(m_stateMachine.State == -1)
		m_stateMachine.State = 0;
	if(!aiinput->ipFlags.S_DEAD)
		m_stateMachine();
}