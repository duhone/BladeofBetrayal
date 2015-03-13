// ProgressMeter.cpp: implementation of the ProgressMeter class.
//
//////////////////////////////////////////////////////////////////////


#include "ProgressMeter.h"
#include "game.h"
#include <string.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int ProgressMeter::pProgress;
int ProgressMeter::pTotalProgress;
unsigned int ProgressMeter::pCurrentTime;
unsigned int ProgressMeter::pPreviousTime;
unsigned int ProgressMeter::pStartTime;
unsigned int ProgressMeter::dzUpdateInterval;
unsigned int ProgressMeter::dzTickCurrent;
unsigned int ProgressMeter::dzTickInterval;
bool ProgressMeter::bIsActive;
HPTFont1* ProgressMeter::pMeterFont;
char ProgressMeter::tString[255];
int ProgressMeter::xLoc;
int ProgressMeter::yLoc;

ProgressMeter::ProgressMeter(const char *string, int xLoc, int yLoc)
{
//	this->hWnd = hWnd;

	this->xLoc = xLoc;
	this->yLoc = yLoc;

	strcpy(tString, string);

	dzTime = 0;
	dzTickInterval = 20;
	dzTickCount = 100;
	dzTickCurrent = 0;
	dzUpdateInterval = 5;

	pTotalProgress = 0;
	pProgress = 0;

	bIsActive = true;

	pMeterFont = graphics_engine->CreateFont1();
	
    //NSString * path = [[NSBundle mainBundle] pathForResource:  @"gothic12" ofType: @"HFF"];
	//const char *gothic12 = [path cStringUsingEncoding:1];
	//backTiles->LoadTileSet(const_cast<char*>(level1b));
	
	pMeterFont->LoadHFFFont("gothic12.HFF");

//	pMeterFont = graphics_engine->CreateFont1();
//	pMeterFont->LoadHFFFont(hptstrcat(path,("fonts//game hud.hff")));
}

ProgressMeter::~ProgressMeter()
{
	pMeterFont->Release();
}

/*void CALLBACK ProgressMeter::ProgressMeterCALLBACK(HWND hwnd, UINT uMsg, UINT idEvent, unsigned int dwTime )
{
	pCurrentTime = dwTime - pStartTime;
	pStartTime = dwTime;

	pProgress += (pCurrentTime / dzUpdateInterval);

	if((unsigned)pProgress >= dzTickInterval)
	{
		pProgress = 0;
		dzTickInterval++;
	}

	pTotalProgress = (dzTickCurrent * dzTickInterval) + pProgress;

	if(pTotalProgress > 100) pTotalProgress = 100;
}*/

bool ProgressMeter::ProgressMeterStart()
{
//	pCurrentTime = GetTickCount();
//	pStartTime = GetTickCount();

	// Reset Tick & Progress Variables
	dzTickCurrent = 0;
	pTotalProgress = 0;
	pProgress = 0;

//	SetTimer(hWnd, 25, dzUpdateInterval, ProgressMeter::ProgressMeterCALLBACK);

	return true;
}

bool ProgressMeter::ProgressMeterStop()
{
	//KillTimer(hWnd, 25);
	return true;
}

bool ProgressMeter::SetTickCount(unsigned int dzTickCount)
{
	this->dzTickCount = dzTickCount;

	return true;
}

bool ProgressMeter::SetTickInterval(unsigned int dzTickInterval)
{
	this->dzTickInterval = dzTickInterval;

	return true;
}

bool ProgressMeter::SetUpdateInterval(unsigned int dzUpdateInterval)
{
	this->dzUpdateInterval = dzUpdateInterval;
	
	return true;
}

bool ProgressMeter::SetProgressTimer(unsigned int dzTime)
{
	this->dzTime = dzTime;

	return true;
}

void ProgressMeter::Update()
{
	dzTickCurrent++;
	pProgress = 0;

	pTotalProgress = (dzTickCurrent * dzTickInterval) + pProgress;
	if(pTotalProgress > 100) pTotalProgress = 100;

	//graphics_engine->BeginFrame();
	graphics_engine->Position(xLoc,yLoc);
	(*graphics_engine) << pMeterFont  << tString;
	graphics_engine->Position(300,50);
	(*graphics_engine) << pMeterFont << "..." << pTotalProgress << "%...";
	//graphics_engine->EndFrame();
}

void ProgressMeter::Finish()
{
	pProgress = 0;

	//graphics_engine->BeginFrame();
	graphics_engine->Position(xLoc,yLoc);
	(*graphics_engine) << pMeterFont  << tString;
	graphics_engine->Position(300,50);
	(*graphics_engine) << pMeterFont << "...100%...";
	//graphics_engine->EndFrame();

//	Sleep(1000);
}
