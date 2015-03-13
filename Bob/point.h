#ifndef HPTPOINT_H
#define HPTPOINT_H

class HPTPoint
{
public:
	int x;
	int y;
	
	HPTPoint()
	{
		x = 0;
		y = 0;
	}
	
	HPTPoint(const HPTPoint &arg)
	{
		x = arg.x;
		y = arg.y;
		
	}
	HPTPoint& operator=(HPTPoint &arg)
	{
		x = arg.x;
		y = arg.y;
		return *this;
	}
	bool operator!=(HPTPoint &arg)
	{
		return true;
	}
	void Set(int _x,int _y) {x = _x; y = _y;}
};

class HPTRect
{
public:
	HPTPoint p1;
	HPTPoint p2;

	HPTRect()
	{
		p1.x = 0;
		p1.y = 0;
		p2.x = 0;
		p2.y = 0;
	}
	
	HPTRect(const HPTRect &rect)
	{
		p1.x = rect.p1.x;
		p1.y = rect.p1.y;
		p2.x = rect.p2.x;
		p2.y = rect.p2.y;
	}
};

#endif
