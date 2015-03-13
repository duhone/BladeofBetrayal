// ProjectileJunkbotFlying.h: interface for the ProjectileJunkbotFlying class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEJUNKBOTFLYING_H__E257CB9D_0AEE_4B71_BF89_438B181A99C7__INCLUDED_)
#define AFX_PROJECTILEJUNKBOTFLYING_H__E257CB9D_0AEE_4B71_BF89_438B181A99C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileJunkbotFlying : public Projectile  
{
public:
	ProjectileJunkbotFlying(int xPos, int yPos, float xVel, float yVel);
	virtual ~ProjectileJunkbotFlying();

	HPTRect &GetWeaponBounds();

	virtual void Update();
};

#endif // !defined(AFX_PROJECTILEJUNKBOTFLYING_H__E257CB9D_0AEE_4B71_BF89_438B181A99C7__INCLUDED_)
