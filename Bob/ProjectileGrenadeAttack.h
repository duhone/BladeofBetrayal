// ProjectileGrenadeAttack.h: interface for the ProjectileGrenadeAttack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEGRENADEATTACK_H__0D9509ED_264D_465A_9641_8E46B37E04E3__INCLUDED_)
#define AFX_PROJECTILEGRENADEATTACK_H__0D9509ED_264D_465A_9641_8E46B37E04E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
//#include "hptlist.h"

#include<list>

class ProjectileGrenadeAttack : public Projectile  
{
public:
	ProjectileGrenadeAttack(bool bDirection, int xPos, int yPos, std::list<Projectile*> *projectile_list);
	virtual ~ProjectileGrenadeAttack();

	HPTRect &GetWeaponBounds();

	virtual void Update();

	virtual void DeActivate();

	void Explode();

	bool IS_EXPLODING;

	std::list<Projectile*> *projectile_list;
	};

#endif // !defined(AFX_PROJECTILEGRENADEATTACK_H__0D9509ED_264D_465A_9641_8E46B37E04E3__INCLUDED_)
