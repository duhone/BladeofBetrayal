// ProjectileGrenadeFlak.h: interface for the ProjectileGrenadeFlak class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEGRENADEFLAK_H__0B12A586_9778_4463_BC14_FDE6F0FACA18__INCLUDED_)
#define AFX_PROJECTILEGRENADEFLAK_H__0B12A586_9778_4463_BC14_FDE6F0FACA18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
#include<math.h>
#include<stdlib.h>

class ProjectileGrenadeFlak : public Projectile  
{
public:
	ProjectileGrenadeFlak(int xPos, int yPos, float xVel, float yVel, float xAcc, float yAcc);
	virtual ~ProjectileGrenadeFlak();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILEGRENADEFLAK_H__0B12A586_9778_4463_BC14_FDE6F0FACA18__INCLUDED_)
