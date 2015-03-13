// EnemyJunkbotTrack.h: interface for the EnemyJunkbotTrack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYJUNKBOTTRACK_H__6AC418CB_44ED_4018_BDAB_CE3857B71A74__INCLUDED_)
#define AFX_ENEMYJUNKBOTTRACK_H__6AC418CB_44ED_4018_BDAB_CE3857B71A74__INCLUDED_


#include "Enemy.h"

class EnemyJunkbotTrack : public Enemy  
{
public:
	EnemyJunkbotTrack(Level *curLevel);
	virtual ~EnemyJunkbotTrack();


	virtual void processLeft();
	virtual void processRight();
//	virtual void processAttack();
	virtual void processDeath();
	virtual void processDamage();
	virtual void stop();
	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
//	virtual HPTRect &GetWorldLoc();

	void processUpdate();
};

#endif // !defined(AFX_ENEMYJUNKBOTTRACK_H__6AC418CB_44ED_4018_BDAB_CE3857B71A74__INCLUDED_)
