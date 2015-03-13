// ProjectileCrashRocket.h: interface for the ProjectileCrashRocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILECRASHROCKET_H__D807DAA3_C6F8_4925_A637_3288E94F6E51__INCLUDED_)
#define AFX_PROJECTILECRASHROCKET_H__D807DAA3_C6F8_4925_A637_3288E94F6E51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
#include "ProjectileCrashExplosion.h"

//#include "hptlist.h"
#include <list>

class ProjectileCrashRocket : public Projectile  
{
public:
	ProjectileCrashRocket(bool bDirection, int xPos, int yPos, std::list<Projectile*> *projectile_list);
	virtual ~ProjectileCrashRocket();

	virtual void DeActivate();

	HPTRect &GetWeaponBounds();
	virtual void Update();

	std::list<Projectile*> *projectile_list;
};

#endif // !defined(AFX_PROJECTILECRASHROCKET_H__D807DAA3_C6F8_4925_A637_3288E94F6E51__INCLUDED_)
