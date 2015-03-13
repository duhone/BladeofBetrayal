// ProgressMeter.h: interface for the ProgressMeter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRESSMETER_H__E600B7FB_12A8_4537_9E0B_E1BDFEA7A641__INCLUDED_)
#define AFX_PROGRESSMETER_H__E600B7FB_12A8_4537_9E0B_E1BDFEA7A641__INCLUDED_


#include "../Engines/Graphics/HPTGraphics.h"

extern HPTGraphicsEngine *graphics_engine;
extern char path[256];

class ProgressMeter  
{
public:
	ProgressMeter(const char *string, int xLoc, int yLoc = 150);
	virtual ~ProgressMeter();

	bool SetTickCount(unsigned int dzTickCount);
	bool SetTickInterval(unsigned int dzTickInterval);
	bool SetUpdateInterval(unsigned int dzUpdateInterval);
	bool SetProgressTimer(unsigned int dzTime);
	bool ProgressMeterStart();
	bool ProgressMeterStop();

	void Update();
	void Finish();

private:
	static HPTFont1* pMeterFont;

//	HWND hWnd;

	unsigned int dzTime;
	unsigned int dzTickCount;
	static unsigned int dzTickInterval;
	static unsigned int dzTickCurrent;
	static unsigned int dzUpdateInterval;
	static char tString[255];

	static int xLoc;
	static int yLoc;

	//Loading Bar
	static bool bIsActive;
	static int pProgress;
	static int pTotalProgress;
	static unsigned int pCurrentTime;
	static unsigned int pPreviousTime;
	static unsigned int pStartTime;

//	static void CALLBACK ProgressMeterCALLBACK(HWND hwnd, UINT uMsg, UINT idEvent, unsigned int dwTime ); 
};

#endif // !defined(AFX_PROGRESSMETER_H__E600B7FB_12A8_4537_9E0B_E1BDFEA7A641__INCLUDED_)
