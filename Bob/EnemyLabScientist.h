// EnemyLabScientist.h: interface for the EnemyLabScientist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYLABSCIENTIST_H__4D31B1A3_A664_475E_88F0_B03AD96CB43C__INCLUDED_)
#define AFX_ENEMYLABSCIENTIST_H__4D31B1A3_A664_475E_88F0_B03AD96CB43C__INCLUDED_


#include "Enemy.h"

class EnemyLabScientist : public Enemy  
{
public:
	EnemyLabScientist(Level *curLevel, bool S_ON_FIRE = false);
	virtual ~EnemyLabScientist();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();
	virtual void stop();
	HPTRect &GetWeaponWorldLoc();
	//virtual HPTRect &GetWorldLoc();

	void processUpdate();

private:
	bool S_ON_FIRE;

	float flametimer;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_firedeathSound;
};

#endif // !defined(AFX_ENEMYLABSCIENTIST_H__4D31B1A3_A664_475E_88F0_B03AD96CB43C__INCLUDED_)
