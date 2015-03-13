// EnemyTowerBot.h: interface for the EnemyTowerBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYTOWERBOT_H__3B2A6897_CC30_4151_BFEE_639D5A59C173__INCLUDED_)
#define AFX_ENEMYTOWERBOT_H__3B2A6897_CC30_4151_BFEE_639D5A59C173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Enemy.h"

class EnemyTowerBot : public Enemy  
{
public:
	EnemyTowerBot(Level *curLevel);
	virtual ~EnemyTowerBot();

	virtual void processUp();
	virtual void processDown();
	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	void processUpdate();
};

#endif // !defined(AFX_ENEMYTOWERBOT_H__3B2A6897_CC30_4151_BFEE_639D5A59C173__INCLUDED_)
