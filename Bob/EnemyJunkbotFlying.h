// EnemyJunkbotFlying.h: interface for the EnemyJunkbotFlying class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJUNKBOTFLYING_H__6B8181A6_AF02_43E7_962B_EA02016F602F__INCLUDED_)
#define AFX_ENEMYJUNKBOTFLYING_H__6B8181A6_AF02_43E7_962B_EA02016F602F__INCLUDED_


#include "Enemy.h"

class EnemyJunkbotFlying : public Enemy  
{
public:
	EnemyJunkbotFlying(Level *curLevel);
	virtual ~EnemyJunkbotFlying();

	//HPTRect &GetWorldLoc();

	virtual void processLeft();
	virtual void processRight();
	virtual void processUp();
	virtual void processDown();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();

	void processUpdate();
};

#endif // !defined(AFX_ENEMYJUNKBOTFLYING_H__6B8181A6_AF02_43E7_962B_EA02016F602F__INCLUDED_)
