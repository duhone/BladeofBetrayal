// EnemyGawain.h: interface for the EnemyGawain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGAWAIN_H__6965DD75_59C7_42F1_A67A_64E994C1738A__INCLUDED_)
#define AFX_ENEMYGAWAIN_H__6965DD75_59C7_42F1_A67A_64E994C1738A__INCLUDED_


#include "Enemy.h"
#include "EnemyBirdGawain.h"
#include "EnemyWolfGawain.h"
#include "./aiengine/aiengine.h"
#include <vector>

class EnemyGawain : public Enemy  
{
public:
	EnemyGawain(Level *curLevel, std::vector<Enemy*> *enemys, AIEngine* ai_engine, IPlayer *player);
	virtual ~EnemyGawain();

	virtual void setJumpVelocity();
	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
	std::vector<Enemy*> *enemys;
	AIEngine* ai_engine;
	IPlayer *player;
	bool S_TELEPORT;
};

#endif // !defined(AFX_ENEMYGAWAIN_H__6965DD75_59C7_42F1_A67A_64E994C1738A__INCLUDED_)
