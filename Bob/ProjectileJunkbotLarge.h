// ProjectileJunkbotLarge.h: interface for the ProjectileJunkbotLarge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEJUNKBOTLARGE_H__450C7D78_593C_4478_9824_3BA21262D8DE__INCLUDED_)
#define AFX_PROJECTILEJUNKBOTLARGE_H__450C7D78_593C_4478_9824_3BA21262D8DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileJunkbotLarge : public Projectile  
{
public:
	ProjectileJunkbotLarge(bool bDirection, int xPos, int yPos);
	virtual ~ProjectileJunkbotLarge();

	HPTRect &GetWeaponBounds();

	virtual void Update();


};

#endif // !defined(AFX_PROJECTILEJUNKBOTLARGE_H__450C7D78_593C_4478_9824_3BA21262D8DE__INCLUDED_)
