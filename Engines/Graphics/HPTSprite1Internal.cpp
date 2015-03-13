
#include "HPTSprite1Internal.h"
#include "HPTGraphicsEngineInternal.h"
#include "HPTTexturesInternal.h"
#include "HPTClipperInternal1.h"

#include "s3eTimer.h"
#include "GLES/gl.h"
#include "GLES/egl.h"
//#include<OpenGLES/ES1/gl.h>
//#include<OpenGLES/ES1/glext.h>

extern HPTGraphicsEngineInternal *gengine;

#define NOT_ASSIGNED 0x0ffffffff

HPTSprite1Internal::HPTSprite1Internal(bool _singleSetMode) : m_singleSetMode(_singleSetMode),
	m_useDesignScale(false)
{
	pause = false;
	reverse_animation = false;
		frame_skip = true;
	x_position = 0;
	y_position = 0;
	max_frame = 2;
	current_frame = 0;
	//mach_timebase_info_data_t time_info;
	//mach_timebase_info(&time_info);

	//inverse_timerfreq = time_info.numer/(float)time_info.denom;
	inverse_timerfreq = 1/1000.0f;
	
	starttime = s3eTimerGetMs();
	time_to_animate = 1.0f;
	auto_animate = false;
	frame_rate = 1.0f;
	inv_frame_rate = 1.0f;
	image_number = NOT_ASSIGNED;
	current_frame_set = 0;
	texture = NULL;
	auto_stop = false;
	disabled = false;
	blits[0] = &HPTSprite1Internal::Blit;
	blits[HFLIP] = &HPTSprite1Internal::BlitHFlip;
	blits[VFLIP] = &HPTSprite1Internal::BlitVFlip;
	blits[HFLIP | VFLIP] = &HPTSprite1Internal::BlitHVFlip;
	blits[HPTOPAQUE] = &HPTSprite1Internal::BlitO;
	blits[HFLIP | HPTOPAQUE] = &HPTSprite1Internal::BlitHO;
	blits[VFLIP | HPTOPAQUE] = &HPTSprite1Internal::BlitVO;
	blits[HFLIP | VFLIP | HPTOPAQUE] = &HPTSprite1Internal::BlitHVO;

}

HPTSprite1Internal::~HPTSprite1Internal()
{
}

void HPTSprite1Internal::SetImage(int pallette_entry,bool _resetAnimation/* = true*/)
{
	if(image_number == pallette_entry) return;
	if(image_number != NOT_ASSIGNED) texture->ReleaseTexture();
		image_number = pallette_entry;
	if(image_number >= gengine->GetTextureEntrys())
	{
		disabled = true;
		image_number = NOT_ASSIGNED;
		return;
	}
	else disabled = false;
	texture = gengine->GetTexture(pallette_entry);
	texture->UseTexture();
	auto_animate = texture->default_auto_animate;
	frame_rate = texture->default_frame_rate;
	if(frame_rate < 0.00001f) frame_rate = 0.00001f;
	inv_frame_rate = 1.0f/frame_rate;
	time_to_animate = inv_frame_rate;
	if(!m_singleSetMode)
		max_frame = texture->frames_per_set[0] - 1;
	else
	{
		max_frame = (texture->num_frame_sets-1)*texture->frames_per_set[0];
		max_frame += texture->frames_per_set[texture->num_frame_sets-1] - 1;
	}
	if(_resetAnimation)
	{
		starttime = s3eTimerGetMs();

		SetFrameSet(0);
	}
	else
	{
		max_frame = texture->frames_per_set[current_frame_set] - 1;
	}
}

void HPTSprite1Internal::SetFrameRate(float rate)
{
		if(rate < 0.0001f) rate = 0.0001f;
	frame_rate = rate;
	inv_frame_rate = 1.0f/frame_rate;     
	time_to_animate = inv_frame_rate;

}

void HPTSprite1Internal::UpdateFrameRate(float rate)
{
	float old_irate = inv_frame_rate;
	if(rate < 0.0001f) rate = 0.0001f;
	frame_rate = rate;
	inv_frame_rate = 1.0f/frame_rate;     
	time_to_animate = inv_frame_rate - (old_irate - time_to_animate);

}
void HPTSprite1Internal::SetAutoAnimate(bool arg)
{
		auto_animate = arg;
	starttime = s3eTimerGetMs();
	currenttime = s3eTimerGetMs();
	auto_stop = false;

	time_to_animate = inv_frame_rate;

}

void HPTSprite1Internal::Render()
{
	if(disabled) return;
	if(auto_animate) AutoAnimate();

	(this->*blits[0])();
}

void HPTSprite1Internal::RenderBatch(int _num)
{
	if(disabled || _num==0) return;
	
	GLfloat *squarecoords = new GLfloat[8*_num];
	
	GLfloat top,bot,left,right;
	GetUVBounds(left,right,top,bot);
	
	for(int i =0; i < _num;++i)
	{
		int base = i*8;
		squarecoords[base] = left;
		squarecoords[base+2] = right;	
		squarecoords[base+4] = left;	
		squarecoords[base+6] = right;
		
		squarecoords[base+1] = bot;
		squarecoords[base+3] = bot;
		squarecoords[base+5] = top;
		squarecoords[base+7] = top;
	}
	
	GLfloat *squareVertices = new GLfloat[8*_num];
	
	int width,height;
	if(m_useDesignScale)
	{
		width = m_designWidth;
		height = m_designHeight;
	}
	else
	{
		width = texture->width;
		height = texture->height;
	}

	int xstart = x_position-240-(width>>1);
	int ystart = 160-y_position-(height>>1);
	

	for(int i = 0;i < _num;++i)
	{
		int base = i*8;
		squareVertices[base] = xstart;
		squareVertices[base+1] = ystart;
		squareVertices[base+2] = xstart+width;
		squareVertices[base+3] = ystart;
		squareVertices[base+4] = xstart;
		squareVertices[base+5] = ystart+height;
		squareVertices[base+6] = xstart+width;
		squareVertices[base+7] = ystart+height;
		xstart += width;
	}
		
	if(!m_singleSetMode)
		glBindTexture(GL_TEXTURE_2D,texture->glTextureIds[current_frame_set]);
	else
		glBindTexture(GL_TEXTURE_2D,texture->glTextureIds[current_frame/texture->frames_per_set[0]]);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if(gengine->IsHD())
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glEnable(GL_TEXTURE_2D);
	
    glVertexPointer(2, GL_FLOAT, 0, squareVertices);
    glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, squarecoords);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4*_num);

	delete[] squarecoords;
	delete[] squareVertices;
}

void HPTSprite1Internal::RenderHFlip()
{
	if(disabled) return;
	if(auto_animate) AutoAnimate();

	(this->*blits[HFLIP])();

}

void HPTSprite1Internal::RenderVFlip()
{
		if(disabled) return;
	if(auto_animate) AutoAnimate();

	(this->*blits[VFLIP])();
}

void HPTSprite1Internal::RenderHVFlip()
{
		if(disabled) return;
	if(auto_animate) AutoAnimate();

	(this->*blits[HFLIP | VFLIP])();
}

void HPTSprite1Internal::Release()
{
	if(image_number != NOT_ASSIGNED)
		if(texture != NULL) texture->ReleaseTexture();
	gengine->RemoveSprite(this);
	delete this;
}

void HPTSprite1Internal::AutoAnimate()
{
	float timepassed;
	currenttime = s3eTimerGetMs();
	timepassed = (currenttime - starttime)*inverse_timerfreq;
	timepassed = min(timepassed, 1.0f/10.0f);
	starttime = currenttime;
	if(pause) return;
	time_to_animate -= timepassed;
	if(time_to_animate <= 0)
	{
		if(frame_skip)
		{
			while(time_to_animate <= 0)
			{
				StepFrame();
				time_to_animate += inv_frame_rate;
				if(auto_stop)
				{
					if(!reverse_animation)
					{
						if(current_frame == max_frame)
						{
							auto_animate = false;
							auto_stop = false;
							return;
						}
					}
					else
					{
						if(current_frame == 0)
						{
							auto_animate = false;
							auto_stop = false;
							return;
						}
					}

				}
			}
		}
		else
		{
			StepFrame();
			time_to_animate += inv_frame_rate;
			if(auto_stop)
			{
				if(!reverse_animation)
				{
					if(current_frame == max_frame)
					{
						auto_animate = false;
						auto_stop = false;
						return;
					}
				}
				else
				{
					if(current_frame == 0)
					{
						auto_animate = false;
						auto_stop = false;
						return;
					}
				}

				
			}

		}
	}
	if(auto_stop)
		if(current_frame == max_frame)
		{
			auto_animate = false;
			auto_stop = false;
		}
}

void HPTSprite1Internal::BlitBase(GLfloat _squarecoords[])
{
	GLfloat squareVertices[] = {
        -1.0f, -1.0f,
        1.0f,  -1.0f,
        -1.0f,  1.0f,
        1.0f,   1.0f,
	};		
			
	glPushMatrix();
	glTranslatef(x_position-240, 160-y_position, -60.0f);
	if(m_useDesignScale)
		glScalef(m_designWidth>>1, m_designHeight>>1, 1);
	else
		glScalef(texture->width>>1, texture->height>>1, 1);
	
	if(!m_singleSetMode)
		glBindTexture(GL_TEXTURE_2D,texture->glTextureIds[current_frame_set]);
	else
		glBindTexture(GL_TEXTURE_2D,texture->glTextureIds[current_frame/texture->frames_per_set[0]]);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if(gengine->IsHD())
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glEnable(GL_TEXTURE_2D);
	
    glVertexPointer(2, GL_FLOAT, 0, squareVertices);
    glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _squarecoords);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glPopMatrix();				  
	
}

void HPTSprite1Internal::GetUVBounds(GLfloat &_left,GLfloat &_right,GLfloat &_top,GLfloat &_bot)
{	
	int heightp2 = texture->GetNextPowerOf2(texture->height);
	int diffheight = heightp2-texture->height;
	int top = diffheight/2;
	int bot = top+texture->height-1;
	int left;	
	if(!m_singleSetMode)
		left = texture->width*current_frame;
	else
		left = texture->width*(current_frame%texture->frames_per_set[0]);	
	int right = left + texture->width-1;
		
	_top = static_cast<GLfloat>(top)/heightp2 + texture->m_halfv;
	_bot = static_cast<GLfloat>(bot)/heightp2 + texture->m_halfv;
	_left = static_cast<GLfloat>(left)/(texture->total_width) + texture->m_halfu;
	_right = static_cast<GLfloat>(right)/(texture->total_width) + texture->m_halfu;	
}

void HPTSprite1Internal::Blit()
{		
	GLfloat top,bot,left,right;
	GetUVBounds(left,right,top,bot);
	
	squarecoords[0] = left;
	squarecoords[2] = right;	
	squarecoords[4] = left;	
	squarecoords[6] = right;
	
	squarecoords[1] = bot;
	squarecoords[3] = bot;
	squarecoords[5] = top;
	squarecoords[7] = top;

	BlitBase(squarecoords);	
}


void HPTSprite1Internal::BlitHFlip()
{		
	GLfloat top,bot,left,right;
	GetUVBounds(left,right,top,bot);
	
	squarecoords[0] = right;
	squarecoords[2] = left;	
	squarecoords[4] = right;	
	squarecoords[6] = left;
	
	squarecoords[1] = bot;
	squarecoords[3] = bot;
	squarecoords[5] = top;
	squarecoords[7] = top;
	
	BlitBase(squarecoords);
}

void HPTSprite1Internal::BlitVFlip()
{		
	GLfloat top,bot,left,right;
	GetUVBounds(left,right,top,bot);
	
	squarecoords[0] = left;
	squarecoords[2] = right;	
	squarecoords[4] = left;	
	squarecoords[6] = right;
	
	squarecoords[1] = top;
	squarecoords[3] = top;
	squarecoords[5] = bot;
	squarecoords[7] = bot;
	
	BlitBase(squarecoords);
}

void HPTSprite1Internal::BlitHVFlip()
{	
	GLfloat top,bot,left,right;
	GetUVBounds(left,right,top,bot);
	
	squarecoords[0] = right;
	squarecoords[2] = left;	
	squarecoords[4] = right;	
	squarecoords[6] = left;
	
	squarecoords[1] = top;
	squarecoords[3] = top;
	squarecoords[5] = bot;
	squarecoords[7] = bot;
	
	BlitBase(squarecoords);
}

void HPTSprite1Internal::BlitO()
{
	Blit();	
}

void HPTSprite1Internal::BlitHO()
{
	BlitHFlip();
}

void HPTSprite1Internal::BlitVO()
{
	BlitVFlip();
}

void HPTSprite1Internal::BlitHVO()
{
	BlitHVFlip();
}

void HPTSprite1Internal::SetFrameSet(int set)
{
	if(m_singleSetMode)
		return;
	if(current_frame_set == set) return;
	auto_stop = false;
	current_frame_set = set;
	if(disabled) return;
	int max_set = texture->num_frame_sets;
	if(current_frame_set > max_set-1) current_frame_set = max_set-1;
	max_frame = texture->frames_per_set[current_frame_set] - 1;

}

void HPTSprite1Internal::NextFrameSet()
{
	if(m_singleSetMode)
		return;
	int max_set = texture->num_frame_sets;
	current_frame_set++;
	if(current_frame_set > max_set-1) current_frame_set = 0;
	max_frame = texture->frames_per_set[current_frame_set] - 1;
}

void HPTSprite1Internal::SetTexture(HPTTextureStruct *arg)
{
	texture = arg;
	max_frame = texture->frames_per_set[current_frame_set] - 1;
	
	SetFrameSet(0);
	current_frame_set = 0;

}

bool HPTSprite1Internal::IsAnimating()
{
	return auto_animate;
}

void HPTSprite1Internal::AutoStopAnimate()
{
	auto_stop = true;
}

void HPTSprite1Internal::Refresh()
{
	if(image_number >= gengine->GetTextureEntrys())
	{
		disabled = true;
		image_number = NOT_ASSIGNED;
		return;
	}
	else disabled = false;

	texture = gengine->GetTexture(image_number);
	texture->UseTexture();
	auto_animate = texture->default_auto_animate;
	frame_rate = texture->default_frame_rate;
	if(frame_rate < 0.00001f) frame_rate = 0.00001f;
	
	if(!m_singleSetMode)
		max_frame = texture->frames_per_set[0] - 1;
	else
	{
		max_frame = (texture->num_frame_sets-1)*texture->frames_per_set[0];
		max_frame += texture->frames_per_set[texture->num_frame_sets-1] - 1;
	}
	
	starttime = s3eTimerGetMs();
	time_to_animate = 1.0f/frame_rate;
	SetFrame(0);
	SetFrameSet(0);
}

int HPTSprite1Internal::GetFrameSet()
{
	if(m_singleSetMode)
		return 0;
	else
		return current_frame_set;
}

int HPTSprite1Internal::GetFrame()
{
	return current_frame;
}

void HPTSprite1Internal::SetReverseAnimation(bool arg)
{
	reverse_animation = arg;
}

void HPTSprite1Internal::SetPositionAbsalute(float x,float y)
{
	if(gengine->IsHD())
	{
		x_position = x;
		y_position = y;
	}
	else
	{
		x_position = round(x);
		y_position = round(y);
	}
}