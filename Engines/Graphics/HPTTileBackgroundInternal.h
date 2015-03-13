#ifndef HPT_TILE_BACKGROUND_INTERNAL_H
#define HPT_TILE_BACKGROUND_INTERNAL_H

#include "HPTGraphics.h"
#include "HPTSprite1Internal.h"
#include <string>

struct Tile
{
	unsigned short layer;
};

class HPTTileBackgroundInternal : public HPTTileBackground  
{
public:
	void ReLoad();
	void Render();
	HPTTileBackgroundInternal();
	virtual ~HPTTileBackgroundInternal();
	virtual void LoadTileSet(char *name);
	virtual void Release();
	inline virtual void SetPositionAbsalute(float x,float y);
	inline virtual void SetPositionRelative(int x,int y)
	{
		x_position = x;
		y_position = y;

	};
	float y_position;
	float x_position;
	unsigned int tile_matrix_height;
	unsigned int tile_matrix_width;
	unsigned char *tile_flags;

	void Free();
private:
	const static int gridWidth = 31;
	const static int gridHeight = 21;
	const static int vertsPerTile = 12;
	
	HPTSprite1Internal *tile_sprite;
	HPTTextureStruct *tiles;
	Tile *tile_matrix;
	bool set_loaded;	
	std::string m_fileName;

	GLfloat gridVerts[vertsPerTile*gridWidth*gridHeight];
	GLfloat gridTexCoords[vertsPerTile*gridWidth*gridHeight];
};

#endif