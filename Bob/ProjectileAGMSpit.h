/*
 *  ProjectileAGMSpit.h
 *  BoB
 *
 *  Created by Eric Duhon on 2/28/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "Projectile.h"
#include <list>

class ProjectileAGMSpit : public Projectile  
{
public:
	ProjectileAGMSpit(bool bDirection, int xPos, int yPos, std::list<Projectile*> &_projectile_list,int _playerX,bool _isSmall=false);
	virtual ~ProjectileAGMSpit();
	
	HPTRect &GetWeaponBounds();
	
	virtual void Update();	
	virtual void DeActivate();
private:
	std::list<Projectile*> &m_projectileList;
	static const float c_xTime;
	float m_xVel;
	float m_yVel;
	bool m_isSmall;
};



