// EnemyShadowElitePistol.h: interface for the EnemyShadowElitePistol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYSHADOWELITEPISTOL_H__79CE9BEB_68F5_4EC5_AD54_ABF1FDF839FB__INCLUDED_)
#define AFX_ENEMYSHADOWELITEPISTOL_H__79CE9BEB_68F5_4EC5_AD54_ABF1FDF839FB__INCLUDED_


#include "Enemy.h"

class EnemyShadowElitePistol : public Enemy  
{
public:
	EnemyShadowElitePistol(Level *curLevel);
	virtual ~EnemyShadowElitePistol();

	virtual void processLeft();
	virtual void processRight();
	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
};

#endif // !defined(AFX_ENEMYSHADOWELITEPISTOL_H__79CE9BEB_68F5_4EC5_AD54_ABF1FDF839FB__INCLUDED_)
