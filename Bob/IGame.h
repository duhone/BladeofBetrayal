// IGame.h: interface for the IGame class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "SaveGameManager.h"
#include "LevelStateManager.h"
#include "GameStateManager.h"

class IGame  
{
public:
	IGame();
	virtual ~IGame();
	
	virtual void StartGame(int nLevel, bool skipMovie) = 0;
	virtual void SetVideoQuality(int arg) = 0;
	virtual int GetVideoQuality() = 0;
	virtual bool GetEnableStatus() = 0;
	virtual void SetEnableStatus(bool arg) = 0;
	
	virtual void Resume() = 0;
	virtual void ReplayIntro() = 0;
	
	virtual SaveGameManager *GetSaveGameManager() = 0;
	virtual GameStateManager *GetGameStateManager() = 0;
	virtual LevelStateManager *GetLevelStateManager() = 0;
};
