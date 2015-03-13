// ProjectileNinjaStar.h: interface for the ProjectileNinjaStar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILENINJASTAR_H__A751FF0D_04F8_4CC6_9BE4_95D1C2EC4D2C__INCLUDED_)
#define AFX_PROJECTILENINJASTAR_H__A751FF0D_04F8_4CC6_9BE4_95D1C2EC4D2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileNinjaStar : public Projectile  
{
public:
	ProjectileNinjaStar(bool bDirection, int xPos, int yPos);
	virtual ~ProjectileNinjaStar();

	HPTRect &GetWeaponBounds();

	virtual void Update();

};

#endif // !defined(AFX_PROJECTILENINJASTAR_H__A751FF0D_04F8_4CC6_9BE4_95D1C2EC4D2C__INCLUDED_)
