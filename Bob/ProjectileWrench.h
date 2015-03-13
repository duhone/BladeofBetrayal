// ProjectileWrench.h: interface for the ProjectileWrench class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEWRENCH_H__BD7233F7_5027_451F_9838_A492DFD95F8D__INCLUDED_)
#define AFX_PROJECTILEWRENCH_H__BD7233F7_5027_451F_9838_A492DFD95F8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileWrench : public Projectile  
{
public:
	ProjectileWrench(bool sDirection, int xPos, int yPos, float xVel, float yVel, float xAcc, float yAcc);
	virtual ~ProjectileWrench();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILEWRENCH_H__BD7233F7_5027_451F_9838_A492DFD95F8D__INCLUDED_)
