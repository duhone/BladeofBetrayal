// ProjectileJacobStone.h: interface for the ProjectileJacobStone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEJACOBSTONE_H__FD258397_0B43_482F_91C9_31B40FC3007C__INCLUDED_)
#define AFX_PROJECTILEJACOBSTONE_H__FD258397_0B43_482F_91C9_31B40FC3007C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileJacobStone : public Projectile  
{
public:
	ProjectileJacobStone(bool sDirection, int xPos, int yPos, float xVel, float yVel, float xAcc, float yAcc, float tDelay);
	virtual ~ProjectileJacobStone();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILEJACOBSTONE_H__FD258397_0B43_482F_91C9_31B40FC3007C__INCLUDED_)
