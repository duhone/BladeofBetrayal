// ProjectileStephRifle.h: interface for the ProjectileStephRifle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILESTEPHRIFLE_H__4443946F_3B58_4077_84E0_5D8F79DC4901__INCLUDED_)
#define AFX_PROJECTILESTEPHRIFLE_H__4443946F_3B58_4077_84E0_5D8F79DC4901__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"ProjectileEliteGuardRifleBullet.h"
#include "IPlayer.h"


class ProjectileStephRifle : public ProjectileEliteGuardRifleBullet
{
	IPlayer *player;
	int xoffset;
	int yoffset;

public:
	ProjectileStephRifle(int angle, float delay,float xveladd,float yveladd,IPlayer *player,int xoffset,int yoffset);
	virtual ~ProjectileStephRifle();

	HPTRect &GetWeaponBounds();

	virtual void Update();

};

#endif // !defined(AFX_PROJECTILESTEPHRIFLE_H__4443946F_3B58_4077_84E0_5D8F79DC4901__INCLUDED_)
