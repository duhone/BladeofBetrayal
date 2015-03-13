// ProjectileEliteGuardRifleBullet.h: interface for the ProjectileEliteGuardRifleBullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEELITEGUARDRIFLEBULLET_H__9D40149B_5A78_474C_BAB6_7655E374B29F__INCLUDED_)
#define AFX_PROJECTILEELITEGUARDRIFLEBULLET_H__9D40149B_5A78_474C_BAB6_7655E374B29F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileEliteGuardRifleBullet : public Projectile
{
public:
	ProjectileEliteGuardRifleBullet(bool bDirection, int xPos, int yPos, float delay);
	virtual ~ProjectileEliteGuardRifleBullet();
	ProjectileEliteGuardRifleBullet();

	
	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILEELITEGUARDRIFLEBULLET_H__9D40149B_5A78_474C_BAB6_7655E374B29F__INCLUDED_)
