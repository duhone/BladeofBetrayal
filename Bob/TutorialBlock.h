#pragma once
#include "object.h"
#include "TutorialManager.h"

class TutorialBlock : public Object
{
public:
	TutorialBlock(TutorialManager::Tutorials _tutorial);
	virtual ~TutorialBlock(void);
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype);
	bool IsObject() const { return false; }
private:
	TutorialManager::Tutorials m_tutorial;
};

