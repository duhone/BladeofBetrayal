// ProjectileJacobFlameBall.h: interface for the ProjectileJacobFlameBall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEJACOBFLAMEBALL_H__E703B7B5_F7B5_4CE8_B8D5_52ADBCC62CD0__INCLUDED_)
#define AFX_PROJECTILEJACOBFLAMEBALL_H__E703B7B5_F7B5_4CE8_B8D5_52ADBCC62CD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileJacobFlameBall : public Projectile  
{
public:
	ProjectileJacobFlameBall(bool bDirection, int xPos, int yPos, int xVel, int yVel, int frameset, float sDelay);
	virtual ~ProjectileJacobFlameBall();

	HPTRect &GetWeaponBounds();

	virtual void Update();

	int frameset;
};

#endif // !defined(AFX_PROJECTILEJACOBFLAMEBALL_H__E703B7B5_F7B5_4CE8_B8D5_52ADBCC62CD0__INCLUDED_)
