#include "HPTGraphicsEngineInternal.h"
#include "HPTSprite1Internal.h"
#include "HPTBackgroundInternal.h"

#include "s3e.h"
#include "../Utility/FunctionObjects.h"
#include <functional>

extern HPTGraphicsEngineInternal *gengine;
using namespace CR::Utility;

static void checkGLErrors()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "GL Error");
    }
}


static void checkEGLErrors()
{
    EGLint error = eglGetError();
    if (error != EGL_SUCCESS)
    {
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "EGL Error");
    }
}

HPTGraphicsEngineInternal::HPTGraphicsEngineInternal() :
	m_windowWidth(0),
	m_windowHeight(0),
	m_eglDisplay(EGL_NO_DISPLAY),
	m_eglContext(EGL_NO_CONTEXT),
	m_eglSurface(EGL_NO_SURFACE)
{
	textures = new HPTTexturesInternal();

	ref_count = 0;
	cur_text_x = 20;
	cur_text_y = 20;
	cur_text_paragraph_x = 20;
	
	background_image = NULL;
	tile_image[0] = NULL;
	tile_image[1] = NULL;

	default_clipper.SetClipper(0,0,479,319);
	current_clipper = &default_clipper;
	capture = false;
	clearscreen = true;
	CreateContext();

	/*IwGxInit();
	IwGxSetSortMode(IW_GX_SORT_NONE);
	IwGxSetFarZNearZ(50000, 50);
	IwGxSetPerspMul(IwGxGetScreenWidth() / 2);
	IwGxSetScreenOrient(IW_GX_ORIENT_90);
	IwGxSetColClear(0,0,0,255);

	m_defaultMaterial = new CIwMaterial;
	IwGxSetMaterial(m_defaultMaterial);*/
}

HPTGraphicsEngineInternal::~HPTGraphicsEngineInternal()
{
	ClearContext();
	//delete m_defaultMaterial;
	//IwGxTerminate();
}

void HPTGraphicsEngineInternal::ClearContext()
{
    eglMakeCurrent(m_eglDisplay, NULL, NULL, NULL);
    eglDestroyContext(m_eglDisplay, m_eglContext);
    eglDestroySurface(m_eglDisplay, m_eglSurface);
    eglTerminate(m_eglDisplay);
}

void HPTGraphicsEngineInternal::CreateContext()
{
    static const EGLint configAttribs[] =
    {
        EGL_RED_SIZE,       8,
        EGL_GREEN_SIZE,     8,
        EGL_BLUE_SIZE,      8,
        EGL_DEPTH_SIZE,     0,
        EGL_ALPHA_SIZE,     EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   0,
        //EGL_SURFACE_TYPE,   EGL_WINDOW_BIT,
        EGL_NONE
    };
    EGLBoolean success;
    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;

    m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    success = eglInitialize(m_eglDisplay, &majorVersion, &minorVersion);
    if (success != EGL_FALSE)
        success = eglGetConfigs(m_eglDisplay, NULL, 0, &numConfigs);
    if (success != EGL_FALSE)
        success = eglChooseConfig(m_eglDisplay, configAttribs,
                                  &m_eglConfig, 1, &numConfigs);
    if (success != EGL_FALSE)
    {
        m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig,
                                             s3eGLGetNativeWindow(), NULL);
        if (m_eglSurface == EGL_NO_SURFACE)
            success = EGL_FALSE;
    }
    if (success != EGL_FALSE)
    {
        m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, NULL, NULL);
        if (m_eglContext == EGL_NO_CONTEXT)
            success = EGL_FALSE;
    }
    if (success != EGL_FALSE)
        success = eglMakeCurrent(m_eglDisplay, m_eglSurface,
                                 m_eglSurface, m_eglContext);

    if (success == EGL_FALSE)
        checkEGLErrors();
	
	backingWidth = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	backingHeight = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

	if(backingWidth > 480 || backingHeight > 480)
		m_hd = true;
	else
		m_hd = false;

	glDisable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL,0.85f); 

	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_NORMALIZE);
	glDisable(GL_SCISSOR_TEST);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_DITHER);

	eglSwapInterval(m_eglDisplay,2);
}

int HPTGraphicsEngineInternal::LoadHGF(const char *_name)
{ 
	char *name = const_cast<char*>(_name);

	textures->LoadHGF(name);

	return 0;
}
void HPTGraphicsEngineInternal::Release()
{
	ref_count--;
	if(ref_count == 0)
	{
		gengine = NULL;
		delete this;
	}
}

HPTSprite1* HPTGraphicsEngineInternal::CreateSprite1(bool _singleSetMode)
{
	HPTSprite1Internal *temp;
	temp = new HPTSprite1Internal(_singleSetMode);
	return temp;
}

HPTBackground* HPTGraphicsEngineInternal::CreateHPTBackground()
{
	HPTBackgroundInternal *temp = new HPTBackgroundInternal();
	return temp;
}

HPTTileBackground* HPTGraphicsEngineInternal::CreateHPTTileBackground()
{
	HPTTileBackgroundInternal *temp = new HPTTileBackgroundInternal();
	return temp;
}

HPTFont1* HPTGraphicsEngineInternal::CreateFont1()
{
	HPTFont1Internal *temp = new HPTFont1Internal();
	m_fonts.push_back(temp);
	return temp;

	//return 0;
}

HPTClipper1* HPTGraphicsEngineInternal::CreateClipper1()
{
	HPTClipperInternal1 *temp = new HPTClipperInternal1();
	return temp;
}

extern s3eSurfaceBlitDirection hooptyFlip;

void HPTGraphicsEngineInternal::BeginFrame()
{	
	backingWidth = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	backingHeight = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

	bool iphone = false;
	if(s3eDeviceGetInt(S3E_DEVICE_OS) == S3E_OS_ID_IPHONE)
		iphone = true;
	
	if(!iphone)
		glViewport(0, 0, backingWidth, backingHeight);
	else
		glViewport(0, 0, backingHeight, backingWidth);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT90 || hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT270)
		glOrthof(-160.0f, 160.0f, -240.0f, 240.0f, 0.0f, 100.0f);
	//else
	//	glOrthof(-240.0f, 240.0f, -160.0f, 160.0f, 0.0f, 100.0f);
	//if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT90)
	//	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	//else if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT180)
	//	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	//else if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT270)
	//	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	//else
	//	glRotatef(0.0f, 0.0f, 0.0f, 1.0f);

	s3eSurfaceBlitDirection flip = (s3eSurfaceBlitDirection)s3eSurfaceGetInt(S3E_SURFACE_BLIT_DIRECTION);

	if(!iphone)
	{
		if(flip == S3E_SURFACE_BLIT_DIR_ROT270)
		{
			glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
			glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
		}
		else if(flip == S3E_SURFACE_BLIT_DIR_ROT180)
		{
			glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
			glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
		}
		else if(flip == S3E_SURFACE_BLIT_DIR_ROT90)
		{
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
		}
		else if(flip == S3E_SURFACE_BLIT_DIR_NORMAL)
		{
			glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
			glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
		}
		else if(flip == S3E_SURFACE_BLIT_DIR_NATIVE)
		{
			glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
			glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
		}
		else
		{
			glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
			glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
		}
	}
	else
	{
		if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT270)
		{
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(480.0f/480.0f, 320.0f/320.0f, 1.0f);
		}
		else if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT180)
		{
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
		}
		else if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT90)
		{
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(480.0f/480.0f, 320.0f/320.0f, 1.0f);
		}
		else
		{
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
		}
	}
	//glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
	//glScalef(480.0f/480.0f, 320.0f/320.0f, 1.0f);
	
    glMatrixMode(GL_MODELVIEW);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	
	if(background_image == NULL)
	{
		if(clearscreen)
			clear_screen();
	}
	else background_image->RenderHighQuality(0,0);
	//clear_screen();
	//if(background_image)
	//	background_image->RenderHighQuality(0,0);
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
}

void HPTGraphicsEngineInternal::DrawTiles1()
{
	/*if(m_hd)
	{
		glDisable(GL_ALPHA_TEST);
		//glEnable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}*/
	if(tile_image[0])
		tile_image[0]->Render();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
}

void HPTGraphicsEngineInternal::DrawTiles2()
{	
	/*if(m_hd)
	{
		glDisable(GL_ALPHA_TEST);
		//glEnable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}*/
	if(tile_image[1])
		tile_image[1]->Render();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
}

void HPTGraphicsEngineInternal::DisableAlphaTest()
{
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
}

void HPTGraphicsEngineInternal::EnableAlphaTest()
{
	if(m_hd)
	{
		glEnable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
}

void HPTGraphicsEngineInternal::EndFrame()
{
	
    eglSwapBuffers(m_eglDisplay, m_eglSurface);
    checkEGLErrors();
	s3eDeviceYield(0);
}

void HPTGraphicsEngineInternal::AddRef()
{
	ref_count++;
}

void HPTGraphicsEngineInternal::SetBackgroundColor(int red,int green,int blue)
{
	clear_red = red;
	clear_green = green;
	clear_blue = blue;
}

void HPTGraphicsEngineInternal::SetBackgroundImage(HPTBackground *arg)
{
	background_image = static_cast<HPTBackgroundInternal*>(arg);
}

void HPTGraphicsEngineInternal::SetClearScreen(bool arg)
{
	clearscreen = arg;
}

void HPTGraphicsEngineInternal::SetClipper(HPTClipper1 *clipper)
{
	if(clipper == NULL) current_clipper = &default_clipper;
	else current_clipper = static_cast<HPTClipperInternal1*>(clipper);
}

void HPTGraphicsEngineInternal::SetTileBackgroundImage(int number,HPTTileBackground *arg)
{
	if(number > 1) number = 1;
	tile_image[number] = static_cast<HPTTileBackgroundInternal*>(arg);
}

HPTGraphicsEngine& HPTGraphicsEngineInternal::operator<<(HPTFont1* arg)
{
	cur_font = (HPTFont1Internal*)arg;
	return *this;
}

HPTGraphicsEngine& HPTGraphicsEngineInternal::operator<<(int arg)
{
	char temp[12];
	sprintf(temp,"%d",arg);
	(*this) << temp;
	return *this;
}

HPTGraphicsEngine& HPTGraphicsEngineInternal::operator<<(double arg)
{
	char temp[30];
	sprintf(temp,"%f",arg);
	int pos = 0;
	for(unsigned int count = 0;count < strlen(temp);count++)
	{
		if(temp[count] != '0') pos = count;
	}
	temp[pos+1] = 0;
	(*this) << temp;
	return *this;
}

HPTGraphicsEngine& HPTGraphicsEngineInternal::operator<<(unsigned int arg)
{
	char temp[12];
	sprintf(temp,"%u",arg);
	(*this) << temp;
	return *this;
}

void HPTGraphicsEngineInternal::clear_screen()
{	
//	IwGxSetColClear(clear_red,clear_green,clear_blue,255);
//	IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
    glClearColor(clear_red/255.0f,clear_green/255.0f,clear_blue/255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void HPTGraphicsEngineInternal::RemoveSprite(HPTSprite1Internal *arg)
{

}

int HPTGraphicsEngineInternal::GetTextureEntrys()
{
	return textures->GetNumEntrys();
}

int HPTGraphicsEngineInternal::GetAvailableMemory()
{
	long result = 0;
	return result;
}

void HPTGraphicsEngineInternal::Free()
{
	textures->Free();
	if(tile_image[0] != NULL) tile_image[0]->Free();
	if(tile_image[1] != NULL) tile_image[1]->Free();
	ForEach(m_fonts,mem_fun(&HPTFont1Internal::Free));
	ClearContext();
}

void HPTGraphicsEngineInternal::ReLoadGraphics()
{
	CreateContext();
	textures->ReLoad();
	if(tile_image[0] != NULL) tile_image[0]->ReLoad();
	if(tile_image[1] != NULL) tile_image[1]->ReLoad();
	ForEach(m_fonts,mem_fun(&HPTFont1Internal::Reload));
}

void HPTGraphicsEngineInternal::ReleaseFont(HPTFont1Internal *_font)
{
	m_fonts.erase(remove(m_fonts.begin(),m_fonts.end(),_font),m_fonts.end());
}

void HPTGraphicsEngineInternal::CacheTexture(int _texture)
{
	textures->GetTextureInfo(_texture)->Cached();
}