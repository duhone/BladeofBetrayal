// onveyorBlock.h: interface for the ConveyorBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONVEYORBLOCK_H__EC6907CA_0B3A_4D65_A9CA_861AD04128B9__INCLUDED_)
#define AFX_ONVEYORBLOCK_H__EC6907CA_0B3A_4D65_A9CA_861AD04128B9__INCLUDED_


#include "Object.h"
#define LEFT 0
#define RIGHT 1


class ConveyorBlock : public Object  
{
public:
	void SetDirection(int arg);
	ConveyorBlock();
	virtual ~ConveyorBlock();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype);
	virtual bool ProjectileCollideCheck(Projectile* arg);

	bool IsObject() const { return false; }
private:
	int direction;
};

#endif // !defined(AFX_ONVEYORBLOCK_H__EC6907CA_0B3A_4D65_A9CA_861AD04128B9__INCLUDED_)
