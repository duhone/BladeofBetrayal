#ifndef WEAPON_H
#define WEAPON_H

#include "../Engines/Graphics/HPTGraphics.h"

class Weapon
{
public:
	Weapon();
	virtual ~Weapon();

	virtual void SetWeaponDamage(int nDamage);
	int GetWeaponDamage();

protected:
	int nAmtDmg;

private:

};

#endif