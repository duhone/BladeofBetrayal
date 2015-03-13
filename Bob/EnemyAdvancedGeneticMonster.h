// EnemyAdvancedGeneticMonster.h: interface for the EnemyAdvancedGeneticMonster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYADVANCEDGENETICMONSTER_H__B0C71498_D692_470F_8274_A95E0D3780A3__INCLUDED_)
#define AFX_ENEMYADVANCEDGENETICMONSTER_H__B0C71498_D692_470F_8274_A95E0D3780A3__INCLUDED_


#include "Enemy.h"
#include "point.h"

class EnemyAdvancedGeneticMonster : public Enemy  
{
	enum SPRITES
	{
		BACK_SPIKE = 0,
		DIE,
		IDLE,
		INTRO,
		JUMP,
		RUN,
		SPLASH,
		SPIT,
		TRANS_SPIT,
		NUM_SPRITES
	};
public:
	EnemyAdvancedGeneticMonster(Level *curLevel, IPlayer *player);
	virtual ~EnemyAdvancedGeneticMonster();

	virtual void processDamage();
	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDeath();
	virtual void setJumpVelocity();
	virtual void stop();
	virtual void processUpdate();
	virtual void SuperJump(int _xtile,float _jumpTime,float _exponent,float _height);
	virtual bool FinishedSuperJump() {return !m_superJumping;}
	
	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
	void RenderHealthBar();
private:
	static const float c_spikeDropTime;
	float deathtimer;
	std::vector<HPTSprite1*> m_sprites;
	HPTPoint m_jumpTarget;
	HPTPoint m_jumpStart;
	bool m_superJumping;
	float m_jumpTime;
	float m_totalJumpTime;
	float m_jumpXP;
	float m_jumpHeight;
	bool m_firedSpikes;	
	float m_spikeDropTime;
	int m_droppedSpikes;
	int m_dropOffset;
	IPlayer *m_player;
	int m_numSpits;
	MeterBar *healthBar;
	HPTSprite1 *bossIcon;
};

#endif // !defined(AFX_ENEMYADVANCEDGENETICMONSTER_H__B0C71498_D692_470F_8274_A95E0D3780A3__INCLUDED_)
