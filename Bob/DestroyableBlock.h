// DestroyableBlock.h: interface for the DestroyableBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESTROYABLEBLOCK_H__AF775B2A_D8E1_40CF_90D5_DB1A94AD664A__INCLUDED_)
#define AFX_DESTROYABLEBLOCK_H__AF775B2A_D8E1_40CF_90D5_DB1A94AD664A__INCLUDED_


#include "Object.h"

class DestroyableBlock : public Object  
{
public:
	void SetHitPoints(int arg);
	DestroyableBlock();
	virtual ~DestroyableBlock();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype);
	virtual void SetTime(float time_passed);
	virtual bool WeaponCollideCheck(IPlayer* arg);
	virtual void Update();
	virtual bool ProjectileCollideCheck(IPlayer *arg0, Projectile* arg);
	int GetState() const {return state;}
	void SetState(int _value);
	void InitObject();
	bool IsObject() const { return false; }
	void Reinitialize(){InitObject();}
private:
	int state;
	float time_to_hit;
	int hit_points;
};

#endif // !defined(AFX_DESTROYABLEBLOCK_H__AF775B2A_D8E1_40CF_90D5_DB1A94AD664A__INCLUDED_)
