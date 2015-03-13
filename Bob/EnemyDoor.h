// EnemyDoor.h: interface for the EnemyDoor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYDOOR_H__4CFE2377_95C6_4DDD_BDFC_23A994AB9714__INCLUDED_)
#define AFX_ENEMYDOOR_H__4CFE2377_95C6_4DDD_BDFC_23A994AB9714__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Enemy.h"
#include "Object.h"
class EnemyDoor : public Enemy  
{
private:
	int type;
	Object** object;
	Object** object1;
	Object** object2;
	unsigned char *level_data;
	bool isDead;
public:
	EnemyDoor(Level *curLevel,int arg,Object** obj,Object** obj1,Object** obj2,unsigned char*ld);
	virtual ~EnemyDoor();
	HPTRect &GetWeaponWorldLoc();
	void processUpdate();
	void processDeath();
	void doDoor(int type);
	bool forceOpenDoor();
	virtual void SetSprite(int nSet, int nSprite);

	bool IsEnemy() const { return false; }
};

#endif // !defined(AFX_ENEMYDOOR_H__4CFE2377_95C6_4DDD_BDFC_23A994AB9714__INCLUDED_)
