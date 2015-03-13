// ProjectileStephPistol.h: interface for the ProjectileStephPistol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILESTEPHPISTOL_H__B4052477_DE3F_4034_B47F_EDB12388E170__INCLUDED_)
#define AFX_PROJECTILESTEPHPISTOL_H__B4052477_DE3F_4034_B47F_EDB12388E170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProjectileEliteGuardPistolBullet.h"
#include "IPlayer.h"

class ProjectileStephPistol : public ProjectileEliteGuardPistolBullet  
{
private:
	IPlayer *player;
	int xoffset;
	int yoffset;
public:
	ProjectileStephPistol(int angle, int xPos, int yPos,float xveladd,float yveladd,IPlayer *player,int xoffset,int yoffset);
	virtual ~ProjectileStephPistol();
	virtual void Update();

};

#endif // !defined(AFX_PROJECTILESTEPHPISTOL_H__B4052477_DE3F_4034_B47F_EDB12388E170__INCLUDED_)
