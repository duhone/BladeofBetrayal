#ifndef HPT_TEXTURE_STRUCT_H
#define HPT_TEXTURE_STRUCT_H

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<GLES/gl.h>
#include<GLES/glext.h>
#include<limits>
#include <vector>

struct HPTTextureStruct
{
	int width;
	int height;
	int total_width;
	int total_height;
	int padded_height;
	float m_halfu;
	float m_halfv;
	unsigned short color_key;
	float default_frame_rate;
	bool default_auto_animate;
	int num_frame_sets;
	int numTextures;
	int *frames_per_set;
	int zlib_size;
	int zlib_pos;
	char file_name[255];
	int ref_count;
	GLuint *glTextureIds;
	int type;
	unsigned char *m_stream;
	HPTTextureStruct()
	{
		frames_per_set = NULL;
		ref_count = 0;	
		glTextureIds = NULL;
		m_stream = NULL;
	}
	~HPTTextureStruct()
	{
		if(frames_per_set != NULL) delete[] frames_per_set;
		frames_per_set = NULL;
		FreeTexture();
		if(!m_stream)
			delete[] m_stream;
	}
public:
	void FreeTexture();
	void ReLoad();
	void LoadTexture(FILE *filep);
	void LoadTextureTiles(FILE *filep,std::vector<unsigned char> &_opacityCollecter);
	void ReleaseTexture();
	void UseTexture();
	short old_num_frame_sets;
	int ReadPNG(char *name,FILE* &filep);
	unsigned int GetNextPowerOf2(unsigned int _original);
	void Cached();
private:

	void LoadTexture();

};

#endif