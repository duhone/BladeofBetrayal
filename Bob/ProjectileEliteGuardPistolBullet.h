// ProjectileEliteGuardPistolBullet.h: interface for the ProjectileEliteGuardPistolBullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEELITEGUARDPISTOLBULLET_H__1D317E2D_D804_4E19_A6D7_6C829510EB8F__INCLUDED_)
#define AFX_PROJECTILEELITEGUARDPISTOLBULLET_H__1D317E2D_D804_4E19_A6D7_6C829510EB8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileEliteGuardPistolBullet : public Projectile  
{
public:
	ProjectileEliteGuardPistolBullet(bool bDirection, int xPos, int yPos);
	virtual ~ProjectileEliteGuardPistolBullet();
	ProjectileEliteGuardPistolBullet();

	
	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILEELITEGUARDPISTOLBULLET_H__1D317E2D_D804_4E19_A6D7_6C829510EB8F__INCLUDED_)
