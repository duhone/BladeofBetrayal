// BounceBlock.h: interface for the BounceBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOUNCEBLOCK_H__28395D41_A266_4F77_A1E2_2611A83D17E4__INCLUDED_)
#define AFX_BOUNCEBLOCK_H__28395D41_A266_4F77_A1E2_2611A83D17E4__INCLUDED_


#include "Object.h"

class BounceBlock : public Object  
{
public:
	BounceBlock();
	virtual ~BounceBlock();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype);

	bool IsObject() const { return false; }
};

#endif // !defined(AFX_BOUNCEBLOCK_H__28395D41_A266_4F77_A1E2_2611A83D17E4__INCLUDED_)
