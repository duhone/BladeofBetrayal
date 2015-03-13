// EnemyElectricField.h: interface for the EnemyElectricField class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYELECTRICFIELD_H__0AB7E0BA_B725_497D_B1C5_5E485AE15F63__INCLUDED_)
#define AFX_ENEMYELECTRICFIELD_H__0AB7E0BA_B725_497D_B1C5_5E485AE15F63__INCLUDED_


#include "Enemy.h"

class EnemyElectricField : public Enemy  
{
public:
public:
	EnemyElectricField(Level *curLevel, float tDelay, bool bOrientation, bool sDirection = true);
	virtual ~EnemyElectricField();

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

#endif // !defined(AFX_ENEMYELECTRICFIELD_H__0AB7E0BA_B725_497D_B1C5_5E485AE15F63__INCLUDED_)
