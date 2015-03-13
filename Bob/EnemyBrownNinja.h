// EnemyBrownNinja.h: interface for the EnemyBrownNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBROWNNINJA_H__85FC846A_86EC_4616_8F17_2076A2934D66__INCLUDED_)
#define AFX_ENEMYBROWNNINJA_H__85FC846A_86EC_4616_8F17_2076A2934D66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EnemyNinja.h"

class EnemyBrownNinja : public EnemyNinja  
{
public:
	EnemyBrownNinja(Level *curLevel);
	virtual ~EnemyBrownNinja();

	virtual void processLeft();
	virtual void processRight();
	virtual void processDamage();
	virtual void stop();
	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
};

#endif // !defined(AFX_ENEMYBROWNNINJA_H__85FC846A_86EC_4616_8F17_2076A2934D66__INCLUDED_)
