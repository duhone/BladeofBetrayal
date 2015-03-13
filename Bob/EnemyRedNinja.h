// EnemyRedNinja.h: interface for the EnemyRedNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYREDNINJA_H__28C96897_A953_4E18_B2DD_931C84C7738C__INCLUDED_)
#define AFX_ENEMYREDNINJA_H__28C96897_A953_4E18_B2DD_931C84C7738C__INCLUDED_


#include "EnemyNinja.h"

class EnemyRedNinja : public EnemyNinja   
{
public:
	EnemyRedNinja(Level *curLevel);
	virtual ~EnemyRedNinja();

	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
};

#endif // !defined(AFX_ENEMYREDNINJA_H__28C96897_A953_4E18_B2DD_931C84C7738C__INCLUDED_)
