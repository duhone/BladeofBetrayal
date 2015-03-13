// ProjectileBird.h: interface for the ProjectileBird class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEBIRD_H__4FEE61EE_9A80_490C_A65D_E5CEB3FF67AB__INCLUDED_)
#define AFX_PROJECTILEBIRD_H__4FEE61EE_9A80_490C_A65D_E5CEB3FF67AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
#include "IPlayer.h"

class ProjectileBird : public Projectile  
{
public:
	ProjectileBird(IPlayer *player);
	virtual ~ProjectileBird();

};

#endif // !defined(AFX_PROJECTILEBIRD_H__4FEE61EE_9A80_490C_A65D_E5CEB3FF67AB__INCLUDED_)
