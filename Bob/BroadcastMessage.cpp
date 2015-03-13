// BroadcastMessage.cpp: implementation of the BroadcastMessage class.
//
//////////////////////////////////////////////////////////////////////


#include "BroadcastMessage.h"
#include "string.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BroadcastMessage::BroadcastMessage(char *msg, list<BroadcastMessage*> *message_queue)
{
	bImage = false;

	this->msg = new char[sizeof(char)*strlen(msg)];
	strcpy(this->msg, msg);
	this->message_queue = message_queue;
}

BroadcastMessage::~BroadcastMessage()
{
	delete[] this->msg;
}

void BroadcastMessage::SetImage(HPTSprite1 *image)
{
	hpt_image = image;
	bImage = true;
}

HPTSprite1 *BroadcastMessage::GetImage()
{
	return hpt_image;
}

char *BroadcastMessage::GetMessage()
{
	return msg;
}

void BroadcastMessage::Send()
{
	message_queue->push_back(this);
}

void BroadcastMessage::SetMessage(char *msg, ...)
{

}
