// MessageBroadcaster.cpp: implementation of the MessageBroadcaster class.
//
//////////////////////////////////////////////////////////////////////


#include "MessageBroadcaster.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


MessageBroadcaster::~MessageBroadcaster()
{

}

void MessageBroadcaster::SetTime(float time)
{
	this->time+= time;
}

void MessageBroadcaster::Render()
{
	while(message_queue.size() > 5)
		message_queue.pop_front();

	if(time > 4)
	{
		message_queue.pop_front();
		time = 0;
	}

	graphics_engine->Position(10,10);
	int dy = 10;
	
	for(list<BroadcastMessage*>::iterator i = message_queue.begin(); i != message_queue.end(); i++)
	{
		(*graphics_engine) << (*i)->GetMessage();

		if((*i)->IsImage())
		{
			(*i)->GetImage()->Render();

		}

		graphics_engine->Position(10,dy+=12);
	}	
	
}
