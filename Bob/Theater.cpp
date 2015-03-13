// Theater.cpp: implementation of the Theater class.
//
//////////////////////////////////////////////////////////////////////


#include "Theater.h"
#include "game.h"
#include "AssetList.h"
#include "Sound.h"
#include "MusicManager.h"
#include "AssetListNew.h"
#include "AppConfig.h"

//#include <UIKit/UIKit.h>

using namespace CR;
using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HPTGraphicsEngine *graphics_engine;
///extern HPTSoundEngine* sound_engine;
extern Input_Engine   *input_engine;
//extern CRMusicPlayer *musicPlayer;
extern Game* game_class;

extern char path[256];
extern char *hptstrcat(char *x,char *y);

Theater::Theater()
{
	done = true;
	scene_timer = 1;
	movie_sprite = graphics_engine->CreateSprite1();
	movie_sprite1 = graphics_engine->CreateSprite1();
	movie_sprite2 = graphics_engine->CreateSprite1();
	movie_sprite3= graphics_engine->CreateSprite1();
	movie_sprite4 = graphics_engine->CreateSprite1();
	movie_sprite5 = graphics_engine->CreateSprite1();
	movie_sprite6 = graphics_engine->CreateSprite1();
	movie_sprite7 = graphics_engine->CreateSprite1();
	movie_sprite8 = graphics_engine->CreateSprite1();
	movie_sprite9 = graphics_engine->CreateSprite1();
	movie_sprite10 = graphics_engine->CreateSprite1();
	movie_sprite11 = graphics_engine->CreateSprite1();

	background = graphics_engine->CreateHPTBackground();
	
	// Create the Skip Movie Button
	skipMovieButton = new Input_Button();
	skipMovieButton->SetButtonBounds(0, 0, 480, 320);
	skipMovieButton->OnClicked += Delegate(this,&Theater::StopMovie);
	skipMovieButton->Disabled(true);
	skipMovieButton->SetSoundOn(true);
	input_objects.push_back(skipMovieButton);
	
	prevMovieButton = new Input_Button();
	prevMovieButton->SetButtonBounds(0, 0, 480, 320);
	prevMovieButton->OnClicked += Delegate(this,&Theater::OnPrev);
	prevMovieButton->Disabled(true);
	prevMovieButton->SetSoundOn(true);
	input_objects.push_back(prevMovieButton);
	
	nextMovieButton = new Input_Button();
	nextMovieButton->SetButtonBounds(0, 0, 480, 320);
	nextMovieButton->OnClicked += Delegate(this,&Theater::OnNext);
	nextMovieButton->Disabled(true);
	nextMovieButton->SetSoundOn(true);
	input_objects.push_back(nextMovieButton);
	
#ifdef BOB_LITE
	buyGameScreenTime = 0;
	
	buyGameButton = new Input_Button();
	buyGameButton->SetSpriteAndBounds(250, 210, CR::AssetList::buy_button_2);
	//buyGameButton->OnClicked += Delegate(this,&Theater::OnBuyGame);
	buyGameButton->Disabled(true);
	buyGameButton->SetSoundOn(true);
	input_objects.push_back(buyGameButton);
	
	returnToMenuButton = new Input_Button();
	returnToMenuButton->SetSpriteAndBounds(20, 210, CR::AssetList::return_to_menu_button);
	//buyGameButton->OnClicked += Delegate(this,&Theater::OnBuyGame);
	returnToMenuButton->Disabled(true);
	returnToMenuButton->SetSoundOn(true);
	input_objects.push_back(returnToMenuButton);
	
#endif
	
}

Theater::~Theater()
{
	movie_sprite->Release();
	movie_sprite2->Release();
	movie_sprite3->Release();
	if(background)
		background->Release();
	delete skipMovieButton;
	delete prevMovieButton;
	delete nextMovieButton;
}

void Theater::OnNext()
{
	if(current_scene < (scenes.size() - 1))
		current_scene++;
}

void Theater::OnPrev()
{
	if(current_scene>0)
		current_scene--;
}

/*#ifdef BOB_LITE

void Theater::OnBuyGame()
{
	[[UIApplication sharedApplication] openURL:[[NSURL alloc]  initWithString: [NSString stringWithCString:"itms://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=308315671&mt=8"]]];
}

#endif*/

void Theater::InputChanged()
{
#ifdef BOB_LITE
	if (current_movie == 2)
	{
		if (buyGameButton->WasPressed())
		{
			[[UIApplication sharedApplication] openURL:[[NSURL alloc]  initWithString: [NSString stringWithCString:"itms://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=308315671&mt=8"]]];
		}
		else if (returnToMenuButton->WasPressed())
		{
			StopMovie();
		}
	}
#endif
}

void Theater::StartMovie(int arg)
{
	input_engine->RegisterInputController(this);
	done_b = false;
	next_b = false;
	prev_b = false;
	if(arg > 17) arg = 17;
	done = false;
	current_movie = arg;
	current_scene = 0;
	
	black_font = graphics_engine->CreateFont1();	
	/*NSString * path1 = [[NSBundle mainBundle] pathForResource:  @"arial20" ofType: @"HFF"];
	const char *blackfont = [path1 cStringUsingEncoding:1];
	black_font->LoadHFFFont(const_cast<char*>(blackfont));*/
	black_font->LoadHFFFont("arial20.HFF");
	
	white_font = graphics_engine->CreateFont1();	
	/*path1 = [[NSBundle mainBundle] pathForResource:  @"arial20w" ofType: @"HFF"];
	const char *whitefont = [path1 cStringUsingEncoding:1];
	white_font->LoadHFFFont(const_cast<char*>(whitefont));*/
	white_font->LoadHFFFont("arial20w.HFF");
	
	background = graphics_engine->CreateHPTBackground();
	switch(arg)
	{
	case 0:
		current_image = 0;
		max_scene = 1;
		time_to_go = 3.0f;
		set_time = 1.5f;
			
		background->SetImage(AssetList::splash_screen_01);
		graphics_engine->SetBackgroundImage(background);
			
		skipMovieButton->SetButtonBounds(0, 0, 480, 320);
		skipMovieButton->SetSoundOn(false);
		skipMovieButton->Disabled(false);

//		sound_engine->LoadHSF(hptstrcat(path, ("sounds//intro.hsf")), 1);
//		music = sound_engine->CreateSoundObject(0, 1);

//		if((music != 0) && (game->mute_music != true)) music->HPTPlaySound();
		break;
	case 1:
		CreateScene1a();
			//CreateSceneFinal();
		break;
	case 2:
#ifdef BOB_LITE
		CreateSceneLite();
#else
		CreateScene1b();
#endif
		break;
	case 3:
		CreateScene1c();
		break;
	case 4:
		CreateScene2a();
		break;
	case 5:
		CreateScene2b();
		break;
	case 6:
		CreateScene2c();
		break;
	case 7:
		CreateScene3a();
		break;
	case 8:
		CreateScene3b();
		break;
	case 9:
		CreateScene3c();
		break;
	case 10:
		CreateSceneFinal();
		break;
	case 11:
		CreateSceneBonus1();
		break;
	}
	if(arg >= 1)
	{
		background->SetImage(scenes[current_scene].background);
		graphics_engine->SetBackgroundImage(background);
		
		if(AppConfig::Instance().IsIpad())
			skipMovieButton->SetSpriteAndBounds(192, 274, AssetList::button_skip);
		else
			skipMovieButton->SetSpriteAndBounds(210, 279, AssetList::button_skip);
		skipMovieButton->SetSoundOn(true);
		skipMovieButton->Disabled(false);
		if(AppConfig::Instance().IsIpad())
			skipMovieButton->DesignSize(96,47);
		
		if(AppConfig::Instance().IsIpad())
			prevMovieButton->SetSpriteAndBounds(104, 274, AssetList::button_previous);
		else
			prevMovieButton->SetSpriteAndBounds(5, 279, AssetList::button_previous);
		prevMovieButton->SetSoundOn(true);
		prevMovieButton->Disabled(true);
		if(AppConfig::Instance().IsIpad())
			prevMovieButton->DesignSize(78,47);
		
		if(AppConfig::Instance().IsIpad())
			nextMovieButton->SetSpriteAndBounds(298, 274, AssetList::button_next);
		else
			nextMovieButton->SetSpriteAndBounds(420, 279, AssetList::button_next);
		nextMovieButton->SetSoundOn(true);
		nextMovieButton->Disabled(false);
		if(AppConfig::Instance().IsIpad())
			nextMovieButton->DesignSize(78,47);
		
		if (arg == 10)
		{
			MusicManager::Instance().PlaySong(MusicManager::Finale);
//			musicPlayer->ChangeSong(MUSIC_CREDITS);
		}
		else
		{
			MusicManager::Instance().PlaySong(MusicManager::Cutscene);
//			musicPlayer->ChangeSong(MUSIC_CUTSCENE);
		}
		
//		musicPlayer->Play();
	}


	text_dialog_sprite = graphics_engine->CreateSprite1();
	text_dialog_sprite->SetImage(AssetList::cutscene_text_box);
	text_dialog_sprite->SetFrame(0);
	text_dialog_sprite->SetPositionAbsalute(240,160);
	if(AppConfig::Instance().IsIpad())
		text_dialog_sprite->SetDesignSize(323,105);
	char_dialog_sprite_top = graphics_engine->CreateSprite1();
	char_dialog_sprite_top->SetImage(AssetList::cutscene_balloon);
	char_dialog_sprite_top->SetFrame(0);
	char_dialog_sprite_top->SetPositionAbsalute(165,50);
	if(AppConfig::Instance().IsIpad())
		char_dialog_sprite_top->SetDesignSize(336,100);
	char_dialog_sprite_bot = graphics_engine->CreateSprite1();
	char_dialog_sprite_bot->SetImage(AssetList::cutscene_balloon);
	char_dialog_sprite_bot->SetFrame(0);
	char_dialog_sprite_bot->SetPositionAbsalute(75,250);
	if(AppConfig::Instance().IsIpad())
	{
		char_dialog_sprite_bot->SetDesignSize(336,100);
	}
		
}

void Theater::Update(float time)
{
#ifdef BOB_LITE
	if (current_movie == 2)
	{
		buyGameScreenTime -= time;
	}
#endif
	
	this->time = time;
	if(done) return;
	time_to_go -= time;
	switch(current_movie)
	{
	case 0:
		switch(current_image)
		{
		case 0:
			if(time_to_go <= 0)
			{
				time_to_go = 32.0f;
				current_image++;
				loc1 = 340.0f;
				loc2 = 0;
			}
			break;
		case 1:
//			if((music != 0) && (game->mute_music != true)) music->HPTStopSound();
			done = true;
			break;

		}
		break;

/*	case 16:

		scene_timer -= time;

		if(scene_timer < 0)
		{
			if(current_image == 26) return;
			current_image++;
			switch(current_image)
			{
			case 0:
				scene_timer = 5;
				break;
			case 1:
				scene_timer = 5;
				break;
			case 2:
				scene_timer = 5;
				break;
			case 3:
				scene_panning = 0;
				scene_timer = 10;
				break;
			case 4:
				scene_timer = 10;
				break;
			case 5:
				scene_timer = 5;
				break;
			case 6:
				movie_sprite5->SetFrameRate(1);
				movie_sprite5->SetAutoAnimate(true);
				movie_sprite5->AutoStopAnimate();
				scene_timer = 5;
				break;
			case 7:
				scene_timer = 5;
				break;
			case 8:
				scene_timer = 5;
				break;
			case 9:
				scene_timer = 5;
				break;
			case 10:
				scene_timer = 5;
				break;
			case 11:
				scene_timer = 10;
				break;
			case 12:
				scene_panning = 0;
				scene_timer = 38;
				break;
			case 13:
				scene_timer = 5;
				break;
			case 14:
				scene_timer = 5;
				break;
			case 15:
				scene_timer = 5;
				break;
			case 16:
				scene_timer = 5;
				break;
			case 17:
				scene_timer = 5;
				break;
			case 18:
				scene_timer = 5;
				break;
			case 19:
				scene_timer = 5;
				break;
			case 20:
				scene_timer = 5;
				break;
			case 21:
				scene_timer = 5;
				break;
			case 22:
				scene_timer = 5;
				break;
			case 23:
				scene_timer = 5;
				break;
			case 24:
				scene_timer = 5;
				break;
			case 25:
				scene_panning = 10;
				scene_timer = 14;
				break;
			case 26:
				scene_panning = 0;
				scene_timer = 100;
//				sound_engine->LoadHSF(hptstrcat(path, ("sounds//level1c-m.hsf")), 1);
//				music = sound_engine->CreateSoundObject(0, 1);
//				if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);
				break;

			};
		};
		break;*/

	default:
		background->SetImage(scenes[current_scene].background);
		break;
	}
}

void Theater::Render()
{
	if(done) return;
	switch(current_movie)
	{
	case 0:
		switch(current_image)
		{
		case 0:
		case 1:
			//movie_sprite->SetPositionAbsalute(0,0);
			//movie_sprite->SetFrame(0);
			//movie_sprite->Render();

			//graphics_engine->Position(120,90);
			//(*graphics_engine) << black_font << "HPT Interactive";
			break;
		/*case 1:
			movie_sprite->SetPositionAbsalute(480-loc2,160);
			movie_sprite->SetFrame(0);
			movie_sprite->Render();
			movie_sprite1->SetPositionAbsalute(240,160);
			//movie_sprite1->Render();
			graphics_engine->Position(25,(int)loc1);
			(*graphics_engine) << white_font << "It is the near future...\n\n  Two weapon manufacturers struggle"
    << "\nto become the favored supplier to\nthe government...\n\n"
    << "  NagolaCorp, headed by Suke Hato\ndeals with chemical and biological\nweapons...\n\n"
    << "  Fortified Industries, owned and\ncontrolled by James and Jacob\nCorinth produces traditional arms...\n\n"
    << "  The government comes to favor \nFortified Industries and NagolaCorp\nis threatened with bankruptcy...\n\n"
    << "  Desperate, Suke Hato attempts to\nform a partnership with the Corinth\nbrothers but he fails...\n\n"
    << "  James ends up dead, his murderer\nunknown...\n\n"
    << "  Spencer Corinth, the only son of\nJames, vows to uncover those guilty\nand avenge his father...";
			break;
		case 2:
			movie_sprite2->SetPositionAbsalute(240,160);
			movie_sprite2->SetFrame(0);
			movie_sprite2->Render();
			movie_sprite3->SetPositionAbsalute(214,loc2);
			movie_sprite3->SetFrame(0);
			movie_sprite3->Render();

			break;
		case 3:
			movie_sprite4->SetPositionAbsalute(240,160);
			movie_sprite4->SetFrame(0);
			movie_sprite4->Render();
			
			break;
		case 4:
			movie_sprite->SetPositionAbsalute(161,160);
			movie_sprite->SetFrame(0);
			movie_sprite->Render();
			movie_sprite2->SetPositionAbsalute(78,161);
			movie_sprite2->SetFrame(0);
			movie_sprite2->Render();
			movie_sprite3->SetPositionAbsalute(120,62);
			movie_sprite3->SetFrame(0);
			movie_sprite3->Render();

			graphics_engine->Position(30,70);
			break;*/
		}
		break;

	/*				if(scene_panning < 1250) scene_panning += 16 * time;
				if(scene_panning > 1250) scene_panning = 1250;
				movie_sprite11->SetPositionAbsalute(120, -120 + 480);
				movie_sprite11->Render();

				graphics_engine->Position(10,270 - static_cast<int>(scene_panning));
				(*graphics_engine) << black_font << "Thanks for playing Blade of Betrayal!\n\n\n"
												 << "HPT Interactive Team\n\n"
												 << "Game Concept & Story:\n"
												 << "Billy Garretsen\n\n"
												 << "Artwork:\n"
												 << "Billy Garretsen\n\n"
												 << "Level Programming:\n"
												 << "Eric Duhon\n\n"
												 << "Character Programming:\n"
												 << "Matthew Shoemate\n\n"
												 << "AI Programming:\n"
												 << "David Harms\n\n"
												 << "Enemy Behavior Design:\n"
												 << "Billy Garretsen\n"
												 << "David Harms\n\n"
												 << "Cut Scene Programming:\n"
												 << "Eric Duhon\n"
												 << "Matthew Shoemate\n\n"
												 << "Cut Scene Artwork:\n"
												 << "Billy Garretsen\n\n"
												 << "Game Programming:\n"
												 << "Eric Duhon\n"
												 << "Matthew Shoemate\n"
												 << "David Harms\n\n"
												 << "Sound, Music & Programming:\n"
												 << "Matthew Shoemate\n\n"
												 << "Tools Programming:\n"
												 << "David Harms\n"
												 << "Eric Duhon\n\n"
												 << "Misc. Programming:\n"
												 << "Eric Duhon\n"
												 << "Matthew Shoemate\n"
												 << "David Harms\n\n"
												 << "Misc. Artwork:\n"
												 << "Billy Garretsen\n\n"
												 << "Game Documentation:\n"
												 << "David Harms\n\n"
												 << "Special Thanks:\n"
												 << "Billy Holland (Billy Evil)\n"
												 << "William Ramby (VRam)\n"
												 << "Barry Morgan (GreyWolf)\n"
												 << "www.ppx3k.com\n"
												 << "ppx3k community\n\n"
												 << "Beth Lang (blang)\n"
												 << "Shanna Shoemate\n\n\n\n";*/
				//Though Spencer's old family is gone, he feels 
//a strong sense of unity growing among his new one.
//The pain he felt for so long after his father's 
//death slowly fades away as he exhales, liberated from vengeance...


		default:
			if(scenes[current_scene].dialog_box)
			{
				text_dialog_sprite->SetPositionAbsalute(240,160);
				text_dialog_sprite->Render();
				graphics_engine->Position(105,120+scenes[current_scene].yOffsetDialog);
				(*graphics_engine) << white_font << scenes[current_scene].dialog;
			}

				if(scenes[current_scene].top_portrait != NONE && scenes[current_scene].top[0] != 0)
			{
				char_dialog_sprite_top->SetPositionAbsalute(285,70);
				char_dialog_sprite_top->Render();
				/*movie_sprite->SetImage(scenes[current_scene].top_portrait);
				movie_sprite->SetFrame(0);
				movie_sprite->SetPositionAbsalute(75,160);
				movie_sprite->Render();*/
				graphics_engine->Position(160,31+scenes[current_scene].yOffsetTop);
				(*graphics_engine) << black_font << scenes[current_scene].top;
	

			}
			if(scenes[current_scene].bot_portrait != NONE && scenes[current_scene].bottom[0] != 0)
			{
				char_dialog_sprite_bot->SetPositionAbsalute(195,210);
				char_dialog_sprite_bot->RenderHFlip();
				/*movie_sprite->SetImage(scenes[current_scene].bot_portrait);
				movie_sprite->SetFrame(0);
				movie_sprite->SetPositionAbsalute(405,160);
				movie_sprite->Render();*/
				graphics_engine->Position(50,172+scenes[current_scene].yOffsetBot);
				(*graphics_engine) << black_font << scenes[current_scene].bottom;
		

			}
			if(scenes[current_scene].top_portrait != NONE)
			{
				portraits[scenes[current_scene].top_portrait]->SetPositionAbsalute(60,70);
				portraits[scenes[current_scene].top_portrait]->Render();
			}
			if(scenes[current_scene].bot_portrait != NONE)
			{
				if(AppConfig::Instance().IsIpad())
					portraits[scenes[current_scene].bot_portrait]->SetPositionAbsalute(411,208);
				else
					portraits[scenes[current_scene].bot_portrait]->SetPositionAbsalute(420,210);
				portraits[scenes[current_scene].bot_portrait]->Render();
			}
			
#ifdef BOB_LITE
			if(current_scene != 0 && !(current_movie == 2 && current_scene == (scenes.size() - 1)))
			{
				prevMovieButton->Disabled(false);
				prevMovieButton->Render();
			}
			else
				prevMovieButton->Disabled(true);
			
			if(current_scene != (scenes.size() - 1) && !(current_movie == 2 && current_scene == (scenes.size() - 1)))
			{
				nextMovieButton->Disabled(false);
				nextMovieButton->Render();
				skipMovieButton->SetSprite(CR::AssetList::button_skip);
			}
			else
			{
				nextMovieButton->Disabled(true);
				skipMovieButton->SetSprite(CR::AssetList::button_done);
			}
			
			if (current_movie != 2)
			{
				skipMovieButton->Disabled(false);
				skipMovieButton->Render();
			}
			else
			{
				skipMovieButton->Disabled(true);
			}
			
			if (current_movie == 2)
			{
				buyGameButton->Disabled(false);
				buyGameButton->Render();
				returnToMenuButton->Disabled(false);
				returnToMenuButton->Render();
			}
			else
			{
				buyGameButton->Disabled(true);
				returnToMenuButton->Disabled(true);
			}
			
			if (current_movie == 2 && buyGameScreenTime <= 0)
				StopMovie();
#else
			if(current_scene != 0 && !(current_movie == 10 && current_scene == (scenes.size() - 1)))
			{
				prevMovieButton->Disabled(false);
				prevMovieButton->Render();
			}
			else
				prevMovieButton->Disabled(true);
			if(current_scene != (scenes.size() - 1))
			{
				nextMovieButton->Disabled(false);
				nextMovieButton->Render();
				skipMovieButton->SetSprite(CR::AssetList::button_skip);
			}
			else
			{
				nextMovieButton->Disabled(true);
				skipMovieButton->SetSprite(CR::AssetList::button_done);
			}
			
			// Final scene of game
			if (current_movie == 10 && current_scene == (scenes.size() - 1))
			{
				skipMovieButton->SetPosition(380, 265);
				/*
				if (game_class->GetCompletionPercent() <= 9)
					graphics_engine->Position(447, 175);
				else if (game_class->GetCompletionPercent() < 100)
					graphics_engine->Position(434, 175);
				else
					graphics_engine->Position(421, 175);
				
				(*graphics_engine) << game_class->bankGothic << game_class->GetCompletionPercent() << "%";
				 */
				
				 if (game_class->GetAchievementsCount() <= 9)
					 graphics_engine->Position(430, 175);
				 else
					 graphics_engine->Position(417, 175);
				 
				 (*graphics_engine) << game_class->bankGothic << game_class->GetAchievementsCount() << "/30";
			}
			
			skipMovieButton->Render();
#endif
		break;
	}
}

bool Theater::IsDone()
{
//	if(done) black_font->Release();
	/*if((current_movie == 0) && done)
	{
		movie_sprite->SetImage(86);
		movie_sprite1->SetImage(86);
		movie_sprite2->SetImage(86);
		movie_sprite3->SetImage(86);
	}*/
	//if(done) FreePortraits();
	return done;
}

void Theater::StopMovie()
{
	if(current_movie != 16)
	{
		done = true;
//		if((music != 0) && (game->mute_music != true)) music->HPTStopSound();
	}
	else
	{
//		if((music != 0) && (game->mute_music != true)) music->HPTStopSound();
		//if(game->HaveAllItems()) StartMovie(17);
		/*else*/ done = true;
	}
	/*text_dialog_sprite->Release();
	char_dialog_sprite_top->Release();
	char_dialog_sprite_bot->Release();
//	buttons_dialog_sprite->Release();
	black_font->Release();
	white_font->Release();
	background->Release();
	FreePortraits();*/
	
	skipMovieButton->Disabled(true);
	//skipMovieButton->FreeResources();
	prevMovieButton->Disabled(true);
	//prevMovieButton->FreeResources();
	nextMovieButton->Disabled(true);
	//nextMovieButton->FreeResources();

}

void Theater::FreeAssets()
{	
	skipMovieButton->FreeResources();
	prevMovieButton->FreeResources();
	nextMovieButton->FreeResources();
	
	if (text_dialog_sprite != NULL){
		text_dialog_sprite->Release();
		text_dialog_sprite = NULL;
	}
	
	if (char_dialog_sprite_top != NULL){
		char_dialog_sprite_top->Release();
		char_dialog_sprite_top = NULL;
	}
	
	if (char_dialog_sprite_bot != NULL){
		char_dialog_sprite_bot->Release();
		char_dialog_sprite_bot = NULL;
	}
	//	buttons_dialog_sprite->Release();
	
	if (black_font != NULL){
		black_font->Release();
		black_font = NULL;
	}
	
	if (white_font != NULL){
		white_font->Release();
		white_font = NULL;
	}
	
	if (background != NULL){
		background->Release();
		background = NULL;
	}
	FreePortraits();
}

void Theater::SetGame(IGame *lpGame)
{
	game = lpGame;
}

void Theater::CreateScene1a()
{
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_jacob);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);

	scenes.clear();
	
	/*It is the near future...  Two weapon manufacturers struggle to become the favored supplier to  the government...NCorp, 
	headed by Suke Hato deals with chemical and biological weapons... Fortified Industries, owned and controlled by 
	James and Jacob Corinth produces traditional arms... The government comes to favor Fortified Industries and NCorp is
	threatened with bankruptcy... Desperate, Suke Hato attempts to form a partnership with the Corinth brothers but he fails... 
	James ends up dead, his murderer unknown... Spencer Corinth, the only son of James, vows to uncover those guilty and avenge his father...
	A month has gone by and no new information has been discovered about the death of James Corinth... Spencer has almost given up hope... */
	
	Scene temp;
	temp.background = 73;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog," It is the near future... Two weapon \n"
						" manufacturers struggle to become\n"
						"      the favored supplier to the\n"
						"  government... NCorp, headed by \n"
						"   Suke Hato deals with chemical ");
	scenes.push_back(temp);
	
	temp.background = 73;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"and biological weapons... Fortified\n"
						"Industries, owned and controlled by\n"
						"James and Jacob Corinth, produces\n"
						"traditional arms... The government\n"
						"comes to favor Fortified Industries");
	scenes.push_back(temp);	
	
	temp.background = 73;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 12;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"   and NCorp is threatened with\n"
						"bankruptcy... Desperate, Suke Hato\n"
						"attempts to form a partnership with\n"
						"the Corinth brothers, but he fails...");
	scenes.push_back(temp);	
	
	temp.background = 73;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"James ends up dead, his murderer\n"
						" unknown... Spencer Corinth, the\n"
						"only son of James, vows to uncover\n"
						"those guilty and avenge his father...");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_1a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_1a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog," A month has gone by and no new\n"
						" information has been discovered\n"
						"about the death of James Corinth...\n"
						"Spencer has almost given up hope... ");
	scenes.push_back(temp);
	
	/*SPENCER: You called, Uncle Jacob?	
	JACOB: I have some interesting news for you my boy. My informant has been searching for leads and it seems that your father's murder traces itself back to Suke Hato.
	SPENCER: Hato!? Him? Why?	
	JACOB: That is what I would like to know. We need to question him before turning him over to the authorities. I want you to break into NCorp and bring him back here. 
	Spencer arrives outside of the NCorp complex... 	
	SPENCER: It's too risky going in through the front. I will have to find some way around.*/ 
	
	temp.background = AssetList::cutscene_1a1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"       You called, Uncle Jacob?\n");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_1a1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	sprintf(temp.top,"       You called, Uncle Jacob?\n");
	sprintf(temp.bottom,"  I have some interesting news for\n"
						"you my boy. My informant has been\n"
						"  searching for leads and it seems\n"
						"   that your father's murder traces\n"
						"        itself back to Suke Hato.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = AssetList::cutscene_1a1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	sprintf(temp.top,"            Hato!? Him? Why?");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = AssetList::cutscene_1a1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	sprintf(temp.top,"            Hato!? Him? Why?");
	sprintf(temp.bottom," That is what I would like to know.\n"
						" We need to question him before\n"
						"turning him over to the authorities.\n"
						"I want you to break into NCorp and\n"
						"         bring him back here.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 71;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = 71;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 30;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"   Spencer arrives outside of the\n"
						"             NCorp complex...");
	scenes.push_back(temp);
	
	temp.background = 71;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 19;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"    It's too risky going in through\n"
					 "      the front. I will have to find\n"
					"            some way around.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//1a.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);

}

void Theater::CreateScene1b()
{

	
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);	
	
	scenes.clear();

	/*Spencer finds his way into the main building where Suke Hato is located.	
	Spencer: I need to find a way up to that bastard's penthouse and get to the bottom of this. */ 
		
	Scene temp;
		
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 20;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"      Spencer finds his way into\n"
						"    the main building where Suke\n"
						"              Hato is located.");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_1b1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 20;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_1b1;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 19;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"    I need to find a way up to that\n"
					"    bastard's penthouse and get to\n"
					"             the bottom of this.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//1b.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);

}


void Theater::CreateScene1c()
{
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_mr_thomas);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);

	/*Spencer rides the elevator up to Suke Hato's penthouse, only to find a man in sunglasses awaiting his arrival. 	
	Spencer: Who are you?	
	Thomas: The name's Thomas.	
	Spencer: Tell me where Suke Hato is.	
	Thomas: I'm afraid I can't. It is my duty to protect him.	
	Spencer: My business is with Hato. Don't make me hurt you.	
	Thomas: Sorry, friend. I can't let you pass. */
	
	scenes.clear();
	
	Scene temp;
		
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 12;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"    Spencer rides the elevator up\n"
						"    to Suke Hato's penthouse only\n"
						"      to find a man in sunglasses\n"
						"           awaiting his arrival.");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_1c1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 12;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_1c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"               Who are you?");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_1c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"               Who are you?");
	sprintf(temp.bottom,"          The name's Thomas.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_1c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"      Tell me where Suke Hato is.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_1c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"      Tell me where Suke Hato is.");
	sprintf(temp.bottom,"           I'm afraid I can't. It\n"
						"       is my duty to protect him.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
		
	temp.background = AssetList::cutscene_1c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 29;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"       My business is with Hato.\n"
					"        Don't make me hurt you.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_1c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 29;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"       My business is with Hato.\n"
			"        Don't make me hurt you.");
	sprintf(temp.bottom,"         Sorry, friend. I can't\n"
						"               let you pass.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//1c.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);

}

void Theater::CreateScene2a()
{
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_mr_thomas);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_jacob);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_hato);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_guard);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);	
	
	scenes.clear();

	/*Spencer: NOW TELL ME WHERE HATO IS BEFORE I END YOU!!! 	
	Out of nowhere, Spencer is surrounded by dozens of Hato's elite guards. A large monitor on the wall flickers on... Suke Hato stares with a devilish grin. 
	Hato: Impressive.	
	Jacob: I told you he was not to be underestimated. 	
	Jacob appears next to Hato on the monitor. Spencer stands silent. 	
	Jacob: Look how confused you are. Priceless.	
	Spencer: Uncle Jacob? What is this?	
	Jacob: It was ME who ordered the hit on James.	
	Spencer: You? But I dont understand.	
	Jacob: The two of you could never understand. James was too stubborn to see the benefits of partnering with NCorp. He did not approve. I however, am more open-minded. It's just good business.
	Spencer: But we are a family.	
	Jacob: Ha! You are so much like your father. Blinded by some sense of nobility. I will enjoy having you out of the picture.	
	Spencer: This whole thing, this manhunt, was all a trap? You're going to kill me aren't you?	
	Jacob: That is up to Mr. Hato. You are my gift to him.	
	Hato: I think we should make him part of the "PROGRAM". Guards, put him in a cell until we are ready to experiment.	
	Jacob: Goodbye Spencer.	
	Spencer: NOOOOOOOOO!!!!!! 	
	Lost in a storm of emotions, Spencer allows himself to be carried away without putting up a struggle. Inside the holding area, there is much commotion.	
	 Guard: There's been a jail break! An escapee fried the locks and all prisoners are loose. Stay here with the boy while I go check it out.	
	Seeing an opportunity to escape, Spencer knocks out the guards. Having no choice he runs towards the cellblocks hoping to find a way out. */
	
	Scene temp;
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 29;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"  NOW TELL ME WHERE HATO IS\n"
					"        BEFORE I END YOU!!! ");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
		
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"      Out of nowhere, Spencer is\n"
						"   surrounded by dozens of Hato's\n"
						"     elite guards. A large monitor\n"
						"    on the wall flickers on... Suke\n"
						"   Hato stares with a devilish grin.");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 19;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"     Jacob appears next to Hato\n"
			"       on the monitor. Spencer\n"
			"               stands silent.");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 3;
	temp.dialog_box = false;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 29;	
	sprintf(temp.top,"                 Impressive.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 3;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"                 Impressive.");
	sprintf(temp.bottom,"      I told you he was not to be\n"
						"             underestimated.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"     Look how confused you are.\n"
						"                 Priceless.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"      Uncle Jacob? What is this?");
	sprintf(temp.bottom,"     Look how confused you are.\n"
			"                 Priceless.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"    It was ME who ordered the hit\n"
						"                 on James.	");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"      You? But I dont understand.");
	sprintf(temp.bottom,"    It was ME who ordered the hit\n"
						"                 on James.	");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 9;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"     The two of you could never\n"
						"     understand. James was too\n"
						"    stubborn to see the benefits\n"
						"      of partnering with NCorp. \n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 19;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"  He did not approve. I, however,\n"
						"        am more open-minded. \n"
						"        It's just good business.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 19;
	sprintf(temp.top,"            But we are a family.");
	sprintf(temp.bottom,"  He did not approve. I, however,\n"
						"        am more open-minded. \n"
						"        It's just good business.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 9;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"   Ha! You are so much like your\n"
						"   father. Blinded by some sense\n"
						"   of nobility. I will enjoy having\n"
						"         you out of the picture.\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 19;
	temp.yOffsetBot = 9;
	sprintf(temp.top,"    This whole thing, this manhunt,\n"
					 "    was all a trap? You're going to\n"
					 "             kill me aren't you?");
	sprintf(temp.bottom,"   Ha! You are so much like your\n"
						"   father. Blinded by some sense\n"
						"   of nobility. I will enjoy having\n"
						"         you out of the picture.\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"        That is up to Mr. Hato.\n"
						"        You are my gift to him.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 3;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 9;
	temp.yOffsetBot = 29;
	sprintf(temp.top," I think we should make him part of\n"
					 " the \"PROGRAM\". Guards, put him\n"
					 "      in a cell until we are ready\n"
					 "               to experiment.");
	sprintf(temp.bottom,"        That is up to Mr. Hato.\n"
						"        You are my gift to him.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"           Goodbye Spencer.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2a1;
	temp.bot_portrait = 2;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"            NOOOOOOOOO!!!!!!");
	sprintf(temp.bottom,"           Goodbye Spencer.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"     Lost in a storm of emotions,\n"
						"    Spencer allows himself to be\n"
						"   carried away without putting up\n"
						"    a struggle. Inside the holding\n"
						"   area, there is much commotion.");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = 4;
	temp.top_portrait = 4;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 9;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"     There's been a jail break! An \n"
					 "    escapee fried the locks and all\n"
					 "    prisoners are loose. Stay here\n"
					 " with the boy while I go check it out.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 9;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog," Seeing an opportunity to escape,\n"
						"  Spencer knocks out the guards.\n"
						" Having no choice he runs towards\n"
						"   the cellblocks hoping to find a\n"
						"                  way out.");
	scenes.push_back(temp);	
	
	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//2a.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);

}

void Theater::CreateScene2b()
{
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);

	scenes.clear();
	
	/*The elevator only goes down. During the descent, Spencer feels a large tremor. 	
	INTERCOM: Warning. Fire detected on all laboratory levels. Possible contamination and outbreak of specimens. Use extreme caution.	
	Spencer: Specimens? */
	
	Scene temp;
		
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 19;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"     The elevator only goes down.\n"
						"     During the descent, Spencer\n"
						"           feels a large tremor. ");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_2b1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_2b1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 12;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"INTERCOM: Warning. Fire detected\n"
						"  on all laboratory levels. Possible\n"
						"   contamination and outbreak of\n"
						"  specimens. Use extreme caution.\n");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_2b1;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"                 Specimens?");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//2b.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);

}

void Theater::CreateScene2c()
{
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_agm);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);

	scenes.clear();

	/*The waste tunnel takes Spencer directly into the city's sewers below NCorp.	
	Spencer: I can't believe I made it out of there. What a nightmare!	
	In the darkness, Spencer hears a low growling. From the shadows emerges a hideous beast with hunger in its eyes. 	
	Creature: Grrrrrrrr....		
	Spencer: Oh my... */
	
	Scene temp;	
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 19;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"   The waste tunnel takes Spencer\n"
						"     directly into the city's sewers\n"
						"                below NCorp.");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 29;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"     I can't believe I made it out\n"
					 "     of there. What a nightmare!");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
		
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"                Grrrrrrrr....");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_2c1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 19;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_2c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"                   Oh my...");
	sprintf(temp.bottom,"                Grrrrrrrr....");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	

	
	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//2c.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);

}

void Theater::CreateScene3a()
{
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);	
	
	scenes.clear();

	/*Spencer carefully examines an ID tag around the creature's arm. 
	Spencer: “Specimen 102383 - Austin Ament”. This thing was human once? All those monsters were prisoners...lab rats. What the hell is NCorp really up to? Genetic engineering on humans? Bastards. And now Fortified Industries is mixed up in all of it. I can't believe my uncle, my own flesh and blood...he has betrayed everything my father ever worked to build. Our company. Our family...They can't get away with this! 
	Spencer, determined to bring justice to his betrayers, follows the maze of sewers until he finds the access tunnel that would lead him right into the water line of Fortified Industries. There is no turning back. He must put an end to Jacob's plans or die trying.
*/
	
	Scene temp;	
	temp.background = AssetList::cutscene_3a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 30;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 30;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog," Spencer carefully examines an ID\n"
						"    tag around the creature's arm.\n");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	sprintf(temp.top,"\"Specimen 102383 - Austin Ament\".\n"
					"  This thing was human once? All\n"
					"  those monsters were prisoners...\n"
					"  lab rats. What the hell is NCorp\n"
					"  really up to? Genetic engineering");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 19;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"   on humans? Bastards. And now\n"
					 "   Fortified Industries is mixed up\n"
					 "     in all of it. I can't believe my\n"
					 "   uncle, my own flesh and blood...\n"
					 "   He has betrayed everything my");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 19;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"     father ever worked to build.\n"
					 "     Our company. Our family...\n"
					 "    They can't get away with this!\n");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"Spencer, determined to bring justice\n"
						"  to his betrayers, follows the maze\n"
						" of sewers until he finds the access\n"
						"  tunnel that leads him right into the\n"
						"   water line of Fortified Industries.");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 30;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog," There is no turning back. He must\n"
						"    put an end to Jacob's plans...\n");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3a1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 39;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"             ...or die trying.");
	scenes.push_back(temp);	
	
	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//5a.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);

}

void Theater::CreateScene3b()
{
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_jacob);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_hato);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_guard);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);	
	

	
	
	scenes.clear();

	/*Jacob sits in his office quietly, pleased with how perfectly his plans have developed.	
	GUARD: Sir, we have spotted your nephew on our security cameras. He appears to have wiped out our entire ground forces. We lost him somewhere in the air ducts.
	JACOB: Spencer? Alive? 	
	Jacob punches a series of numbers and Suke Hato appears on his monitor. 	
	JACOB: Spencer escaped, Hato. He is here.	
	HATO: No need to worry, my friend. I will recover you immediately.	
	JACOB: Guard, we have an intruder in the building. Tell the men to release the creatures.	
	GUARD: Um, sir, is that such a wise decision? We have not experimented with them enough. Our results are inconclusive.	
	JACOB: I said release them!	
	GUARD: Right away, sir... */
	
	Scene temp;
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 20;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"   Jacob sits quietly in his office,\n"
						"pleased with how perfectly his plans\n"
						"              have developed.\n");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = 1;
	temp.top_portrait = 3;
	temp.dialog_box = false;
	sprintf(temp.top," Sir, we have spotted your nephew\n"
					 "     on our security cameras. He\n"
					 "    appears to have wiped out our\n"
					 "    entire ground forces. We lost\n"
					 "   him somewhere in the air ducts.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = 1;
	temp.top_portrait = 3;
	temp.dialog_box = false;
	temp.yOffsetBot = 39;
	sprintf(temp.top," Sir, we have spotted your nephew\n"
					 "     on our security cameras. He\n"
					 "    appears to have wiped out our\n"
					 "    entire ground forces. We lost\n"
					 "   him somewhere in the air ducts.");
	sprintf(temp.bottom,"             Spencer? Alive?");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 19;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"       Jacob punches a series\n"
						"      of numbers and Suke Hato\n"
						"        appears on his monitor.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = 1;
	temp.top_portrait = 2;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"        Spencer escaped, Hato.\n"
						"                 He is here.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = 1;
	temp.top_portrait = 2;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 19;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"          No need to worry, my\n"
					"           friend. I will recover\n"
					"              you immediately.");
	sprintf(temp.bottom,"        Spencer escaped, Hato.\n"
						"                 He is here.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = 1;
	temp.top_portrait = 3;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 19;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"     Guard, we have an intruder\n"
						"        in the building. Tell the\n"
						"    men to release the creatures.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = 1;
	temp.top_portrait = 3;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 8;
	temp.yOffsetBot = 19;
	sprintf(temp.top,"     Um, sir, is that such a wise\n"
					"        decision? We have not\n"
					"   experimented with them enough.\n"
					"     Our results are inconclusive.	");
	sprintf(temp.bottom,"     Guard, we have an intruder\n"
						"        in the building. Tell the\n"
						"    men to release the creatures.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = 1;
	temp.top_portrait = 3;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"          I said release them!");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3b1;
	temp.bot_portrait = 1;
	temp.top_portrait = 3;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"             Right away, sir...");
	sprintf(temp.bottom,"          I said release them!");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	
	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//5b.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);

}

void Theater::CreateScene3c()
{
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(CR::AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_jacob);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);	
	
	scenes.clear();

	/*Spencer rushes into Jacob's empty office. A helicopter can be heard in the distance. Spencer follows a stairwell to the roof. The helicopter begins its descent as Jacob waits on the helipad.  
	SPENCER: JACOB!!!  
	Spencer thrusts his sword upward, releasing a ball of energy that hits the chopper's propeller blades. In a blinding flash of light, the helicopter loses control and crashes into the roof, barely missing Jacob.  
	JACOB: You just killed Suke Hato. Perhaps I should thank you for that.
	SPENCER: You're next.
	JACOB: So, it has come to this. You are no match for me, nephew.
	SPENCER: Don't call me that. We are not a family.
	JACOB: No I suppose not. Let me show you something.  
	Jacob produces a vial of chemicals from his coat.  
	JACOB: Behold the true fruits of my partnership with Hato. Forget money...just one drop of this will make me immortal. Just one drop...will make me a god.
	SPENCER: You are a sick man. My father did not deserve to die. Not for this.
	JACOB: Your father always had the power while I stood on the side. Time after time I had to watch him make decisions and treat me like a fool. No, Spencer, now it is my turn to have the power.  
	Spencer rushes towards Jacob with his sword drawn. In a panic, Jacob quickly consumes the entire vial of chemicals just as Spencer runs his sword through his chest. Jacob falls to his knees, gasping for breath.  
	SPENCER: It is over... 				
	Jacob's head jerks up violently, his eyes bright red. Spencer looks on in disbelief as Jacob rises to his feet and pulls the sword out of his chest. He throws it back to Spencer and smiles.  
	JACOB: You're right, nephew. It is over... */
	
	
	Scene temp;
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 12;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"Spencer rushes into Jacob's empty\n"
						" office. A helicopter can be heard\n"
						" in the distance. Spencer follows a\n"
						"           stairwell to the roof.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 30;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"The helicopter begins its descent as\n"
						"      Jacob waits on the helipad.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"                  JACOB!!!");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 20;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"Spencer thrusts his sword upward,\n"
						"    releasing a ball of energy that\n"
						" hits the chopper's propeller blades.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 20;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"    In a blinding flash of light, the\n"
						"helicopter loses control and crashes\n"
						" into the roof, barely missing Jacob.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 18;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"You just killed Suke Hato. Perhaps\n"
						"      I should thank you for that.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 19;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"                You're next.");
	sprintf(temp.bottom,"You just killed Suke Hato. Perhaps\n"
						"      I should thank you for that.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"  So, it has come to this. You are\n"
						"      no match for me, nephew.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 29;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"      Don't call me that. We are\n"
					"                  not family.");
	sprintf(temp.bottom,"  So, it has come to this. You are\n"
						"      no match for me, nephew.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 29;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"      No I suppose not. Let me\n"
						"         show you something.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 28;
	temp.yOffsetTop = 29;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"       Jacob produces a vial of\n"
						"       chemicals from his coat.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"     Behold the true fruits of my\n"
						"    partnership with Hato. Forget\n"
						"    money...just one drop of this\n"
						"  will make me immortal. Just one\n"
						"      drop...will make me a god.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 29;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"   You are a sick man. My father\n"
					" did not deserve to die. Not for this.");
	sprintf(temp.bottom,"     Behold the true fruits of my\n"
			"    partnership with Hato. Forget\n"
			"    money...just one drop of this\n"
			"  will make me immortal. Just one\n"
			"      drop...will make me a god.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom," Your father always had the power\n"
						"   while I stood on the side. Time\n"
						"    after time I had to watch him\n"
						"    make decisions and treat me\n"
						"                 like a fool.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 29;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"   No, Spencer, now it is my turn\n"
						"            to have the power.");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"Spencer rushes towards Jacob with\n"
						"his sword drawn. In a panic, Jacob\n"
						"quickly consumes the entire vial of\n"
						"chemicals just as Spencer runs his\n"
						"        sword through his chest.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3c2;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 12;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_3c2;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 29;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"        Jacob falls to his knees,\n"
						"            gasping for breath.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3c2;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"                  It is over...");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_3c2;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"   Jacob's head jerks up violently,\n"
						"     his eyes bright red. Spencer\n"
						"    looks on in disbelief as Jacob\n"
						"    rises to his feet and pulls the\n"
						"         sword out of his chest. ");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3c2;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 29;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"     He throws it back to Spencer\n"
						"                 and smiles.  ");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_3c2;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"");
	sprintf(temp.bottom," You're right, nephew. It is over...");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	
	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//5c.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);
}

void Theater::CreateSceneBonus1()
{
	scenes.clear();
		
	Scene temp;	
	
	//Welcome to SURVIVAL RUN - the high tech training exercise developed by Fortified Industries to toughen 
	//soldiers and test endurance. Your health will slowly drain as time passes. Your objective is to find 
	//as many glowing beacons as you can and make it to the exit before your health runs out. Each beacon
	//will restore life and extend your chances for survival. Are you skilled enough to get all the 
	//beacons and make it out alive?
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog," Welcome to SURVIVAL RUN - the\n"
						"      high tech training exercise \n"
						"developed by Fortified Industries to \n"
						"       toughen soldiers and test.\n"
						"                 endurance \n");
	scenes.push_back(temp);	
			
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"   Your health will slowly drain as\n"
						" time passes. Your objective is to\n"
						" find as many glowing beacons as \n"
						"   you can and make it to the exit \n"
						"      before your health runs out.\n");
	scenes.push_back(temp);	

	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 10;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"  Each beacon will restore life and\n"
						"  extend your chances for survival.\n"
						"Are you skilled enough to get all the\n"
						"   beacons and make it out alive?\n");
	scenes.push_back(temp);	

	current_scene = 0;
}

void Theater::CreateSceneFinal()
{	
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(CR::AssetList::cutscene_spencer);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_jacob);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);		
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::SpencerSpyPortrait);
	if(AppConfig::Instance().IsIpad())
		tempp->SetDesignSize(127,120);
	portraits.push_back(tempp);		
	
	scenes.clear();	
	
	/*JACOB: Now my boy, you shall be reunited with your father. Ha ha ha hyack...AAAAAARRRRRRGH! 
	A sharp pain tears through Jacob's body. The stress of the serum is too much to handle and his heart stops beating.  
	JACOB: Spencer... 
	Spencer picks up the vial from his uncle's dead hand. The logo of NCorp is etched on the side. 
	SPENCER: This should be enough to put NCorp down... 
	By the time the NCorp facilities were inspected by the authorities, any evidence of genetic experimentation had been mysteriously burned and destroyed. The government shut down all operations at the complex despite any concrete proof of the illegal activity.  
	Time passes yet Spencer's mind remains troubled. As the reluctant head of Fortified Industries, he now sees the broader scope of dealing arms to the countries of the world. Evil men take power for themselves and destroy the lives of the innocent every day. 
	SPENCER: I can't rest. I will never rest until all the men who live only to destroy our world are brought under the justice of my blade. NCorp was only the beginning. I promise you, father, I will not let this world fall. I have the power to change it. It is all I have now...Vengeance. 
	*/
	
	Scene temp;
	
	temp.background = 73;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 9;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"Now my boy, you shall be reunited\n"
						"             with your father.\n"
						"             Ha ha ha hyack...\n"
						"          AAAAAARRRRRRGH!");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_finale1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_finale1;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 12;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"       A sharp pain tears through\n"
						"      Jacob's body. The stress of\n"
						"   the serum is too much to handle\n"
						"      and his heart stops beating.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_finale1;
	temp.bot_portrait = 1;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 12;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 39;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"                 Spencer...");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 20;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog," Spencer picks up the vial from his\n"
						"    uncle's dead hand. The logo of\n"
						"      NCorp is etched on the side.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 29;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"     This should be enough to put\n"
					"               NCorp down... ");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
		
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"By the time the NCorp facilities were\n"
						"  inspected by the authorities, any\n"
						"evidence of genetic experimentation\n"
						"    had been mysteriously burned\n"
						"               and destroyed.");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 9;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"    The government shut down all\n"
						"       operations at the complex\n"
						"      despite any concrete proof\n"
						"           of the illegal activity. ");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog," Time passes yet Spencer's mind\n"
						"       remains troubled. As the\n"
						"     reluctant head of Fortified \n"
						"     Industries, he now sees the\n"
						"   broader scope of dealing arms");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	temp.yOffsetDialog = 9;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"    to the countries of the world.\n"
						"        Evil men take power for\n"
						"     themselves and destroy the\n"
						"   lives of the innocent every day. ");
	scenes.push_back(temp);		
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"I can't rest. I will never rest until all\n"
					"the men who live only to destroy our\n"
					"world are brought under the justice\n"
					"     of my blade. NCorp was only\n"
					"               the beginning.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_black;
	temp.bot_portrait = NONE;
	temp.top_portrait = 0;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 9;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"   I promise you, father, I will not\n"
					 "     let this world fall. I have the\n"
					 "      power to change it. It is all\n"
					 "                I have now...");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	temp.background = AssetList::cutscene_finale2;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	temp.background = AssetList::cutscene_finale2;
	temp.bot_portrait = NONE;
	temp.top_portrait = 2;
	temp.dialog_box = false;
	temp.yOffsetDialog = 0;
	temp.yOffsetTop = 39;
	temp.yOffsetBot = 0;
	sprintf(temp.top, "               ...Vengeance.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);	
	
	if (game_class->GetAchievementsCount() < 15)
		temp.background = AssetList::completion_screen_a;
	else
		temp.background = AssetList::completion_screen_b;
	
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 12;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
	
	current_scene = 0;
}

#ifdef BOB_LITE
void Theater::CreateSceneLite()
{
	
	
	HPTSprite1 *tempp;
	tempp = graphics_engine->CreateSprite1();
	tempp->SetImage(AssetList::cutscene_spencer);
	portraits.push_back(tempp);	
	
	scenes.clear();
	
	/*Spencer finds his way into the main building where Suke Hato is located.	
	 Spencer: I need to find a way up to that bastard's penthouse and get to the bottom of this. */ 
	
	Scene temp;
	
	temp.background = AssetList::free_attract_background;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	temp.yOffsetDialog = 20;
	temp.yOffsetTop = 0;
	temp.yOffsetBot = 0;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);
		
	current_scene = 0;
	//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//1b.hgf")));
	//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
	//	music = sound_engine->CreateSoundObject(0, 1);
	//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);

	buyGameScreenTime = 30.0f; // 30 seconds for this screen
}
#endif

/*
void Theater::CreateSceneSpecial()
{
	scenes.clear();

	Scene temp;

	temp.background = 4;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"In a dark office on the other\n"
						"side of the world...");
	scenes.push_back(temp);

	//In a dark office on the other side of the world.

	temp.background = 4;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"Of course this\n"
					 "complicates things.\n"
					 "Regardless, the\n"
					 "operation must\n"
					 "continue as planned..\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"at the South\n"
					 "American and Asian\n"
					 "facilities.\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

//Of course this complicates things. Regardless, 
//the operation must continue as planned at the South American and Asian facilities.

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"We destroyed the\n"
					 "evidence at\n"
					 "NagolaCorp as you\n"
					 "requested, although\n"
					 "some files were...\n");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

//We destroyed the evidence at NagolaCorp
//as you requested, although some files were missing.

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"missing.\n");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

//The ones in young Mr. Corinth's possession?

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"missing.\n");
	sprintf(temp.bottom,"The ones in young\n"
					 "Mr. Corinth's\n"
					 "possession?");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

//Yes sir. Do not worry, there is nothing incriminating. Only loose endsÖ

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"Yes sir.\n"
			  		 "Do not worry, there\n"
					 "is nothing\n"
					 "incriminating.\n"
					 "Only loose ends.\n");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

//Loose ends that could lead them here. I want security up at the facilities. I do not like unwelcome guests.

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"Yes sir.\n"
			  		 "Do not worry, there\n"
					 "is nothing\n"
					 "incriminating.\n"
					 "Only loose ends.\n");
	sprintf(temp.bottom,"Loose ends that \n"
			  		 "could lead them \n"
					 "here. I want security\n"
					 "up at the facilities...\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"I do not like\n"
			  		 "unwelcomed guests.\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 4;
	temp.bot_portrait = 9;
	temp.top_portrait = 10;
	temp.dialog_box = false;
	sprintf(temp.top,"Yes, Mr. Hato.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 5;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = true;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"Somewhere over the jungles of\n"
						"Peru...");
	scenes.push_back(temp);

	temp.background = 5;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 5;
	temp.bot_portrait = 8;
	temp.top_portrait = 7;
	temp.dialog_box = false;
	sprintf(temp.top,"We almost there?");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 5;
	temp.bot_portrait = 8;
	temp.top_portrait = 7;
	temp.dialog_box = false;
	sprintf(temp.top,"We almost there?");
	sprintf(temp.bottom,"Yeah, according to \n"
						"these files you found \n"
						"we should be coming\n"
						"up on one of the\n"
						"testing facilities...\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 5;
	temp.bot_portrait = 8;
	temp.top_portrait = 7;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"shortly. \n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

//Yeah, according to these files you found we should be coming up on one of the testing facilities shortly

	temp.background = 5;
	temp.bot_portrait = 8;
	temp.top_portrait = 7;
	temp.dialog_box = false;
	sprintf(temp.top,"You better drop me\n"
					 "off a few miles out.\n"
					 "I don't want to set\n"
					 "off any alarms.\n");
	sprintf(temp.bottom,"\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

//You better drop me off a few miles out. I don't want to set off any alarms.

	temp.background = 5;
	temp.bot_portrait = 8;
	temp.top_portrait = 7;
	temp.dialog_box = false;
	sprintf(temp.top,"You better drop me\n"
					 "off a few miles out.\n"
					 "I don't want to set\n"
					 "off any alarms.\n");
	sprintf(temp.bottom,"Okay, ready?\n"
						"Use your comlink\n"
						"to contact me if\n"
						"you get into trouble.\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 5;
	temp.bot_portrait = 8;
	temp.top_portrait = 7;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"I'm gonna try and\n"
						"crack these disks\n"
						"you found and see\n"
						"what more I can find\n"
						"out about...\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

	temp.background = 5;
	temp.bot_portrait = 8;
	temp.top_portrait = 7;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"NagolaCorp's\n"
						"operations. Be \n"
						"careful Spencer, you \n"
						"don't know what's\n"
						"out there.\n");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

//Okay, ready? Use your comlink to contact me if you get into trouble.
//I'm gonna try and crack these disks you found and see what more I can
//find out about NagolaCorp's operations. Be careful Spencer,
//you don't know what's out there.

	temp.background = 5;
	temp.bot_portrait = 8;
	temp.top_portrait = 7;
	temp.dialog_box = false;
	sprintf(temp.top,"Don't worry about me.\n"
						"After what I've been\n"
						"through, I think I can\n"
						"handle myself.");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);

//Don't worry about me. After what I've been through, I think I can handle myselfÖ

	temp.background = 6;
	temp.bot_portrait = NONE;
	temp.top_portrait = NONE;
	temp.dialog_box = false;
	sprintf(temp.top,"");
	sprintf(temp.bottom,"");
	sprintf(temp.dialog,"");
	scenes.push_back(temp);


	current_scene = 0;
//	graphics_engine->LoadHGF(1,hptstrcat(path,("cutscenes//end.hgf")));
//	sound_engine->LoadHSF(hptstrcat(path, ("sounds//title.hsf")), 1);
//	music = sound_engine->CreateSoundObject(0, 1);
//	if((music != 0) && (game->mute_music != true)) music->HPTPlaySound(true);
}*/

void Theater::FreePortraits()
{
	for(int count = 0;count < portraits.size();count++)
	{
		HPTSprite1 *temp = portraits[count];
		temp->Release();
	}
	portraits.clear();
}
