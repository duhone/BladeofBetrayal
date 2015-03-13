//-------------------------------------------------------------------------- 
// HelloWorld main file 
//-------------------------------------------------------------------------- 
  
#include "s3e.h" 
#include "../Engines/Graphics/HPTGraphics.h"

#include "../Bob/game.h"
#include "AppConfig.h"

//HPTGraphicsEngine* GGraphics;
//HPTGraphicsEngine *graphics_engine;

// Externs for functions which examples must implement 
/*void ExampleInit(); 
void ExampleShutDown(); 
void ExampleRender(); 
bool ExampleUpdate();*/ 
  
char path[256] = "";

Game* game_class;

extern Input_Engine* input_engine;

int UnPauseCallback(void* systemData, void* userData)
{
	if(AppConfig::Instance().IsAndroid())
	{
		HPTGraphicsEngine *graphicsEngine = GetHPTGraphicsEngine();
		graphicsEngine->ReLoadGraphics();
		graphicsEngine->Release();
	}
	return S3E_RESULT_SUCCESS;
}

int PauseCallback(void* systemData, void* userData)
{
	if(AppConfig::Instance().IsAndroid())
	{
		HPTGraphicsEngine *graphicsEngine = GetHPTGraphicsEngine();
		graphicsEngine->Free();
		graphicsEngine->Release();
	}
	return S3E_RESULT_SUCCESS;
}

s3eSurfaceBlitDirection hooptyFlip = S3E_SURFACE_BLIT_DIR_NORMAL;

int ScreenCallback(void* systemData, void* userData)
{
	s3eSurfaceOrientation *oreint = (s3eSurfaceOrientation*)systemData;
	hooptyFlip = oreint->m_DeviceBlitDirection;
	/*if(oreint->m_DeviceBlitDirection != S3E_SURFACE_BLIT_DIR_NORMAL)
	{
		hooptyFlip = -1.0f;
	}
	else
		hooptyFlip = 1.0f;*/
	return S3E_RESULT_SUCCESS;
}

//-------------------------------------------------------------------------- 
// Main global function 
//-------------------------------------------------------------------------- 
S3E_MAIN_DECL void IwMain() 
{ 
#ifdef EXAMPLE_DEBUG_ONLY 
// Test for Debug only examples 
#endif 
  
// Example main loop 
	input_engine = GetInputEngine();
	game_class = new Game();
	game_class->Initialize();
	input_engine->RegisterInputController(game_class);
	//graphics_engine = GetHPTGraphicsEngine();
	//graphics_engine->SetBackgroundColor(100,100,255);
	//ExampleInit(); 
	s3eDeviceRegister(S3E_DEVICE_PAUSE,PauseCallback,NULL);
	s3eDeviceRegister(S3E_DEVICE_UNPAUSE,UnPauseCallback,NULL);
	s3eSurfaceRegister(S3E_SURFACE_SCREENSIZE,ScreenCallback,NULL);

	while (1) 
	{ 
		s3eDeviceYield(0); 
		s3eKeyboardUpdate(); 
		//bool result = ExampleUpdate(); 
		if( /*(result == false) ||*/ (s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) || 
			(s3eKeyboardGetState(s3eKeyLSK) & S3E_KEY_STATE_DOWN) || (s3eDeviceCheckQuitRequest())) 
			break; 
		input_engine->InputChanged();
		game_class->ExecuteGame();
		//ExampleRender(); 
		//graphics_engine->BeginFrame();
		//graphics_engine->EndFrame();
		//s3eSurfaceShow(); 
	} 
	input_engine->Release();
	delete game_class;
	//graphics_engine->Release();
	//ExampleShutDown(); 
} 
