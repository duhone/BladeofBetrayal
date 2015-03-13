// EnemyPrisonerRock.h: interface for the EnemyPrisonerRock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYPRISONERROCK_H__52BFD440_2956_4BBD_A4F0_019A23E26656__INCLUDED_)
#define AFX_ENEMYPRISONERROCK_H__52BFD440_2956_4BBD_A4F0_019A23E26656__INCLUDED_


#include "Enemy.h"

class EnemyPrisonerRock : public Enemy  
{
public:
	EnemyPrisonerRock(Level *curLevel);
	virtual ~EnemyPrisonerRock();

	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
};

#endif // !defined(AFX_ENEMYPRISONERROCK_H__52BFD440_2956_4BBD_A4F0_019A23E26656__INCLUDED_)
