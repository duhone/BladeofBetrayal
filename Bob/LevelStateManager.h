/*
 *  LevelStateManager.h
 *  BoB
 *
 *  Created by Robert Shoemate on 2/5/09.
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

#define LEVELSTATETYPE_NOTUPGRADE 0
#define LEVELSTATETYPE_HEALTH 1
#define LEVELSTATETYPE_ENERGY 2
#define LEVELSTATETYPE_ATTACK 3
#define LEVELSTATETYPE_WEAPON 4

#define BOB_LEVELSTATE_VERSION 2
#define DEFAULT_LEVELSTATE_FILE "crpds_bob_levelstate.sav"

struct LevelStateInfo
{
	int level;
	
	int numHealthUpgrades;
	bool *hasHealthUpgrade;
	
	int numEnergyUpgrades;
	bool *hasEnergyUpgrade;
	
	int numAttackUpgrades;
	bool *hasAttackUpgrade;
	
	int numWeaponUpgrades;
	bool *hasWeaponUpgrade;
	
	LevelStateInfo()
	{
		level = -1;
		numHealthUpgrades = 0;
		numEnergyUpgrades = 0;
		numAttackUpgrades = 0;
		numWeaponUpgrades = 0;
	}
};

class LevelStateManager
{
public:
	LevelStateManager();
	~LevelStateManager();
	void SaveToDisk(char* saveFile);
	void LoadFromDisk(char* saveFile);
	void SaveLevelState(LevelStateInfo levelStateInfo);
	LevelStateInfo GetLevelStateInfo(int level) const;
	void Reset();
	
private:
	vector<LevelStateInfo> levelStates;
};