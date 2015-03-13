/*
 *  Input_MissionSelect.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 1/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "Input_MissionSelect.h"
#include "math.h"
#include "AppConfig.h"

extern HPTGraphicsEngine *graphics_engine;

Input_MissionSelect::Input_MissionSelect(SaveGameManager *savedGames)
{
	this->levelSelectBaseSprite = graphics_engine->CreateSprite1();	
	this->levelSelectBaseSprite->SetImage(CR::AssetList::mission_select_level_select_base);
	if(AppConfig::Instance().IsIpad())
		levelSelectBaseSprite->SetDesignSize(156,254);

	this->levelSelectPushSprite = graphics_engine->CreateSprite1();	
	this->levelSelectPushSprite->SetImage(CR::AssetList::mission_select_level_select_push);
	if(AppConfig::Instance().IsIpad())
		levelSelectPushSprite->SetDesignSize(141,241);
	
	this->medalsSprite = graphics_engine->CreateSprite1();	
	this->medalsSprite->SetImage(CR::AssetList::mission_select_medals);
	if(AppConfig::Instance().IsIpad())
		medalsSprite->SetDesignSize(38,34);
	
	this->chapterLabelsSprite = graphics_engine->CreateSprite1();	
	this->chapterLabelsSprite->SetImage(CR::AssetList::mission_select_chapter_labels);
	if(AppConfig::Instance().IsIpad())
		chapterLabelsSprite->SetDesignSize(114,7);
	
	this->chapterTagsSprite = graphics_engine->CreateSprite1();	
	this->chapterTagsSprite->SetImage(CR::AssetList::mission_select_chapter_tags);
	if(AppConfig::Instance().IsIpad())
		chapterTagsSprite->SetDesignSize(296,24);
	
	this->rightArrowSprite = graphics_engine->CreateSprite1();
	this->rightArrowSprite->SetImage(CR::AssetList::menu_right_arrow_buttons);
	if(AppConfig::Instance().IsIpad())
		rightArrowSprite->SetDesignSize(27,35);

	this->leftArrowSprite = graphics_engine->CreateSprite1();
	this->leftArrowSprite->SetImage(CR::AssetList::menu_left_arrow_buttons);
	if(AppConfig::Instance().IsIpad())
		leftArrowSprite->SetDesignSize(27,35);
	
	this->missionSelectIcons = graphics_engine->CreateSprite1();
	this->missionSelectIcons->SetImage(CR::AssetList::mission_select_icons);
	if(AppConfig::Instance().IsIpad())
		missionSelectIcons->SetDesignSize(108,122);
	
	this->comingSoonLevelCover = graphics_engine->CreateSprite1();
	this->comingSoonLevelCover->SetImage(CR::AssetList::mission_select_coming_soon);
	if(AppConfig::Instance().IsIpad())
		comingSoonLevelCover->SetDesignSize(108,122);

	this->savedGames = savedGames;
	chptWidth = levelSelectBaseSprite->DesignWidth() * 3 + 10;
	if(AppConfig::Instance().IsIAd())
		chapters = 3;
	else
		this->chapters = 4;
	this->currChapter = 1;
	focusedChapter = 1;
	SetPosition(0, 0);
	isDragging = false;
	attemptedDrag = false;
	isDrifting = false;
	draggedRight = false;
	driftVel.x = 0;
	driftVel.y = 0;
	this->touchID = -1;
	
	startLevel = false;
	startLevelTimer = false;
	timeToStart = 0;
	levelToStart = 0;
}

void Input_MissionSelect::SetPosition(int x, int y)
{
	maxPos.x = x;
	maxPos.y = y;
	currPos.x = x;
	currPos.y = y;
	
	// calculate min position
	int chptMod = (chapters - 1) * 40;
	minPos.x = maxPos.x - (chptMod + ((chapters - 1) * 3 * (levelSelectBaseSprite->DesignWidth() - 10)));
	minPos.y = 0;
	stopPos.x = maxPos.x;// + chptWidth;
}


Input_MissionSelect::~Input_MissionSelect()
{
	this->levelSelectBaseSprite->Release();
	this->levelSelectPushSprite->Release();
	this->medalsSprite->Release();
	this->chapterLabelsSprite->Release();
	this->chapterTagsSprite->Release();
}

void Input_MissionSelect::FreeResources()
{
	
}

void Input_MissionSelect::TouchesBeganImpl(Touch &_touch)
{
	//for (UITouch *touch in touches)
	{
		if (this->touchID != -1 && _touch.ID != this->touchID)
			return;

		//CGPoint glLocation = GetGLLocation(view, touch);
		
		this->touchID = _touch.ID;
		
		isDragging = false;
		attemptedDrag = false;
		isDrifting = false;
		touchPos.x = _touch.X;
		touchPos.y = _touch.Y;
	}	
}

void Input_MissionSelect::TouchesMovedImpl(Touch &_touch)
{
	//for (UITouch *touch in touches)
	{
		if (this->touchID != -1 && _touch.ID != this->touchID)
			return;
		
		//CGPoint glLocation = GetGLLocation(view, touch);
		
		// Detect touch dragging distance
		float dX = _touch.X - touchPos.x;
		
		if (dX > 0)
			draggedRight = true;
		else
			draggedRight = false;
		
		if (isDragging || fabs(dX) > 3.0f)
		{
			// Update the current draw position
			currPos.x += dX;
			driftVel.x = dX;
			
			// Update the touch position
			touchPos.x = _touch.X;
			touchPos.y = _touch.Y;
			
			// user is dragging the levels
			isDragging = true;
			attemptedDrag = true;
			
			if (currPos.x > maxPos.x)
			{
				currPos.x = maxPos.x;
				isDragging = false;
			}
			else if (currPos.x < minPos.x)
			{
				currPos.x = minPos.x;
				isDragging = false;
			}
		}
	}
}

void Input_MissionSelect::TouchesEndedImpl(Touch &_touch)
{
	//for (UITouch *touch in touches)
	{
		if (_touch.ID == this->touchID)
		{
			this->touchID = -1;
			bool adjustStop = false;
			
			// if up from dragging the view
			if (isDragging)
			{
				isDragging = false;
				isDrifting = true;
				adjustStop = true;
			}
			else
			{
				// detect if user stopped the scroll
				// if so, scroll to nearest side
				if (currPos.x != stopPos.x)
				{
					if (stopPos.x > currPos.x) // drift right
						driftVel.x = 25;
					else // drift left
						driftVel.x = -25;
					
					isDrifting = true;
					adjustStop = false;
				}
			}

			// the user stopped the view in a drift, we need to float it back to the nearest locked position
			if (isDrifting && driftVel.x == 0)
			{
				if (!draggedRight)
					driftVel.x = -25;
				else if (draggedRight)
					driftVel.x = 25;
			}
			
			// adjusts the stop position for drifting
			if (adjustStop)
			{
				if (driftVel.x < 0) // drifting left
				{
					//stopPos.x = maxPos.x - (currChapter * chptWidth);
					stopPos.x = maxPos.x - ((focusedChapter+1) * chptWidth);
					if (stopPos.x < minPos.x)
						stopPos.x = minPos.x;
				}
				else if (driftVel.x > 0) // drifting right
				{
					//stopPos.x = maxPos.x - ((currChapter-2) * chptWidth);
					stopPos.x = maxPos.x - ((focusedChapter) * chptWidth);
					if (stopPos.x > maxPos.x)
						stopPos.x = maxPos.x;
				}
			}
			
			// detect button press here
			if (!isDrifting && !isDragging && !attemptedDrag)
			{
				// button press occured
				//CGPoint glLocation = GetGLLocation(view, touch);

				int chptMod = 0;
				Rect rect;
				for (int i = 0; i < 12; i++)
				{
					rect.top = currPos.y - levelSelectBaseSprite->DesignHeight()/2;
					rect.left = currPos.x + chptMod + (i * (levelSelectBaseSprite->DesignWidth() - 10)) - levelSelectBaseSprite->DesignWidth()/2 + 10;
					//rect.left = chptMod + (i * (levelSelectBaseSprite->GetFrameWidth() - 10));
					rect.bottom = currPos.y + levelSelectBaseSprite->DesignHeight()/2;
					rect.right = rect.left + levelSelectBaseSprite->DesignWidth();
					
					// detect level touch
					if (_touch.X > rect.left && _touch.X < rect.right &&
						_touch.Y > rect.top && _touch.Y < rect.bottom)
					{
						startLevelTimer = true;
						levelToStart = i;
						timeToStart = 0.5f;
					}
					
					// skip over 40 pixels every 3 chapters
					if ((i+1) % 3 == 0)
					{
						chptMod += 40;
					}
				}
			}
		}
	}
}

/*void Input_MissionSelect::TouchesCancelledImpl(UIView *view, NSSet *touches)
{
}*/

void Input_MissionSelect::Update(float time)
{
	// Determine the current chapter
	int diff = abs(maxPos.x - currPos.x);
	currChapter = diff / chptWidth;
	if (diff % chptWidth > chptWidth/2)
		currChapter++;
	currChapter++;
	
	// Determine the focused chapter
	focusedChapter = diff / (chptWidth);
	
	
	if (isDrifting)
	{
		currPos.x += driftVel.x;
		
		// drifting left
		if (currPos.x < stopPos.x && driftVel.x < 0)
		{
			currPos.x = stopPos.x;
			isDrifting = false;
		}
		else if (currPos.x > stopPos.x && driftVel.x > 0)
		{
			currPos.x = stopPos.x;
			isDrifting = false;
		}
	}
	
	if (startLevelTimer)
	{
		timeToStart -= time;
		int chptMod = 0;
		for (int i = 0; i < levelToStart; i++)
		{
			// skip over 40 pixels every 3 chapters
			if ((i+1) % 3 == 0)
			{
				chptMod += 40;
			}
		}
		
		if (timeToStart <= 0)
		{
#ifdef BOB_LITE
			if (levelToStart == 0)
				startLevel = true;
			else
			{
				//[[UIApplication sharedApplication] openURL:[[NSURL alloc]  initWithString: [NSString stringWithCString:"itms://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=308315671&mt=8"]]];
			}
#else
			if ((levelToStart+1) <= savedGames->GetSaveGameInfo().level)
				startLevel = true;
			else if (((levelToStart+1) == 10 && savedGames->IsBonusUnlocked(SaveGameManager::Bonus1)) || // TODO: Hack for bonus level loading
					 ((levelToStart+1) == 11 && false/*savedGames->IsBonusUnlocked(SaveGameManager::Bonus2)*/) ||
					 ((levelToStart+1) == 12 && false/*savedGames->IsBonusUnlocked(SaveGameManager::Bonus3)*/))
			{
				startLevel = true;
			}
#endif
		}
		
		levelSelectPushSprite->SetPositionAbsalute(currPos.x + chptMod + (levelToStart * (levelSelectBaseSprite->DesignWidth() - 10)), currPos.y - 6);
		levelSelectPushSprite->SetFrame(0);
	}
}

void Input_MissionSelect::Render()
{
	// Draw label for currently focused chapter
	if(AppConfig::Instance().IsIpad())
		chapterTagsSprite->SetPositionAbsalute(320, 32);
	else
		chapterTagsSprite->SetPositionAbsalute(365, 32);
	chapterTagsSprite->SetFrameSet(currChapter-1);
	//chapterTagsSprite->SetFrameSet(focusedChapter);
	chapterTagsSprite->Render();
	int chptMod = 0;
	
	int rightScreenHackArrow = 12;
	if(AppConfig::Instance().IsIAd())
		rightScreenHackArrow = 9;

	for (int i = 0; i < 12; i++)
	{
		if ((i+1) % 3 == 0)
		{
			// Render arrows
			if (i+1 == 3) // special case, left screen
			{
				rightArrowSprite->SetPositionAbsalute(currPos.x + chptMod + (i * (levelSelectBaseSprite->DesignWidth() - 10)) + 80, currPos.y);
				rightArrowSprite->Render();
			}
			else if ( i+1 == rightScreenHackArrow) // special case, right screen
			{
				leftArrowSprite->SetPositionAbsalute(currPos.x + chptMod + (i * (levelSelectBaseSprite->DesignWidth() - 10)) - 374, currPos.y);
				leftArrowSprite->Render();
			}
			else // all center screens
			{
				leftArrowSprite->SetPositionAbsalute(currPos.x + chptMod + (i * (levelSelectBaseSprite->DesignWidth() - 10)) - 374, currPos.y);
				leftArrowSprite->Render();
				rightArrowSprite->SetPositionAbsalute(currPos.x + chptMod + (i * (levelSelectBaseSprite->DesignWidth() - 10)) + 80, currPos.y);
				rightArrowSprite->Render();
			}
		}
		
		levelSelectBaseSprite->SetPositionAbsalute(currPos.x + chptMod + (i * (levelSelectBaseSprite->DesignWidth() - 10)) - 1, currPos.y);
		//levelSelectBaseSprite->SetFrame(0);
		levelSelectBaseSprite->Render();
		
#ifdef BOB_LITE
		if (i < 1)
#else
		if (i < savedGames->GetSaveGameInfo().level)
#endif
		{
			RenderMissionInfo(i, chptMod);
		}
		
		// TODO: HACK! - Shows Available Bonus Level Overlays
		if (i == 9 && savedGames->IsBonusUnlocked(SaveGameManager::Bonus1))
		{
			RenderMissionInfo(i, chptMod);
		}
		else if (i == 10 && savedGames->IsBonusUnlocked(SaveGameManager::Bonus2))
		{
			RenderMissionInfo(i, chptMod);
		}
		else if (i == 11 && savedGames->IsBonusUnlocked(SaveGameManager::Bonus3))
		{
			RenderMissionInfo(i, chptMod);
		}

		// TODO: HACK! - Shows "Coming Soon" on Unavailable levels!
		if (i >= 10)
		{
			comingSoonLevelCover->SetPositionAbsalute(currPos.x + chptMod + (i * (levelSelectBaseSprite->DesignWidth() - 10)), currPos.y-24);
			comingSoonLevelCover->Render();
		}

		// render achievement medals
		for (int j = 0; j < 3; j++)
		{
			if ( (j == 0 && savedGames->GetSaveGameInfo().levelInfo[i].bronzeAchievement) ||
				 (j == 1 && savedGames->GetSaveGameInfo().levelInfo[i].silverAchievement) ||
				 (j == 2 && savedGames->GetSaveGameInfo().levelInfo[i].goldAchievement))
			{
				int xPlot = (currPos.x - 41) + (j * 41) + (i * 146) + chptMod;
				if(AppConfig::Instance().IsIpad())
					medalsSprite->SetPositionAbsalute(xPlot-1, currPos.y + 78);
				else
					medalsSprite->SetPositionAbsalute(xPlot, currPos.y + 79);
				medalsSprite->SetFrameSet(j);
				medalsSprite->Render();
			}
		}
		
		// skip over 40 pixels every 3 chapters and render arrows
		if ((i+1) % 3 == 0)
		{			
			chptMod += 40;
		}
	}
	
	if (startLevelTimer)
	{
		levelSelectPushSprite->Render();
	}
}

void Input_MissionSelect::RenderMissionInfo(int mission, int chptMod)
{
	missionSelectIcons->SetFrameSet(mission);
	missionSelectIcons->SetPositionAbsalute(currPos.x + chptMod + (mission * (levelSelectBaseSprite->DesignWidth() - 10)) + 1, currPos.y-24);
	missionSelectIcons->Render();
			
	chapterLabelsSprite->SetFrameSet(mission);
	chapterLabelsSprite->SetPositionAbsalute(currPos.x + chptMod + (mission * (levelSelectBaseSprite->DesignWidth() - 10)) - 1, currPos.y-102);
	chapterLabelsSprite->Render();
}