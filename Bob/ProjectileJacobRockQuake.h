// ProjectileJacobRockQuake.h: interface for the ProjectileJacobRockQuake class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEJACOBROCKQUAKE_H__DFEC0DEC_6726_49CA_9561_B62FEE0A3A37__INCLUDED_)
#define AFX_PROJECTILEJACOBROCKQUAKE_H__DFEC0DEC_6726_49CA_9561_B62FEE0A3A37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
//#include "hptlist.h"
#include "IPlayerConfig.h"
#include <list>

class ProjectileJacobRockQuake : public Projectile  
{
public:
	ProjectileJacobRockQuake(int *xOffset, int *yOffset, int xPos, int yPos,std::list<Projectile*> *projectile_list, float *xLoc, float *yLoc, IPlayerFlags *ipFlags);
	virtual ~ProjectileJacobRockQuake();
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

#endif // !defined(AFX_PROJECTILEJACOBROCKQUAKE_H__DFEC0DEC_6726_49CA_9561_B62FEE0A3A37__INCLUDED_)
