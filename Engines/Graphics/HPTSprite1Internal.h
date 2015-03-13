#ifndef HPT_SPRITE_1_INTERNAL_H
#define HPT_SPRITE_1_INTERNAL_H

#include "HPTGraphics.h"
#include "HPTTexturesInternal.h"

class HPTSprite1Internal;

typedef void (HPTSprite1Internal::*PNTRTOBLT)(void);
 
class HPTSprite1Internal : public HPTSprite1  
{
public:
	__inline void Render(char arg)
	{
		if(!disabled) (this->*(blits[arg]))();
	};
	void Refresh();
	void SetTexture(HPTTextureStruct *arg);
	HPTSprite1Internal(bool _singleSetMode = false);
	virtual ~HPTSprite1Internal();
	__inline virtual void StepFrame()
	{
		if(!reverse_animation)
		{
			current_frame++;
			if(current_frame > max_frame)
				current_frame = 0;
		}
		else
		{
			current_frame--;
			if(current_frame < 0)
				current_frame = max_frame;
		}

	};
	__inline virtual void SetFrame(int frame)
	{
		if(frame > max_frame) current_frame = 0;
		else current_frame = frame;
	};
	virtual void SetImage(int pallette_entry,bool _resetAnimation = true);
	virtual void SetFrameRate(float rate);
	virtual void UpdateFrameRate(float rate);
	virtual void SetAutoAnimate(bool arg);
	virtual void Render();
	virtual void RenderHFlip();
	virtual void RenderVFlip();
	virtual void RenderHVFlip();
	virtual void SetPositionAbsalute(float x,float y);
	__inline virtual void SetPositionRelative(int x,int y)
	{
		x_position += x;
		y_position += y;
	};
	virtual void Release();
	virtual void SetFrameSet(int set);
	virtual void NextFrameSet();
	virtual bool IsAnimating();
	virtual void AutoStopAnimate();
	virtual int GetFrameSet();
	virtual int GetFrame();
	virtual int GetFrameWidth()
	{
		return texture->width;
	}
	virtual int GetFrameHeight()
	{
		return texture->height;
	}
	virtual void EnableFrameSkip(bool arg)
	{
		frame_skip = arg;
	}
	virtual void SetReverseAnimation(bool arg);
	virtual void PauseAnimation(bool arg)
	{
		pause = arg;
	}
	
	virtual void RenderBatch(int _num);
	virtual void SetDesignSize(int _width,int _height)
	{
		m_useDesignScale = true;
		m_designWidth = _width;
		m_designHeight = _height;
	}
	virtual int DesignWidth() const
	{
		if(m_useDesignScale)
			return m_designWidth;
		else
			return texture->width;
	}
	virtual int DesignHeight() const
	{
		if(m_useDesignScale)
			return m_designHeight;
		else
			return texture->height;
	}
private:
	bool pause;
	bool reverse_animation;
	bool frame_skip;
	bool disabled;
	bool auto_stop;
	int current_frame_set;
	float time_to_animate;
	bool auto_animate;
	float frame_rate;
	float inv_frame_rate;
	int image_number;
	int max_frame;
	float y_position;
	float x_position;
	int current_frame;
	uint64_t starttime;
	uint64_t currenttime;
	float inverse_timerfreq;
	HPTTextureStruct *texture;
	PNTRTOBLT blits[16];
	GLfloat squarecoords[8];
	bool m_singleSetMode;
	bool m_useDesignScale;
	int m_designWidth;
	int m_designHeight;
protected:
	void GetUVBounds(GLfloat &_left,GLfloat &_right,GLfloat &_top,GLfloat &_bot);
	void BlitBase(GLfloat _squarecoords[]);
	void Blit();
	void BlitHFlip();
	void BlitVFlip();
	void BlitHVFlip();
	void BlitO();
	void BlitHO();
	void BlitVO();
	void BlitHVO();
	void AutoAnimate();
};

#endif