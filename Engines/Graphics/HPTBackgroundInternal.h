#ifndef HPT_BACKGROUND_INTERNAL_H
#define HPT_BACKGROUND_INTERNAL_H

#include "HPTGraphics.h"
#include "HPTTexturesInternal.h"
#include "HPTTileBackgroundInternal.h"

class HPTBackgroundInternal : public HPTBackground  
{
public:
	void ReLoad();
	HPTBackgroundInternal();
	virtual ~HPTBackgroundInternal();
	inline virtual void SetImage(int pallette_entry);
	virtual void Release();
	virtual void RenderLowQuality();
	virtual void RenderMedQuality(HPTTileBackgroundInternal *arg1);
	virtual void RenderHighQuality(HPTTileBackgroundInternal *arg1,HPTTileBackgroundInternal *arg2);
	void Free();
private:
	int image_number;
	HPTTextureStruct *texture;

};

#endif 