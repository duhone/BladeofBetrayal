// Object.cpp: implementation of the Object class.
//
//////////////////////////////////////////////////////////////////////


#include "Object.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HPTGraphicsEngine *graphics_engine;

float Object::time = 0;

Object::Object()
{
	time = 0;
	sprite = graphics_engine->CreateSprite1();
	draw = false;
	sprite2 = graphics_engine->CreateSprite1();
	draw2 = false;
	sprite3 = graphics_engine->CreateSprite1();
	draw3 = false;
	SetPointValue(0);
	hflip_object = false;
/*	x_render_offset = 0;
	y_render_offset = 0;
*/
	gotObject = false;
	isCollidable = true;
}

Object::~Object()
{
	sprite->Release();
	sprite2->Release();
	sprite3->Release();
}

void Object::SetTime(float time_passed)
{
	time = time_passed;
}

void Object::SetPallette(int set, int pal_numb)
{
	pallete = pal_numb;
	sprite->SetImage(pal_numb);
	draw = true;

}

void Object::Render()
{
	if(draw2)
	{
		//(*graphics_engine).Position(50,150);
		//(*graphics_engine) << screenx_trans << " " << screeny_trans;
		sprite2->SetPositionAbsalute(/*worldx+*/screenx_trans/*+x_render_offset*/,/*worldy+*/screeny_trans/*+y_render_offset*/);
		sprite2->Render();
	}
	if(draw)
	{
		//(*graphics_engine).Position(50,150);
		//(*graphics_engine) << screenx_trans << " " << screeny_trans;
		sprite->SetPositionAbsalute(/*worldx+*/screenx_trans/*+x_render_offset*/,/*worldy+*/screeny_trans/*+y_render_offset*/);
		if(hflip_object) sprite->RenderHFlip();
			else sprite->Render();
	}
	if(draw3)
	{
		//(*graphics_engine).Position(50,150);
		//(*graphics_engine) << screenx_trans << " " << screeny_trans;
		sprite3->SetPositionAbsalute(/*worldx+*/screenx_trans/*+x_render_offset*/,/*worldy+*/screeny_trans/*+y_render_offset*/);
		sprite3->Render();
	}

}

/*void Object::SetWorldPosition(int x, int y)
{
	worldx = x;
	worldy = y;

}
*/
/*void Object::SetScreenTransform(int x, int y)
{
	screenx_trans = x;
	screeny_trans = y;
}
*/
bool Object::OnGround(int y)
{
	return false;
}

bool Object::WeaponCollideCheck(IPlayer *arg)
{
	return false;
}

bool Object::ProjectileCollideCheck(IPlayer *arg0, Projectile *arg)
{
	return false;
}

void Object::SetHFlip()
{
	hflip_object = true;
}
