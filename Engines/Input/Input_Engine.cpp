#include "input_engine.h"

#include "s3e.h"
#include <iostream>

Input_Engine *inputengine = NULL;

extern s3eSurfaceBlitDirection hooptyFlip;

/*static int32 keyboardHandler(void* sys, void*)
{
    inputengine->InputChanged();
	return 0;
}*/

void MultiTouchButtonCB(s3ePointerTouchEvent* event)
{
	Touch touch;
	touch.ID = event->m_TouchID;
	touch.X = event->m_x;
	touch.Y = event->m_y;
	touch.Active = event->m_Pressed;
	inputengine->Touched(touch);
    /*CTouch* pTouch = GetTouch(event->m_TouchID);
    if( pTouch )
    {
        pTouch->active = event->m_Pressed != 0; 
        pTouch->x = event->m_x;
        pTouch->y = event->m_y;
    }*/
}

void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event)
{
	Touch touch;
	touch.ID = event->m_TouchID;
	touch.X = event->m_x;
	touch.Y = event->m_y;
	inputengine->TouchMoved(touch);
    /*CTouch* pTouch = GetTouch(event->m_TouchID);
    if( pTouch )
    {
        pTouch->x = event->m_x;
        pTouch->y = event->m_y;
    }*/
}

void SingleTouchButtonCB(s3ePointerEvent* event)
{
	if(event->m_Button == S3E_POINTER_BUTTON_LEFTMOUSE)
	{
		Touch touch;
		touch.ID = 0;
		touch.X = event->m_x;
		touch.Y = event->m_y;
		touch.Active = event->m_Pressed;
		inputengine->Touched(touch);
	}
    /*g_Touches[0].active = event->m_Pressed != 0;
    g_Touches[0].x = event->m_x;
    g_Touches[0].y = event->m_y;*/
}

void SingleTouchMotionCB(s3ePointerMotionEvent* event)
{
	Touch touch;
	touch.ID = 0;
	touch.X = event->m_x;
	touch.Y = event->m_y;
	inputengine->TouchMoved(touch);
    /*g_Touches[0].x = event->m_x;
    g_Touches[0].y = event->m_y;*/
}

Input_Engine* GetInputEngine()
{
	if(inputengine == NULL) inputengine = new Input_Engine;
	
	inputengine->AddRef();
	
	return inputengine;
}

Input_Engine::Input_Engine()
{
	input_controller = NULL;
	ref_count = 0;	
	if( s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) )
    {
        //Register for multi touch events on platforms where the functionality is available.
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, NULL);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, NULL);
    }
    else
    {
        //Register for standard pointer events
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB, NULL);
    }    
	//s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, keyboardHandler, NULL);

	int screenWidth = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	int screenHeight = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
	m_widthFactor = 480.0f/screenWidth;
	m_heightFactor = 320.0f/screenHeight;
}	

Input_Engine::~Input_Engine()
{   
	if( s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) )
    {
        s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB);
        s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB);
    }
    else
    {
        s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB);
        s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB);
    }
	//s3eKeyboardUnRegister(S3E_KEYBOARD_KEY_EVENT, keyboardHandler);
}

void Input_Engine::TransformTouch(Touch &_touch)
{
	int screenWidth = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	int screenHeight = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
	m_widthFactor = 480.0f/screenWidth;
	m_heightFactor = 320.0f/screenHeight;

	_touch.X *= m_widthFactor;
	_touch.Y *= m_heightFactor;
	
	/*if(s3eDeviceGetInt(S3E_DEVICE_OS) == S3E_OS_ID_IPHONE)
	{	
		if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT270)
		{
			_touch.Y = 320 - _touch.Y;
			_touch.X = 480 - _touch.X;
		}
	}	*/
}

bool Input_Engine::RegisterInputController(Input_Controller* arg)
{
	//ResetControls();
	input_controller = arg;
	ResetControls();
	return true;
}

Touch& Input_Engine::GetTouch(int _id)
{
	for(int i = 0;i < m_touches.size();++i)
	{
		if(m_touches[i].ID == _id)
			return m_touches[i];
	}
	m_touches.push_back(Touch(_id));
	return m_touches.back();
}

void Input_Engine::Touched(Touch &_touch)
{
	if (input_controller == NULL) return;
	TransformTouch(_touch);

	Touch &touch = GetTouch(_touch.ID);
	if(touch.Active == _touch.Active)
		return;
	bool pressed;
	_touch.Active ? pressed = true : pressed = false;
	touch = _touch;
	if(pressed)
	{
		for (int i = 0; i < input_controller->input_objects.size(); i++)
		{
			input_controller->input_objects[i]->TouchesBegan(touch);
		}
	}
	else
	{
		for (int i = 0; i < input_controller->input_objects.size(); i++)
		{
			input_controller->input_objects[i]->TouchesEnded(touch);
		}
	}
	
	input_controller->InputChanged();
}

void Input_Engine::TouchMoved(Touch &_touch)
{
	if (input_controller == NULL) return;
	TransformTouch(_touch);
	
	Touch touch = GetTouch(_touch.ID);
	if(touch.Active)
	{
		touch = _touch;

		for (int i = 0; i < input_controller->input_objects.size(); i++)
		{
			input_controller->input_objects[i]->TouchesMoved(touch);
		}
		
		input_controller->InputChanged();
	}
}

void Input_Engine::InputChanged()
{
	input_controller->InputChanged();
}

/*void Input_Engine::TouchesEnded(UIView *view, NSSet *touches)
{
	if (input_controller == NULL) return;
	
	for (int i = 0; i < input_controller->input_objects.size(); i++)
	{
		input_controller->input_objects[i]->TouchesEnded(view, touches);
	}
	
	input_controller->InputChanged();
}*/

/*void Input_Engine::TouchesCancelled(UIView *view, NSSet *touches)
{
	if (input_controller == NULL) return;
	
	for (int i = 0; i < input_controller->input_objects.size(); i++)
	{
		input_controller->input_objects[i]->TouchesCancelled(view, touches);
	}
	
	input_controller->InputChanged();
}*/


//Input_Button* Input_Engine::CreateButton()
//{
//	Input_Button *btn = new Input_Button();
//	input_objects.push_front(btn);
//	return btn;
//}

//Input_Analog* Input_Engine::CreateAnalogStick()
//{
//	Input_Analog *analog = new Input_Analog();
//	input_objects.push_front(analog);
//	return analog;
//}

void Input_Engine::Release()
{
	--ref_count;
	
	if(ref_count == 0)
	{
		// delete all input objects
		//for(list<Input_Object*>::iterator tempi = input_objects.begin();tempi != input_objects.end();)
		//{
		//	delete (*tempi);
		//	tempi = input_objects.erase(tempi);
		//}
		
		delete this;
		inputengine=NULL;
	}
}
			
void Input_Engine::ResetControls()
{
	if (input_controller != NULL)
	{
		for (int i = 0; i < input_controller->input_objects.size(); i++)
		{
			input_controller->input_objects[i]->Reset();
		}
	}
}
