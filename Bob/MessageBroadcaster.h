// MessageBroadcaster.h: interface for the MessageBroadcaster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEBROADCASTER_H__D061F6F3_9492_4606_B329_6BE058C8953A__INCLUDED_)
#define AFX_MESSAGEBROADCASTER_H__D061F6F3_9492_4606_B329_6BE058C8953A__INCLUDED_


#include "broadcastmessage.h"
//#include "hptlist.h"
#include<list>
#include "../Engines/Graphics/HPTGraphics.h"

extern HPTGraphicsEngine *graphics_engine;

class MessageBroadcaster  
{
public:

	MessageBroadcaster():msg(&message_queue) {bActive = false;
};
	virtual ~MessageBroadcaster();

	void SetTime(float time);
	void FlushQueue();
	void QueueMessage(BroadcastMessage);

	void SetQueueSize(unsigned int dwSize);

	void Render();

	void Activate();
	void Deactivate();

	BMessages msg;

private:

//	HPTFont1 *font;
	float time;
	bool bActive;
	std::list<BroadcastMessage*> message_queue;
};

#endif // !defined(AFX_MESSAGEBROADCASTER_H__D061F6F3_9492_4606_B329_6BE058C8953A__INCLUDED_)
