// EnemyGawain.h: interface for the EnemyGawain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGAWAIN_H__F8BAB620_8DBE_4480_9609_9EB01484424A__INCLUDED_)
#define AFX_ENEMYGAWAIN_H__F8BAB620_8DBE_4480_9609_9EB01484424A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyGawain : public BaseEnemy  
{
public:
	float berzerk_time;
	float berzerk_timer;
	float above_head_time;
	float above_head_timer;
	float wait_timer;
	int animal_attack_count;
	bool second_stage;
	int shock_count;
	int jump_count;
	bool jump;
	void Chase();
	int teleport_lx;
	int teleport_rx;
	float slash_time;
	float slash_timer;
	int temp;
	int teleport_x;
	int teleport_range;
	int teleport_distance;
	void Attack();
	AIEnemyGawain();
	virtual ~AIEnemyGawain();

};

#endif // !defined(AFX_ENEMYGAWAIN_H__F8BAB620_8DBE_4480_9609_9EB01484424A__INCLUDED_)
