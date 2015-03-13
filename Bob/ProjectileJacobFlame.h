// ProjectileJacobFlame.h: interface for the ProjectileJacobFlame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEJACOBFLAME_H__1D7D72D2_9520_4F8E_ABAD_12CF8F2BEAAF__INCLUDED_)
#define AFX_PROJECTILEJACOBFLAME_H__1D7D72D2_9520_4F8E_ABAD_12CF8F2BEAAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
#include "ProjectileJacobFlameBall.h"
//#include "hptlist.h"
#include <list>

class ProjectileJacobFlame : public Projectile  
{
public:
	ProjectileJacobFlame(bool bDirection, int xPos, int yPos, std::list<Projectile*> *projectile_list);
	virtual ~ProjectileJacobFlame();

	HPTRect &GetWeaponBounds();

	virtual void Update();

	 std::list<Projectile*> *projectile_list;
};

#endif // !defined(AFX_PROJECTILEJACOBFLAME_H__1D7D72D2_9520_4F8E_ABAD_12CF8F2BEAAF__INCLUDED_)
