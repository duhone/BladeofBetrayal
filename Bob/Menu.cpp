#include "Menu.h"
#include "../Engines/Graphics/HPTGraphics.h"
#include "math.h"
#include "../Engines/Input/input_engine.h"
#include <string.h>
#include <stdio.h>
#include "AssetList.h"
#include "MusicManager.h"
#include "AssetListNew.h"
#include "SpecialsMenuPage.h"

extern HPTGraphicsEngine *graphics_engine;
extern Input_Engine   *input_engine;

Menu::Menu(SaveGameManager *sarg)//:mapping_key(false)
{
	// Set the initial menu state
	currentMenuPage = NULL;
	ChangeState(menu_main);
	
	game= 0;
	saved_games = sarg;
	startLevel = 0;
	canResume = false;
}

Menu::~Menu()
{
	// Menu Pages
	delete currentMenuPage;
}

void Menu::ChangeState(MENU_STATE newState)
{	
	stateChanged = true;
	ActiveMState = newState;
}

void Menu::Update(float time)
{
	if(!game)
		return;
	if (!stateChanged)
	{
		if (currentMenuPage != NULL)
			currentMenuPage->Update(time);
		
		return;
	}
	
	stateChanged = false;
	
	// delete the previous menu page from memory
	if (currentMenuPage != NULL)
	{
		if(background)
			background->Release();
		background = NULL;
		delete currentMenuPage;
		currentMenuPage = NULL;
	}
	
	// change the active menu state
	switch (ActiveMState)
	{
		case menu_main:
			SetCurrentMenuPage(new MainMenuPage(this, saved_games));
			break;
		case menu_resume_game:
			//game->StartGame(saved_games->GetSaveGameInfo().level);
			game->Resume();
			break;
		case menu_start_game:
			game->StartGame(startLevel, false);
			break;
		case menu_mission_select:
			SetCurrentMenuPage(new MissionSelectMenuPage(this, saved_games));
			break;
		case menu_options:
			SetCurrentMenuPage(new OptionsMenuPage(this, saved_games));
			break;
		case menu_about:
			SetCurrentMenuPage(new AboutMenuPage(this, saved_games));
			break;
		case menu_instructions:
			SetCurrentMenuPage(new InstructionsMenuPage(this, saved_games));
			break;
		case menu_specials:
			SetCurrentMenuPage(new SpecialsMenuPage(this, saved_games));
			break;
		default:
			break;
	}
}

void Menu::Render()
{
	if (currentMenuPage != NULL)
		currentMenuPage->Render();
}

void Menu::RestartMenu(IGame *arg, bool canResume, SaveGameManager *sarg)
{	
	saved_games = sarg;
	ChangeState(menu_main);
	game = arg;
	this->canResume = canResume;
	
	MusicManager::Instance().PlaySong(MusicManager::TitleTheme);
//	musicPlayer->ChangeSong(MUSIC_TITLE, MUSIC_CUTSCENE);
//	musicPlayer->Play();
}

void Menu::ReplayIntro()
{
	game->ReplayIntro();
}

// *** Menu Pages ***
void Menu::SetCurrentMenuPage(IMenuPage *menuPage)
{
	//if (currentMenuPage == menuPage)
	//	return;
	
	currentMenuPage = menuPage;
	
	// Set the background image for this page
	background = graphics_engine->CreateHPTBackground();
	background->SetImage(currentMenuPage->GetBackgroundImage());
	graphics_engine->SetBackgroundImage(background);
	
	// Register this page as the current input controller
	input_engine->RegisterInputController(currentMenuPage);
}

void Menu::SetStartLevel(int level)
{
	startLevel = level;
}
