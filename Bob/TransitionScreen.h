// TransitionScreen.h: interface for the TransitionScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSITIONSCREEN_H__308BC67A_5359_4D4A_B694_B42DCDE297EB__INCLUDED_)
#define AFX_TRANSITIONSCREEN_H__308BC67A_5359_4D4A_B694_B42DCDE297EB__INCLUDED_


#include "../Engines/Graphics/HPTGraphics.h"
//#include "CRSoundPlayer.h"
#include "Sound.h"

extern HPTGraphicsEngine* graphics_engine;

//extern CRSoundPlayer *soundPlayer;

class TransitionScreen  
{
public:
	TransitionScreen(bool arg);
	virtual ~TransitionScreen();

	void SetTime(float arg);
	void Begin(bool arg);
	void Update();
	void End();
	void Render();
	bool sActive;
private:
	HPTSprite1* background;
	HPTSprite1* slider;
	HPTSprite1* banner;

	float time;
	bool mode;
	float dx;
	float dy;
	float delaytimer;
	unsigned int starttime;
	unsigned int currenttime;
	float timerfreq;
	int nframes;
	bool snd_play;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFX;
};

#endif // !defined(AFX_TRANSITIONSCREEN_H__308BC67A_5359_4D4A_B694_B42DCDE297EB__INCLUDED_)
