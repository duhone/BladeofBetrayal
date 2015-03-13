/*
 *  Input_WeaponSelect.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 1/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Input_WeaponSelect.h"
#include "AssetList.h"
#include "AppConfig.h"
#include "Game.h"

extern HPTGraphicsEngine *graphics_engine;

extern Game* game_class;

Input_WeaponSelect::Input_WeaponSelect(Player *player)
{
	this->player = player;
	this->weaponIconsSprite = graphics_engine->CreateSprite1();	
	this->weaponIconsSprite->SetImage(CR::AssetList::hud_weapon_icons);
	if(AppConfig::Instance().IsIpad())
		weaponIconsSprite->SetDesignSize(46,38);
		
	this->grenadeIconSprite = graphics_engine->CreateSprite1();
	this->grenadeIconSprite->SetImage(CR::AssetList::icon_grenade);
	if(AppConfig::Instance().IsIpad())
		grenadeIconSprite->SetDesignSize(8,8);
	SetPosition(0, 0, 0);
	currWeapon = 0;
	isDown = false;
	touchID = -1;
	boundFuzz = 0;
}

Input_WeaponSelect::~Input_WeaponSelect()
{
	FreeResources();
}

int Input_WeaponSelect::GetSelectedWeapon(int _x,int _y)
{
	if(_y >= 270 && _y <= 318 && _x >= 144 && _x <= 328)
	{
		_x -= 144;
		_x /= 46;
		return _x;
	}
	else
		return -1;
}

void Input_WeaponSelect::TouchesBeganImpl(Touch &_touch)
{
	if(game_class->IsInTransition())
		return;
	if(AppConfig::Instance().IsIpad())
	{
		int weapon = GetSelectedWeapon(_touch.X,_touch.Y);
		if(weapon == -1)
			return;
		player->SetAttack(weapon+1);
	}
	else
	{
		//CGPoint glLocation;
		//for (UITouch *touch in touches)
		{
			if (this->touchID != -1 && _touch.ID != this->touchID)
				return;
			
			//glLocation = GetGLLocation(view, touch);
			
			if (_touch.X > bounds.left - boundFuzz && 
				_touch.X < bounds.right + boundFuzz &&
				_touch.Y > bounds.top - boundFuzz &&
				_touch.Y < bounds.bottom + boundFuzz)
			{
				this->touchID = _touch.ID;
				isDown = true;
			}
			else
			{
				isDown = false;
			}
		}	
	}
}

void Input_WeaponSelect::TouchesMovedImpl(Touch &_touch)
{
	if(game_class->IsInTransition())
		return;
	if (this->touchID != -1 && _touch.ID != this->touchID)
		return;
	if(AppConfig::Instance().IsIpad())
	{
		int weapon = GetSelectedWeapon(_touch.X,_touch.Y);
		if(weapon == -1)
			return;
		player->SetAttack(weapon+1);
	}
	else
	{
		//CGPoint glLocation;
		//for (UITouch *touch in touches)
		{
			//if (this->touchID != -1 && _touch.ID != this->touchID)
			//	return;
			
			//glLocation = GetGLLocation(view, touch);
			
			if (_touch.X > bounds.left - boundFuzz && 
				_touch.X < bounds.right + boundFuzz &&
				_touch.Y > bounds.top - boundFuzz &&
				_touch.Y < bounds.bottom + boundFuzz)
			{
				isDown = true;
				this->touchID = _touch.ID;
			}
			else
			{
				isDown = false;
			}
		}
	}
}

void Input_WeaponSelect::TouchesEndedImpl(Touch &_touch)
{
	if(game_class->IsInTransition())
		return;
	//for (UITouch *touch in touches)
	{
		if (_touch.ID == this->touchID)
		{
			if (isDown)
			{
				// Change to the next weapon
			player->SetAttack(player->GetAttack()+1);			}
			
			isDown = false;
			this->touchID = -1;
			//break;
		}
	}
}

void Input_WeaponSelect::Reset()
{
}

void Input_WeaponSelect::Update(float time)
{
	weaponIconsSprite->SetFrameSet(player->GetAttack() - 1);
}

void Input_WeaponSelect::SetPosition(float x, float y, int boundFuzz)
{
	pos.x = x;
	pos.y = y;
	
	//set the bounds
	Rect r;
	r.top = y - weaponIconsSprite->GetFrameHeight()/2 ;
	r.left = x -  weaponIconsSprite->GetFrameWidth()/2;
	r.bottom = r.top + weaponIconsSprite->GetFrameHeight();
	r.right = r.left + weaponIconsSprite->GetFrameWidth();
	bounds = r;
	this->boundFuzz = boundFuzz;
	// update the position of the sprite
	weaponIconsSprite->SetPositionAbsalute(pos.x, pos.y);
}

void Input_WeaponSelect::Render()
{
	if(AppConfig::Instance().IsIpad())
	{
		int xPos = 10;
		int yPos = 44;
		
		for (int i = 1; i <= player->GetGrenades(); i++)
		{
			grenadeIconSprite->SetPositionAbsalute(xPos, yPos);
			grenadeIconSprite->Render();
			xPos += 8;
		}

		xPos = 167;
		yPos = 293;
		for(int i = 0;i < 4;i++)
		{
			weaponIconsSprite->SetFrameSet(i);
			if(player->GetAttack() - 1 == i)
				weaponIconsSprite->SetFrame(1);
			else
			{
				SaveGameInfo saveInfo = game_class->GetSaveGameManager()->GetSaveGameInfo();

				//if(saveInfo.weapons[i+1] == true)
				if(player->IsWeaponAvailable(i+1))
					weaponIconsSprite->SetFrame(2);
				else
					weaponIconsSprite->SetFrame(0);
			}
			weaponIconsSprite->SetPositionAbsalute(xPos,yPos);
			weaponIconsSprite->Render();

			xPos += 46;
		}
	}
	else
	{
		if (player->GetAttack() > 0)
			weaponIconsSprite->Render();
		
		// draw grenade icons for available grenades, 5 per row
		int xPos = bounds.left + 6;
		int yPos;
		
		if (player->GetAttack() > 0)
			yPos = bounds.bottom + 5;
		else
			yPos = bounds.top + 6;
		
		for (int i = 1; i <= player->GetGrenades(); i++)
		{
			grenadeIconSprite->SetPositionAbsalute(xPos, yPos);
			grenadeIconSprite->Render();
			
			if (i % 5 == 0)
			{
				yPos += grenadeIconSprite->GetFrameHeight() + 1;
				xPos = bounds.left + 6;
			}
			else
				xPos += grenadeIconSprite->GetFrameWidth() + 1;
		}
	}
}

void Input_WeaponSelect::FreeResources()
{
	weaponIconsSprite->Release();
	grenadeIconSprite->Release();
}