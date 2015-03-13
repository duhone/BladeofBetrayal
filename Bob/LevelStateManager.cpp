/*
 *  LevelStateManager.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 2/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelStateManager.h"

LevelStateManager::LevelStateManager()
{
}

LevelStateManager::~LevelStateManager()
{
}

void LevelStateManager::SaveToDisk(char* saveFile)
{
	// Get the documents directory path of bob.sav
	/*NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSString *file = [documentsDirectory stringByAppendingPathComponent: [[NSString alloc] initWithCString: saveFile]];
	const char* fileName = [file cStringUsingEncoding:1];*/
	
	if (FILE *file = fopen(saveFile, "w"))
	{
		// Write the header tag, and file version
		char headerTag[] = "BoBLevelState";
		int version = BOB_LEVELSTATE_VERSION;
		
		fwrite(&headerTag, sizeof(headerTag), 1, file);
		fwrite(&version, sizeof(int), 1, file);
		
		// LevelStateInfo Structure
		int numLevelStates = levelStates.size();
		fwrite(&numLevelStates, sizeof(int), 1, file);
		for (int i = 0; i < numLevelStates; i++)
		{
			fwrite(&levelStates[i], sizeof(struct LevelStateInfo), 1, file);
		
			// Health upgrade states
			fwrite(&levelStates[i].numHealthUpgrades, sizeof(int), 1, file);
			for (int j = 0; j < levelStates[i].numHealthUpgrades; j++)
				fwrite(&levelStates[i].hasHealthUpgrade[j], sizeof(bool), 1, file);
			
			// Energy upgrade states
			fwrite(&levelStates[i].numEnergyUpgrades, sizeof(int), 1, file);
			for (int j = 0; j < levelStates[i].numEnergyUpgrades; j++)
				fwrite(&levelStates[i].hasEnergyUpgrade[j], sizeof(bool), 1, file);
			
			// Attack upgrade states
			fwrite(&levelStates[i].numAttackUpgrades, sizeof(int), 1, file);
			for (int j = 0; j < levelStates[i].numAttackUpgrades; j++)
				fwrite(&levelStates[i].hasAttackUpgrade[j], sizeof(bool), 1, file);
			
			// Weapon upgrade states
			fwrite(&levelStates[i].numWeaponUpgrades, sizeof(int), 1, file);
			for (int j = 0; j < levelStates[i].numWeaponUpgrades; j++)
				fwrite(&levelStates[i].hasWeaponUpgrade[j], sizeof(bool), 1, file);
		}
		
		fclose(file);
	}
	else
	{
		// could not open file for writing
	}
}

void LevelStateManager::LoadFromDisk(char* saveFile)
{
	levelStates.clear();
	
	// Get the documents directory path of bob.sav
	/*NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSString *file = [documentsDirectory stringByAppendingPathComponent: [[NSString alloc] initWithCString: saveFile]];
	const char* fileName = [file cStringUsingEncoding:1];*/
	
	if (FILE *file = fopen(saveFile, "r"))
	{
		// Read the header tag and version
		char headerTag[14];// = "BoBSav";
		int version = 0;
		
		fread(&headerTag, sizeof(char), 14, file);
		fread(&version, sizeof(int), 1, file);
		
		// check if file read is of the correct version
		if (strcmp(headerTag, "BoBLevelState") != 0 || version != BOB_LEVELSTATE_VERSION)
		{
			// don't read the saveGameInfo structure, this file is corrupt, or an older version
		}
		else
		{
			int numLevelStates = 0;
			fread(&numLevelStates, sizeof(int), 1, file);
			
			LevelStateInfo tmpLevelState;
			for (int i = 0; i < numLevelStates; i++)
			{
				fread(&tmpLevelState, sizeof(struct LevelStateInfo), 1, file);
				
				// Health upgrade states
				fread(&tmpLevelState.numHealthUpgrades, sizeof(int), 1, file);
				tmpLevelState.hasHealthUpgrade = new bool[tmpLevelState.numHealthUpgrades];
				for (int j = 0; j < tmpLevelState.numHealthUpgrades; j++)
					fread(&tmpLevelState.hasHealthUpgrade[j], sizeof(bool), 1, file);
				
				// Energy upgrade states
				fread(&tmpLevelState.numEnergyUpgrades, sizeof(int), 1, file);
				tmpLevelState.hasEnergyUpgrade = new bool[tmpLevelState.numEnergyUpgrades];
				for (int j = 0; j < tmpLevelState.numEnergyUpgrades; j++)
					fread(&tmpLevelState.hasEnergyUpgrade[j], sizeof(bool), 1, file);
				
				// Attack upgrade states
				fread(&tmpLevelState.numAttackUpgrades, sizeof(int), 1, file);
				tmpLevelState.hasAttackUpgrade = new bool[tmpLevelState.numAttackUpgrades];
				for (int j = 0; j < tmpLevelState.numAttackUpgrades; j++)
					fread(&tmpLevelState.hasAttackUpgrade[j], sizeof(bool), 1, file);
				
				// Weapon upgrade states
				fread(&tmpLevelState.numWeaponUpgrades, sizeof(int), 1, file);
				tmpLevelState.hasWeaponUpgrade = new bool[tmpLevelState.numWeaponUpgrades];
				for (int j = 0; j < tmpLevelState.numWeaponUpgrades; j++)
					fread(&tmpLevelState.hasWeaponUpgrade[j], sizeof(bool), 1, file);
				
				levelStates.push_back(tmpLevelState);
			}
		}
		
		fclose(file);		
	}
	else
	{
		// file does not exist, leave default settings
	}	
}

void LevelStateManager::SaveLevelState(LevelStateInfo levelStateInfo)
{
	for (vector<LevelStateInfo>::iterator i = levelStates.begin(); i < levelStates.end(); i++)
	{
		if (i->level == levelStateInfo.level)
		{
			i = levelStates.erase(i);
			levelStates.push_back(levelStateInfo);
			return;
		}
	}
	
	// no level state was found, push this one on the vector
	levelStates.push_back(levelStateInfo);
}

LevelStateInfo LevelStateManager::GetLevelStateInfo(int level) const
{
	for (int i = 0; i < levelStates.size(); i++)
	{
		if (levelStates[i].level == level)
			return levelStates[i];
	}
	
	// if it doesnt have it, create it
	LevelStateInfo levelStateInfo;
	levelStateInfo.level = level;
	return levelStateInfo;
}

void LevelStateManager::Reset()
{
	levelStates.clear();
	SaveToDisk(DEFAULT_LEVELSTATE_FILE);
}