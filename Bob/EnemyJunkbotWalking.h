// EnemyJunkbotWalking.h: interface for the EnemyJunkbotWalking class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJUNKBOTWALKING_H__4A0BF9F4_BEA9_47B3_8245_EB9AEEA9B197__INCLUDED_)
#define AFX_ENEMYJUNKBOTWALKING_H__4A0BF9F4_BEA9_47B3_8245_EB9AEEA9B197__INCLUDED_


#include "Enemy.h"

class EnemyJunkbotWalking : public Enemy  
{
public:
	EnemyJunkbotWalking(Level *curLevel);
	virtual ~EnemyJunkbotWalking();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();

};

#endif // !defined(AFX_ENEMYJUNKBOTWALKING_H__4A0BF9F4_BEA9_47B3_8245_EB9AEEA9B197__INCLUDED_)
