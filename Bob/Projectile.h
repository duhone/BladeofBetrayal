// Projectile.h: interface for the Projectile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTILE_H__8DD46F2A_CFB3_4F57_93FD_3A6A06CA027A__INCLUDED_)
#define AFX_PROJECTILE_H__8DD46F2A_CFB3_4F57_93FD_3A6A06CA027A__INCLUDED_


#include "Weapon.h"
#include "../Engines/Graphics/HPTGraphics.h"
#include "point.h"
#include "projectileconfig.h"
//#include "CRSoundPlayer.h"
#include "AssetList.h"
#include "AssetListNew.h"
#include "Sound.h"

//extern CRSoundPlayer *soundPlayer;
extern HPTGraphicsEngine *graphics_engine;
extern int difficulty_level;

struct ProjectileParams
{
	//Physics
	float xLoc;
	float yLoc;
	float xVel;
	float yVel;
	float xAcc;
	float yAcc;
	float MaxXVel;
	float MaxYVel;
	
	float xLocTarget;
	float yLocTarget;

	//Timers
	float timeDelay;
	float timeActive;

	ProjectileParams()
	{
		xLoc = 0;
		yLoc = 0;
		xVel = 0;
		yVel = 0;
		xAcc = 0;
		yAcc = 0;
		MaxXVel = 200;
		MaxYVel = 200;
		
		xLocTarget = 0;
		yLocTarget = 0;
		
		timeDelay = 0;
		timeActive = 0;
	};

	~ProjectileParams()
	{
	};
};

struct ProjectileFlags
{
	bool S_VISIBLE;
	bool S_ACTIVE;
	bool S_ON_GROUND;
	bool S_DIRECTION;
	bool S_TARGETED;
	bool S_SOURCE;
	bool S_NON_PROJECTILE;

	ProjectileFlags()
	{
		S_ACTIVE = true;
		S_VISIBLE = true;
		S_ON_GROUND = false;
		S_DIRECTION = true;
		S_TARGETED = false;
		S_SOURCE = false; //source is enemy (eminates from enemy)
		S_NON_PROJECTILE = false;
	};

	~ProjectileFlags()
	{
	
	}
};

class Projectile : public Weapon
{
public:
	Projectile();
	virtual ~Projectile();

	//Set Physics
	virtual HPTRect &GetWeaponBounds();

	void SetTime(float time);
	void SetDelayTime(float timeDelay);
	void SetActiveTime(float timeActive);
	void setViewTransform(float x, float y);
	
	 void SetRectangle(HPTRect &r1, unsigned int dx, unsigned int dy, int xoffset = 0, int yoffset = 0)
	{
		if(proj_flags.S_DIRECTION)
		{
			r1.p1.x = static_cast<int>(proj_params.xLoc) + 0 + xoffset;
			r1.p2.x = static_cast<int>(proj_params.xLoc) + dx + xoffset;
			r1.p1.y = static_cast<int>(proj_params.yLoc) + 0 + yoffset;
			r1.p2.y = static_cast<int>(proj_params.yLoc) + dy + yoffset;
		}
		else
		{
			//r1.p1.x = static_cast<int>(proj_params.xLoc) + 0 + xoffset;
			//r1.p2.x = static_cast<int>(proj_params.xLoc) + dx + xoffset;
			//r1.p1.y = static_cast<int>(proj_params.yLoc) + 0 + yoffset;
			//r1.p2.y = static_cast<int>(proj_params.yLoc) + dy + yoffset;

			r1.p1.x = static_cast<int>(proj_params.xLoc) - dx - xoffset;
			r1.p2.x = static_cast<int>(proj_params.xLoc) - 0 - xoffset;
			r1.p1.y = static_cast<int>(proj_params.yLoc) + 0 + yoffset;
			r1.p2.y = static_cast<int>(proj_params.yLoc) + dy + yoffset;
		}
	};

	void SetDirection(bool);
	bool GetDirection();
	bool IsActive();

	virtual void Update();
	virtual void Render();

	bool GetSource();
	void SetSource(bool bSource);

	ProjectileFlags &GetProjectileFlags();

	virtual void DeActivate();
	void OnGround();

	int GetXLoc() {return static_cast<int>(proj_params.xLoc);}
	int GetYLoc() {return static_cast<int>(proj_params.yLoc);}
	void SetPosition(int x, int y);
	void SetVelocityVector(float dx, float dy);
	void SetAccelerationVector(float dx, float dy);

	virtual void SetWeaponDamage(int  nDamage);

	ProjectileParams proj_params;
	ProjectileFlags  proj_flags;

	int GetType() {return weapon_type;};
protected:

	int weapon_type;

	HPTSprite1* pixel_spr;
	HPTSprite1* pixel_red_spr;
	HPTSprite1* pixel_yellow_spr;
	HPTSprite1* pixel_black_spr;
	HPTSprite1* pixel_green_spr;

	bool SetAnimation(int nFrameSet, int nStartFrame, bool bAutoAnim, bool bAutoStop, float nFrameRate, bool bReset)
	{
		if(!bReset)
		{
			if(projectile_spr->GetFrameSet() != nFrameSet)
			{
				projectile_spr->SetFrameSet(nFrameSet);
				projectile_spr->SetFrame(nStartFrame);
				projectile_spr->SetFrameRate(nFrameRate);
				projectile_spr->SetAutoAnimate(bAutoAnim);

				if(bAutoStop)
					projectile_spr->AutoStopAnimate();

				return false;
			}
			else
			{
				if(!projectile_spr->IsAnimating())
				{
					projectile_spr->SetAutoAnimate(bAutoAnim);
				
					if(bAutoStop)
						projectile_spr->AutoStopAnimate();
				}

				return true;
			}
		}
		else
		{
				projectile_spr->SetFrameSet(nFrameSet);
				projectile_spr->SetFrame(nStartFrame);
				projectile_spr->SetFrameRate(nFrameRate);
				projectile_spr->SetAutoAnimate(bAutoAnim);

				if(bAutoStop)
					projectile_spr->AutoStopAnimate();

				return false;
		}
	};

	void SetSpriteOffset(int nOffset);
	void SetSprite(int nSet, int nSprite);
	void SetWeaponBounds(int dx, int dy);
	void processCalculations();

	HPTSprite1 *projectile_spr;
	int nOffset;

	HPTRect hptrectBounds;
	int dx_width;
	int dy_height;

	float xViewLoc;
	float yViewLoc;

	float time;

	float difficultyHitModifier;
	bool m_vflip;
	static const int c_gravityConstant = 500;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_sound;
};

#endif // !defined(AFX_PROJECTILE_H__8DD46F2A_CFB3_4F57_93FD_3A6A06CA027A__INCLUDED_)
