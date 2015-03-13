// EnemyBlueNinja.h: interface for the EnemyBlueNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBLUENINJA_H__CCAB923D_AFFE_4CD6_B933_04D0618B7976__INCLUDED_)
#define AFX_ENEMYBLUENINJA_H__CCAB923D_AFFE_4CD6_B933_04D0618B7976__INCLUDED_


#include "EnemyNinja.h"



class EnemyBlueNinja : public EnemyNinja    
{
public:
	EnemyBlueNinja(Level *curLevel);
	virtual ~EnemyBlueNinja();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
};

#endif // !defined(AFX_ENEMYBLUENINJA_H__CCAB923D_AFFE_4CD6_B933_04D0618B7976__INCLUDED_)
