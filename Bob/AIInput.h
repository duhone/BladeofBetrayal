// AIInput.h: interface for the AIInput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIINPUT_H__3C6E5CA3_400B_4B64_AE32_530E8561AFE3__INCLUDED_)
#define AFX_AIINPUT_H__3C6E5CA3_400B_4B64_AE32_530E8561AFE3__INCLUDED_


#include "IPlayerConfig.h"
#include "PhysicsObject.h"

class AIInput
{
public:
	AIInput();
	virtual ~AIInput();
	
	 int         GetXTilePos() { xTilePos = static_cast<int>(xLoc) >> 4; return xTilePos; };
	 int         GetYTilePos() { yTilePos = static_cast<int>(yLoc + (static_cast<int>(player_spr->GetFrameHeight())>>1))>>4;return yTilePos; };
	 float       GetXLoc() { return xLoc; };
	 float       GetYLoc() { return yLoc; };
//	virtual float GetXLoc() = 0;
//	virtual float GetYLoc() = 0;
//	virtual int GetXTilePos() = 0;
//	virtual int GetYTilePos() = 0;
	virtual void GetVelocityVector(float *x, float *y) = 0;
	virtual void GetDisplacementVector(float *x, float *y) = 0;
	virtual bool GetDirection() = 0;

	virtual int GetCurLife() = 0;
	virtual int GetTileHeight()=0;
	virtual bool FinishedSuperJump() {return false;}
	
	IPlayerFlags *GetStateFlags() { return &ipFlags; };
	HPTRect& GetWorldLoc() { return rectWorldLoc; };
//	virtual HPTRect& GetWorldLoc()=0;

	int lower_patrol_x;
	int upper_patrol_x;
	int lower_patrol_y;
	int upper_patrol_y;
	HPTSprite1* player_spr;

	float xLoc;
	float yLoc;
	int xTilePos;
	int yTilePos;

	IPlayerFlags ipFlags;
	HPTRect rectWorldLoc;
};

#endif // !defined(AFX_AIINPUT_H__3C6E5CA3_400B_4B64_AE32_530E8561AFE3__INCLUDED_)
