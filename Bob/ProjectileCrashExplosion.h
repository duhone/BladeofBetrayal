// ProjectileCrashExplosion.h: interface for the ProjectileCrashExplosion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILECRASHEXPLOSION_H__C9A55D0F_E9A9_49FE_A6F4_991F63C28ED1__INCLUDED_)
#define AFX_PROJECTILECRASHEXPLOSION_H__C9A55D0F_E9A9_49FE_A6F4_991F63C28ED1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileCrashExplosion : public Projectile  
{
public:
	ProjectileCrashExplosion(int xPos, int yPos, float tDelay);
	virtual ~ProjectileCrashExplosion();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILECRASHEXPLOSION_H__C9A55D0F_E9A9_49FE_A6F4_991F63C28ED1__INCLUDED_)
