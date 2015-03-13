//#include "StdAfx.h"
#include "Timer.h"
#include <s3e.h>

using namespace CR::Utility;

Timer::Timer(void)
{
	Reset();
}

Timer::~Timer(void)
{
}

/*!
	Reset the total time back to 0. Also resets the last frame time back to 0.
	Generally only used when total time is needed.
*/
void Timer::Reset(void)
{

	starttime = s3eTimerGetMs();
		
	timerFreqInv = 1/1000.0f;
	
	totalTime = 0;
	timeLastFrame = 0;

}

/*!
	Updates the last frame time, and the total time. 
*/
void Timer::Update(void)
{

	currenttime = s3eTimerGetMs();
	timeLastFrame = (currenttime - starttime)*timerFreqInv;
	starttime = currenttime;
	totalTime += timeLastFrame;

}

void Timer::StartFrame()
{
	starttime = s3eTimerGetMs();
}