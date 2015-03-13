// EnemyBirdGawain.h: interface for the EnemyBirdGawain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBIRDGAWAIN_H__BB0FFE87_9667_4BFB_8338_6C4E109ADC9B__INCLUDED_)
#define AFX_ENEMYBIRDGAWAIN_H__BB0FFE87_9667_4BFB_8338_6C4E109ADC9B__INCLUDED_


#include "Enemy.h"

class EnemyBirdGawain : public Enemy  
{
public:
	EnemyBirdGawain(Level *curLevel, IPlayer *player);
	virtual ~EnemyBirdGawain();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	virtual void processDamage();
	virtual void processDeath();
	void processUpdate();

	IPlayer *player;
	bool HIT;
};

#endif // !defined(AFX_ENEMYBIRDGAWAIN_H__BB0FFE87_9667_4BFB_8338_6C4E109ADC9B__INCLUDED_)
