// EnemyFlameThrower.h: interface for the EnemyFlameThrower class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYFLAMETHROWER_H__6F406B23_A234_4319_8981_6F5936A086B4__INCLUDED_)
#define AFX_ENEMYFLAMETHROWER_H__6F406B23_A234_4319_8981_6F5936A086B4__INCLUDED_


#include "Enemy.h"

class EnemyFlameThrower : public Enemy  
{
public:
	EnemyFlameThrower(Level *curLevel, float tDelay, bool bOrientation, bool sDirection = true);
	virtual ~EnemyFlameThrower();

	HPTRect &GetWeaponWorldLoc();
//	HPTRect &GetWorldLoc();

	void processUpdate();

	bool IsEnemy() const { return false; }
	
private:
	float dTimer;
	float tDelay;
	bool bOrientation;
	bool sDirection;

};

#endif // !defined(AFX_ENEMYFLAMETHROWER_H__6F406B23_A234_4319_8981_6F5936A086B4__INCLUDED_)
