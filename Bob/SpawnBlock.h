// SpawnBlock.h: interface for the SpawnBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPAWNBLOCK_H__8E7B24A2_4569_4C28_8AE4_24CD76E3E29E__INCLUDED_)
#define AFX_SPAWNBLOCK_H__8E7B24A2_4569_4C28_8AE4_24CD76E3E29E__INCLUDED_


#include "Object.h"


class SpawnBlock : public Object  
{
private:
	int state;

	
public:
	SpawnBlock();
	virtual ~SpawnBlock();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype);
	virtual bool WeaponCollideCheck(IPlayer* arg);
	virtual void Update();
	virtual bool ProjectileCollideCheck(IPlayer *arg0, Projectile* arg);
	int GetState() const {return state;}
	void SetState(int _value);
	bool IsObject() const { return false; }
};
#endif // !defined(AFX_SPAWNBLOCK_H__8E7B24A2_4569_4C28_8AE4_24CD76E3E29E__INCLUDED_)
