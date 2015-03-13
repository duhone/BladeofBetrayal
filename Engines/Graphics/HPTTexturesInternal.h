#ifndef HPT_TEXTURES_INTERNAL_H
#define HPT_TEXTURES_INTERNAL_H

#include "hpttexturestruct.h"

class HPTTexturesInternal  
{
public:
	int GetNumEntrys();
	void LoadHGF(char *name);
	HPTTexturesInternal();
	virtual ~HPTTexturesInternal();
	inline HPTTextureStruct *GetTextureInfo(int entry)
	{
		if(entrys == 0) return 0;
		else
		{
			return &(entrys[entry]);
		}
	};
	void Free();
	void ReLoad();
	void DumpUsage();
private:
	int num_entrys;
	HPTTextureStruct *entrys;
};

#endif