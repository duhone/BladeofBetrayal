// BroadcastMessage.h: interface for the BroadcastMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROADCASTMESSAGE_H__9DADA372_26C6_4546_B48C_81D62467CF47__INCLUDED_)
#define AFX_BROADCASTMESSAGE_H__9DADA372_26C6_4546_B48C_81D62467CF47__INCLUDED_


#include "../Engines/Graphics/HPTGraphics.h"
//#include "hptlist.h"
//extern HPTGraphicsEngine *graphics_engine;

#include <list>

class BroadcastMessage  
{
public:
	BroadcastMessage(char *msg, std::list<BroadcastMessage*> *message_queue);
	virtual ~BroadcastMessage();

	char *GetMessage();
	void Send();


	void SetImage(HPTSprite1 *image);
	HPTSprite1 *GetImage();
	bool IsImage() {return bImage;};
	void SetMessage(char *msg, ...);

private:
	std::list<BroadcastMessage*> *message_queue;
	HPTSprite1 *hpt_image;
	char *msg;

	bool bImage;
};

class BroadcastMessageDamage : BroadcastMessage
{
	BroadcastMessageDamage();
	~BroadcastMessageDamage();
};

class BMessages
{
public:

	/* Message Initialization */
	BMessages(std::list<BroadcastMessage*> *message_queue)
	{
		this->message_queue = message_queue;
		ShockAttackUpgrade = new BroadcastMessage("You have recieve the shock attack!", message_queue);
		PlayerDamaged = new BroadcastMessage("You have been hit!", message_queue);
		EnemyDamaged = new BroadcastMessage("You have hit an enemy!", message_queue);

		/* Enemy Taunt Messages */
//		NinjaTaunt[0] = new BroadcastMessage("You'll never get by me Spencer!", message_queue);
//		NinjaTaunt[1] = new BroadcastMessage("Fuck you Bitch!", message_queue);
//		NinjaTaunt[2] = new BroadcastMessage("Go fuck yourself, your mother's a bitch!", message_queue);
//		NinjaTaunt[3] = new BroadcastMessage("Eat my asshole nigger!", message_queue);
//		NinjaTaunt[4] = new BroadcastMessage("Lick my peehole!", message_queue);
	};

	void SetMessage();

/* Weapon Upgrade Messages */
	BroadcastMessage *ShockAttackUpgrade;
	BroadcastMessage *FlameAttackUpgrade;
	BroadcastMessage *GrenadeAttackUpgrade;
	BroadcastMessage *ProjectileAttackUpgrade;
	BroadcastMessage *QuakeAttackUpgrade;

/* Upgrade Messages */
	BroadcastMessage *HealthUpgrade;
	BroadcastMessage *EnergyUpgrade;
	
/* Damage Messages */
	BroadcastMessage *PlayerDamaged;
	BroadcastMessage *EnemyDamaged;

/* Enemy Taunt Message */
	BroadcastMessage *NinjaTaunt[5];

	std::list<BroadcastMessage*> *message_queue;
};
#endif // !defined(AFX_BROADCASTMESSAGE_H__9DADA372_26C6_4546_B48C_81D62467CF47__INCLUDED_)
