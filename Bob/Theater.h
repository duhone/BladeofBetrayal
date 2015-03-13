// Theater.h: interface for the Theater class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THEATER_H__0E9A93BC_DEE2_4911_8C49_6DB13C807E19__INCLUDED_)
#define AFX_THEATER_H__0E9A93BC_DEE2_4911_8C49_6DB13C807E19__INCLUDED_


#include "../Engines/Graphics/HPTGraphics.h"
//#include "HPT sound.h"
#include "../Engines/Input/input_engine.h"
#include "IGame.h"
//#include "HPTVector.h"
//#include "soundprocessor.h"
#include "stdio.h"
#include "string.h"
#include<vector>

using namespace std;

//extern SoundProcessor *sound_processor;
//extern Game_Sounds *game_sounds;

#define NONE 1000

struct Scene
{
	int top_portrait;
	int bot_portrait;
	bool dialog_box;
	char top[255];
	char dialog[255];
	char bottom[255];
	int background;
	int yOffsetDialog;
	int yOffsetTop;
	int yOffsetBot;
	Scene()
	{
		top_portrait = 0;
		bot_portrait = 0;
		dialog_box = false;
		top[0] = 0;
		dialog[0] = 0;
		bottom[0] = 0;
		background = 0;
		yOffsetDialog = 0;
		yOffsetTop = 0;
		yOffsetBot = 0;
	}
	Scene(const Scene& arg)
	{
		top_portrait = arg.top_portrait;
		bot_portrait = arg.bot_portrait;
		dialog_box = arg.dialog_box;
		strcpy(top,arg.top);
		strcpy(dialog,arg.dialog);
		strcpy(bottom,arg.bottom);
		background = arg.background;
		yOffsetDialog = arg.yOffsetDialog;
		yOffsetTop = arg.yOffsetTop;
		yOffsetBot = arg.yOffsetBot;

	}
	Scene& operator=(const Scene& arg)
	{
		top_portrait = arg.top_portrait;
		bot_portrait = arg.bot_portrait;
		dialog_box = arg.dialog_box;
		strcpy(top,arg.top);
		strcpy(dialog,arg.dialog);
		strcpy(bottom,arg.bottom);
		background = arg.background;
		yOffsetDialog = arg.yOffsetDialog;
		yOffsetTop = arg.yOffsetTop;
		yOffsetBot = arg.yOffsetBot;		
		return *this;
	}
};


class Theater: public Input_Controller
{
public:
	void FreePortraits();
	void SetGame(IGame *game);
	void StopMovie();
	bool IsDone();
	void Render();
	void Update(float time);
	void StartMovie(int arg);
	Theater();
	virtual ~Theater();
	void InputChanged();
	void OnNext();
	void OnPrev();
//#ifdef BOB_LITE
	//void OnBuyGame();
//#endif
	void FreeAssets();
private:
	void CreateScene1a();
	void CreateScene1b();
	void CreateScene1c();
	void CreateScene2a();
	void CreateScene2b();
	void CreateScene2c();
	void CreateScene3a();
	void CreateScene3b();
	void CreateScene3c();
	/*void CreateScene4a();
	void CreateScene4b();
	void CreateScene4c();
	void CreateScene5a();
	void CreateScene5b();
	void CreateScene5c();*/
	void CreateSceneFinal();
	void CreateSceneBonus1();
	//void CreateSceneSpecial();
	float loc2;
	float loc1;
	float scene_panning;
	float scene_timer;
	float time;
	int current_movie;
	float set_time;
	int max_scene;
	bool done;
	bool key_state;
	int current_image;
	float time_to_go;
	HPTSprite1* movie_sprite; 
	HPTSprite1* movie_sprite1; 
	HPTSprite1* movie_sprite2; 
	HPTSprite1* movie_sprite3; 
	HPTSprite1* movie_sprite4; 
	HPTSprite1* movie_sprite5; 
	HPTSprite1* movie_sprite6; 
	HPTSprite1* movie_sprite7; 
	HPTSprite1* movie_sprite8; 
	HPTSprite1* movie_sprite9; 
	HPTSprite1* movie_sprite10; 
	HPTSprite1* movie_sprite11; 
	HPTSprite1* text_dialog_sprite; 
	HPTSprite1* char_dialog_sprite_top; 
	HPTSprite1* char_dialog_sprite_bot; 
//	HPTSprite1* buttons_dialog_sprite; 
//	HPTSoundObject* music;
	HPTBackground* background;
	HPTFont1* black_font;
	HPTFont1* white_font;
	IGame *game;
	vector<Scene> scenes;
	int current_scene;
	bool prev_b,next_b,done_b;
	vector<HPTSprite1*> portraits;
	Input_Button* skipMovieButton;
	Input_Button* prevMovieButton;
	Input_Button* nextMovieButton;
	
#ifdef BOB_LITE
	Input_Button* buyGameButton;
	Input_Button* returnToMenuButton;
	float buyGameScreenTime;
	void CreateSceneLite();
#endif
	
};

#endif // !defined(AFX_THEATER_H__0E9A93BC_DEE2_4911_8C49_6DB13C807E19__INCLUDED_)
