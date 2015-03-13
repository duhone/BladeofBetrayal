// ProjectileGMonsterSpit.h: interface for the ProjectileGMonsterSpit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEGMONSTERSPIT_H__66299677_1176_4FE5_A00B_1EB27D6B0DF3__INCLUDED_)
#define AFX_PROJECTILEGMONSTERSPIT_H__66299677_1176_4FE5_A00B_1EB27D6B0DF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileGMonsterSpit : public Projectile  
{
public:
	ProjectileGMonsterSpit(bool bDirection, int xPos, int yPos);
	virtual ~ProjectileGMonsterSpit();

	HPTRect &GetWeaponBounds();

	virtual void Update();

};

#endif // !defined(AFX_PROJECTILEGMONSTERSPIT_H__66299677_1176_4FE5_A00B_1EB27D6B0DF3__INCLUDED_)
