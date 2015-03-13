// EnemyFire.h: interface for the EnemyFire class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYFIRE_H__83C3A8C4_2897_4F1D_A4DE_7FFAC2FC96B5__INCLUDED_)
#define AFX_ENEMYFIRE_H__83C3A8C4_2897_4F1D_A4DE_7FFAC2FC96B5__INCLUDED_


#include "Enemy.h"

class EnemyFire : public Enemy  
{
public:
	void StartFlame();
	EnemyFire(Level *curLevel);
	virtual ~EnemyFire();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	void processUpdate();
	bool IsEnemy() const { return false; }
};

#endif // !defined(AFX_ENEMYFIRE_H__83C3A8C4_2897_4F1D_A4DE_7FFAC2FC96B5__INCLUDED_)
