// EnemyJunkbotLarge1.h: interface for the EnemyJunkbotLarge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJUNKBOTLARGE1_H__B0105819_90C9_4959_89BD_EBEE85A68A16__INCLUDED_)
#define AFX_ENEMYJUNKBOTLARGE1_H__B0105819_90C9_4959_89BD_EBEE85A68A16__INCLUDED_

#
#include "Enemy.h"

class EnemyJunkbotLarge : public Enemy  
{
public:
	EnemyJunkbotLarge(Level *curLevel, bool sDirection);
	virtual ~EnemyJunkbotLarge();

	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();

private:
	float timer;
};

#endif // !defined(AFX_ENEMYJUNKBOTLARGE1_H__B0105819_90C9_4959_89BD_EBEE85A68A16__INCLUDED_)
