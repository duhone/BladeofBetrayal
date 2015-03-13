// ProjectileUpgrade.h: interface for the ProjectileUpgrade class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEUPGRADE_H__88CF791A_C9BD_47A7_9817_CA4606975E3E__INCLUDED_)
#define AFX_PROJECTILEUPGRADE_H__88CF791A_C9BD_47A7_9817_CA4606975E3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"


extern HPTFont1 *gothic10;

class ProjectileUpgrade : public Projectile  
{
public:
	ProjectileUpgrade(char *Message);
	virtual ~ProjectileUpgrade();

	virtual void Update();
	virtual void Render();

private:
	char *message;
};

#endif // !defined(AFX_PROJECTILEUPGRADE_H__88CF791A_C9BD_47A7_9817_CA4606975E3E__INCLUDED_)
