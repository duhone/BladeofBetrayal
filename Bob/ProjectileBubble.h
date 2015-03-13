// ProjectileBubble.h: interface for the ProjectileBubble class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILEBUBBLE_H__E7CEC675_5111_4558_A047_8E44ECFD4C74__INCLUDED_)
#define AFX_PROJECTILEBUBBLE_H__E7CEC675_5111_4558_A047_8E44ECFD4C74__INCLUDED_


#include "Projectile.h"

class ProjectileBubble : public Projectile  
{
public:
	ProjectileBubble(int xPos, int yPos);
	virtual ~ProjectileBubble();

	HPTRect &GetWeaponBounds();

	virtual void Update();
private:
	float movetimer;
};

#endif // !defined(AFX_PROJECTILEBUBBLE_H__E7CEC675_5111_4558_A047_8E44ECFD4C74__INCLUDED_)
