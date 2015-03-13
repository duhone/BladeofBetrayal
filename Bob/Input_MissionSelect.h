/*
 *  Input_MissionSelect.h
 *  BoB
 *
 *  Created by Robert Shoemate on 1/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "../Engines/Graphics/HPTGraphics.h"
#include "../Engines/Input/Input_Object.h"
#include "AssetList.h"
#include "SaveGameManager.h"
#include "point.h"

class Input_MissionSelect : public Input_Object
{
public:
	Input_MissionSelect(SaveGameManager *savedGames);
	~Input_MissionSelect();
	
	void TouchesBeganImpl(Touch &_touch);
	void TouchesMovedImpl(Touch &_touch);
	void TouchesEndedImpl(Touch &_touch);
	void Update(float time);
	void Render();
	void Reset(){};
	virtual void FreeResources();
	void SetPosition(int x, int y);
	bool StartLevel() const {return startLevel;}
	//void Temp(int _value) {temp = _value;}
	int LevelToStart() const {return levelToStart + 1;}
	//void Temp(int _value) {temp = _value;}
	
private:
	void RenderMissionInfo(int mission, int chptMod);

	HPTSprite1* levelSelectBaseSprite;
	HPTSprite1* levelSelectPushSprite;
	HPTSprite1* medalsSprite;
	HPTSprite1* chapterLabelsSprite;
	HPTSprite1* chapterTagsSprite;
	HPTSprite1* rightArrowSprite;
	HPTSprite1* leftArrowSprite;
	HPTSprite1* missionSelectIcons;
	HPTSprite1* comingSoonLevelCover;

	//SaveGameInfo saveGameInfo;
	SaveGameManager *savedGames;
	int touchID;
	
	// drag information
	bool isDragging;
	bool attemptedDrag;
	bool isDrifting;
	bool draggedRight;
	HPTPoint touchPos;
	
	int chapters;
	int currChapter;
	int focusedChapter;
	int chptWidth;
	
	// mission select location
	HPTPoint maxPos;
	HPTPoint minPos;
	HPTPoint stopPos;
	HPTPoint currPos;
	HPTPoint driftVel;
	
	bool startLevelTimer;
	bool startLevel;
	float timeToStart;
	int levelToStart;
};