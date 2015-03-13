#ifndef _I_PLAYER_CONFIG_H
#define _I_PLAYER_CONFIG_H

#include "Weapon.h"
//#include "HPTList.h"
//#include "HPTVector.h"
#include "point.h"
#include <math.h>
#include <list>
using namespace std;

const int health_per_life_bar = 5;
const int energy_upgrade_amt = 5;

// Determines Current Movement and Functions
typedef enum INPUT_STATE {
	input_0,
	input_stop,
	input_left,
	input_right,
	input_up,
	input_down,
	input_button1,
	input_button2,
	input_button3,
	input_button4,
	input_button5,
	FACE_LEFT,
	FACE_RIGHT
} I_STATE;

typedef enum MOVEMENT_STATE {
	move_0,
	move_stop,
	move_left,
	move_right,
	move_up,
	move_down,
	move_attack,
	move_reserved_action_1,
	move_reserved_action_2,
	move_attack2
} M_STATE;

typedef enum ANIMATION_STATE {
	anim_0,
	anim_left,
	anim_right,
	anim_stop,
	anim_attack,
} A_STATE;

struct IPlayerFlags
{
	list<I_STATE> InputQueue;
//	HPTVector<I_STATE> InputQueue;

	// Movement States
	I_STATE ReqIState;  //Input State
	M_STATE CurMState;  //Move State
	M_STATE PrevMState;
	A_STATE CurAState;  //Anim State

	// State Flags
	bool S_JUMP;
	bool S_ATTACK;
	bool S_ATTACK_COLLISION;
	
	bool S_RENDER_DIRECTION;
	bool S_DIRECTION;
	bool S_ON_GROUND; // need
	bool S_HEAD_COLLISION;
	bool S_NEXT_TO_LADDER; // need
	bool S_ON_LADDER; // need
	int  S_LADDER_TYPE; // need
	bool S_CROUCH; // need
	bool S_CROUCH_TOGGLE; // need
	bool S_CRAWL; // need
	bool S_DAMAGED;
	bool S_DEAD;
	bool S_DAMAGED_DIRECTION;
	bool S_INVULNERABLE;
	bool S_IS_PLAYER;
	bool S_UNDER_WATER;
	bool S_ACTIVE;
	bool S_NO_GRAVITY;
	bool S_FALLING;
	bool S_VISIBLE;
	bool S_PROCESS_DEATH;
	bool S_POINTS;
	bool S_RENDER;
	bool S_RENDER_HEALTH_BAR;
	bool S_CONVEYOR;
	bool S_CONVEYOR_TYPE;
	bool S_RENDER_FLASH;
	bool S_NO_COLLISION;
	bool S_FINAL_ANIM;
	bool S_ALWAYS_ATTACK;
	bool S_FREEZE_INPUT;
	
	int nCurrAttack;
	int nDamageAmount;
	float fDmgTimer;
	float fInvulnerableTimer;
	bool door;

	IPlayerFlags()
	{
		S_RENDER_DIRECTION = true;
		S_ATTACK = false;
		S_ATTACK_COLLISION = false;
		S_DIRECTION = true;
		S_JUMP = false;
		S_CROUCH = false;
		S_CROUCH_TOGGLE = false;
		S_CRAWL = false;
		S_HEAD_COLLISION = false;
		S_ON_GROUND = true;
		S_NEXT_TO_LADDER = false;
		S_DAMAGED = false;
		S_DEAD = false;
		S_DAMAGED_DIRECTION = false;
		S_INVULNERABLE = false;
		S_IS_PLAYER = false;
		S_ACTIVE = false;
		S_NO_GRAVITY = false;
		S_ON_LADDER = false;
		S_FALLING = false;
		S_VISIBLE = true;
		S_PROCESS_DEATH = false;
		S_POINTS = true;
		S_UNDER_WATER = false;
		S_RENDER = true;
		S_RENDER_HEALTH_BAR = true;
		S_CONVEYOR = false;
		S_RENDER_FLASH = true;
		S_NO_COLLISION = false;
		S_FINAL_ANIM = false;
		S_ALWAYS_ATTACK=false;
		S_FREEZE_INPUT=false;
		door = false;

		CurMState = move_stop;
		ReqIState = input_0;
		PrevMState = move_0;
		CurAState = anim_0;

		nDamageAmount = 0;
		nCurrAttack = 0;
		fDmgTimer = 0;
		fInvulnerableTimer = 0;
	}
};

#endif