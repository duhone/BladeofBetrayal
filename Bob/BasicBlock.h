// BasicBlock.h: interface for the BasicBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASICBLOCK_H__4DB8F9E7_6343_4CBC_9B57_56B2486DF7A0__INCLUDED_)
#define AFX_BASICBLOCK_H__4DB8F9E7_6343_4CBC_9B57_56B2486DF7A0__INCLUDED_


#include "Object.h"

class BasicBlock : public Object  
{
public:
	virtual bool ProjectileCollideCheck(IPlayer *arg0, Projectile* arg);
	void SetTopCollide(bool arg);
	void SetSideCollide(bool arg);
	BasicBlock();
	virtual ~BasicBlock();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype);
	virtual bool OnGround(int y);

	bool IsObject() const { return false; }
private:
	bool side_collide;
	bool top_collide;
};

#endif // !defined(AFX_BASICBLOCK_H__4DB8F9E7_6343_4CBC_9B57_56B2486DF7A0__INCLUDED_)
