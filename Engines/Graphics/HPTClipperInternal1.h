#ifndef HPT_CLIPPER_INTERNAL_H
#define HPT_CLIPPER_INTERNAL_H

#include "HPTGraphics.h"

class HPTClipperInternal1 : public HPTClipper1  
{
public:
	HPTClipperInternal1();
	virtual ~HPTClipperInternal1();
	virtual void SetClipper(int ulx,int uly,int lrx,int lry);
	virtual void Release();

	int upper_leftx;
	int upper_lefty;
	int lower_rightx;
	int lower_righty;
};

#endif