// BaseEnemy.h: interface for the BaseEnemy class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BASEENEMY_H
#define BASEENEMY_H



//#include <stdio.h>
#include "../aiinput.h"
#include "../aioutput.h"
#include "aiengine.h"
#include "../AILevel.h"
#include "../point.h"
//#include "Probes.h"
//#include "UpcommingObject.h"
//#include<math.h>
#include "../../Engines/Utility/Property.h"


#define AIS_NEW 10
#define AIS_CHASE   100
#define AIS_ATTACK  200
#define AIS_ATTACK_ATTACK 201
#define AIS_ATTACK_WAIT 202
#define AIS_ATTACK_ATTACKRUN 203
#define AIS_MOVE    300
#define AIS_PATROL  400
#define AIS_WAIT    500

#define AIS_MRT_SLASH 600
#define AIS_MRT_SPECIAL 601
#define AIS_MRT_BREATH 602
#define AIS_MRT_INTRO  603

#define AIS_AGM_INTRO 700
#define AIS_AGM_SLASH 701
#define AIS_AGM_RUN   702
#define AIS_AGM_JUMP  703
#define AIS_AGM_SPIKE 704
#define AIS_AGM_SLASH2 705


#define AIS_GAW_INTRO 800
#define AIS_GAW_TELEPORT 801
#define AIS_GAW_SLASH 802
#define AIS_GAW_ANIMAL_START 803
#define AIS_GAW_RUN 804
#define AIS_GAW_JUMP 805
#define AIS_GAW_ATTACKSET1 806
#define AIS_GAW_ATTACKSET2 807
#define AIS_GAW_TELEPORT_FINISH 808
#define AIS_GAW_ANIMAL_FINISH 809
#define AIS_GAW_ANIMAL_MOVE 810
#define AIS_GAW_SLASH_JUMP 811

#define AIS_CRASH_HILOW 900
#define AIS_CRASH_ROCKETJUMP1 901
#define AIS_CRASH_GRENADE1 902
#define AIS_CRASH_INTRO 903
#define AIS_CRASH_RAPIDFIRE 904
#define AIS_CRASH_GRENADE2 905
#define AIS_CRASH_WALKAWAY 906
#define AIS_CRASH_PAUSE 907
#define AIS_CRASH_HIGHSPREAD 908
#define AIS_CRASH_LOWSPREAD 909


#define AIS_JACOB_INTRO 1000
#define AIS_JACOB_STOMP 1001
#define AIS_JACOB_RUN 1002
#define AIS_JACOB_STANDARD 1003
#define AIS_JACOB_JUMPBACK 1004
#define AIS_JACOB_STAND 1005
#define AIS_JACOB_SPIKE 1006
#define AIS_JACOB_CROUCH 1007
#define AIS_JACOB_JUMPFORWARD 1008
#define AIS_JACOB_FLAME 1009
#define AIS_JACOB_QUAKE 1010
#define AIS_JACOB_QUAKE2 1011


//#define AIS_MOVE_LOC 400 
//#define AIS_NAVIGATE_DOWN 400
//#define AIS_NAVIGATE_UP 500


//#define DIRECTION_LEFT 1000
//#define DIRECTION_RIGHT 2000

#define DAMAGE_BLOCKS 128


#define MAX_ENEMY_DIST 2 //# of tiles to stop from player
#define MAX_ENEMY_DIST_PIX 32
#define BLK_JUMP 67
#define BLK_JUMPRIGHT 65
#define BLK_JUMPLEFT 66
#define BLK_STOPRIGHT 70
#define BLK_STOPLEFT 69  
#define BLK_STOP 71
#define BLK_LADDER 68
#define BLK_JUMP_LEFT 100
#define BLK_JUMP_RIGHT 101
#define BLK_RUN_LEFT1 102
#define BLK_RUN_LEFT2 103
#define BLK_RUN_RIGHT1 104
#define BLK_RUN_RIGHT2 105

class BaseEnemy  
{
public:
	bool ignore_player;
	bool CheckObstruct();
	bool new_enemy;
	bool use_patrol_bounds;
	int prevattackstate;
	void ChangeAttackState(int arg);
	virtual void Wait();
	int movetoxtile;
	void MoveToXTile(int xtile);
	int attackstate;
	void SetChaseRange(int num_tiles);
	void SetAttackRange(float num_pix);
	virtual void StateManager();
	int chase_range;
	float attack_range;
	virtual bool IsStopBlock();
	bool FacePlayer();
	//void moveJump();
	//bool ProcessUpCommingObject();
	//void MoveLoc();
	//virtual void MoveLeft()=0;
	//virtual void MoveRight()=0;
	//void NavigateDown();
	//void StateManager();
	virtual void Attack(){};
	virtual void Chase(){};
	virtual void Patrol(){};
	virtual void UseBrain();
	virtual void ChangeState(int state);
	inline unsigned char GetAIMapCord(int x, int y){ if( ((unsigned int)x < (unsigned int)aio->aimap_width) && ((unsigned int)y < (unsigned int)aio->aimap_height)) return aio->ai_map[y*aio->aimap_width+x];	else return 0;};
	int GetState();
	BaseEnemy();
	virtual ~BaseEnemy();
	virtual void Init() {}
	//Property<int,BaseEnemy
	

	AIInput* aiinput;
	AIOutput* aioutput;

	//int destx, desty
	AIObject* aio;
	
	int xtile, ytile, tileheight;
	float xpos, ypos;
	float time;
	bool *cblocks;

	int current_state;
	int prev_state;
	bool changed_direction;
private:

	

};

#endif // !defined(AFX_BASEENEMY_H__FDF82F90_90D0_44BE_B40D_061A513EAFB6__INCLUDED_)
