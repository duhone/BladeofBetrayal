// ProjectileQuakeAttackRock.h: interface for the ProjectileQuakeAttackRock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEQUAKEATTACKROCK_H__E0EB5C6F_ED37_4183_85D9_5106F71FC3B2__INCLUDED_)
#define AFX_PROJECTILEQUAKEATTACKROCK_H__E0EB5C6F_ED37_4183_85D9_5106F71FC3B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Projectile.h"

class ProjectileQuakeAttackRock : public Projectile  
{
public:
	ProjectileQuakeAttackRock(int xPos, int yPos, float xVel, float yVel, float xAcc, float yAcc);
	virtual ~ProjectileQuakeAttackRock();

	HPTRect &GetWeaponBounds();

	virtual void Update();

};

#endif // !defined(AFX_PROJECTILEQUAKEATTACKROCK_H__E0EB5C6F_ED37_4183_85D9_5106F71FC3B2__INCLUDED_)
