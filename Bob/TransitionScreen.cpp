// TransitionScreen.cpp: implementation of the TransitionScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "TransitionScreen.h"
#include "stdio.h"
//#include <mach/mach.h>
//#include <mach/mach_time.h>
#include "AssetList.h"
#include "s3eTimer.h"
#include <algorithm>
#include "AppConfig.h"
#include "AssetListNew.h"

using namespace CR;
using namespace std;
using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TransitionScreen::TransitionScreen(bool arg)
{	
	time = 0;
	dx = 0;
	dy = 0;
	delaytimer = 0;
	mode = arg;
	sActive = false;
	//if(mode)
	//	graphics_engine->SetClearScreen(false);
	//else
	//	graphics_engine->SetClearScreen(true);

		background = graphics_engine->CreateSprite1();
		background->SetImage(AssetList::Transition_Background);
		if(AppConfig::Instance().IsIpad())
			background->SetDesignSize(480,320);
		slider = graphics_engine->CreateSprite1();
		slider->SetImage( AssetList::Transition_Slider);
		if(AppConfig::Instance().IsIpad())
			slider->SetDesignSize(485,257);
		banner = graphics_engine->CreateSprite1();
		banner->SetImage( AssetList::Transition_Banner);
		if(AppConfig::Instance().IsIpad())
			banner->SetDesignSize(570,35);

	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::jaildoorclose::ID);
}

TransitionScreen::~TransitionScreen()
{
	background->Release();
	slider->Release();
	banner->Release();

}

void TransitionScreen::Begin(bool arg)
{
	//graphics_engine->SetClearScreen(true);
	nframes = 0;
//	QueryPerformanceCounter(&starttime);
//	QueryPerformanceCounter(&currenttime);
//	LARGE_INTEGER tempq;
	//QueryPerformanceFrequency(&tempq);
//	timerfreq = 1.0f/((float)(tempq.QuadPart));
	//timerfreq = 1.0f/SysTicksPerSecond();
	//mach_timebase_info_data_t time_info;
	//mach_timebase_info(&time_info);
	//timerfreq = time_info.numer/(float)time_info.denom;
	timerfreq = 1/1000.0f;
	
	currenttime = s3eTimerGetMs();
	starttime = currenttime;

	sActive = true;
	mode = arg;
	dx = 0;

	/*if(mode)
	{
		graphics_engine->SetClearScreen(false);
	}
	else
	{
		graphics_engine->SetClearScreen(true);
	}*/

	//Door Close
	if(mode)
	{
		delaytimer = 0;
		background->SetPositionAbsalute(240, -160);
		slider->SetPositionAbsalute(240, 447);
		banner->SetPositionAbsalute(-282, 34);

		//half_door_bottom->SetPositionAbsalute(240, 320+120);
		snd_play = true;
	}
	//Door Open
	else
	{
		delaytimer = 1;
		background->SetPositionAbsalute(240, 160);
		slider->SetPositionAbsalute(240, 194);
		banner->SetPositionAbsalute(282, 34);
		//half_door_bottom->SetPositionAbsalute(240, 160+80);
	}
	
}

void TransitionScreen::Update()
{
//	QueryPerformanceCounter(&currenttime);
//	time = ((float)(currenttime.QuadPart - starttime.QuadPart))*timerfreq;
//	starttime.QuadPart = currenttime.QuadPart;
	currenttime = s3eTimerGetMs();
	time = (currenttime - starttime)*timerfreq;
	time = min(time, 1.0f/10.0f);
	starttime = currenttime;

	delaytimer -= time;

	if(delaytimer <= 0)
	if(dx < 1)
	{
		dx += 2.0f*time;
		if(dx >= 1)
		{
			dx = 1;
		}
		if(mode)
		{
			if(snd_play)
			{
//				sound_processor->PlaySound(game_sounds->doorclose);
				//close_sound->Play(false);
				//snd_play = false;
			}

			background->SetPositionAbsalute(240, -160+dx*320);
			slider->SetPositionAbsalute(240, 447-dx*253);
			banner->SetPositionAbsalute(-282+dx*564, 34);
			//half_door_bottom->SetPositionAbsalute(240, 440-dx);
		}
		else
		{
			background->SetPositionAbsalute(240,160-dx*320);
			slider->SetPositionAbsalute(240, 194+dx*253);
			banner->SetPositionAbsalute(282-dx*564, 34);
			//half_door_bottom->SetPositionAbsalute(240,240+dx);
		}


	}
	//else
	//	sActive = false;

	if(sActive)
	{
		background->Render();
		slider->Render();
		banner->Render();
	}
	if(dx >= 1)
	{
		sActive = false;
		
		if (snd_play)
		{
			//close_sound->Play(false);
//			soundPlayer->PlaySound(jaildoorclose);
			m_soundFX->Play();
			snd_play = false;
		}
		
		dx = 1;
	}
}

void TransitionScreen::Render()
{
	background->Render();
	slider->Render();
	banner->Render();
	//half_door_top->Render();
}

void TransitionScreen::End()
{

}

void TransitionScreen::SetTime(float arg)
{
	//time = arg;
}

