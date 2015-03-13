// AIInput.cpp: implementation of the AIInput class.
//
//////////////////////////////////////////////////////////////////////


#include "AIInput.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIInput::AIInput():
lower_patrol_x(0),
lower_patrol_y(0),
upper_patrol_x(0),
upper_patrol_y(0)
{
	rectWorldLoc.p1.x = 0;
	rectWorldLoc.p1.y = 0;
	rectWorldLoc.p2.x = 0;
	rectWorldLoc.p2.y = 0;
}

AIInput::~AIInput()
{

}
