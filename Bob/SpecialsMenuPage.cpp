#include "SpecialsMenuPage.h"
#include "menu.h"
#include "AssetList.h"
#include "MusicManager.h"
#include "Sound.h"
#include "AppConfig.h"
#include "Game.h"

extern HPTGraphicsEngine *graphics_engine;
extern Game* game_class;

SpecialsMenuPage::SpecialsMenuPage(Menu *menu, SaveGameManager *savedGames) : IMenuPage(menu)
{
	this->menu = menu;
	this->savedGames = savedGames;

	this->backButton = new Input_Button();
	if(AppConfig::Instance().IsIpad())
		backButton->SetSpriteAndBounds(12, 15, CR::AssetList::specials_backButton);
	else
		backButton->SetSpriteAndBounds(12, 11, CR::AssetList::specials_backButton);
	if(AppConfig::Instance().IsIpad())
		backButton->DesignSize(69,30);
	backButton->SetSoundOn(true);
	input_objects.push_back(backButton);

	showSelectionSprite = false;
	selectionSprite = graphics_engine->CreateSprite1();
	selectionSprite->SetImage(CR::AssetList::specials_selector);
	if(AppConfig::Instance().IsIpad())
		selectionSprite->SetDesignSize(456,31);

	medalFontSprite = graphics_engine->CreateSprite1();
	medalFontSprite->SetImage(CR::AssetList::SpecialMedalFont);
	if(AppConfig::Instance().IsIpad())
		medalFontSprite->SetDesignSize(12,11);

	// Survival Run (Unlocked)
	survivalRunUnlockedSprite = graphics_engine->CreateSprite1();
	survivalRunUnlockedSprite->SetPositionAbsalute(10,10);
	survivalRunUnlockedSprite->SetImage(CR::AssetList::specials_lockedUnlockedTag);
	this->showSurvivalRunUnlockedSprite = savedGames->GetSaveGameInfo().bonusInfo.BonusLevel1;
	if(AppConfig::Instance().IsIpad())
		survivalRunUnlockedSprite->SetDesignSize(98,8);

	// Speed Boost (Toggle)
	speedBoostToggle = new Input_Toggle();
	speedBoostToggle->SetSprite(CR::AssetList::options_on_off);
	if(AppConfig::Instance().IsIpad())
		speedBoostToggle->SetPosition(417, 103);
	else
		speedBoostToggle->SetPosition(407, 105);
	speedBoostToggle->SetTouchBounds(0, 91, 480, 30);
	speedBoostToggle->OnToggled += Delegate(this, &SpecialsMenuPage::OnToggledSpeedBoost);
	speedBoostToggle->ToggleOn(savedGames->GetSaveGameInfo().bonusToggles[1]);
	speedBoostToggle->SetSoundOn(true);
	if(AppConfig::Instance().IsIpad())
		speedBoostToggle->DesignSize(65,10);
	input_objects.push_back(speedBoostToggle);

	//gamerGirlToggle = new Input_Toggle();
	//gamerGirlToggle->SetSprite(CR::AssetList::options_on_off);
	//gamerGirlToggle->SetPosition(405, 300);
	//gamerGirlToggle->SetTouchBounds(360, 115, 90, 58);
	//gamerGirlToggle->OnToggled += Delegate(this, &SpecialsMenuPage::OnToggledGamerGirl);
	//gamerGirlToggle->ToggleOn(settingsInfo.musicOn);
	//gamerGirlToggle->SetSoundOn(true);
	//input_objects.push_back(gamerGirlToggle);
}

SpecialsMenuPage::~SpecialsMenuPage()
{
	delete speedBoostToggle;
	//delete gamerGirlToggle;
	delete backButton;
	selectionSprite->Release();
	survivalRunUnlockedSprite->Release();
	medalFontSprite->Release();
}

int SpecialsMenuPage::GetBackgroundImage() const
{
	return CR::AssetList::specials_menuBase;
}

void SpecialsMenuPage::Update(float time)
{
	speedBoostToggle->Update(time);
}

void SpecialsMenuPage::Render()
{
	backButton->Render();

	//gamerGirlToggle->Render();

	if (showSelectionSprite)
		selectionSprite->Render();

	const bool requiresToggle[] = {false,true,false,false,false,false,false};

	for(int i = 0;i < 7;++i)
	{
		if(AppConfig::Instance().IsIpad())
		{
			if(i<4)
				survivalRunUnlockedSprite->SetPositionAbsalute(415,68+35*i+(i==0?1:0));
			else
				survivalRunUnlockedSprite->SetPositionAbsalute(415,67+35*i);
		}
		else
			survivalRunUnlockedSprite->SetPositionAbsalute(405,72+35*i+(i==0?1:0));
		if(savedGames->IsBonusUnlocked(static_cast<SaveGameManager::Unlockables>(i)))
		{
			survivalRunUnlockedSprite->SetFrameSet(1);
			if(requiresToggle[i])
			{
				if(i == 1)
					speedBoostToggle->Render();
			}
			else
				survivalRunUnlockedSprite->Render();
		}
		else
		{
			survivalRunUnlockedSprite->SetFrameSet(0);
			survivalRunUnlockedSprite->Render();
		}
	}
	//graphics_engine->Position(425,35);
	//(*graphics_engine) << game_class->gothic12 << savedGames->GetSaveGameInfo().AchievmentCount();

	int xcoord = 385;
	if(AppConfig::Instance().IsIpad())
		xcoord = 392;

	int achievmentCount = savedGames->GetSaveGameInfo().AchievmentCount();
	int number = achievmentCount/10;
	if(number != 0)
	{
		medalFontSprite->SetPositionAbsalute(xcoord,32);
		medalFontSprite->SetFrameSet(number);
		medalFontSprite->Render();
	}
	xcoord += 12;
	number = achievmentCount%10;
	medalFontSprite->SetPositionAbsalute(xcoord,32);
	medalFontSprite->SetFrameSet(number);
	medalFontSprite->Render();
	xcoord += 12;
	medalFontSprite->SetPositionAbsalute(xcoord,32);
	medalFontSprite->SetFrameSet(10);
	medalFontSprite->Render();
	xcoord += 12;
	medalFontSprite->SetPositionAbsalute(xcoord,32);
	medalFontSprite->SetFrameSet(3);
	medalFontSprite->Render();
	xcoord += 12;
	medalFontSprite->SetPositionAbsalute(xcoord,32);
	medalFontSprite->SetFrameSet(0);
	medalFontSprite->Render();
}

void SpecialsMenuPage::InputChanged()
{
	if (backButton->WasPressed())
	{
		menu->ChangeState(menu_mission_select);
	}

	if (speedBoostToggle->IsDown())
	{
		showSelectionSprite = true;
		if(AppConfig::Instance().IsIpad())
			selectionSprite->SetPositionAbsalute(240, 104);
		else
			selectionSprite->SetPositionAbsalute(238, 108);
	}
	//else if (gamerGirlToggle->IsDown())
	//{
	//	showSelectionSprite = true;
	//	selectionSprite->SetPositionAbsalute(276, 142);
	//}
}

void SpecialsMenuPage::OnToggledSpeedBoost()
{
	// toggle speed boost in the save game file
	savedGames->SetUnlockToggle(SaveGameManager::SpencerBoost,speedBoostToggle->IsToggleOn());
}

//void SpecialsMenuPage::OnToggledGamerGirl()
//{
//}
//
//void SpecialsMenuPage::OnToggledMachineGun()
//{
//}
//
//void SpecialsMenuPage::OnToggledInfinityBlade()
//{
//}