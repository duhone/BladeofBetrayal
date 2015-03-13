// EnemyGMonsterSpit.h: interface for the EnemyGMonsterSpit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGMONSTERSPIT_H__AD844221_0EBA_4EE6_98DC_CFCDFA69FF63__INCLUDED_)
#define AFX_ENEMYGMONSTERSPIT_H__AD844221_0EBA_4EE6_98DC_CFCDFA69FF63__INCLUDED_


#include "Enemy.h"

class EnemyGMonsterSpit : public Enemy  
{
public:
	EnemyGMonsterSpit(Level *curLevel,IPlayer *_player);
	virtual ~EnemyGMonsterSpit();

	virtual void processAttack();
	virtual void processDamage();
	virtual void processDeath();
	virtual void stop();
//	virtual HPTRect &GetWorldLoc();
	void processUpdate();
	
private:
	IPlayer *m_player;
};

#endif // !defined(AFX_ENEMYGMONSTERSPIT_H__AD844221_0EBA_4EE6_98DC_CFCDFA69FF63__INCLUDED_)
