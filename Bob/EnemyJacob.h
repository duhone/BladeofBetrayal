// EnemyJacob.h: interface for the EnemyJacob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJACOB_H__A74769D3_D9A3_4B3B_A4B7_746C327549B0__INCLUDED_)
#define AFX_ENEMYJACOB_H__A74769D3_D9A3_4B3B_A4B7_746C327549B0__INCLUDED_


#include "Enemy.h"
#include "Player.h"

struct Rain
{
	std::vector<HPTSprite1*> m_sprites;
	int m_currentSprite;
	float m_delay;
	float m_x;
	float m_y;
};

class EnemyJacob : public Enemy  
{
	enum SPRITES
	{		
		IDLE = 0,
		INTRO,
		FLAME,
		GRAB,
		GROUND,
		GROUND_IDLE,
		JUMP,
		WALK,
		QUAKE,
		STANDARD,
		STOMP,
		NUM_SPRITES
	};
public:
	EnemyJacob(Level *curLevel, Player *player);
	virtual ~EnemyJacob();
	virtual void doDamage(int num, bool sDirection,int damage_type);
	//virtual bool TransitionMovement(M_STATE);

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void processDown();
	virtual void processUp();
	virtual void stop();
	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();

	//virtual void setTime(float time);
	float resetDelay;

	void StartJacob();
	virtual void SuperJump(int _xtile,float _jumpTime,float _exponent,float _height);
	virtual bool FinishedSuperJump() {return !m_superJumping;}
	void RenderHealthBar();
	
	bool S_START;
	Player *player;
	float shake;
	
	virtual void Render();

private:	
	std::vector<HPTSprite1*> m_sprites;
	HPTPoint m_jumpTarget;
	HPTPoint m_jumpStart;
	bool m_superJumping;
	float m_jumpTime;
	float m_totalJumpTime;
	float m_jumpXP;
	float m_jumpHeight;
	float m_quakeTime;
	bool m_quakeStart;
	bool m_stoneLeft;
	float m_stoneDropTime;
	bool m_drop;
	int m_groundWaves;
	MeterBar *healthBar;
	HPTSprite1 *bossIcon;
	std::vector<Rain> m_rain;
	HPTSprite1 *m_thunder;
	float m_thunderDelay;
	bool m_thundering;

	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_swingSound;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_shockSound;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_flameSound;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_waveSound;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_quakeSound;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_explodeSound;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_jumpSound;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_thunderSound;
	
};

#endif // !defined(AFX_ENEMYJACOB_H__A74769D3_D9A3_4B3B_A4B7_746C327549B0__INCLUDED_)
