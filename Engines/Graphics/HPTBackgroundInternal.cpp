#include "HPTBackgroundInternal.h"
#include "HPTGraphicsEngineInternal.h"

extern HPTGraphicsEngineInternal *gengine;

#define NOT_ASSIGNED 0x0ffffffff

const GLfloat squareVertices[] = {
-240.0f, -160.0f,
240.0f,  -160.0f,
-240.0f,  160.0f,
240.0f,   160.0f,
};

/*const GLfloat squarecoords[] = {
0, 1-(512-320)/1024.0f,
480.0f/512.0f, 1-(512-320)/1024.0f,
0, (512-320)/1024.0f,
480.0f/512.0f, (512-320)/1024.0f,
	};*/

GLfloat squarecoords[] = {
0, 1-(1024-768)/(1024*2.0f),
1024.0f/1024.0f, 1-(1024-768)/(1024*2.0f),
0, (1024-768)/(1024*2.0f),
1024.0f/1024.0f, (1024-768)/(1024*2.0f),
	};

HPTBackgroundInternal::HPTBackgroundInternal()
{
	image_number = NOT_ASSIGNED;
}

HPTBackgroundInternal::~HPTBackgroundInternal()
{
	if(image_number != NOT_ASSIGNED) texture->ReleaseTexture();
	if(gengine->GetBackgroundImage() == this)
		gengine->SetBackgroundImage(NULL);
}

void HPTBackgroundInternal::SetImage(int pallette_entry)
{
	if(image_number == pallette_entry) return;
	if(image_number != NOT_ASSIGNED) texture->ReleaseTexture();
	image_number = pallette_entry;
	texture = gengine->GetTexture(pallette_entry);
	texture->UseTexture();
}

void HPTBackgroundInternal::Release()
{
	delete this;
}

void HPTBackgroundInternal::RenderLowQuality()
{

}

void HPTBackgroundInternal::RenderMedQuality(HPTTileBackgroundInternal *arg1)
{
}

void HPTBackgroundInternal::RenderHighQuality(HPTTileBackgroundInternal *arg1,HPTTileBackgroundInternal *arg2)
{
	float halfu = -0.5f/texture->total_width;
	float halfv = 0.55f/texture->total_height;

	squarecoords[0] = 0+halfu;
	squarecoords[1] = 1-(texture->total_height-texture->height)/(texture->total_height*2.0f)-halfv;
	squarecoords[2] = texture->width/(float)texture->total_width+halfu;
	squarecoords[3] = 1-(texture->total_height-texture->height)/(texture->total_height*2.0f)-halfv;
	squarecoords[4] = 0+halfu;
	squarecoords[5] = (texture->total_height-texture->height)/(texture->total_height*2.0f)+halfv;
	squarecoords[6] = texture->width/(float)texture->total_width+halfu;
	squarecoords[7] = (texture->total_height-texture->height)/(texture->total_height*2.0f)+halfv;

	glBindTexture(GL_TEXTURE_2D, texture->glTextureIds[0]);
	
	if(gengine->IsHD())
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glEnable(GL_TEXTURE_2D);
	
    glVertexPointer(2, GL_FLOAT, 0, squareVertices);
    glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, squarecoords);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//glPopMatrix();
}


void HPTBackgroundInternal::ReLoad()
{
	texture->ReLoad();
}

void HPTBackgroundInternal::Free()
{
	texture->FreeTexture();
}