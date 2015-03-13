#include "HPTClipperInternal1.h"

HPTClipperInternal1::HPTClipperInternal1()
{
		upper_leftx = 0;
	upper_lefty = 0;
	lower_rightx = 0;
	lower_righty = 0;

}

HPTClipperInternal1::~HPTClipperInternal1()
{

}

void HPTClipperInternal1::SetClipper(int ulx,int uly,int lrx,int lry)
{
		upper_leftx = ulx;
	upper_lefty = uly;
	lower_rightx = lrx;
	lower_righty = lry;

}

void HPTClipperInternal1::Release()
{
	delete this;
}
