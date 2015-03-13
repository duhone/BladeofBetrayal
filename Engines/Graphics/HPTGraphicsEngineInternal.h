#ifndef HPT_GRAPHICS_ENGINE_INTERNAL
#define HPT_GRAPHICS_ENGINE_INTERNAL

#define FORMAT555 1
#define FORMAT565 2
#define FORMAT888 4

#include "HPTGraphics.h"
#include "HPTTexturesInternal.h"
#include "HPTFont1Internal.h"
#include "HPTClipperInternal1.h"

#include "HPTBackgroundInternal.h"
#include "HPTTileBackgroundInternal.h"

//#include "IwGx.h"

#include "GLES/gl.h"
#include "GLES/egl.h"
//#import <GLES/EAGL.h>
//#import <OpenGLES/ES1/gl.h>
//#import <OpenGLES/ES1/glext.h>

#include<list>
#include<vector>
using namespace std;

#define HIGH_QUALITY 1
#define MED_QUALITY 2
#define LOW_QUALITY 3

class HPTGraphicsEngineInternal : public HPTGraphicsEngine  
{
public:
	int GetTextureEntrys();
	void RemoveSprite(HPTSprite1Internal* arg);
	void clear_screen();
	virtual int GetAvailableMemory();
	inline HPTTextureStruct* GetTexture(int number)
	{
		return textures->GetTextureInfo(number);
	};
	void AddRef();
	HPTGraphicsEngineInternal();
	virtual ~HPTGraphicsEngineInternal();
	virtual int LoadHGF(const char *name);
	virtual void Release();
	virtual HPTClipper1* CreateClipper1();
	virtual HPTSprite1* CreateSprite1(bool _singleSetMode = false);
	virtual HPTFont1* CreateFont1();
	virtual HPTBackground* CreateHPTBackground();
	virtual HPTTileBackground* CreateHPTTileBackground();
	virtual void BeginFrame();
	virtual void EndFrame();
	virtual void SetBackgroundColor(int red,int green,int blue);
	virtual void SetBackgroundImage(HPTBackground *arg);
	virtual HPTBackgroundInternal* GetBackgroundImage() const { return background_image;}
	virtual void SetTileBackgroundImage(int number,HPTTileBackground *arg);
	virtual void SetClipper(HPTClipper1 *clipper);
	virtual void SetClearScreen(bool arg);
	inline HPTClipperInternal1* GetClipper()
	{
		return current_clipper;
	};
	virtual HPTGraphicsEngine& operator<<(HPTFont1* arg);
	inline virtual HPTGraphicsEngine& operator<<(char* arg)
	{
		cur_font->Render(arg,cur_text_x,cur_text_y,cur_text_paragraph_x);	
		return *this;
	};
	virtual HPTGraphicsEngine& operator<<(int arg);
	virtual HPTGraphicsEngine& operator<<(double arg);
	virtual HPTGraphicsEngine& operator<<(unsigned int arg);
	inline virtual HPTGraphicsEngine& Position(int x,int y)
	{
		cur_text_x = x;
		cur_text_y = y;
		cur_text_paragraph_x = x;
		return *this;
	};
	virtual void EnableCapture(bool arg) {capture = arg; if(arg == true) next_capture = 0;};
	virtual void ReLoadGraphics();
	virtual void Free();
	
	/* The pixel dimensions of the backbuffer */
    GLint backingWidth;
    GLint backingHeight;
    
    //EAGLContext *context;
    
    /* OpenGL names for the renderbuffer and framebuffers used to render to this view */
    //GLuint viewRenderbuffer, viewFramebuffer;

	void ReleaseFont(HPTFont1Internal *_font);
	virtual void DisableAlphaTest();
	virtual void EnableAlphaTest();
	virtual void CacheTexture(int _texture);
	virtual void DrawTiles1();
	virtual void DrawTiles2();
	bool IsHD() const {return m_hd;}
	virtual void DumpUsage() {textures->DumpUsage();}
	virtual float GetAspectRatioMod() { return (320.0f/480.0f)*(backingWidth/(float)backingHeight);}
private:
	void ClearContext();
	void CreateContext();
	bool clearscreen;
	int quality;
	bool capture;
	int next_capture;
	bool landscape;
	int cur_text_paragraph_x;
	int cur_text_y;
	int cur_text_x;
	int clear_blue;
	int clear_green;
	int clear_red;
	int screen_format;
	int ref_count;
	HPTTexturesInternal* textures;
	HPTFont1Internal *cur_font;
	HPTBackgroundInternal *background_image;
	HPTTileBackgroundInternal *tile_image[2];
	HPTClipperInternal1 default_clipper;
	HPTClipperInternal1 *current_clipper;
	list<HPTSprite1Internal*> sprite_list;
	unsigned short *frame_pointer;
	int screen_size;
	//CIwMaterial* m_defaultMaterial;
	//vector<HPTSprite1*> m_layerSprites;

	int m_windowWidth;
	int m_windowHeight;
	EGLDisplay m_eglDisplay;
	EGLConfig m_eglConfig;
	EGLContext m_eglContext;
	EGLSurface m_eglSurface;
	std::vector<HPTFont1Internal*> m_fonts;
	bool m_hd;

protected:
};

#endif