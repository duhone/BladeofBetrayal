#include "hpttexturestruct.h"
#include "HPTGraphicsEngineInternal.h"
#include "thirdparty/zlib/zlib.h"
#include "AppConfig.h"
#include "FunctionObjects.h"

extern HPTGraphicsEngineInternal *gengine;

using namespace std;
using namespace CR::Utility;

int HPTTextureStruct::ReadPNG(char *name,FILE* &filep)
{
	padded_height = GetNextPowerOf2(height);
	strcpy(file_name,name);

	int bytes_read = 0;
	fread(&bytes_read,sizeof(int),1,filep);
	zlib_size = bytes_read;
	zlib_pos = ftell(filep);
	fseek(filep,bytes_read,SEEK_CUR);

	return bytes_read+4;
}

void HPTTextureStruct::LoadTexture()
{
	if(glTextureIds != NULL) FreeTexture();
		
	unsigned char *stream;
	FILE *filep = NULL;
	if(m_stream)
	{
		stream = m_stream;
	}
	else
	{
		filep = fopen(file_name,"rb");
		fseek(filep,zlib_pos,SEEK_SET);

		stream = new unsigned char[zlib_size];
		fread(stream,sizeof(unsigned char),zlib_size,filep);
	}
	
	z_stream zlib_stream;
	unsigned long size = total_width*1*2+1;

	memset(&zlib_stream,0,sizeof(z_stream));
	zlib_stream.next_in = stream;
	zlib_stream.avail_in = zlib_size;
	zlib_stream.data_type = Z_BINARY;

	inflateInit(&zlib_stream);

	old_num_frame_sets = num_frame_sets;
	numTextures = num_frame_sets;

	glTextureIds = new GLuint[numTextures];
	glGenTextures(numTextures,glTextureIds);
	
		unsigned char *tempout = NULL;
		if(type <= 1)
			tempout = new unsigned char[total_width*padded_height*2];
		else if(type == 2)
			tempout = new unsigned char[total_width*padded_height*4];
		else if(type == 3)
			tempout = new unsigned char[total_width*padded_height*3];
	for(int count = 0;count < num_frame_sets;count++)
	{
		/*unsigned char *tempout = NULL;
		if(type <= 1)
			tempout = new unsigned char[total_width*padded_height*2];
		else if(type == 2)
			tempout = new unsigned char[total_width*padded_height*4];
		else if(type == 3)
			tempout = new unsigned char[total_width*padded_height*3];*/
			
		zlib_stream.next_out = tempout;//reinterpret_cast<unsigned char*>(tempout);
		if(type <= 1)
			zlib_stream.avail_out = total_width*padded_height*2;
		else if(type == 2)
			zlib_stream.avail_out = total_width*padded_height*4;
		else if(type == 3)
			zlib_stream.avail_out = total_width*padded_height*3;
			
		//while(zlib_stream.avail_out > 0)
			inflate(&zlib_stream,Z_FINISH);
		
		glBindTexture(GL_TEXTURE_2D,glTextureIds[count]);	
		if(type == 0)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_SHORT_5_5_5_1,tempout);
		else if(type == 1)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_SHORT_4_4_4_4,tempout);
		else if(type == 2)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_BYTE,tempout);
		else if(type == 3)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, total_width,padded_height,0,
						 GL_RGB,GL_UNSIGNED_BYTE,tempout);
				
		//delete[] tempout;
	}
		delete[] tempout;
	
	inflateEnd(&zlib_stream);
	if(!m_stream)
		delete[] stream;

	fclose(filep);
}

void HPTTextureStruct::Cached()
{
	if(!m_stream)
	{
		FILE *filep = fopen(file_name,"rb");
		fseek(filep,zlib_pos,SEEK_SET);

		m_stream = new unsigned char[zlib_size];

		fread(m_stream,sizeof(unsigned char),zlib_size,filep);
	}

}

void HPTTextureStruct::LoadTexture(FILE *filep)
{
	if(glTextureIds != NULL) FreeTexture();

	
	fseek(filep,zlib_pos,SEEK_SET);
	z_stream zlib_stream;

	unsigned char *stream = new unsigned char[zlib_size];

	fread(stream,sizeof(unsigned char),zlib_size,filep);
	unsigned long size = total_width*1*3+1;
	unsigned char *tdata = new unsigned char[size];

	zlib_stream.next_in = stream;
	zlib_stream.avail_in = zlib_size;
	zlib_stream.total_in = 0;
	zlib_stream.next_out = tdata;
	zlib_stream.avail_out = size;
	zlib_stream.total_out = 0;
	zlib_stream.data_type = Z_BINARY;
	zlib_stream.zalloc = Z_NULL;
	zlib_stream.zfree = Z_NULL;

	inflateInit(&zlib_stream);

	old_num_frame_sets = num_frame_sets;
	numTextures = num_frame_sets;
	
	glTextureIds = new GLuint[numTextures];
	glGenTextures(numTextures,glTextureIds);
	for(int count = 0;count < num_frame_sets;count++)
	{
		unsigned short tempi;
		
		unsigned short *tempout = new unsigned short[total_width*padded_height];
		int i=0;
		
		for(int count3 = 0;count3 < padded_height;count3++)
		{
			zlib_stream.next_out = tdata;
			zlib_stream.avail_out = size;
			inflate(&zlib_stream,Z_SYNC_FLUSH);
			unsigned char *tempin = tdata;

			tempin++;

			for(int count2 = 0;count2 < total_width;count2++)
			{
				tempi = 0;
				tempi += (*tempin)>>3;
				tempi = tempi<<5;
				tempin++;
				tempi += (*tempin)>>3;
				tempi = tempi<<5;
				tempin++;
				tempi+= (*tempin)>>3;
				tempi = tempi<<1;
				if(color_key == 0 || tempi != color_key)
					tempi += 1;
				tempin++;
				tempout[(padded_height-count3-1)*total_width+count2] = tempi;
				i++;
			}
		}
		glBindTexture(GL_TEXTURE_2D,glTextureIds[count]);	
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
					 GL_RGBA,GL_UNSIGNED_SHORT_5_5_5_1,tempout);
		
		delete[] tempout;
	}
	
	inflateEnd(&zlib_stream);
	delete[] tdata;
	delete[] stream;
}

void HPTTextureStruct::FreeTexture()
{
	if(ref_count == 0) return;
	
	if(glTextureIds != NULL)
	{
		glDeleteTextures(numTextures,glTextureIds);
		delete[] glTextureIds;
		glTextureIds = NULL;
	}	
}

void HPTTextureStruct::UseTexture()
{
	if(ref_count == 0) LoadTexture();
	ref_count++;	
}

void HPTTextureStruct::ReleaseTexture()
{
	if(ref_count == 1) FreeTexture();
	ref_count--;
}

void HPTTextureStruct::ReLoad()
{
	if(ref_count == 0) return;
	FreeTexture();
	LoadTexture();
	/*FILE *filep = fopen(file_name,"rb");
	fseek(filep,zlib_pos,SEEK_SET);
	z_stream zlib_stream;

	unsigned char *stream = new unsigned char[zlib_size];

	fread(stream,sizeof(unsigned char),zlib_size,filep);
	unsigned long size = total_width*1*3+1;
	unsigned char *tdata = new unsigned char[size];

	zlib_stream.next_in = stream;
	zlib_stream.avail_in = zlib_size;
	zlib_stream.total_in = 0;
	zlib_stream.next_out = tdata;
	zlib_stream.avail_out = size;
	zlib_stream.total_out = 0;
	zlib_stream.data_type = Z_BINARY;
	zlib_stream.zalloc = Z_NULL;
	zlib_stream.zfree = Z_NULL;

	inflateInit(&zlib_stream);

	for(int count = 0;count < num_frame_sets;count++)
	{
		unsigned short *tempout = new unsigned short[total_width*padded_height];
		int i=0;
			unsigned short tempi;
			for(int count3 = 0;count3 < padded_height;count3++)
			{
				zlib_stream.next_out = tdata;
				zlib_stream.avail_out = size;
				inflate(&zlib_stream,Z_SYNC_FLUSH);
				unsigned char *tempin = tdata;
	
				tempin++;

				for(int count2 = 0;count2 < total_width;count2++)
				{
					tempi = 0;
					tempi += (*tempin)>>3;
					tempi = tempi<<5;
					tempin++;
					tempi += (*tempin)>>3;
					tempi = tempi<<5;
					tempin++;
					tempi+= (*tempin)>>3;
					tempi = tempi<<1;
					if(color_key == 0 || tempi != color_key)
						tempi += 1;
					tempin++;
					tempout[(padded_height-count3-1)*total_width+count2] = tempi;
					i++;
				}
			}
		glBindTexture(GL_TEXTURE_2D,glTextureIds[count]);	
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
					 GL_RGBA,GL_UNSIGNED_SHORT_5_5_5_1,tempout);
		
		delete[] tempout;
	}
	
	inflateEnd(&zlib_stream);
	delete[] tdata;
	delete[] stream;

	fclose(filep);*/
}

unsigned int HPTTextureStruct::GetNextPowerOf2(unsigned int _original)
{
	unsigned int result = 2048;
	while ((result&_original) == 0 && result > 0)
	{
		result = result >> 1;
	}
	if(result == 0)
		return 0;
	if((_original&(result-1)) == 0)
		return result;
	else
		return result<<1;
}

void HPTTextureStruct::LoadTextureTiles(FILE *filep,vector<unsigned char> &_opacityCollecter)
{
	if(glTextureIds != NULL) FreeTexture();
	
	int padded_width = GetNextPowerOf2(total_width);
	int padded_height = GetNextPowerOf2(total_height);
	
	fseek(filep,zlib_pos,SEEK_SET);
	z_stream zlib_stream;
	
	//vector<unsigned char> opacityColecter;
	_opacityCollecter.resize(total_width*total_height/16);
	FillAll(_opacityCollecter,0);

	unsigned char *stream = new unsigned char[zlib_size];
	
	fread(stream,sizeof(unsigned char),zlib_size,filep);
	unsigned long size = total_width*1*3+1;
	unsigned char *tdata = new unsigned char[size];
	
	zlib_stream.next_in = stream;
	zlib_stream.avail_in = zlib_size;
	zlib_stream.total_in = 0;
	zlib_stream.next_out = tdata;
	zlib_stream.avail_out = size;
	zlib_stream.total_out = 0;
	zlib_stream.data_type = Z_BINARY;
	zlib_stream.zalloc = Z_NULL;
	zlib_stream.zfree = Z_NULL;
	
	inflateInit(&zlib_stream);
	
	old_num_frame_sets = num_frame_sets;
	numTextures = 1;
	
	glTextureIds = new GLuint[numTextures];
	glGenTextures(numTextures,glTextureIds);
	unsigned short tempi;
	unsigned int tempipad;

	unsigned short *tempout = NULL;
	unsigned char *tempoutipad = NULL;

	if(AppConfig::Instance().IsIpad())
		tempoutipad = new unsigned char[padded_width*padded_height*4];
	else
		tempout = new unsigned short[padded_width*padded_height];
	

	int i=0;
		
	for(int count3 = 0;count3 < total_height;count3++)
	{
		zlib_stream.next_out = tdata;
		zlib_stream.avail_out = size;
		inflate(&zlib_stream,Z_SYNC_FLUSH);
		unsigned char *tempin = tdata;
			
		tempin++;
			
		if(AppConfig::Instance().IsIpad())
		{
			for(int count2 = 0;count2 < total_width;count2++)
			{
				unsigned char red = *tempin;
				tempin++;
				unsigned char green = *tempin;
				tempin++;
				unsigned char blue = *tempin;
				tempin++;

				unsigned char alpha = 0;
				bool transparent = (red == 255 && green == 0 && blue == 255);
				if(!transparent)
					alpha = 255;
				else
				{
					unsigned int index = ((count3/16)*(total_width/16)) + count2/16;
					if(_opacityCollecter[index] < 255)
						_opacityCollecter[index] += 1;
				}
				
				tempoutipad[(padded_height-count3-1)*padded_width*4+count2*4] = red;
				tempoutipad[(padded_height-count3-1)*padded_width*4+count2*4+1] = green;
				tempoutipad[(padded_height-count3-1)*padded_width*4+count2*4+2] = blue;
				tempoutipad[(padded_height-count3-1)*padded_width*4+count2*4+3] = alpha;
				i++;
			}
		}
		else
		{
			for(int count2 = 0;count2 < total_width;count2++)
			{
				tempi = 0;
				tempi += (*tempin)>>3;
				tempi = tempi<<5;
				tempin++;
				tempi += (*tempin)>>3;
				tempi = tempi<<5;
				tempin++;
				tempi+= (*tempin)>>3;
				tempi = tempi<<1;
				if(color_key == 0 || tempi != color_key)
					tempi += 1;
				else
				{
					unsigned int index = ((count3/16)*(total_width/16)) + count2/16;
					if(_opacityCollecter[index] < 255)
						_opacityCollecter[index] += 1;
				}
				//	_opacityCollecter[((count3/16)*total_width) + count2/16] += 1;
				tempin++;
				tempout[(padded_height-count3-1)*padded_width+count2] = tempi;
				i++;
			}
		}
	}
	glBindTexture(GL_TEXTURE_2D,glTextureIds[0]);	
	
	if(AppConfig::Instance().IsIpad())
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, padded_width,padded_height,0,
					GL_RGBA,GL_UNSIGNED_BYTE,tempoutipad);
	else
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, padded_width,padded_height,0,
					GL_RGBA,GL_UNSIGNED_SHORT_5_5_5_1,tempout);
		
	delete[] tempout;
	delete[] tempoutipad;

	inflateEnd(&zlib_stream);
	delete[] tdata;
	delete[] stream;
}

