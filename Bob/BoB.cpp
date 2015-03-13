// BoB.cpp : Defines the entry point for the application.
//


#include "../Engines/Graphics/hpt graphics.h"
#include "game.h"
//#include "resource.h"
//#include<new.h>
//#include <TapWave.h>



//HWND hwnd;
Game* game_class;
char path[256];

extern HPTInput_Engine* input_engine;


/*int my_new_handler(size_t size)
{
	static int new_retries = 0;
	if(new_retries < 6)
	{
		new_retries++;
		Sleep(250);
		return 1;
	}
	else
	{
		MessageBox(hwnd,("Out of memory. 9.5MB of free memory required"),("Error"),MB_OK);
		delete game_class;
		exit(1);
	}
};
*/
/*LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			game_class->CloseGame();
			return false;
		case WM_LBUTTONDOWN:
			PostQuitMessage(0);
			game_class->CloseGame();
			return false;

			
}
//return DefWindowProc(hwnd,message,wParam,lParam);
	return 0;
}
*/

/*int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
	//	MessageBox(0,lpCmdLine,lpCmdLine,MB_OK);

//	_set_new_handler(my_new_handler);
	int temp = GetLastError();
	GetModuleFileName(0,path,256);
	path[_tcslen(path) - 7] = 0;
	input_engine= HPTGetInputEngine();
	

	
#if defined POCKET_PC	
	// TODO: Place code here.
		WNDCLASS wc;
		wc.style = CS_NOCLOSE;
		wc.lpfnWndProc = input_engine->GetWndProc();
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(0,MAKEINTRESOURCE(IDI_ICON1));
		wc.hCursor = LoadCursor(hInstance,IDC_ARROW);
		wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = 0;
		wc.lpszClassName = ("BoB");
		RegisterClass(&wc);
		hwnd = CreateWindow(("BoB"),0,WS_POPUP,0,0,240,320,0,0,hInstance,0);
		SetWindowPos(hwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

#endif
		temp = GetLastError();

#if defined X86
		WNDCLASS wc;
		wc.style = 0;
		wc.lpfnWndProc = input_engine->GetWndProc();
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
		wc.hCursor = LoadCursor(0,IDC_ARROW);
		wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = 0;
		wc.lpszClassName = ("BoB");
		temp = GetLastError();
		RegisterClass(&wc);
		temp = GetLastError();

		RECT r1;
		SetRect(&r1,0,0,240,320);
		AdjustWindowRect(&r1,WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZE,0);
	
		hwnd = CreateWindow(("BoB"),("Blade of Betrayal"),WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,r1.right-r1.left,r1.bottom-r1.top,0,0,hInstance,0);
		temp = GetLastError();

#endif		
		
		ShowWindow(hwnd,SW_SHOW);
		SetFocus(hwnd);
		HPTSetWindow(hwnd);
		game_class = new Game();
		NEW(game_class);
		game_class->Initialize();
		
//		MessageBox(0, ("INPUT"), ("INPUT"), MB_OK);
		
		input_engine->RegisterInputObject(game_class);
		input_engine->RegisterInputEngineObject(game_class);

		//set up the default keys
		game_class->ky_left   = game_class->default_keys.vkLeft;
		game_class->ky_right  = game_class->default_keys.vkRight;
		game_class->ky_down   = game_class->default_keys.vkDown;
		game_class->ky_up     = game_class->default_keys.vkUp;
		game_class->ky_attack = game_class->default_keys.vkC;
		game_class->ky_jump   = game_class->default_keys.vkB;
		game_class->ky_menu   = game_class->default_keys.vkA;

//		MessageBox(0, ("INPUT"), ("INPUT"), MB_OK);

		game_class->ExecuteGame();

		delete game_class;
	return 0;
}
*/


SYSTEM_CALLBACK Boolean GameHandleEvent(EventType* eventP)
{
	Boolean						handled = false;
	RectangleType 				bounds;
//	static const RGBColorType 	fill = {0, 0x00, 0xFF, 0x00}; 
	
	switch (eventP->eType)
	{
		case winDisplayChangedEvent:
			// Resize the active window so that it matches the display window.
			WinGetBounds( WinGetDisplayWindow(), &bounds );
			WinSetBounds( WinGetActiveWindow(), &bounds );
			
			handled = true;
			break;

		case nilEvent:
		case frmUpdateEvent:
			// Paint the screen green just so we draw something.
/*			WinPushDrawState();
			WinSetDrawMode( winPaint );
			WinSetForeColorRGB( &fill, NULL );
			WinGetBounds( WinGetDisplayWindow(), &bounds );
			WinPaintRectangle( &bounds, 0 );
			WinPopDrawState();
*/	
			game_class->ExecuteGame();
			handled = true;
			break;
	}

	return (handled);
}


Err wakehandler(SysNotifyParamType *arg)
{
	((HPTGraphicsEngine*)(arg->userDataP))->ReLoadGraphics();

	return 0;
}
/***********************************************************************
 *
 * FUNCTION:    PilotMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  cmd - word value specifying the launch code. 
 *              cmdPB - pointer to a structure that is associated with the launch code. 
 *              launchFlags -  word value providing extra information about the launch.
 *
 * RETURNED:    Result of launch
 *
 ***********************************************************************/
extern UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	int		timeOut = evtWaitForever;
	timeOut = 5;
	MemHandle my_handle;
//	strcpy(path,"/PALM/programs/bob/");
#ifdef WIN32
	path[0] = 0;
#else
	strcpy(path,"/PALM/programs/bob/");
#endif
/*	if(cmd == sysNotifyLateWakeupEvent)
	{
//		gengine = GetHPTGraphicsEngine();
		
		((HPTGraphicsEngine*)(((SysNotifyParamType*)cmdPBP)->userDataP))->ReLoadGraphics();
//		gengine->Release();

	}*/
	if (cmd == sysAppLaunchCmdNormalLaunch) 
	{
		// Get the screen to a state we want.
		PINSetInputAreaState(pinInputAreaHide);
		StatHide();
		SysSetOrientation(sysOrientationLandscape);
		// Set everything up.
		TwAppStart(&GameHandleEvent);
		input_engine = HPTGetInputEngine();

		game_class = new Game();
		game_class->Initialize();
//		game_class->MadeIt();

		input_engine->RegisterInputObject(game_class);

	    SysCurAppDatabase(&my_handle);
	 
	      // Tell the system we want to know when 
	      // the device sleeps and wakes.
//	      SysNotifyRegister(my_handle, sysNotifyLateWakeupEvent, wakehandler,sysNotifyNormalPriority,gengine);

		// Run event loop.
		
		TwAppRun(&timeOut);
//	      SysNotifyUnregister(my_handle, sysNotifyLateWakeupEvent,sysNotifyNormalPriority);
		input_engine->Release();
		delete game_class;
		// Tear everything down.
		TwAppStop();
	}
	
	return 0;
}
