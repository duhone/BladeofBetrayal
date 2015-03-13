// EnemyWolfGawain.h: interface for the EnemyWolfGawain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYWOLFGAWAIN_H__AB7F9D41_ECD2_430F_80D7_94998DFC01FB__INCLUDED_)
#define AFX_ENEMYWOLFGAWAIN_H__AB7F9D41_ECD2_430F_80D7_94998DFC01FB__INCLUDED_


#include "Enemy.h"

class EnemyWolfGawain : public Enemy  
{
public:
	EnemyWolfGawain(Level *curLevel, IPlayer *player);
	virtual ~EnemyWolfGawain();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

//	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();

	void updateWorldLoc();
	void processUpdate();

	IPlayer *player;
	bool HIT;
	bool START;
	bool COLLISION;
};

#endif // !defined(AFX_ENEMYWOLFGAWAIN_H__AB7F9D41_ECD2_430F_80D7_94998DFC01FB__INCLUDED_)
