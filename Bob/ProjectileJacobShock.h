// ProjectileJacobShock.h: interface for the ProjectileJacobShock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEJACOBSHOCK_H__F5680667_EFFC_4A01_8B52_D35338814E25__INCLUDED_)
#define AFX_PROJECTILEJACOBSHOCK_H__F5680667_EFFC_4A01_8B52_D35338814E25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileJacobShock : public Projectile  
{
public:
	ProjectileJacobShock(bool bDirection, int xPos, int yPos);
	virtual ~ProjectileJacobShock();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILEJACOBSHOCK_H__F5680667_EFFC_4A01_8B52_D35338814E25__INCLUDED_)
