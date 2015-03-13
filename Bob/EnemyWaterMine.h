// EnemyWaterMine.h: interface for the EnemyWaterMine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYWATERMINE_H__3777AE18_4F24_484F_8AC0_FFD7BDDE213B__INCLUDED_)
#define AFX_ENEMYWATERMINE_H__3777AE18_4F24_484F_8AC0_FFD7BDDE213B__INCLUDED_


#include "Enemy.h"

class EnemyWaterMine : public Enemy  
{
public:
	EnemyWaterMine(Level *curLevel);
	virtual ~EnemyWaterMine();

	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	void processUpdate();
	bool IsEnemy() const { return false; }
	
	void StartMine();
private:
	float bobtimer;

};

#endif // !defined(AFX_ENEMYWATERMINE_H__3777AE18_4F24_484F_8AC0_FFD7BDDE213B__INCLUDED_)
