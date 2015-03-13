// ProjectileFlameAttack.h: interface for the ProjectileFlameAttack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEFLAMEATTACK_H__BB0E11A7_8F97_4750_8711_5E6E9EB7E98B__INCLUDED_)
#define AFX_PROJECTILEFLAMEATTACK_H__BB0E11A7_8F97_4750_8711_5E6E9EB7E98B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
#include "ProjectileFlameBall.h"
//#include "hptlist.h"
#include<list>

class ProjectileFlameAttack : public Projectile  
{
public:
	ProjectileFlameAttack(bool bDirection, int xPos, int yPos, std::list<Projectile*> *projectile_list);
	virtual ~ProjectileFlameAttack();

	HPTRect &GetWeaponBounds();

	virtual void Update();

	 std::list<Projectile*> *projectile_list;
};

#endif // !defined(AFX_PROJECTILEFLAMEATTACK_H__BB0E11A7_8F97_4750_8711_5E6E9EB7E98B__INCLUDED_)
