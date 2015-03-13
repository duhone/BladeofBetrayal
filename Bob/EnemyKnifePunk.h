// EnemyKnifePunk.h: interface for the EnemyKnifePunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYKNIFEPUNK_H__03589D79_2688_4BD2_BEFA_392052BDC878__INCLUDED_)
#define AFX_ENEMYKNIFEPUNK_H__03589D79_2688_4BD2_BEFA_392052BDC878__INCLUDED_


#include "Enemy.h"

class EnemyKnifePunk : public Enemy  
{
public:
	EnemyKnifePunk(Level *curLevel);
	virtual ~EnemyKnifePunk();

	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();

};

#endif // !defined(AFX_ENEMYKNIFEPUNK_H__03589D79_2688_4BD2_BEFA_392052BDC878__INCLUDED_)
