// ProjectileMrThomasPhase.h: interface for the ProjectileMrThomasPhase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEMRTHOMASPHASE_H__00C3AFFE_916B_4875_9C1A_F13096BB71BE__INCLUDED_)
#define AFX_PROJECTILEMRTHOMASPHASE_H__00C3AFFE_916B_4875_9C1A_F13096BB71BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
#include "IPlayerConfig.h"

class ProjectileMrThomasPhase : public Projectile  
{
public:
	ProjectileMrThomasPhase(int xPos, int yPos, float xVel, IPlayerFlags *ipFlags, float *xLoc, 
							float *yLoc,int _leftBound,int _rightBound);
	virtual ~ProjectileMrThomasPhase();

	HPTRect &GetWeaponBounds();

	virtual void Update();

	
	virtual void DeActivate();

	IPlayerFlags *ipFlags;

	float *xLoc;
	float *yLoc;
private:
	int m_leftBound;
	int m_rightBound;
//	bool *stflag;
};

#endif // !defined(AFX_PROJECTILEMRTHOMASPHASE_H__00C3AFFE_916B_4875_9C1A_F13096BB71BE__INCLUDED_)
