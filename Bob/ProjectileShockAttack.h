// ProjectileShockAttack.h: interface for the ProjectileShockAttack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILESHOCKATTACK_H__80EAD198_AE33_4B46_8B1D_9AF650CD8974__INCLUDED_)
#define AFX_PROJECTILESHOCKATTACK_H__80EAD198_AE33_4B46_8B1D_9AF650CD8974__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileShockAttack : public Projectile  
{
public:
	ProjectileShockAttack(bool bDirection, int xPos, int yPos);
	virtual ~ProjectileShockAttack();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILESHOCKATTACK_H__80EAD198_AE33_4B46_8B1D_9AF650CD8974__INCLUDED_)
