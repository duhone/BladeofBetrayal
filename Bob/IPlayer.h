// IPlayer.h: interface for the IPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPLAYER_H__DAE88735_BAEA_464A_AF45_9F8B881909FD__INCLUDED_)
#define AFX_IPLAYER_H__DAE88735_BAEA_464A_AF45_9F8B881909FD__INCLUDED_


#include "IPlayerConfig.h"
//#include "Level.h"

#include "AIOutput.h"
#include "AIInput.h"
#include "AILevel.h"
#include "../Engines/Graphics/HPTGraphics.h"
//#include "CRSoundPlayer.h"
#include "Ailevel.h"
#include "Weapon.h"
#include "GProjectiles.h"
#include "MessageBroadcaster.h"
#include "PointValues.h"
#include <vector>
#include <list>
#include "Sound.h"

using namespace std;
extern HPTSprite1* pixel_spr ;
extern HPTSprite1* pixel_red_spr ;
extern HPTSprite1* pixel_yellow_spr ;
extern HPTSprite1* pixel_black_spr ;
extern HPTSprite1* pixel_green_spr ;
extern HPTSprite1* pixel_blue_spr ;

extern HPTGraphicsEngine *graphics_engine;
//extern CRSoundPlayer *soundPlayer;
extern int CollidableBlocks[];

class IPlayer : 
	public AIInput, 
	public AIOutput
{
public:
	int GetXSpawn(){ return x_spawn; }
	int GetYSpawn(){ return y_spawn; }
	virtual void doDoor(int type) {};
	virtual bool forceOpenDoor() { return false; };
	virtual void AddGrenades(int arg) {};
	virtual void AddWeapon(int arg) {};
	virtual void SetAnalogMods();
	 virtual bool GetBasicAttackUpgrade() { return false; };

	virtual void AddBasicAttackUpgrade();
	IPlayer();
	virtual ~IPlayer();

	 int GetSpecialItems() { return n_special_items; };
	 int GetTreasureItems() { return n_treasure_items; };
	 int GetBasicItems() { return n_basic_items; };
	virtual void AddSpecialItems();
	virtual void AddTreasureItem();
	virtual void AddBasicItem();
	void         ResetItems();
	void         SubtractLife();
	void         ReSpawn();
	virtual void SetSpawnPoint(int xarg,int yarg);
	virtual void SetSpawnPoint();

	// Render Functions
	void          SetRenderHealthBar(bool);

	// Player Physics
	// World Coordinates
	// Tile Coordinates
	void          SetWalkAcceleration(float);
	void          SetMaxWalkVelocity(float);
	void          SetMaxJumpVelocity(float);
	void          SetMaxClimbVelocity(float);
	void          SetPlayerRectangle(int dx, int dy);
	void          SetDamageTimer(float arg) {fDmgTimer = arg;};
	void          SetDirection(bool);
	void          velocityModify(int pixSec);
	void          setGravityConstant(float gravConst);
	 void GetVelocityVector(float *x, float *y)
	{
		*x = (xLoc - xLocPrev);
		*y = (yLoc - yLocPrev);

		if(*x > (static_cast<float>(rectWorldLoc.p2.x - rectWorldLoc.p1.x)))
			*x = static_cast<float>(rectWorldLoc.p2.x - rectWorldLoc.p1.x);
	};
	 void GetDisplacementVector(float *x, float *y)
	{
		*x = (xLocPrev - xLoc) * time;
		*y = (yLocPrev - xLoc) * time;
	};
	 bool GetDirection() { return ipFlags.S_DIRECTION; };

	void          NextToLadder(bool,int);
	void          StandingOnGround(bool);
	 void HeadCollision(bool val) { ipFlags.S_HEAD_COLLISION = val; };
	void          BelowFeetLadderCheck();

	// Health Level
	void         SetExtraLives(int arg) {nLives = arg;};
	virtual void AddLife(int nLife);
	 int GetCurLife() { return nCurLife; };
	 int GetNumLifeBars() { return nCurLifeBars; }
	virtual void SetCurLife(int nLife);
	virtual void SetNumLifeBars(int nBars);
	virtual void IncNumLifeBars() {	if(nCurLifeBars < MaxLifeBars) nCurLifeBars++;};
	virtual void AddExtraLife();
	 int GetNumLives() { return nLives; };
	
	// Energy Level	
	 int GetMaxEnergyLevel() { return MaxELevel; };
	 int GetEnergyLevel() { return CurELevel; }

	virtual void AddEnergy(int nEnergy);
	virtual bool UseEnergy(int nEnergy);
	virtual void SetEnergyLevel(int nELevel) {CurELevel = nELevel;};
	virtual void SetMaxEnergyLevel(int nMELevel) {MaxELevel = nMELevel;};
	virtual	void IncMaxEnergyLevel() {MaxELevel+=energy_upgrade_amt;};

	// Trigger Damage (Lower Health)
	virtual void doDamage(int num, bool sDirection,int damage_type,bool silent = false);
	virtual void doChemicalDamage(int num) {};
	virtual void doWaterDamage(int num) {};
	virtual void forceDeath();
	 void Die() {ipFlags.S_DEAD = true; ipFlags.S_ACTIVE = false; ipFlags.InputQueue.clear();};

	// Game Control Action Functions
	 void moveLeft()    {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_left);/* LeaveCriticalSection(&cs);*/  };
	 void moveRight()   {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_right); /*LeaveCriticalSection(&cs);*/ };
	 void moveUp()      {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_up);  /* LeaveCriticalSection(&cs); */ };
	 void moveDown()    {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_down); /* LeaveCriticalSection(&cs);*/ };
	 void moveStop()    {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_stop); /* LeaveCriticalSection(&cs);*/ };
	 void moveButton1() {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_button1);/*LeaveCriticalSection(&cs);*/};
	 void moveButton2() {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_button2);/*LeaveCriticalSection(&cs);*/};
	 void moveButton3() {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_button3);/*LeaveCriticalSection(&cs);*/};
	 void moveButton4() {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_button4);/*LeaveCriticalSection(&cs);*/};
	 void moveButton5() {/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(input_button5);/*LeaveCriticalSection(&cs);*/};
	virtual void FaceLeft(){/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(FACE_LEFT);/*LeaveCriticalSection(&cs);*/};
	virtual void FaceRight(){/*EnterCriticalSection(&cs)*/ ipFlags.InputQueue.push_back(FACE_RIGHT);/*LeaveCriticalSection(&cs);*/};
	
	bool GetDead();

	
	// State Input / Output
	virtual bool TransitionMovement(M_STATE);
	bool SetAnimation(int nFrameSet, int nStartFrame, bool bAutoAnim, bool bAutoStop, float nFrameRate, bool bReset)
	{
		if(!bReset)
		{
			if(player_spr->GetFrameSet() != nFrameSet)
			{
				player_spr->SetFrameSet(nFrameSet);
				player_spr->SetFrame(nStartFrame);
				player_spr->SetFrameRate(nFrameRate);
				player_spr->SetAutoAnimate(bAutoAnim);	

				if(bAutoStop)
					player_spr->AutoStopAnimate();

				return false;
			}
			else
			{
				player_spr->UpdateFrameRate(nFrameRate);
				if(!player_spr->IsAnimating())
				{
					player_spr->SetFrame(nStartFrame);
					player_spr->SetAutoAnimate(bAutoAnim);
			
					if(bAutoStop)
						player_spr->AutoStopAnimate();
				}

				return true;
			}
		}
		else
		{
				player_spr->SetFrameSet(nFrameSet);
				player_spr->SetFrame(nStartFrame);
				player_spr->SetFrameRate(nFrameRate);
				player_spr->SetAutoAnimate(bAutoAnim);

				if(bAutoStop)
					player_spr->AutoStopAnimate();

				return false;
		}
	};
	virtual void ResetIPlayer();
	virtual void ResetStates();

	// Attack / Weapon Control Functions
	virtual void SetSpencerVictory() {};
	virtual void ActivateBarrierShield() {};
	virtual void SetAttack(int nAttack);
	 int GetAttack()
	{
//		if(ipFlags.nCurrAttack < 0)
//			ipFlags.nCurrAttack = 0;
		return ipFlags.nCurrAttack;
	}
	void         CycleAttack();
	void         SetMaxAttacks(int nMaxAttacks) {this->nMaxAttacks = nMaxAttacks; if(this->nMaxAttacks >= 12) this->nMaxAttacks = 12; else if(this->nMaxAttacks < 1) this->nMaxAttacks = 1;};
	 int GetMaxAttacks() { return nMaxAttacks; };
	 int GetWeaponDamage() { return nWeaponDamage; };
	void         SetWeaponDamage(int arg0) {nWeaponDamage = arg0;};
	void         SetProjectileList(std::list<Projectile *> *projectile_list);
	std::list<Projectile *> *GetProjectileList() { return projectile_list; };
//	HPTVector<Projectile *> *GetProjectileList() { return projectile_list; };

	// World Coordinate Function Handlers -- Pixels
	 int GetTileHeight()
	{
		HPTRect &temp = GetWorldLoc();
		int tempi,tempi2,tempfrac;
		tempi = temp.p2.y<<4;
		tempi2 = temp.p1.y<<4;
		int tHeight = abs(tempi2-tempi);
		tempfrac = ((tHeight>>4) & 0x04);
		tHeight = tHeight>>8;
		if(tempfrac >0) tHeight++;
		return tHeight;
	};
	virtual HPTRect& GetWeaponWorldLoc() { SetRectangle(rectWeaponWorldLoc,0,0,0,0); return rectWeaponWorldLoc; };
	void				 SetWorldLoc(int dx,int dy);
	void				 SetWorldLocAbsolute(int x, int y);
	void				 SetWorldLocAbsoluteT(int x, int y, int dx = 0, int dy = 0);
	void			     AddTransformationQueue(float dx, float dy);
	int					 GetXTransformQueue();
	int					 GetYTransformQueue();
	void				 ResetTransformQueue();
	void	 SetRectangle(HPTRect &r1, unsigned int dx, unsigned int dy, int xoffset = 0, int yoffset = 0)
	{
		if(ipFlags.S_DIRECTION)
		{
			r1.p1.x = static_cast<int>(xLoc) + 0 + xoffset + xTransformOffset;
			r1.p2.x = static_cast<int>(xLoc) + dx + xoffset + xTransformOffset;
			r1.p1.y = static_cast<int>(yLoc) + 0 + yoffset + yTransformOffset;
			r1.p2.y = static_cast<int>(yLoc) + dy + yoffset + yTransformOffset;
		}
		else
		{
			r1.p1.x = static_cast<int>(xLoc) - dx - xoffset + xTransformOffset;
			r1.p2.x = static_cast<int>(xLoc) - 0 - xoffset + xTransformOffset;
			r1.p1.y = static_cast<int>(yLoc) + 0 + yoffset + yTransformOffset;
			r1.p2.y = static_cast<int>(yLoc) + dy + yoffset + yTransformOffset;	
		}
	}

	// Time Interval Passed Since Last Frame
	virtual void setTime(float time);

	// Update Player State -- Call Once Per Frame
	virtual void ProcessPreCalculations();
	virtual void ProcessPostCalculations();
	virtual void processUpdate() = 0;
	void         Update();

	//Graphics Engine Functions
	void         SetRenderOffset(int argx, int argy = 0);
	virtual void SetSprite(int nSet, int nSprite);
	virtual void Render() = 0;
	virtual void RenderHealthBar() = 0;

	float xLocPrev;
	float yLocPrev;

	float flashtimer;

	// Player State Engine Virtual Transitions - To be defined for each monster
	virtual void setJumpVelocity() {};
	virtual void processRight()    {};
	virtual void processLeft()     {};
	virtual void processUp()       {};
	virtual void processDown()     {};
	virtual void processAttack()   {};
	virtual void processAttack2()   {};
	virtual void processDamage()   {};
	virtual void processDeath()    {};
	virtual void processSpecial1() {};
	virtual void processSpecial2() {};
	virtual void stop()            {};

	// Internal State Functions
	 void StopMovement() {velMovement = 0; velModifier = 0;}
	void ApplyGravity();

	// Bounding World Coordinates
	HPTRect rectWeaponWorldLoc;

	//Rendering Offset
	int nOffSet;
	int nyOffSet;

	/* Constant Variables */
	int LifePerBar;// = 20;
	int MaxLifeBars;// = 5;
	int MaxLife;// = MaxLifeBars * LifePerBar;

	// Acceleration Constants -- Used for calculation during update
	float velModifier;
	float velMovement;
	float velYModifier;
	float velYJumpModifier;
	float velGravityModifier;
	float velWaterJumpModifier;
	float velWaterModifier;
	float gravityConstant;	
	float walkAcceleration;
	float maxWalkSpeed;
	float jumpAcceleration;
	float climbVelocity;
	float jumpMaxVelocity;
	float MaxYVelocity;
	float MaxPixelDisplacement;// = 14.0; // Pixels Per Frame
	float yDisplacement;
	float xDisplacement;

	int rectDX;
	int rectDY;
	int rectXOffset;
	int rectYOffset;

	float time;
	float fDmgTimer;
	
	int CurELevel;
	int MaxELevel;

	// Current Life Amount
	int nCurLife;
	int nCurLifeBars;
	
	// Score
	//int nScore;
	//int nPointValue;

	// Number of Lives
	int nLives;

	// Weapons
	int nMaxAttacks;
	int nWeaponDamage;

	std::list<Projectile *> *projectile_list;
	//HPTVector<Projectile *> *projectile_list;

	//Player Dimensions
	int nPlayerWidth;
	int nPlayerHeight;
	int nHalfPlayerWidth;
	int nHalfPlayerHeight;
	int xTransformOffset;
	int yTransformOffset;

	float x_transform_queue;
	float y_transform_queue;
	int n_special_items;
	int n_treasure_items;
	int n_basic_items;
	int y_spawn;
	int x_spawn;
	bool stunned;
	float stunned_time;
	//CRITICAL_SECTION cs;
protected:
	float freeze_for_intro_time;
	bool freeze_for_intro;
	float analog_mod_y;
	float analog_mod_x;
	vector<HPTSprite1*> hold_sprites;
	bool take_all_damage;
	int damage_resistance[12];
	bool m_attackWhenDamaged;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFXDamage;
};

#endif // !defined(AFX_IPLAYER_H__DAE88735_BAEA_464A_AF45_9F8B881909FD__INCLUDED_)
