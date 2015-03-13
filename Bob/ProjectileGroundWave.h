// ProjectileGroundWave.h: interface for the ProjectileGroundWave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEGROUNDWAVE_H__0BE36ED4_60BD_4241_9B95_56554C7425FE__INCLUDED_)
#define AFX_PROJECTILEGROUNDWAVE_H__0BE36ED4_60BD_4241_9B95_56554C7425FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileGroundWave : public Projectile  
{
public:
	ProjectileGroundWave(bool bDirection, int xPos, int yPos);
	virtual ~ProjectileGroundWave();

	HPTRect &GetWeaponBounds();
	virtual void Update();
};

#endif // !defined(AFX_PROJECTILEGROUNDWAVE_H__0BE36ED4_60BD_4241_9B95_56554C7425FE__INCLUDED_)
