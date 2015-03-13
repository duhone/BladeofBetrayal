/*
 *  GameStateManager.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 2/4/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::SaveToDisk(char* saveFile)
{
	// Get the documents directory path of bob.sav
	/*NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSString *file = [documentsDirectory stringByAppendingPathComponent: [[NSString alloc] initWithCString: saveFile]];
	const char* fileName = [file cStringUsingEncoding:1];*/
	
	if (FILE *file = fopen(saveFile, "w"))
	{
		// Write the header tag, and file version
		char headerTag[] = "BoBGameState";
		int version = BOB_GAMESTATE_VERSION;
		
		fwrite(&headerTag, sizeof(headerTag), 1, file);
		fwrite(&version, sizeof(int), 1, file);
		
		// SaveGameInfo Structure
		fwrite(&gameStateInfo, sizeof(struct GameStateInfo), 1, file);
		
		// Enemies states
		fwrite(&gameStateInfo.numEnemies, sizeof(int), 1, file);
		for (int i = 0; i < gameStateInfo.numEnemies; i++)
			fwrite(&gameStateInfo.enemyStates[i], sizeof(struct GameStateEnemyInfo), 1, file);
		
		// Object states
		fwrite(&gameStateInfo.numObjects, sizeof(int), 1, file);
		for (int i = 0; i < gameStateInfo.numObjects; i++)
			fwrite(&gameStateInfo.objectStates[i], sizeof(int), 1, file);
		
		// Spawn point Info
		// Enemy states
		fwrite(&gameStateInfo.spawnPointInfo.numEnemies, sizeof(int), 1, file);
		for (int i = 0; i < gameStateInfo.spawnPointInfo.numEnemies; i++)
			fwrite(&gameStateInfo.spawnPointInfo.enemyDeadStates[i], sizeof(bool), 1, file);
		
		// Object states
		fwrite(&gameStateInfo.spawnPointInfo.numObjects, sizeof(int), 1, file);
		for (int i = 0; i < gameStateInfo.spawnPointInfo.numObjects; i++)
			fwrite(&gameStateInfo.spawnPointInfo.objectStates[i], sizeof(int), 1, file);
		
		
		/*
		// Weapons
		for (int i = 0; i < 6; i++)
		{
			fwrite(&saveGameInfo.weapons[i], sizeof(bool), 1, file);
		}
		
		// Levels
		for (int i = 0; i < 9; i++)
		{
			fwrite(&saveGameInfo.levelInfo[i], sizeof(LevelInfo), 1, file);
		}
		
		// Settings
		fwrite(&saveGameInfo.settingsInfo, sizeof(SettingsInfo), 1, file);
		*/
		fclose(file);
	}
	else
	{
		// could not open file for writing
	}	
}

void GameStateManager::LoadFromDisk(char* saveFile)
{
	// Get the documents directory path of bob.sav
	/*NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSString *file = [documentsDirectory stringByAppendingPathComponent: [[NSString alloc] initWithCString: saveFile]];
	const char* fileName = [file cStringUsingEncoding:1];*/
	
	if (FILE *file = fopen(saveFile, "r"))
	{
		// Read the header tag and version
		char headerTag[13];// = "BoBSav";
		int version = 0;
		
		fread(&headerTag, sizeof(char), 13, file);
		fread(&version, sizeof(int), 1, file);
		
		// check if file read is of the correct version
		if (strcmp(headerTag, "BoBGameState") != 0 || version != BOB_GAMESTATE_VERSION)
		{
			// don't read the saveGameInfo structure, this file is corrupt, or an older version
		}
		else
		{
			// SaveGameInfo Structure
			fread(&gameStateInfo, sizeof(struct GameStateInfo), 1, file);
						
			// Enemies dead states
			fread(&gameStateInfo.numEnemies, sizeof(int), 1, file);
			gameStateInfo.enemyStates = new GameStateEnemyInfo[gameStateInfo.numEnemies];
			for (int i = 0; i < gameStateInfo.numEnemies; i++)
				fread(&gameStateInfo.enemyStates[i], sizeof(struct GameStateEnemyInfo), 1, file);

			// Object states
			fread(&gameStateInfo.numObjects, sizeof(int), 1, file);
			gameStateInfo.objectStates = new int[gameStateInfo.numObjects];
			for (int i = 0; i < gameStateInfo.numObjects; i++)
				fread(&gameStateInfo.objectStates[i], sizeof(int), 1, file);
			
			// Spawn point Info
			// Enemy states
			fread(&gameStateInfo.spawnPointInfo.numEnemies, sizeof(int), 1, file);
			gameStateInfo.spawnPointInfo.enemyDeadStates = new bool[gameStateInfo.spawnPointInfo.numEnemies];
			for (int i = 0; i < gameStateInfo.spawnPointInfo.numEnemies; i++)
				fread(&gameStateInfo.spawnPointInfo.enemyDeadStates[i], sizeof(bool), 1, file);
			
			// Object states
			gameStateInfo.spawnPointInfo.objectStates = new int[gameStateInfo.spawnPointInfo.numObjects];
			fread(&gameStateInfo.spawnPointInfo.numObjects, sizeof(int), 1, file);
			for (int i = 0; i < gameStateInfo.spawnPointInfo.numObjects; i++)
				fread(&gameStateInfo.spawnPointInfo.objectStates[i], sizeof(int), 1, file);
			
			/*
			// Enemies dead states
			bool isDead;
			int enemies = gameStateInfo.enemyDead.size();
			gameStateInfo.enemyDead.clear();
			for (int i = 0; i < enemies; i++)
			{
				//isDead = gameStateInfo.enemyDead[i];
				fread(&isDead, sizeof(bool), 1, file);
				gameStateInfo.enemyDead.push_back(isDead);
			}
			
			
			for (int i = 0; i < gameStateInfo.enemyDead.size(); i++)
			{
				if (gameStateInfo.enemyDead[i] == true)
					int i = 1;
			}
			*/
			/*
			// Levels
			for (int i = 0; i < 9; i++)
			{
				fread(&saveGameInfo.levelInfo[i], sizeof(LevelInfo), 1, file);
			}
			
			// Settings
			fread(&saveGameInfo.settingsInfo, sizeof(SettingsInfo), 1, file);*/
		}
		
		fclose(file);		
	}
	else
	{
		// file does not exist, leave default settings
	}
}

void GameStateManager::SaveGameState(GameStateInfo gameStateInfo)
{
	this->gameStateInfo.canResume = gameStateInfo.canResume;
	this->gameStateInfo.level = gameStateInfo.level;
	this->gameStateInfo.inTheater = gameStateInfo.inTheater;
	this->gameStateInfo.playTime = gameStateInfo.playTime;
	//this->gameStateInfo.playerPos = gameStateInfo.playerPos;
	this->gameStateInfo.playerInfo = gameStateInfo.playerInfo;
	this->gameStateInfo.numEnemies = gameStateInfo.numEnemies;
	this->gameStateInfo.enemyStates = gameStateInfo.enemyStates;
	this->gameStateInfo.numObjects = gameStateInfo.numObjects;
	this->gameStateInfo.objectStates = gameStateInfo.objectStates;
	this->gameStateInfo.spawnPointInfo = gameStateInfo.spawnPointInfo;
}

void GameStateManager::Reset()
{
	GameStateInfo defaultGameStateInfo;
	SaveGameState(defaultGameStateInfo);
	SaveToDisk(DEFAULT_GAMESTATE_FILE);
}