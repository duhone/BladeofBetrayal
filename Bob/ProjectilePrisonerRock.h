// ProjectilePrisonerRock.h: interface for the ProjectilePrisonerRock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEPRISONERROCK_H__BF7280E9_2D34_4286_B60A_11F03481E034__INCLUDED_)
#define AFX_PROJECTILEPRISONERROCK_H__BF7280E9_2D34_4286_B60A_11F03481E034__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
#include <math.h>
#include <stdlib.h>

class ProjectilePrisonerRock : public Projectile  
{
public:
	ProjectilePrisonerRock(bool bDirection, int xPos, int yPos);
	virtual ~ProjectilePrisonerRock();

	HPTRect &GetWeaponBounds();

	virtual void Update();

};

#endif // !defined(AFX_PROJECTILEPRISONERROCK_H__BF7280E9_2D34_4286_B60A_11F03481E034__INCLUDED_)
