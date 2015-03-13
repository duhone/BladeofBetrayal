// EnemyBird.h: interface for the EnemyBird class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBIRD_H__ED33FAFD_AEF9_4362_96E7_38452605855B__INCLUDED_)
#define AFX_ENEMYBIRD_H__ED33FAFD_AEF9_4362_96E7_38452605855B__INCLUDED_


#include "Enemy.h"

class EnemyBird : public Enemy  
{
public:
	EnemyBird(Level *curLevel, IPlayer *player);
	virtual ~EnemyBird();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	void processUpdate();

//	void updateWorldLoc();

	IPlayer *player;
	bool HIT;
};

#endif // !defined(AFX_ENEMYBIRD_H__ED33FAFD_AEF9_4362_96E7_38452605855B__INCLUDED_)
