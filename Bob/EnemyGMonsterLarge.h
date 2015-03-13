// EnemyGMonsterLarge.h: interface for the EnemyGMonsterLarge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGMONSTERLARGE_H__FD49F8E0_D138_4225_B2C8_1A9ECE18EC79__INCLUDED_)
#define AFX_ENEMYGMONSTERLARGE_H__FD49F8E0_D138_4225_B2C8_1A9ECE18EC79__INCLUDED_


#include "Enemy.h"

class EnemyGMonsterLarge : public Enemy  
{
public:
	EnemyGMonsterLarge(Level *curLevel);
	virtual ~EnemyGMonsterLarge();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();
	virtual void stop();

	void processUpdate();
private:
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_firedeathSound;
};

#endif // !defined(AFX_ENEMYGMONSTERLARGE_H__FD49F8E0_D138_4225_B2C8_1A9ECE18EC79__INCLUDED_)
