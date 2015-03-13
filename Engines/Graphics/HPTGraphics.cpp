#include "HPTGraphics.h"
#include "HPTGraphicsEngineInternal.h"


HPTGraphicsEngineInternal *gengine = NULL;

HPTGraphicsEngine* GetHPTGraphicsEngine()
{
	if(gengine == NULL)
	{
		gengine = new HPTGraphicsEngineInternal();
	}
	gengine->AddRef();
	return gengine;
}