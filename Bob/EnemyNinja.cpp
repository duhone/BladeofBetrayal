// EnemyNinja.cpp: implementation of the EnemyNinja class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyNinja.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyNinja::EnemyNinja()
{
	SetRenderOffset(enemy_ninja_render_offset);
	SetMaxWalkVelocity(static_cast<float>(enemy_ninja_max_walk_velocity));
	SetWalkAcceleration(static_cast<float>(enemy_ninja_walk_acceleration));
	SetPlayerRectangle(enemy_ninja_width, enemy_ninja_height);
}

EnemyNinja::~EnemyNinja()
{

}

/*HPTRect &EnemyNinja::GetWorldLoc()
{
	rectWorldLoc.p1.x = static_cast<int>(xLoc - 20 + nOffSet); 
	rectWorldLoc.p2.x = static_cast<int>(xLoc - 5 + nOffSet);
	rectWorldLoc.p1.y = static_cast<int>(yLoc - 15);
	rectWorldLoc.p2.y = static_cast<int>(yLoc + 30);

	return rectWorldLoc;
}*/

/*HPTRect &EnemyNinja::GetWeaponWorldLoc()
{
	if(ipFlags.S_DIRECTION)
	{
		rectWeaponWorldLoc.p1.x = static_cast<int>(xLoc + nOffSet);
		rectWeaponWorldLoc.p2.x = static_cast<int>(xLoc + 20 + nOffSet);
		rectWeaponWorldLoc.p1.y = static_cast<int>(yLoc - 2);
		rectWeaponWorldLoc.p2.y = static_cast<int>(yLoc + 2);
	}
	else
	{
		rectWeaponWorldLoc.p1.x = static_cast<int>(xLoc - 20 - nOffSet);
		rectWeaponWorldLoc.p2.x = static_cast<int>(xLoc - nOffSet);
		rectWeaponWorldLoc.p1.y = static_cast<int>(yLoc - 2);
		rectWeaponWorldLoc.p2.y = static_cast<int>(yLoc + 2);
	}

	return rectWeaponWorldLoc;
}*/
