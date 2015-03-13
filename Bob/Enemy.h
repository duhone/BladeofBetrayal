// Enemy.h: interface for the Enemy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMY_H__376A89AC_A460_4846_A39F_1A9F45388A08__INCLUDED_)
#define AFX_ENEMY_H__376A89AC_A460_4846_A39F_1A9F45388A08__INCLUDED_


#include "IPlayer.h"
#include "EnemyConfig.h"
#include "Level.h"
#include "point.h"
//#include "CRSoundPlayer.h"
#include "MeterBar.h"
#include "Sound.h"

//extern CRSoundPlayer *soundPlayer;

class Enemy : public IPlayer  
{
public:
	Enemy();
	virtual ~Enemy();

	void setViewTransform(float x, float y);
	virtual void Render();
	virtual void RenderHealthBar();
	void BelowFeetLadderCheck();
	void InitEnemy(int nHitPoints, int nMaxXVelocity, int nMaxYVelocity, float nMaxXAcceleration, float nRecoveryTime, int nPointValue, bool bRenderHBar);
	virtual bool IsEnemy() const { return true; }
	int m_rangeExtra;
protected:
	Level *level_class;
	float introtimer;
	
	float xViewLoc;
	float yViewLoc;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFX;
};

#endif // !defined(AFX_ENEMY_H__376A89AC_A460_4846_A39F_1A9F45388A08__INCLUDED_)
