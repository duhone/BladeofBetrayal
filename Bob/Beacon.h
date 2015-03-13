#pragma once

#include "Object.h"

class Beacon : public Object  
{
public:
	Beacon();
	virtual ~Beacon();
	virtual void Update();
	virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprectt,int& ltype);
	int GetState() const {return state;}
	void SetState(int _value);
	
	void InitObject(int type);
	void Reinitialize(){InitObject(0);}
private:
	int state;	
};

