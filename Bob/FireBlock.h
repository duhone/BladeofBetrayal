// FireBlock.h: interface for the FireBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREBLOCK_H__25768375_25BF_4392_BA87_76BD9229ADDC__INCLUDED_)
#define AFX_FIREBLOCK_H__25768375_25BF_4392_BA87_76BD9229ADDC__INCLUDED_


#include "Object.h"

class FireBlock : public Object  
{
public:
	FireBlock(int arg);
	virtual ~FireBlock();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype);
	virtual void Update();

	bool IsObject() const { return false; }
private:
	float time_to_damage;
	int type;
};

#endif // !defined(AFX_FIREBLOCK_H__25768375_25BF_4392_BA87_76BD9229ADDC__INCLUDED_)
