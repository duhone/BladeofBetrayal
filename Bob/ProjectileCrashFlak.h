// ProjectileCrashFlak.h: interface for the ProjectileCrashFlak class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILECRASHFLAK_H__6DDB53D6_EF33_419C_A51F_BC601E4FE9E4__INCLUDED_)
#define AFX_PROJECTILECRASHFLAK_H__6DDB53D6_EF33_419C_A51F_BC601E4FE9E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileCrashFlak : public Projectile  
{
public:
	ProjectileCrashFlak(int xPos, int yPos, float xVel, float yVel, float tDelay = 0);
	virtual ~ProjectileCrashFlak();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILECRASHFLAK_H__6DDB53D6_EF33_419C_A51F_BC601E4FE9E4__INCLUDED_)
