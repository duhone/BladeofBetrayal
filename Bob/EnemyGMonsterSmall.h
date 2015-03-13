// EnemyGMonsterSmall.h: interface for the EnemyGMonsterSmall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGMONSTERSMALL_H__7BEAEADA_F5D6_4E90_B319_B09689C8998A__INCLUDED_)
#define AFX_ENEMYGMONSTERSMALL_H__7BEAEADA_F5D6_4E90_B319_B09689C8998A__INCLUDED_


#include "Enemy.h"

/* Three types of small monster
1) Arc Jumping
2) Up and Down Jumping
3) Attack Jump
*/
class EnemyGMonsterSmall : public Enemy  
{
public:
	EnemyGMonsterSmall(Level *curLevel);
	virtual ~EnemyGMonsterSmall();

	virtual void setJumpVelocity();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
	void processUpdate();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
private:
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_monsterSound;
};

#endif // !defined(AFX_ENEMYGMONSTERSMALL_H__7BEAEADA_F5D6_4E90_B319_B09689C8998A__INCLUDED_)
