// ProjectileSentryBullet.h: interface for the ProjectileSentryBullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILESENTRYBULLET_H__3CC918AE_A841_4116_80A4_68F6AAB3A69B__INCLUDED_)
#define AFX_PROJECTILESENTRYBULLET_H__3CC918AE_A841_4116_80A4_68F6AAB3A69B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileSentryBullet : public Projectile  
{
public:
	ProjectileSentryBullet(int xPos, int yPos, float xVel, float yVel);
	virtual ~ProjectileSentryBullet();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILESENTRYBULLET_H__3CC918AE_A841_4116_80A4_68F6AAB3A69B__INCLUDED_)
