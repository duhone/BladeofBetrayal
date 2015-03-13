// EnemyMohawkPunk.h: interface for the EnemyMohawkPunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYMOHAWKPUNK_H__EC8C0113_A932_4CB2_AD44_52120A47CAD0__INCLUDED_)
#define AFX_ENEMYMOHAWKPUNK_H__EC8C0113_A932_4CB2_AD44_52120A47CAD0__INCLUDED_


#include "Enemy.h"

class EnemyMohawkPunk : public Enemy  
{
public:
	EnemyMohawkPunk(Level *curLevel);
	virtual ~EnemyMohawkPunk();
	
	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();
	virtual void stop();

	HPTRect &GetWeaponWorldLoc();
	//virtual HPTRect &GetWorldLoc();

	void processUpdate();
};

#endif // !defined(AFX_ENEMYMOHAWKPUNK_H__EC8C0113_A932_4CB2_AD44_52120A47CAD0__INCLUDED_)
