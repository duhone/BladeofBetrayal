// ProjectileCrashBullet.h: interface for the ProjectileCrashBullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILECRASHBULLET_H__FFE1EE30_14B3_465F_BB38_CC3DE8D30135__INCLUDED_)
#define AFX_PROJECTILECRASHBULLET_H__FFE1EE30_14B3_465F_BB38_CC3DE8D30135__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileCrashBullet : public Projectile  
{
public:
	ProjectileCrashBullet(bool bDirection, int xPos, int yPos);
	virtual ~ProjectileCrashBullet();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILECRASHBULLET_H__FFE1EE30_14B3_465F_BB38_CC3DE8D30135__INCLUDED_)
