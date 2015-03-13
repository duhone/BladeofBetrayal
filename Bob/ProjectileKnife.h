// ProjectileKnife.h: interface for the ProjectileKnife class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEKNIFE_H__A46EC815_F1C7_4BEE_8BF0_88B7CB83489F__INCLUDED_)
#define AFX_PROJECTILEKNIFE_H__A46EC815_F1C7_4BEE_8BF0_88B7CB83489F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileKnife : public Projectile  
{
public:
	ProjectileKnife(bool sDirection, int xPos, int yPos, float xVel, float yVel, float xAcc, float yAcc);
	virtual ~ProjectileKnife();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILEKNIFE_H__A46EC815_F1C7_4BEE_8BF0_88B7CB83489F__INCLUDED_)
