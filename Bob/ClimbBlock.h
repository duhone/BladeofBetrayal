// ClimbBlock.h: interface for the ClimbBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIMBBLOCK_H__9EE77185_2477_4298_A793_C73C2BFAA3C5__INCLUDED_)
#define AFX_CLIMBBLOCK_H__9EE77185_2477_4298_A793_C73C2BFAA3C5__INCLUDED_


#include "Object.h"

class ClimbBlock : public Object  
{
public:
	ClimbBlock();
	virtual ~ClimbBlock();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype);
	void SetBlockType(int arg);
	bool IsObject() const { return false; }
private:
	int block_type;
};

#endif // !defined(AFX_CLIMBBLOCK_H__9EE77185_2477_4298_A793_C73C2BFAA3C5__INCLUDED_)
