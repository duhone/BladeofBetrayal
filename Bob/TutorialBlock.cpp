#include "TutorialBlock.h"

extern Game* game_class;

TutorialBlock::TutorialBlock(TutorialManager::Tutorials _tutorial) : m_tutorial(_tutorial)
{
}

TutorialBlock::~TutorialBlock(void)
{
}

bool TutorialBlock::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype)
{
	if(!game_class->IsInTransition())
		TutorialManager::Instance().Trigger(m_tutorial);
	return false;
}