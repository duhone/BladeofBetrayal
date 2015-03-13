// ProjectileQuakeAttack.h: interface for the ProjectileQuakeAttack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEQUAKEATTACK_H__8D10386F_C8C3_4008_AA40_C24F4050ED41__INCLUDED_)
#define AFX_PROJECTILEQUAKEATTACK_H__8D10386F_C8C3_4008_AA40_C24F4050ED41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
//#include "hptlist.h"
#include "IPlayerConfig.h"
#include <list>

class ProjectileQuakeAttack : public Projectile  
{
public:
	ProjectileQuakeAttack(int *xOffset, int *yOffset, int xPos, int yPos,std::list<Projectile*> *projectile_list, float *xLoc, float *yLoc, IPlayerFlags *ipFlags);
	virtual ~ProjectileQuakeAttack();

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

#endif // !defined(AFX_PROJECTILEQUAKEATTACK_H__8D10386F_C8C3_4008_AA40_C24F4050ED41__INCLUDED_)
