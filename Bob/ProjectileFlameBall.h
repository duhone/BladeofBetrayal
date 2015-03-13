// ProjectileFlameBall.h: interface for the ProjectileFlameBall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEFLAMEBALL_H__56F32768_F849_429B_8135_3DC8CDB31A75__INCLUDED_)
#define AFX_PROJECTILEFLAMEBALL_H__56F32768_F849_429B_8135_3DC8CDB31A75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileFlameBall : public Projectile  
{
public:
	ProjectileFlameBall(bool bDirection, int xPos, int yPos, int xVel, int yVel, int frameset, float sDelay);
	virtual ~ProjectileFlameBall();

	HPTRect &GetWeaponBounds();

	virtual void Update();

	int frameset;
};

#endif // !defined(AFX_PROJECTILEFLAMEBALL_H__56F32768_F849_429B_8135_3DC8CDB31A75__INCLUDED_)
