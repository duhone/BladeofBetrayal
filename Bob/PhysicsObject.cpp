// PhysicsObject.cpp: implementation of the PhysicsObject class.
//
//////////////////////////////////////////////////////////////////////


#include "PhysicsObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PhysicsObject::PhysicsObject()
{
	dTime = 0;
	valGravity = 0;

	xAcc = 0;
	yAcc = 0;
	xVel = 0;
	yVel = 0;
	xLoc = 0;
	yLoc = 0;

	xAccPrev = 0;
	yAccPrev = 0;
	xVelPrev = 0;
	yVelPrev = 0;
	xLocPrev = 0;
	yLocPrev = 0;
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::GetAcceleration(float *x, float *y)
{
	xAccPrev = xAcc;
	yAccPrev = yAcc;

	*x = xAcc;
	*y = yAcc;
}

void PhysicsObject::GetLocation(float *x, float *y)
{
	xLocPrev = xLoc;
	yLocPrev = yLoc;

	*x = xLoc;
	*y = yLoc;
}

void PhysicsObject::GetVelocity(float *x, float *y)
{
	xVelPrev = xVel;
	yVelPrev = yVel;

	*x = xVel;
	*y = yVel;
}

void PhysicsObject::GetVelocityVector(float *dVect)
{
}

void PhysicsObject::SetAcceleration(float x, float y)
{
	xAccPrev = xAcc;
	yAccPrev = yAcc;

	xAcc = x;
	yAcc = y;
}

void PhysicsObject::SetXAcceleration(float x)
{
	xAccPrev = xAcc;

	xAcc = x;
}

void PhysicsObject::SetYAcceleration(float y)
{
	yAccPrev = yAcc;

	yAcc = y;
}

void PhysicsObject::SetGravity(float Gravity)
{
	valGravity = Gravity;
}

void PhysicsObject::SetLocation(float x, float y)
{
	xLocPrev = xLoc;
	yLocPrev = yLoc;

	xLoc = x;
	yLoc = y;
}

void PhysicsObject::SetXLocation(float x)
{
	xLocPrev = xLoc;

	xLoc = x;
}

void PhysicsObject::SetYLocation(float y)
{
	yLocPrev = yLoc;

	yLoc = y;
}

void PhysicsObject::SetTime(float dVal)
{
	dTime = dVal;
}

void PhysicsObject::SetVelocity(float x, float y)
{
	xVelPrev = xVel;
	yVelPrev = yVel;

	xVel = x;
	yVel = y;
}

void PhysicsObject::SetXVelocity(float x)
{
	xVelPrev = xVel;

	xVel = x;
}

void PhysicsObject::SetYVelocity(float y)
{
	yVelPrev = yVel;

	yVel = y;
}
