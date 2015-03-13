// ProjectileProjectileAttack.h: interface for the ProjectileProjectileAttack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEPROJECTILEATTACK_H__67E7E783_9425_4859_83AD_197171654F1D__INCLUDED_)
#define AFX_PROJECTILEPROJECTILEATTACK_H__67E7E783_9425_4859_83AD_197171654F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileProjectileAttack : public Projectile  
{
public:
	ProjectileProjectileAttack(bool bDirection, int xPos, int yPos);
	virtual ~ProjectileProjectileAttack();

	HPTRect &GetWeaponBounds();
	virtual void Update();

};

#endif // !defined(AFX_PROJECTILEPROJECTILEATTACK_H__67E7E783_9425_4859_83AD_197171654F1D__INCLUDED_)
