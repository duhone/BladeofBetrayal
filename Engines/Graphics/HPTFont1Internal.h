#ifndef HPT_FONT_INTERNAL_1_H
#define HPT_FONT_INTERNAL_1_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<string>
#include "HPTGraphics.h"
#include "HPTTexturesInternal.h"
#include "HPTSprite1Internal.h"

class HPTFont1Internal : public HPTFont1  
{
public:
	void Render(char *arg,int& x,int& y,int py);
	inline void SetPosition(int x,int y)
	{
		current_x = x;
		current_y = y;
		sprite.SetPositionAbsalute(x,y);
	};
	HPTFont1Internal();
	virtual ~HPTFont1Internal();
	virtual void LoadHFFFont(char *fontname);
	virtual void Release();
	void Reload();
	void Free();
private:
	void Clear();

	int current_y;
	int current_x;
	int keyred;
	int keygreen;
	int keyblue;
	int fringered;
	int fringegreen;
	int fringeblue;
	int height;
	int width;
	int charwidths[95];
	HPTTextureStruct *texture;
	HPTSprite1Internal sprite;
	int numChars;
	std::string m_fontName;
};

#endif