// ProjectileJunkbotWalkingBullet.h: interface for the ProjectileJunkbotWalkingBullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEJUNKBOTWALKINGBULLET_H__5ED9E36B_16CE_4A1E_80D4_9A5B0E4E56F5__INCLUDED_)
#define AFX_PROJECTILEJUNKBOTWALKINGBULLET_H__5ED9E36B_16CE_4A1E_80D4_9A5B0E4E56F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"
//#include "hptlist.h"
#include <list>

class ProjectileJunkbotWalkingBullet : public Projectile  
{
public:
	ProjectileJunkbotWalkingBullet(bool bDirection, int xPos, int yPos, std::list<Projectile*> *projectile_list, int xVel = 0, int yVel = 0, float delay = 0, float activetime = 1);
	virtual ~ProjectileJunkbotWalkingBullet();

	HPTRect &GetWeaponBounds();

	virtual void Update();

	std::list<Projectile*> *projectile_list;

	bool TYPE;
};

#endif // !defined(AFX_PROJECTILEJUNKBOTWALKINGBULLET_H__5ED9E36B_16CE_4A1E_80D4_9A5B0E4E56F5__INCLUDED_)
