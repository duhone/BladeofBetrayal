// AIOutput.h: interface for the AIOutput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIOUTPUT_H__257D9A6C_3FA2_4C23_9A84_40F481F7D3FB__INCLUDED_)
#define AFX_AIOUTPUT_H__257D9A6C_3FA2_4C23_9A84_40F481F7D3FB__INCLUDED_


class AIOutput  
{
public:
	AIOutput();
	virtual ~AIOutput();

	virtual void moveLeft()=0;
	virtual void moveRight()=0;
	virtual void moveUp()=0;
	virtual void moveDown()=0;
	virtual void moveStop()=0;
	virtual void moveButton1()=0;
	virtual void moveButton2()=0;
	virtual void moveButton3()=0;
	virtual void moveButton4()=0;
	virtual void FaceLeft()=0;
	virtual void FaceRight()=0;

	virtual void SetDirection(bool)=0;
	virtual void SetAttack(int nAttack)=0;
	virtual void SuperJump(int _xtile,float _time,float _exponent,float _height) {}
	virtual void SetEnds(int _left,int _right) {}
};

#endif // !defined(AFX_AIOUTPUT_H__257D9A6C_3FA2_4C23_9A84_40F481F7D3FB__INCLUDED_)
