/*
 *  GameStateManager.h
 *  BoB
 *
 *  Created by Robert Shoemate on 2/4/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "point.h"
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "IPlayerConfig.h"

using namespace std;

#define BOB_GAMESTATE_VERSION 2
#define DEFAULT_GAMESTATE_FILE "crpds_bob_gamestate.sav"

struct GameStateEnemyInfo
{
	bool isDead;
	int life;
	
	GameStateEnemyInfo()
	{
		isDead = false;
		life = 0;
	}
};

struct GameStatePlayerInfo
{
	HPTPoint lastSpawnPoint; // last spawnobject
	HPTPoint saveSpawnPoint; // when game was exited

	bool S_ON_GROUND; // need
	bool S_NEXT_TO_LADDER; // need
	bool S_ON_LADDER; // need
	int  S_LADDER_TYPE; // need
	bool S_CROUCH; // need
	bool S_CROUCH_TOGGLE; // need
	bool S_CRAWL; // need
	
	
	bool bossUsedOnlyBasicAttack;
	bool bossNoDamageTaken;
	
	int frameSet;
	
	GameStatePlayerInfo()
	{
		lastSpawnPoint.x = 0;
		lastSpawnPoint.y = 0;
		saveSpawnPoint.x = 0;
		saveSpawnPoint.y = 0;
		frameSet = 0;
		
		S_ON_GROUND = false;
		S_NEXT_TO_LADDER = false;
		S_ON_LADDER = false;
		S_LADDER_TYPE = 0;
		S_CROUCH = false;
		S_CROUCH_TOGGLE = false;
		S_CRAWL = false;
		
		bossUsedOnlyBasicAttack = false;
		bossNoDamageTaken = false;
	}
};

struct SpawnPointInfo
{
	int numEnemies;
	bool *enemyDeadStates;
	
	int numObjects;
	int *objectStates;
	
	SpawnPointInfo()
	{
		numEnemies = 0;
		numObjects = 0;
	}
};

struct GameStateInfo
{
	bool canResume;
	int level;
	bool inTheater;
	float playTime;
	GameStatePlayerInfo playerInfo;
	
	int numEnemies;
	GameStateEnemyInfo *enemyStates;
	
	int numObjects;
	int *objectStates;
	
	SpawnPointInfo spawnPointInfo;
	
	GameStateInfo()
	{
		canResume = false;
		level = -1;
		numEnemies = 0;
		numObjects = 0;
		playTime = 0;
		inTheater = false;
	}
};

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();
	void SaveToDisk(char* saveFile);
	void LoadFromDisk(char* saveFile);
	void SaveGameState(GameStateInfo gameStateInfo);
	void Reset();
	
	GameStateInfo GetGameStateInfo() const {return gameStateInfo;}
private:
	GameStateInfo gameStateInfo;
};