#include "StdAfx.h"
#include "Timer.h"

using namespace Syntax::Utility;

Timer::Timer(void)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	timerFreqInv = 1.0/(double)freq.QuadPart;
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
	totalTime = 0;
	timeLastFrame = 0;
	QueryPerformanceCounter(&lastFrameQuery);
}

/*!
	Updates the last frame time, and the total time. 
*/
void Syntax::Utility::Timer::Update(void)
{
	LARGE_INTEGER thisFrameQuery;

	QueryPerformanceCounter(&thisFrameQuery);
	timeLastFrame = (thisFrameQuery.QuadPart - lastFrameQuery.QuadPart)*timerFreqInv;
	totalTime += timeLastFrame;

	lastFrameQuery = thisFrameQuery;
}
