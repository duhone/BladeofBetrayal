// EnemyBear1.h: interface for the EnemyBear class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBEAR1_H__A46E6E98_7D0B_4E7A_A5C0_DD7CBCAAE100__INCLUDED_)
#define AFX_ENEMYBEAR1_H__A46E6E98_7D0B_4E7A_A5C0_DD7CBCAAE100__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Enemy.h"

class EnemyBear : public Enemy  
{
public:
	EnemyBear(Level *curLevel);
	virtual ~EnemyBear();

	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
};

#endif // !defined(AFX_ENEMYBEAR1_H__A46E6E98_7D0B_4E7A_A5C0_DD7CBCAAE100__INCLUDED_)
