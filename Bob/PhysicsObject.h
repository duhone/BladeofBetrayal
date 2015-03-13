// PhysicsObject.h: interface for the PhysicsObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PHYSICSOBJECT_H__8663BE84_3CA3_436D_827B_BB3397EF498E__INCLUDED_)
#define AFX_PHYSICSOBJECT_H__8663BE84_3CA3_436D_827B_BB3397EF498E__INCLUDED_


class PhysicsObject  
{
public:
	PhysicsObject();
	virtual ~PhysicsObject();

	void SetTime(float dVal);

	void SetLocation(float x, float y);
	void SetXLocation(float x);
	void SetYLocation(float y);

	void SetVelocity(float x, float y);
	void SetXVelocity(float x);
	void SetYVelocity(float y);

	void SetAcceleration(float x, float y);
	void SetXAcceleration(float x);
	void SetYAcceleration(float y);

	void SetGravity(float Gravity);

	void GetLocation(float *x, float *y);
	void GetVelocity(float *x, float *y);
	void GetAcceleration(float *x, float *y);

	void GetVelocityVector(float *dVect);
	bool IsObject() const { return false; }

private:

	float valGravity;

	float xLoc;
	float yLoc;
	float xVel;
	float yVel;
	float xAcc;
	float yAcc;

	float xLocPrev;
	float yLocPrev;
	float xVelPrev;
	float yVelPrev;
	float xAccPrev;
	float yAccPrev;

	float dTime;
};

#endif // !defined(AFX_PHYSICSOBJECT_H__8663BE84_3CA3_436D_827B_BB3397EF498E__INCLUDED_)
