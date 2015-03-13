#ifndef HPT_GRAPHICS_H
#define HPT_GRAPHICS_H

#define HFLIP 0x01
#define VFLIP 0x02
#define HPTOPAQUE 0x04

#define NORMAL_SIZE 0x01
#define DOUBLE_SIZE 0x02
#ifndef NULL 
#define NULL 0L
#endif

class HPTClipper1
{
public:
	HPTClipper1() {};
	virtual ~HPTClipper1() {};
	virtual void SetClipper(int upper_leftx,int upper_lefty,int lower_rightx,int lower_righty) = 0;
	virtual void Release() = 0;
};

class HPTBackground
{
public:
	HPTBackground() {};
	virtual ~HPTBackground() {};
	virtual void SetImage(int pallette_entry) = 0;
	virtual void Release() = 0;
};

class HPTTileBackground
{
public:
	HPTTileBackground() {};
	virtual ~HPTTileBackground() {};
	virtual void LoadTileSet(char *name) = 0;
	virtual void Release() = 0;
	virtual void SetPositionAbsalute(float x,float y) = 0;
	virtual void SetPositionRelative(int x,int y) = 0;

};


class HPTSprite1 {
public:
	HPTSprite1() {};
	virtual ~HPTSprite1() {};
	virtual void StepFrame() = 0;
	virtual void SetFrame(int frame) = 0;
	virtual void SetImage(int pallette_entry,bool _resetAnimation = true) = 0;
	virtual void SetFrameRate(float rate) = 0;
	virtual void UpdateFrameRate(float rate) = 0;
	virtual void SetAutoAnimate(bool arg) = 0;
	virtual void Render() = 0;
	virtual void RenderBatch(int _num) = 0;
	virtual void RenderHFlip() = 0;
	virtual void RenderVFlip() = 0;
	virtual void RenderHVFlip() = 0;
	virtual void SetPositionAbsalute(float x,float y) = 0;
	virtual void SetPositionRelative(int x,int y) = 0;
	virtual void Release() = 0;
	virtual void SetFrameSet(int set) = 0;
	virtual void NextFrameSet() = 0;
	virtual bool IsAnimating() = 0;
	virtual void AutoStopAnimate() = 0;
	virtual int GetFrameSet() = 0;
	virtual int GetFrame() = 0;
	virtual int GetFrameWidth() = 0;
	virtual int GetFrameHeight() = 0;
	virtual void EnableFrameSkip(bool arg) = 0;
	virtual void SetReverseAnimation(bool arg) = 0;
	virtual void PauseAnimation(bool arg) = 0;
	virtual void SetDesignSize(int _width,int _height) = 0;
	virtual int DesignWidth() const = 0;
	virtual int DesignHeight() const = 0;
};

class HPTFont1 {
public:
	HPTFont1() {};
	virtual ~HPTFont1() {};
	virtual void LoadHFFFont(char *fontname) = 0;
	virtual void Release() = 0;
};

class HPTGraphicsEngine {
public:
	HPTGraphicsEngine() {};
	virtual ~HPTGraphicsEngine() {};
	virtual int LoadHGF(const char *name) = 0;
	virtual int GetAvailableMemory() = 0;
	virtual void Release() = 0;
	virtual HPTClipper1* CreateClipper1() = 0;
	virtual HPTSprite1* CreateSprite1(bool _singleSetMode = false) = 0;
	virtual HPTFont1* CreateFont1() = 0;
	virtual HPTBackground* CreateHPTBackground() = 0;
	virtual HPTTileBackground* CreateHPTTileBackground() = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual void SetBackgroundColor(int red,int green,int blue) = 0;
	virtual void SetBackgroundImage(HPTBackground *arg) = 0;
	virtual void SetTileBackgroundImage(int number,HPTTileBackground *arg) = 0;
	virtual void SetClipper(HPTClipper1 *clipper) = 0;
	virtual void SetClearScreen(bool arg) = 0;
	virtual HPTGraphicsEngine& operator<<(HPTFont1* arg) = 0;
	virtual HPTGraphicsEngine& operator<<(char *arg) = 0;
	virtual HPTGraphicsEngine& operator<<(int arg) = 0;
	virtual HPTGraphicsEngine& operator<<(unsigned int arg) = 0;
	virtual HPTGraphicsEngine& operator<<(double arg) = 0;

	virtual HPTGraphicsEngine& Position(int x,int y) = 0;
	virtual void EnableCapture(bool arg) = 0;
	virtual void ReLoadGraphics() = 0;
	virtual void Free() = 0;
	virtual void EnableAlphaTest() = 0;
	virtual void DisableAlphaTest() = 0;
	virtual void CacheTexture(int _texture) = 0;
	virtual void DrawTiles1() = 0;
	virtual void DrawTiles2() = 0;

	virtual void DumpUsage() = 0;

	//how much to multiply height to account for aspect ratio. based on 480x320 design resolution
	virtual float GetAspectRatioMod() = 0;
};

HPTGraphicsEngine* GetHPTGraphicsEngine();

#endif
