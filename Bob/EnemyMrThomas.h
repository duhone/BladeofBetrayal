// EnemyMrThomas.h: interface for the EnemyMrThomas class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYMRTHOMAS_H__A4F62502_224C_485F_BCBA_3D835FFF7567__INCLUDED_)
#define AFX_ENEMYMRTHOMAS_H__A4F62502_224C_485F_BCBA_3D835FFF7567__INCLUDED_


#include "Enemy.h"
#include "MeterBar.h"
#include <vector>

class EnemyMrThomas : public Enemy  
{		
	enum SPRITES
	{
		BLADE_CATCH = 0,
		BLADE_THROW,
		CHARGE_IN,
		CHARGE_LOOP,
		DEATH,
		TIDLE,
		INTRO,
		WALK,
		NUM_SPRITES
	};
public:
	EnemyMrThomas(Level *curLevel);
	virtual ~EnemyMrThomas();

	virtual void processDamage();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processSpecial1();
//	virtual void processSpecial2();
	virtual void processDeath();
//	virtual void processDamage();
	virtual void stop();
	virtual void processUpdate();

	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	
	virtual void SetEnds(int _left,int _right) {m_leftBound=_left; m_rightBound=_right;}
	void RenderHealthBar();
private:
	float deathtimer;
	std::vector<HPTSprite1*> m_sprites;
	bool m_threw;
	bool m_threw2;
	float m_waitTime;
	static const float c_totalWaitTime;
	int m_leftBound,m_rightBound;
	MeterBar *healthBar;
	HPTSprite1 *bossIcon;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFXPhase;
};

#endif // !defined(AFX_ENEMYMRTHOMAS_H__A4F62502_224C_485F_BCBA_3D835FFF7567__INCLUDED_)
