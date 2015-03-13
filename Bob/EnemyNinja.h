// EnemyNinja.h: interface for the EnemyNinja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYNINJA_H__E6AE33F4_7AB8_4091_8690_412166D32EE3__INCLUDED_)
#define AFX_ENEMYNINJA_H__E6AE33F4_7AB8_4091_8690_412166D32EE3__INCLUDED_


#include "Enemy.h"

class EnemyNinja : public Enemy  
{
public:
	EnemyNinja();
	virtual ~EnemyNinja();

//	HPTRect &GetWeaponWorldLoc();
//	virtual HPTRect &GetWorldLoc();
};

#endif // !defined(AFX_ENEMYNINJA_H__E6AE33F4_7AB8_4091_8690_412166D32EE3__INCLUDED_)
