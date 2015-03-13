// ProjectileJacobQuake.h: interface for the ProjectileJacobQuake class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEJACOBQUAKE_H__FB755A0E_8EE0_4CDC_8298_86325E2CAAB6__INCLUDED_)
#define AFX_PROJECTILEJACOBQUAKE_H__FB755A0E_8EE0_4CDC_8298_86325E2CAAB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
//#include "hptlist.h"
#include "IPlayerConfig.h"
#include <list>

class ProjectileJacobQuake : public Projectile  
{
public:
	ProjectileJacobQuake(int *xOffset, int *yOffset, int xPos, int yPos,std::list<Projectile*> *projectile_list, float *xLoc, float *yLoc, IPlayerFlags *ipFlags);
	virtual ~ProjectileJacobQuake();

	HPTRect &GetWeaponBounds();

	virtual void Render() {};
	virtual void Update();

private:
	float *xLoc;
	float *yLoc;
	int *xLevelRenderOffset;
	int *yLevelRenderOffset;
	float shake;
	bool S_SHAKE;
	std::list<Projectile*> *projectile_list;
	IPlayerFlags *ipFlags;
};

#endif // !defined(AFX_PROJECTILEJACOBQUAKE_H__FB755A0E_8EE0_4CDC_8298_86325E2CAAB6__INCLUDED_)
