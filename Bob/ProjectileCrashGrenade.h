// ProjectileCrashGrenade.h: interface for the ProjectileCrashGrenade class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILECRASHGRENADE_H__F8FC58D4_6DB9_4A30_9561_46570398EA0F__INCLUDED_)
#define AFX_PROJECTILECRASHGRENADE_H__F8FC58D4_6DB9_4A30_9561_46570398EA0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
//#include "hptlist.h"
#include<list>

class ProjectileCrashGrenade : public Projectile  
{
public:
	ProjectileCrashGrenade(bool bDirection, int xPos, int yPos,std::list<Projectile*> *projectile_list, bool TYPE);
	virtual ~ProjectileCrashGrenade();

	HPTRect &GetWeaponBounds();

	virtual void Update();
	virtual void DeActivate();

	void Explode();

	bool IS_EXPLODING;
	bool TYPE;

	std::list<Projectile*> *projectile_list;
};

#endif // !defined(AFX_PROJECTILECRASHGRENADE_H__F8FC58D4_6DB9_4A30_9561_46570398EA0F__INCLUDED_)
