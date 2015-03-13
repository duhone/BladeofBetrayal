#include "Level.h"
#include "basicblock.h"
#include "fireblock.h"
#include "conveyorblock.h"
#include "bounceblock.h"
#include "destroyableblock.h"
#include "ClimbBlock.h"
#include "HealthObject.h"
//#include "hptlist.h"
#include "EnergyObject.h"
#include "WeaponObject.h"
#include "SpawnBlock.h"
#include "TreasureBlock.h"
#include "game.h"
#include "Grenade.h"
#include "Genemies.h"
#include "GoalMarkerBlock.h"
#include "TutorialBlock.h"
#include "Beacon.h"

extern HPTGraphicsEngine * graphics_engine;
extern Game* game_class;
extern char path[256];
extern char *hptstrcat(char *x,char *y);

Level::Level()
{
#if !defined HPTMIPS
	tile_background_back = graphics_engine->CreateHPTTileBackground();
#endif

	tile_background_front = graphics_engine->CreateHPTTileBackground();
	level_data = 0;
	object_array = 0;
	player = 0;
	projectile_list = 0;

	x_render_offset = 0;
	y_render_offset = 0;
}

Level::~Level()
{
	Object *tempo;
	if(object_array != 0)
	{
		for(int count = 0;count < level_x_size*level_y_size;count++)
		{
			tempo = *(object_array+count);
			if(tempo != 0) delete tempo;
		}
		delete[] object_array;
	}
	if(level_data != 0) delete[] level_data;

#if !defined HPTMIPS
	tile_background_back->Release();
#endif
	tile_background_front->Release();
}

unsigned char Level::GetLevelData(int x,int y)
{
/*	if((x > level_x_size) || (y > level_y_size) || (x < 0) || (y < 0))
		return 0;
	return *(level_data + x + y*level_x_size);*/
	if((((unsigned int)x) < (unsigned int)level_x_size) && (((unsigned int)y) < (unsigned int)level_y_size))
		return *(level_data + x + y*level_x_size);
	else return 0;

}

void Level::LoadLevel(int level_number)
{	
	// hack to skip levels 7 - 12 for the iPhone version
	if (level_number > 6)
		level_number += 6;
	
	char tempc[100];
	if(game_class->GetSaveGameManager()->IsQualityMode())
	{
		sprintf(tempc,("level%db.htf"),level_number);
		tile_background_back->LoadTileSet(tempc);
	}

	sprintf(tempc,("level%df.htf"),level_number);
	tile_background_front->LoadTileSet(tempc);
	if(game_class->GetSaveGameManager()->IsQualityMode())
	{
		graphics_engine->SetTileBackgroundImage(0,tile_background_back);
	}
	else graphics_engine->SetTileBackgroundImage(0,0);

	graphics_engine->SetTileBackgroundImage(1,tile_background_front);

	tile_background_back->SetPositionAbsalute(0,0);
	level_position.p1.x = 0;
	level_position.p2.y = 0;
	level_position.p1.x = 0;
	level_position.p2.y = 0;

	sprintf(tempc,("level%d.hlf"),level_number);
	//path1 = [[NSBundle mainBundle] pathForResource: [[NSString alloc] initWithCString: tempc] ofType: @"hlf"];
	//levelfile1 = [path1 cStringUsingEncoding:1];
	LoadLevelData(tempc);

}

void Level::ReLoadLevel(int level_number)
{	

	char tempc[100];
#if !defined HPTMIPS
	sprintf(tempc,("levels/level%db.htf"),level_number);
	tile_background_back->LoadTileSet(hptstrcat(path,tempc));

#endif
	sprintf(tempc,("levels/level%df.htf"),level_number);
	tile_background_front->LoadTileSet(hptstrcat(path,tempc));
#if !defined HPTMIPS
	if(quality == 0) graphics_engine->SetTileBackgroundImage(0,tile_background_back);
	else graphics_engine->SetTileBackgroundImage(0,0);
#endif
	graphics_engine->SetTileBackgroundImage(1,tile_background_front);
#if !defined HPTMIPS
	tile_background_back->SetPositionAbsalute(0,0);
#endif
	level_position.p1.x = 0;
	level_position.p2.y = 0;
	level_position.p1.x = 0;
	level_position.p2.y = 0;

//	_stprintf(tempc,("levels//level%d.hlf"),level_number);

//	LoadLevelData(hptstrcat(path,tempc));

}

void Level::CollideWithLevel(IPlayer* arg)
{
	//return;
	arg->GetStateFlags()->S_UNDER_WATER = false;
	arg->GetStateFlags()->S_CONVEYOR = false;
	
	
	HPTRect& temprect = arg->GetWorldLoc();
	if(temprect.p1.x < 0) temprect.p1.x = 0;
	if(temprect.p2.x < 0) temprect.p2.x = 0;
	if(temprect.p1.x >= level_x_size*16) temprect.p1.x = level_x_size*16-1;
	if(temprect.p2.x >= level_x_size*16) temprect.p2.x = level_x_size*16-1;
	if(temprect.p1.y < 0) temprect.p1.y = 0;
	if(temprect.p2.y < 0) temprect.p2.y = 0;
	if(temprect.p1.y >= level_y_size*16) temprect.p1.y = level_y_size*16-1;
	if(temprect.p2.y >= level_y_size*16) temprect.p2.y = level_y_size*16-1;


	//temprect = arg->GetWorldLoc();
	//char temps[100];
	//_stprintf(temps,("%d %d %d %d"),temprect.p1.x,temprect.p1.y,temprect.p2.x,temprect.p2.y);
	//MessageBox(0,temps,temps,MB_OK);

	headcollide = false;
	laddercollide = false;
	onground = false;
	int ladder_type = 0;

//	HPTVector<HPTPoint*> spointlist;
//	HPTVector<HPTPoint*> tpointlist;
	spointlist.clear();
	tpointlist.clear();
	HPTPoint center;
//center point
	center.x = ((temprect.p2.x - temprect.p1.x)>>1) + temprect.p1.x;
	center.y = ((temprect.p2.y - temprect.p1.y)>>1) + temprect.p1.y;

//side points
	float xvel,yvel;
	arg->GetVelocityVector(&xvel,&yvel);
	//arg->GetDisplacementVector(&xvel,&yvel);
	bool xvell0 = false;
	if(xvel < 0) xvell0 = true;
	bool yvell0 = false;
	if(yvel < 0) yvell0 = true;
	int xveli = (int)xvel;
	int yveli = (int)yvel;
	bool xvelg0 = false;
	if(xvel > 0) xvelg0 = true;
	bool yvelg0 = false;
	if(yvel > 0) yvelg0 = true;
	
	int xcoord;
	if(xvell0) xcoord = temprect.p1.x;
	else if(xvelg0) xcoord = temprect.p2.x;
	else
	{
		if(arg->GetStateFlags()->S_DIRECTION) xcoord = temprect.p2.x;
		else xcoord = temprect.p1.x;
	}

	int firsty,lasty;
	if(yvell0) firsty = (temprect.p1.y - yveli + 1);
	else firsty = temprect.p1.y;
	if(firsty > temprect.p2.y) firsty = temprect.p2.y;
	if(yvell0) lasty = temprect.p2.y;
	else lasty = (temprect.p2.y - yveli - 2);
	if(lasty < temprect.p1.y) lasty = temprect.p1.y;
	
/*	char temps[100];
	_stprintf(temps,("%d,%d\n"),firsty,lasty);
	OutputDebugString(temps);*/
	
	//if(lasty < firsty) lasty = firsty;

	HPTPoint tempp;
	while(firsty < lasty)
	{
		//tempp = new HPTPoint();
		//NEW(tempp);
		tempp.x = xcoord;
		tempp.y = firsty;
		firsty += 16;
		spointlist.push_back(tempp);
	}
	//tempp = new HPTPoint();
	//NEW(tempp);
	tempp.x = xcoord;
	tempp.y = lasty;
	spointlist.push_back(tempp);
	

//top points
	int ycoord;
	if(yvell0) ycoord = temprect.p1.y;
	else ycoord = temprect.p2.y;
	
	int firstx,lastx;
	if(xvell0) firstx = (temprect.p1.x - xveli + 1);
	else if(xvelg0) firstx = temprect.p1.x;
	else
	{
		if(arg->GetStateFlags()->S_DIRECTION) firstx = temprect.p1.x;
		else firstx = (temprect.p1.x - xveli + 1);
	}
	if(firstx > temprect.p2.x) firstx = temprect.p2.x;
	if(xvell0) lastx = temprect.p2.x-1;
	else if(xvelg0) lastx = (temprect.p2.x - xveli - 2);
	else
	{
		if(arg->GetStateFlags()->S_DIRECTION) lastx = (temprect.p2.x - xveli - 2);
		else lastx = temprect.p2.x-1;
	}
	if(lastx < temprect.p1.x)
	{
		lastx = temprect.p1.x;
		// MessageBox(0,("HOOPTY"),("HOOPTY"),MB_OK);
	}
	while(firstx < lastx)
	{
		//tempp = new HPTPoint();
		//NEW(tempp);
		tempp.x = firstx;
		tempp.y = ycoord;
		firstx += 16;
		tpointlist.push_back(tempp);
	}
	//tempp = new HPTPoint();
	//NEW(tempp);
	tempp.x = lastx;
	tempp.y = ycoord;
	tpointlist.push_back(tempp);

//movment amounts
	int movx,movy;
	if(yvell0)
	{
		movy = 16 - (temprect.p1.y & 15);
		if(movy == 16) movy = 0;
	}
	else
	{
		movy = -(temprect.p2.y & 15);
	}
	if(xvell0)
	{
		movx = 16 - (temprect.p1.x & 15);
		if(movx == 16) movx = 0;
	}
	else
	{
		if(xvelg0) movx = -(temprect.p2.x & 15);
		else
		{
			if(arg->GetStateFlags()->S_DIRECTION)
			{
				movx = -(temprect.p2.x & 15);
			}
			else
			{
				movx = 16 - (temprect.p1.x & 15);
				if(movx == 16) movx = 0;
			}

		}
	}

	bool moved,movedy;
	int omovx,omovy;
	omovx = movx;
	omovy = movy;
	Object *tempo;
	int tempx,tempy;
	int mov0 = 0;
//top collisions
	bool tempb;
	vector<HPTPoint>::iterator tempi = tpointlist.begin();
	vector<HPTPoint>::iterator tend1 = tpointlist.end();
	while(tempi != tend1)
	{
		tempx = (*tempi).x>>4;
		tempy = (*tempi).y>>4;
/*		if(tempx < 0) tempx = 0;
		if(tempx >= level_x_size) tempx = level_x_size-1;
		if(tempy < 0) tempy = 0;
		if(tempy >= level_y_size) tempy = level_y_size-1;
*/		int temploc = tempx + (tempy*level_x_size);
		if((*(level_data + temploc)) == ENDLEVEL)
		{
			if(arg->GetStateFlags()->S_IS_PLAYER)
			{
				game_class->EndLevel();
				return;
			}
		}
		if((*(level_data + temploc)) == WATERBLOCK)
		{
			arg->GetStateFlags()->S_UNDER_WATER = true;
		}
		if((*(level_data + temploc)) != 0)
		{
			tempo = *(object_array+temploc);
			if(tempo != 0)
			{
				tempb = tempo->CollideCheck(arg,mov0,movy,moved,laddercollide,movedy,temprect,ladder_type);
				if(tempb)
				{
					(*(level_data + temploc)) = 0;
				}
				//MessageBox(0,("error"),("error"),MB_OK);
				if(laddercollide)
				{
					if((*(level_data + temploc+1)) == WATERBLOCK)
					{
						arg->GetStateFlags()->S_UNDER_WATER = true;
					}
					if((*(level_data + temploc-1)) == WATERBLOCK)
					{
						arg->GetStateFlags()->S_UNDER_WATER = true;
					}
					if((*(level_data + temploc+1)) == GASBLOCK)
					{
						arg->doChemicalDamage(5);
					}
					if((*(level_data + temploc-1)) == GASBLOCK)
					{
						arg->doChemicalDamage(5);
					}

				}
			}
		
		}
		tempi++;
		if(movy == -100) break;
	}

	if((yvel < 0) && (movy == -100)) headcollide = true;
	if((yvel >= 0) && (movy == -100)) onground = true;

//side collisions

	tempi = spointlist.begin();
	tend1 = spointlist.end(); 
	while(tempi != tend1)
	{
		tempx = (*tempi).x>>4;
		tempy = (*tempi).y>>4;
/*		if(tempx < 0) tempx = 0;
		if(tempx >= level_x_size) tempx = level_x_size-1;
		if(tempy < 0) tempy = 0;
		if(tempy >= level_y_size) tempy = level_y_size-1;
*/		int temploc = tempx + (tempy*level_x_size);
	
		if((*(level_data + temploc)) == ENDLEVEL)
		{
			if(arg->GetStateFlags()->S_IS_PLAYER)
			{
				game_class->EndLevel();
				return;
			}
		}
		if((*(level_data + temploc)) == WATERBLOCK)
		{
			arg->GetStateFlags()->S_UNDER_WATER = true;
		}

		if((*(level_data + temploc)) != 0)
		{
			tempo = *(object_array+temploc);
			if(tempo != 0)
			{
				tempb = tempo->CollideCheck(arg,movx,mov0,moved,laddercollide,movedy,temprect,ladder_type);
				if(tempb)
				{
					(*(level_data + temploc)) = 0;
				}
				//MessageBox(0,("error"),("error"),MB_OK);
				if(laddercollide)
				{
					if((*(level_data + temploc+1)) == WATERBLOCK)
					{
						arg->GetStateFlags()->S_UNDER_WATER = true;
					}
					if((*(level_data + temploc-1)) == WATERBLOCK)
					{
						arg->GetStateFlags()->S_UNDER_WATER = true;
					}
					if((*(level_data + temploc+1)) == GASBLOCK)
					{
						arg->doChemicalDamage(5);
					}
					if((*(level_data + temploc-1)) == GASBLOCK)
					{
						arg->doChemicalDamage(5);
					}

				}
			}
		
		}
		tempi++;
		if(movx == -100) break;
	}


//center point

	tempx = center.x>>4;
	tempy = center.y>>4;
/*	if(tempx < 0) tempx = 0;
	if(tempx >= level_x_size) tempx = level_x_size-1;
	if(tempy < 0) tempy = 0;
	if(tempy >= level_y_size) tempy = level_y_size-1;
*/
	if((*(level_data + tempx + (tempy*level_x_size))) == ENDLEVEL)
	{
		if(arg->GetStateFlags()->S_IS_PLAYER)
		{
			game_class->EndLevel();
			return;
		}
	}
	if((*(level_data + tempx + (tempy*level_x_size))) == WATERBLOCK)
	{
		arg->GetStateFlags()->S_UNDER_WATER = true;
	}

	if((*(level_data + tempx + (tempy*level_x_size))) != 0)
	{
		tempo = *(object_array+tempx+(tempy*level_x_size));
		if(tempo != 0)
		{
			tempb = tempo->CollideCheck(arg,mov0,mov0,moved,laddercollide,movedy,temprect,ladder_type);
			if(tempb)
			{
				(*(level_data + tempx + (tempy*level_x_size))) = 0;
			}
				//MessageBox(0,("error"),("error"),MB_OK);
			if(laddercollide)
			{
				if((*(level_data + tempx + (tempy*level_x_size)+1)) == WATERBLOCK)
				{
					arg->GetStateFlags()->S_UNDER_WATER = true;
				}
				if((*(level_data + tempx + (tempy*level_x_size)-1)) == WATERBLOCK)
				{
					arg->GetStateFlags()->S_UNDER_WATER = true;
				}
				if((*(level_data + tempx + (tempy*level_x_size)+1)) == GASBLOCK)
				{
					arg->doChemicalDamage(5);
				}
				if((*(level_data + tempx + (tempy*level_x_size)-1)) == GASBLOCK)
				{
					arg->doChemicalDamage(5);
				}

			}
		}
	
	}
	
	tempi = tpointlist.begin();
/*	while(tempi != tpointlist.end())
	{
		tempp = (*tempi);
		delete tempp;
		tempi++;

	}*/
	tpointlist.clear();

/*	tempi = spointlist.begin();
	while(tempi != spointlist.end())
	{
		tempp = (*tempi);
		delete tempp;
		tempi++;
	}
	*/
	spointlist.clear();
	arg->StandingOnGround(onground);
	arg->HeadCollision(headcollide);
	
	arg->NextToLadder(laddercollide,ladder_type);
	
}

void Level::CollideWithLevelE(IPlayer* arg)
{
	if(arg->GetStateFlags()->S_NO_COLLISION) return;
	arg->GetStateFlags()->S_UNDER_WATER = false;
	arg->GetStateFlags()->S_CONVEYOR = false;
	
	HPTRect& temprect = arg->GetWorldLoc();
	if(temprect.p1.x < 0) temprect.p1.x = 0;
	if(temprect.p2.x < 0) temprect.p2.x = 0;
	if(temprect.p1.x >= level_x_size*16) temprect.p1.x = level_x_size*16-1;
	if(temprect.p2.x >= level_x_size*16) temprect.p2.x = level_x_size*16-1;
	if(temprect.p1.y < 0) temprect.p1.y = 0;
	if(temprect.p2.y < 0) temprect.p2.y = 0;
	if(temprect.p1.y >= level_y_size*16) temprect.p1.y = level_y_size*16-1;
	if(temprect.p2.y >= level_y_size*16) temprect.p2.y = level_y_size*16-1;


	headcollide = false;
	laddercollide = false;
	onground = false;
	int ladder_type = 0;

	spointlist.clear();
	tpointlist.clear();
//side points
	float xvel,yvel;
	arg->GetVelocityVector(&xvel,&yvel);
	bool xvell0 = false;
	if(xvel < 0) xvell0 = true;
	bool yvell0 = false;
	if(yvel < 0) yvell0 = true;
	int xveli = (int)xvel;
	int yveli = (int)yvel;
	bool xvelg0 = false;
	if(xvel > 0) xvelg0 = true;
	bool yvelg0 = false;
	if(yvel > 0) yvelg0 = true;
	
	int xcoord;
	if(xvell0) xcoord = temprect.p1.x;
	else if(xvelg0) xcoord = temprect.p2.x;
	else
	{
		if(arg->GetStateFlags()->S_DIRECTION) xcoord = temprect.p2.x;
		else xcoord = temprect.p1.x;
	}

	int firsty,lasty;
	if(yvell0) firsty = (temprect.p1.y - yveli + 1);
	else firsty = temprect.p1.y;
	if(firsty > temprect.p2.y) firsty = temprect.p2.y;
	if(yvell0) lasty = temprect.p2.y;
	else lasty = (temprect.p2.y - yveli - 2);
	if(lasty < temprect.p1.y) lasty = temprect.p1.y;
	

	HPTPoint tempp;
	while(firsty < lasty)
	{
		tempp.x = xcoord;
		tempp.y = firsty;
		firsty += 16;
		spointlist.push_back(tempp);
	}
	tempp.x = xcoord;
	tempp.y = lasty;
	spointlist.push_back(tempp);
	

//top points
	int ycoord;
	if(yvell0) ycoord = temprect.p1.y;
	else ycoord = temprect.p2.y;
	
	int firstx,lastx;
	if(xvell0) firstx = (temprect.p1.x - xveli + 1);
	else if(xvelg0) firstx = temprect.p1.x;
	else
	{
		if(arg->GetStateFlags()->S_DIRECTION) firstx = temprect.p1.x;
		else firstx = (temprect.p1.x - xveli + 1);
	}
	if(firstx > temprect.p2.x) firstx = temprect.p2.x;
	if(xvell0) lastx = temprect.p2.x-1;
	else if(xvelg0) lastx = (temprect.p2.x - xveli - 2);
	else
	{
		if(arg->GetStateFlags()->S_DIRECTION) lastx = (temprect.p2.x - xveli - 2);
		else lastx = temprect.p2.x-1;
	}
	if(lastx < temprect.p1.x)
	{
		lastx = temprect.p1.x;
	}
	while(firstx < lastx)
	{
		tempp.x = firstx;
		tempp.y = ycoord;
		firstx += 16;
		tpointlist.push_back(tempp);
	}
	tempp.x = lastx;
	tempp.y = ycoord;
	tpointlist.push_back(tempp);

//movment amounts
	int movx,movy;
	if(yvell0)
	{
		movy = 16 - (temprect.p1.y & 15);
		if(movy == 16) movy = 0;
	}
	else
	{
		movy = -(temprect.p2.y & 15);
	}
	if(xvell0)
	{
		movx = 16 - (temprect.p1.x & 15);
		if(movx == 16) movx = 0;
	}
	else
	{
		if(xvelg0) movx = -(temprect.p2.x & 15);
		else
		{
			if(arg->GetStateFlags()->S_DIRECTION)
			{
				movx = -(temprect.p2.x & 15);
			}
			else
			{
				movx = 16 - (temprect.p1.x & 15);
				if(movx == 16) movx = 0;
			}

		}
	}

	bool moved,movedy;
	//int omovx,omovy;
	//omovx = movx;
	//omovy = movy;
	Object *tempo;
	int tempx,tempy;
	int mov0 = 0;
//top collisions
	bool tempb;
	vector<HPTPoint>::iterator tempi = tpointlist.begin();
	vector<HPTPoint>::iterator tend1 = tpointlist.end();
	
	while(tempi != tend1)
	{
		tempx = (*tempi).x>>4;
		tempy = (*tempi).y>>4;
		int temploc = tempx + (tempy*level_x_size);
		if((*(level_data + temploc)) != 0)
		{
			tempo = *(object_array+temploc);
			if(tempo != 0)
			{
				tempo->CollideCheck(arg,mov0,movy,moved,laddercollide,movedy,temprect,ladder_type);
			}
		
		}
		tempi++;
		if(movy == -100) break;
	}

	if((yvel < 0) && (movy == -100)) headcollide = true;
	if((yvel >= 0) && (movy == -100)) onground = true;

//side collisions

	tempi = spointlist.begin();
	tend1 = spointlist.end();
	while(tempi !=tend1)
	{
		tempx = (*tempi).x>>4;
		tempy = (*tempi).y>>4;
		int temploc = tempx + (tempy*level_x_size);
	

		if((*(level_data + temploc)) != 0)
		{
			tempo = *(object_array+temploc);
			if(tempo != 0)
			{
				tempo->CollideCheck(arg,movx,mov0,moved,laddercollide,movedy,temprect,ladder_type);
			}
		
		}
		tempi++;
		if(movx == -100) break;
	}

	tpointlist.clear();

	spointlist.clear();
	arg->StandingOnGround(onground);
	arg->HeadCollision(headcollide);
	
//	arg->NextToLadder(laddercollide,ladder_type);
	
}

//void Level::SetLevelRenderOffset(int dx, int dy)
//{//
//	x_render_offset = dx;
//	y_render_offset = dy;
//}

void Level::SetLevelPosition(float x, float y)
{

	level_position.p1.x = x;
	level_position.p1.y = y;
	level_position.p2.x = (x/4);
	level_position.p2.y = (y/4);
	//char tempc[100];
	//sprintf(tempc,"%d %d",level_position.p2.x,level_position.p2.y);
	//OutputDebugString(tempc);
	tile_background_front->SetPositionAbsalute(x,y);
	tile_background_back->SetPositionAbsalute(x/4,y/4);
/*	int count = level_y_size*level_x_size;
	for(int ycount = 0;ycount < count;ycount++)
	{
			if(*(object_array+ycount) != 0)
			{
				(*(object_array+ycount))->SetScreenTransform(x,y);
			}
	}*/
	list<Object*>::iterator tempi = object_list.begin();
/*	while(tempi != object_list.end())
	{
		(*tempi)->SetScreenTransform(x,y);
		tempi++;
	}*/	

	int count = object_list.size();
	for(int ycount = 0;ycount < count ;ycount++)
	{
		(*tempi)->SetScreenTransform(x,y);
		tempi++;
	}
}

void Level::SetPlayer(IPlayer *p)
{
	player = p;
}

void Level::SetProjectileList(list<Projectile *> *list)
{
	projectile_list = list;
}


void Level::LoadLevelData(char *name)
{
/*#if defined POCKET_PC
	HANDLE filehandle = CreateFileForMapping(name,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
#endif	
#if defined X86
	HANDLE filehandle = CreateFile(name,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
#endif	
	if(filehandle == INVALID_HANDLE_VALUE)
	{
	//	MessageBox(0,name,("could not open HLF file"),MB_OK);
		return;
	}
	HANDLE filemapping = CreateFileMapping(filehandle,0,PAGE_READONLY | SEC_COMMIT,0,0,0);
	if(filemapping == 0)
	{
	//	MessageBox(0,("name"),("could not map requested HLF file"),MB_OK);
		return;
	}
	void *filepointer = MapViewOfFile(filemapping,FILE_MAP_READ,0,0,0);
	if(filepointer == 0)
	{
	//	MessageBox(0,("name"),("could not view requested HLF file"),MB_OK);
		return;
	}
	*/

	FILE* filep = fopen(name,"rb");
	//char *fptemp = (char*)filepointer;
	char temp[3];
	fread(temp,3,sizeof(char),filep);
	if((temp[0] != 'H') || (temp[1] != 'L') || (temp[2] != 'F'))
	{
		//MessageBox(0,("requested file is not a HLF file"),name,MB_OK);
		fclose(filep);
	}
	int tempi;
	fread(&tempi,1,sizeof(int),filep);
	if(tempi != 1)
	{
	//	MessageBox(0,("requested file is a HLF file version that is not recognized by this version of the HPT Graphics Engine"),name,MB_OK);
		fclose(filep);
	}

	Object *tempo;
	if(object_array != 0)
	{
		for(int count = 0;count < level_x_size*level_y_size;count++)
		{
			tempo = *(object_array+count);
			if(tempo != 0) delete tempo;
		}
		delete[] object_array;
	}
	
	fread(&level_x_size,1,sizeof(int),filep);
	fread(&level_y_size,1,sizeof(int),filep);
	
	if(level_data != 0) delete[] level_data;
	level_data = new unsigned char[level_x_size*level_y_size];
	fread(level_data,level_x_size*level_y_size,sizeof(char),filep);

	object_array = new Object *[level_x_size*level_y_size];
	memset(object_array,0,sizeof(Object*)*level_x_size*level_y_size);
	object_list.clear();
	//char temps[100];
	//_stprintf(temps,("%d %d"),level_x_size,level_y_size);
	//MessageBox(0,temps,temps,MB_OK);
		fclose(filep);
	
	LoadObjects();
}

void Level::LoadObjects(bool _enemiesOnly)
{
	Enemy *enemy;
	EnemyLandMine *enemy_landmine;
	EnemyWaterMine *enemy_watermine;
	EnemyFire *enemy_fire;
	EnemyWolf *enemy_wolf;
	EnemyDockWorkerRope *enemy_dock_worker_rope;
	EnemyJacob *enemy_jacob;
	
	int count = 0;
	for(int ycount = 0;ycount < level_y_size;ycount++)
	{
		for(int xcount = 0;xcount < level_x_size;xcount++)
		{
			unsigned char temp = *(level_data+count);
			
			if(_enemiesOnly && (temp < ENEMYFIRST || temp > ENEMYLAST) && temp != FIREBLOCK)
			{
				count++;
				continue;
			}
			//	*(object_array+count) = 0;
			//MessageBox(0,("errir"),("error"),MB_OK);
			switch(temp)
			{
					/*	case 0:
					 *(object_array+count) = 0;
					 break;*/
				case BASICBLOCK:
					*(object_array+count) = new BasicBlock();
					((BasicBlock*)(*(object_array+count)))->SetSideCollide(true);
					break;
				case NONSIDEBASICBLOCK:
					*(object_array+count) = new BasicBlock();
					((BasicBlock*)(*(object_array+count)))->SetSideCollide(false);
					break;
				case NONTOPBASICBLOCK:
					*(object_array+count) = new BasicBlock();
					((BasicBlock*)(*(object_array+count)))->SetTopCollide(false);
					break;
				case BOUNCEBLOCK:
					*(object_array+count) = new BounceBlock();
					(*(object_array+count))->SetPallette(1,5);
					(*(object_array+count))->SetWorldPosition(xcount<<4 + 8,ycount<<4 + 8);
					break;
				case SPIKEBLOCK:
					*(object_array+count) = new FireBlock(SPIKEBLOCK);
					(*(object_array+count))->SetPallette(1,4);
					(*(object_array+count))->SetWorldPosition(xcount<<4 + 8,ycount<<4 + 8);
					object_list.push_back(*(object_array+count));
					break;
				case GASBLOCK:
					*(object_array+count) = new FireBlock(GASBLOCK);
					//(*(object_array+count))->SetPallette(1,4);
					(*(object_array+count))->SetWorldPosition(xcount<<4 + 8,ycount<<4 + 8);
					break;
				case DESTROYABLEBLOCK:
					*(object_array+count) = new DestroyableBlock();
					//(*(object_array+count))->SetPallette(1,0);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					((DestroyableBlock*)*(object_array+count))->SetHitPoints(1);
					object_list.push_back(*(object_array+count));
					break;
				case CONVEYORBLOCKLEFT:
					*(object_array+count) = new ConveyorBlock();
					(*(object_array+count))->SetPallette(1,122);
					((ConveyorBlock*)*(object_array+count))->SetDirection(LEFT);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case CONVEYORBLOCKLEFTENDLEFT:
					*(object_array+count) = new ConveyorBlock();
					(*(object_array+count))->SetPallette(1,124);
					((ConveyorBlock*)*(object_array+count))->SetDirection(LEFT);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case CONVEYORBLOCKLEFTENDRIGHT:
					*(object_array+count) = new ConveyorBlock();
					(*(object_array+count))->SetPallette(1,124);
					(*(object_array+count))->SetHFlip();
					((ConveyorBlock*)*(object_array+count))->SetDirection(LEFT);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case CONVEYORBLOCKRIGHT:
					*(object_array+count) = new ConveyorBlock();
					(*(object_array+count))->SetPallette(1,123);
					((ConveyorBlock*)*(object_array+count))->SetDirection(RIGHT);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case CONVEYORBLOCKRIGHTENDLEFT:
					*(object_array+count) = new ConveyorBlock();
					(*(object_array+count))->SetPallette(1,125);
					((ConveyorBlock*)*(object_array+count))->SetDirection(RIGHT);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case CONVEYORBLOCKRIGHTENDRIGHT:
					*(object_array+count) = new ConveyorBlock();
					(*(object_array+count))->SetPallette(1,125);
					(*(object_array+count))->SetHFlip();
					((ConveyorBlock*)*(object_array+count))->SetDirection(RIGHT);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case CLIMBBLOCKLEFT:
					*(object_array+count) = new ClimbBlock();
					((ClimbBlock*)*(object_array+count))->SetBlockType(CLIMBBLOCKLEFT);
					break;
				case CLIMBBLOCKRIGHT:
					*(object_array+count) = new ClimbBlock();
					((ClimbBlock*)*(object_array+count))->SetBlockType(CLIMBBLOCKRIGHT);
					break;
				case CLIMBLADDER:
					*(object_array+count) = new ClimbBlock();
					((ClimbBlock*)*(object_array+count))->SetBlockType(CLIMBLADDER);
					break;
				case CLIMBROPE:
					*(object_array+count) = new ClimbBlock();
					((ClimbBlock*)*(object_array+count))->SetBlockType(CLIMBROPE);
					break;
				case SMALLHEALTH:
					*(object_array+count) = new HealthObject(1);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8/*75,75*/);
					object_list.push_back(*(object_array+count));
					break;
				case LARGEHEALTH:
					*(object_array+count) = new HealthObject(2);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
					//case HEALTHUPGRADENKEY:
				case HEALTHUPGRADEBKEY:
				case HEALTHUPGRADEOKEY:
				case HEALTHUPGRADEGKEY:
				case HEALTHUPGRADERKEY:
					*(object_array+count) = new HealthObject(3,temp - HEALTHUPGRADENKEY);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 14,(ycount<<4) + 0);
					object_list.push_back(*(object_array+count));
					break;
				case SMALLENERGY:
					*(object_array+count) = new EnergyObject(1);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8/*75,75*/);
					object_list.push_back(*(object_array+count));
					break;
				case LARGEENERGY:
					*(object_array+count) = new EnergyObject(2);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case ENERGYUPGRADENKEY:
				case ENERGYUPGRADEBKEY:
				case ENERGYUPGRADEOKEY:
				case ENERGYUPGRADEGKEY:
				case ENERGYUPGRADERKEY:
					*(object_array+count) = new EnergyObject(3,temp - ENERGYUPGRADENKEY);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 14,(ycount<<4) + 0);
					object_list.push_back(*(object_array+count));
					break;
				case FREELIFE:
					*(object_array+count) = new HealthObject(4);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case ATTACK1NKEY:
				case ATTACK1BKEY:
				case ATTACK1OKEY:
				case ATTACK1GKEY:
				case ATTACK1RKEY:
					*(object_array+count) = new WeaponObject(1,temp-ATTACK1NKEY);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 14,(ycount<<4) + 0);
					object_list.push_back(*(object_array+count));
					break;
				case ATTACK2NKEY:
				case ATTACK2BKEY:
				case ATTACK2OKEY:
				case ATTACK2GKEY:
				case ATTACK2RKEY:
					*(object_array+count) = new WeaponObject(2,temp-ATTACK2NKEY);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 14,(ycount<<4) + 0);
					object_list.push_back(*(object_array+count));
					break;
				case ATTACK3NKEY:
				case ATTACK3BKEY:
				case ATTACK3OKEY:
				case ATTACK3GKEY:
				case ATTACK3RKEY:
					*(object_array+count) = new WeaponObject(3,temp-ATTACK3NKEY);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 14,(ycount<<4) + 0);
					object_list.push_back(*(object_array+count));
					break;
				case ATTACK4NKEY:
				case ATTACK4BKEY:
				case ATTACK4OKEY:
				case ATTACK4GKEY:
				case ATTACK4RKEY:
					*(object_array+count) = new WeaponObject(4,temp-ATTACK4NKEY);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 14,(ycount<<4) + 0);
					object_list.push_back(*(object_array+count));
					break;
					/*case ATTACK5:
					 *(object_array+count) = new WeaponObject(5);
					 (*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					 object_list.push_back(*(object_array+count));
					 break;
					 case ATTACK6:
					 *(object_array+count) = new WeaponObject(6);
					 (*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					 object_list.push_back(*(object_array+count));
					 break;*/
				case SPAWNFLAG:
					*(object_array+count-level_x_size) = new SpawnBlock();
					(*(object_array+count-level_x_size))->SetWorldPosition((xcount<<4) + 8,((ycount-1)<<4) + 8);
					object_list.push_back(*(object_array+count-level_x_size));
					*(level_data+count) = 0;
					*(level_data+count-level_x_size) = SPAWNFLAG;
					*(object_array+count) = 0;
					break;
				case TREASURE1:
					*(object_array+count) = new Grenade(1);//TreasureBlock(1);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case TREASURE2:
					*(object_array+count) = new Grenade(2);//TreasureBlock(2);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case TREASURE3:
					*(object_array+count) = new GoalMarkerBlock();//TreasureBlock(3);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case TREASURE4:
					*(object_array+count) = new TreasureBlock(4);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case TREASURE5:
					*(object_array+count) = new TreasureBlock(5);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case HEALTHUPGRADENKEY:
					//case TREASURE6:
					*(object_array+count) = new TreasureBlock(6);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 14,(ycount<<4) + 0);
					object_list.push_back(*(object_array+count));
					break;
				case BEACON:
					*(object_array+count) = new Beacon();
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;		
				case TUTORIAL_CROUCH:
					//case TREASURE6:
					*(object_array+count) = new TutorialBlock(TutorialManager::TCROUCH);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case TUTORIAL_EXPLORE:
					//case TREASURE6:
					*(object_array+count) = new TutorialBlock(TutorialManager::TEXPLORE);
					(*(object_array+count))->SetWorldPosition((xcount<<4) + 8,(ycount<<4) + 8);
					object_list.push_back(*(object_array+count));
					break;
				case GREENNINJA:
					
					enemy = new EnemyGreenNinja(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->SetSpawnPoint();
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::shadow_ninja);
					game_class->ai_engine->AddAI(enemy,enemy,eGreenNinja);
					game_class->enemys.push_back(enemy);
					*(object_array+count) = 0;
					
					break;
				case BLUENINJA:
					enemy = new EnemyBlueNinja(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->SetSpawnPoint();
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::blue_ninja);
					game_class->ai_engine->AddAI(enemy,enemy,eBlueNinja);
					game_class->enemys.push_back(enemy);
					break;
				case REDNINJA:
					enemy = new EnemyRedNinja(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->SetSpawnPoint();
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::shadow_ninja);
					game_class->ai_engine->AddAI(enemy,enemy,eRedNinja);
					game_class->enemys.push_back(enemy);
					break;
				case LANDMINE:
					enemy_landmine = new EnemyLandMine(this);
					enemy_landmine->SetProjectileList(projectile_list);
					enemy_landmine->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy_landmine->setGravityConstant(500.0f);
					enemy_landmine->SetSprite(1, CR::AssetList::land_mine);
					enemy_landmine->StartMine();
					game_class->ai_engine->AddAI(enemy_landmine,enemy_landmine, eLandMine);
					game_class->enemys.push_back(enemy_landmine);
					break;
				case ELITEBATONGAURDS:
					enemy = new EnemyBatonEliteGuard(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::elite_guard);
					game_class->ai_engine->AddAI(enemy,enemy,eEliteBatonGuard);
					game_class->enemys.push_back(enemy);
					break;
				case ELITEPISTOLGAURDS:
					enemy = new EnemyPistolEliteGuard(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::elite_guard);
					enemy->lower_patrol_x =xcount-5;
					enemy->upper_patrol_x = xcount+5;
					game_class->ai_engine->AddAI(enemy,enemy,eElitePistolGuard);
					game_class->enemys.push_back(enemy);
					break;
				case ELITERIFLEGAURDS:
					enemy = new EnemySemiAutoEliteGuard(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::elite_guard);
					enemy->lower_patrol_x = xcount-5;
					enemy->upper_patrol_x = xcount+5;
					game_class->ai_engine->AddAI(enemy,enemy,eEliteSemiAutoGuard);
					game_class->enemys.push_back(enemy);
					break;
				case SENTRYA:
					enemy = new EnemyFlyingSentryA(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::snetry_a);
					enemy->lower_patrol_y = ycount+4;
					enemy->upper_patrol_y = ycount-4;
					game_class->ai_engine->AddAI(enemy, enemy, eFlyingSentryA);
					game_class->enemys.push_back(enemy);
					break;
				case SENTRYB:
					enemy = new EnemyFlyingSentryB(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::sentry_b);
					enemy->lower_patrol_x = xcount-5;
					enemy->upper_patrol_x = xcount+5;
					game_class->ai_engine->AddAI(enemy, enemy, eFlyingSentryB);
					game_class->enemys.push_back(enemy);
					break;
				case MRTHOMAS:
					enemy = new EnemyMrThomas(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					//enemy->SetSprite(0,CR::AssetList::mr_thomas_frameset);
					game_class->ai_engine->AddAI(enemy, enemy, eMrThomas);
					game_class->enemys.push_back(enemy);
					break;
				case PRISONER:
					enemy = new EnemyPrisoner(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::prisoner);
					enemy->lower_patrol_x = xcount-5;
					enemy->upper_patrol_x = xcount+5;
					game_class->ai_engine->AddAI(enemy,enemy, ePrisoner);
					game_class->enemys.push_back(enemy);
					break;
				case ROCKTHROWERPRISONER:
					enemy = new EnemyPrisonerRock(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::prisoner);
					enemy->SetDirection(false);
					game_class->ai_engine->AddAI(enemy,enemy, ePrisonerRock);
					game_class->enemys.push_back(enemy);
					break;
				case LARGEGENETICMONSTER:
					enemy = new EnemyGMonsterLarge(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Large_genetic_monster);
					game_class->ai_engine->AddAI(enemy,enemy, eGeneticMonster);
					game_class->enemys.push_back(enemy);
					break;
				case FIREBLOCK:
					enemy_fire = new EnemyFire(this);
					enemy_fire->SetProjectileList(projectile_list);
					enemy_fire->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy_fire->setGravityConstant(500.0f);
					enemy_fire->SetSprite(1, CR::AssetList::Fire_block);
					enemy_fire->StartFlame();
					game_class->ai_engine->AddAI(enemy_fire,enemy_fire, eGMonsterSmall);
					game_class->enemys.push_back(enemy_fire);
					break;
				case SMALLGENETICMONSTER:
					enemy = new EnemyGMonsterSmall(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Small_genetic_monster);
					game_class->ai_engine->AddAI(enemy,enemy, eGMonsterSmall);
					game_class->enemys.push_back(enemy);
					break;
				case FLAMEGENETICMONSTER:
					enemy = new EnemyGMonsterFire(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Fire_genetic_monster);
					game_class->ai_engine->AddAI(enemy,enemy, eGMonsterFire);
					game_class->enemys.push_back(enemy);
					break;
				case ZOMBIE:
					enemy = new EnemyZombiePrisoner(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Zombie_prisoner);
					enemy->SetDirection(true);
					game_class->ai_engine->AddAI(enemy,enemy, eZombie);
					game_class->enemys.push_back(enemy);
					break;
				case ADVANCEDGENETICMONSTER:
					enemy = new EnemyAdvancedGeneticMonster(this,game_class->player);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					//enemy->SetSprite(1,CR::AssetList::Advanced_genetic_monster_boss);
					game_class->ai_engine->AddAI(enemy, enemy, eAdvancedGeneticMonster);
					game_class->enemys.push_back(enemy);
					break;
				case FLYINGJUNKBOTVERTICAL:
					enemy = new EnemyJunkbotFlying(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Flying_Junkbot);
					enemy->lower_patrol_y = ycount-4;
					enemy->upper_patrol_y = ycount+4;
					game_class->ai_engine->AddAI(enemy,enemy, eJunkbotFlying );
					game_class->enemys.push_back(enemy);
					break;
				case FLYINGJUNKBOTHORIZONTAL:
					enemy = new EnemyJunkbotFlying(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Flying_Junkbot);
					enemy->lower_patrol_x = ycount-4;
					enemy->upper_patrol_x = ycount+4;
					game_class->ai_engine->AddAI(enemy,enemy, eJunkbotFlying2 );
					game_class->enemys.push_back(enemy);
					break;
				case WALKINGJUNKBOT:
					enemy = new EnemyJunkbotWalking(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Walking_Junkbot);
					game_class->ai_engine->AddAI(enemy,enemy, eJunkbotWalking );
					game_class->enemys.push_back(enemy);
					break;
				case TRACKBOT:
					enemy = new EnemyJunkbotTrack(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->lower_patrol_x = xcount-5;
					enemy->upper_patrol_x = xcount+5;
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Track_junkbot);
					game_class->ai_engine->AddAI(enemy,enemy, eJunkbotTrack);
					game_class->enemys.push_back(enemy);
					break;
				case FALCON:
					enemy = new EnemyBird(this, game_class->player);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Brown_bird);
					game_class->ai_engine->AddAI(enemy,enemy, eBird);
					game_class->enemys.push_back(enemy);
					break;
				case WOLF1:
					enemy_wolf = new EnemyWolf(this, 0);
					enemy_wolf->SetProjectileList(projectile_list);
					enemy_wolf->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy_wolf->setGravityConstant(500.0f);
					enemy_wolf->SetSprite(1, CR::AssetList::Brown_wolf);
					enemy_wolf->StartWolf();
					game_class->ai_engine->AddAI(enemy_wolf,enemy_wolf, eWolf);
					game_class->enemys.push_back(enemy_wolf);
					break;
				case WOLF2:
					enemy_wolf = new EnemyWolf(this, 1);
					enemy_wolf->SetProjectileList(projectile_list);
					enemy_wolf->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy_wolf->setGravityConstant(500.0f);
					enemy_wolf->SetSprite(1, CR::AssetList::Brown_wolf);
					enemy_wolf->StartWolf();
					game_class->ai_engine->AddAI(enemy_wolf,enemy_wolf, eWolf);
					game_class->enemys.push_back(enemy_wolf);
					break;
				case GAWAIN:
					enemy = new EnemyGawain(this, &(game_class->enemys), game_class->ai_engine, game_class->player);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::Gawain);
					game_class->ai_engine->AddAI(enemy, enemy, eGawain);
					game_class->enemys.push_back(enemy);
					break;
				case WATERMINE:
					enemy_watermine = new EnemyWaterMine(this);
					enemy_watermine->SetProjectileList(projectile_list);
					enemy_watermine->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy_watermine->setGravityConstant(500.0f);
					enemy_watermine->SetSprite(1, CR::AssetList::Water_mine);
					enemy_watermine->StartMine();
					game_class->ai_engine->AddAI(enemy_watermine,enemy_watermine, eWaterMine);
					game_class->enemys.push_back(enemy_watermine);
					//*(level_data+count) = WATERBLOCK;
					break;
				case BASEBALLPUNK:
					enemy = new EnemyBaseballPunk(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Baseball_punk);
					game_class->ai_engine->AddAI(enemy,enemy, eBaseballPunk);
					game_class->enemys.push_back(enemy);
					break;
				case MOHAWKPUNKS:
					enemy = new EnemyMohawkPunk(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Mohawk_punk);
					game_class->ai_engine->AddAI(enemy,enemy, ePunk);
					game_class->enemys.push_back(enemy);
					break;
				case MONKEYPUNKS:
					enemy = new EnemyPunk(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Jumping_punk);
					game_class->ai_engine->AddAI(enemy,enemy, eGMonsterSmall);
					game_class->enemys.push_back(enemy);
					break;
				case KNIFEPUNK:
					enemy = new EnemyKnifePunk(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Knife_punk);
					game_class->ai_engine->AddAI(enemy,enemy, eKnifePunk);
					game_class->enemys.push_back(enemy);
					break;
				case  DOCKWORKERWRENCHTHROWER:
					enemy = new EnemyDockWorkerWrechThrower(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Dock_Worker_throw);
					game_class->ai_engine->AddAI(enemy,enemy, eDockWrenchThrower);
					game_class->enemys.push_back(enemy);
					break;
				case DOCKWORKERLARGEWRENCH:
					enemy = new EnemyDockWorkerWrench(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Dock_Worker_Wrench);
					game_class->ai_engine->AddAI(enemy,enemy, eDockWrench);
					game_class->enemys.push_back(enemy);
					break;
				/*case DOCKWORKERROPE:
					enemy_dock_worker_rope = new EnemyDockWorkerRope(this);
					enemy_dock_worker_rope->SetProjectileList(projectile_list);
					enemy_dock_worker_rope->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy_dock_worker_rope->setGravityConstant(500.0f);
					enemy_dock_worker_rope->SetSprite(1, CR::AssetList::Dock_Worker_Rope);
					enemy_dock_worker_rope->StartDockWorkerRope();
					game_class->ai_engine->AddAI(enemy_dock_worker_rope,enemy_dock_worker_rope, eDockRope);
					game_class->enemys.push_back(enemy_dock_worker_rope);
					break;*/
				/*case BULLDOZER:
					enemy = new EnemyBullDozer(this);
					NEW(enemy);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1, CR::AssetList::Bull_Dozer);
					game_class->ai_engine->AddAI(enemy,enemy, eBullDozer);
					game_class->enemys.push_back(enemy);
					break;*/
				case CRASH:
					enemy = new EnemyCrash(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::Crash);
					game_class->ai_engine->AddAI(enemy, enemy, eCrash);
					game_class->enemys.push_back(enemy);
					break;
				case FLAMETHROWEROBSTACLEVERTICLE:
					enemy = new EnemyFlameThrower(this, 3, true);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount +3,0,7);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::Flame_Thrower_Down);
					game_class->enemys.push_back(enemy);
					break;
				case FLAMETHROWEROBSTACLELEFT:
					enemy = new EnemyFlameThrower(this, 3, false, false);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount-3,ycount +1,15,-2);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::Flame_Thrower_Side);
					game_class->enemys.push_back(enemy);
					break;
				case FLAMETHROWEROBSTACLERIGHT:
					enemy = new EnemyFlameThrower(this, 3, false);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount+1,ycount +1,15,-2);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::Flame_Thrower_Side);
					game_class->enemys.push_back(enemy);
					break;
				case SHOCKOBSTICLEVERTICAL: 
					enemy = new EnemyElectricField(this, 3, true);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount + 4,3,-1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::Electric_Field_Down);
					game_class->enemys.push_back(enemy);
					break;
				case SHOCKOBSTICLEHORIZONTAL:
					enemy = new EnemyElectricField(this, 3, false, false);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount-3,ycount + 1,6,-1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::Electric_Field_Side);
					game_class->enemys.push_back(enemy);
					break;	
				case SHADOWELITEBATONGUARD:
					enemy = new EnemyShadowElite(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::Elite_Shadow_Guard);
					game_class->ai_engine->AddAI(enemy,enemy,eEliteBatonGuard);
					game_class->enemys.push_back(enemy);
					break;
				case SHADOWELITEPISTOLGUARD:
					enemy = new EnemyShadowElitePistol(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::Elite_Shadow_Guard);
					game_class->ai_engine->AddAI(enemy,enemy,eElitePistolGuard);
					game_class->enemys.push_back(enemy);
					break;
				case SHADOWELITERIFLEGUARD:
					enemy = new EnemyShadowEliteRifle(this);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetDirection(false);
					enemy->SetSprite(1,CR::AssetList::Elite_Shadow_Guard);
					game_class->ai_engine->AddAI(enemy,enemy,eEliteSemiAutoGuard);
					game_class->enemys.push_back(enemy);
					break;
				case SPITGENETICMONSTER:
					enemy = new EnemyGMonsterSpit(this, game_class->player);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::Spitting_Genetic_Monster);
					game_class->ai_engine->AddAI(enemy,enemy, eGMonsterSpit);
					game_class->enemys.push_back(enemy);
					break;
				case MADSCIENTIST:
					enemy = new EnemyLabScientist(this,true);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy->setGravityConstant(500.0f);
					enemy->SetSprite(1,CR::AssetList::Mad_Scientist);
					game_class->ai_engine->AddAI(enemy,enemy, eLabScientist);
					game_class->enemys.push_back(enemy);
					break;
				case JACOB:
					enemy_jacob = new EnemyJacob(this, game_class->player);
					enemy_jacob->SetProjectileList(projectile_list);
					enemy_jacob->SetWorldLocAbsoluteT(xcount,ycount - 1);
					enemy_jacob->setGravityConstant(500.0f);
					//enemy_jacob->SetSprite(1,CR::AssetList::Jacob);
					//enemy_jacob->StartJacob();
					game_class->ai_engine->AddAI(enemy_jacob, enemy_jacob, eJacob);
					game_class->enemys.push_back(enemy_jacob);
					break;
				case BLUEDOOR:
					*(object_array+count) = new BasicBlock();
					*(object_array+count-1) = new BasicBlock();
					*(object_array+count+1) = new BasicBlock();
					*(level_data+count-1) = BASICBLOCK;
					*(level_data+count+1) = BASICBLOCK;
					((BasicBlock*)(*(object_array+count)))->SetTopCollide(false);
					((BasicBlock*)(*(object_array+count-1)))->SetTopCollide(false);
					((BasicBlock*)(*(object_array+count+1)))->SetTopCollide(false);
					enemy = new EnemyDoor(this,0,(object_array+count),(object_array+count-1),(object_array+count+1),level_data+count);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1, -8, 0);
					enemy->setGravityConstant(0.0f);
					enemy->SetSprite(1,CR::AssetList::Doors);
					game_class->enemys.push_back(enemy);
					break;
				case ORANGEDOOR:
					*(object_array+count) = new BasicBlock();
					*(object_array+count-1) = new BasicBlock();
					*(object_array+count+1) = new BasicBlock();
					*(level_data+count-1) = BASICBLOCK;
					*(level_data+count+1) = BASICBLOCK;
					((BasicBlock*)(*(object_array+count)))->SetTopCollide(false);
					((BasicBlock*)(*(object_array+count-1)))->SetTopCollide(false);
					((BasicBlock*)(*(object_array+count+1)))->SetTopCollide(false);
					enemy = new EnemyDoor(this,1,(object_array+count),(object_array+count-1),(object_array+count+1),level_data+count);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1, -8, 0);
					enemy->setGravityConstant(0.0f);
					enemy->SetSprite(1,CR::AssetList::Doors);
					game_class->enemys.push_back(enemy);
					break;
					/*case PURPLEDOOR:
					 *(object_array+count) = new BasicBlock();
					 *(object_array+count-1) = new BasicBlock();
					 *(object_array+count+1) = new BasicBlock();
					 *(level_data+count-1) = BASICBLOCK;
					 *(level_data+count+1) = BASICBLOCK;
					 NEW(*(object_array+count));
					 ((BasicBlock*)(*(object_array+count)))->SetTopCollide(false);
					 ((BasicBlock*)(*(object_array+count-1)))->SetTopCollide(false);
					 ((BasicBlock*)(*(object_array+count+1)))->SetTopCollide(false);
					 enemy = new EnemyDoor(this,2,(object_array+count),(object_array+count-1),(object_array+count+1),level_data+count);
					 NEW(enemy);
					 enemy->SetProjectileList(projectile_list);
					 enemy->SetWorldLocAbsoluteT(xcount,ycount - 1);
					 enemy->setGravityConstant(0.0f);
					 enemy->SetSprite(1,CR::AssetList::Doors);
					 game_class->enemys.push_back(enemy);
					 break;*/
				case GREENDOOR:
					*(object_array+count) = new BasicBlock();
					*(object_array+count-1) = new BasicBlock();
					*(object_array+count+1) = new BasicBlock();
					*(level_data+count-1) = BASICBLOCK;
					*(level_data+count+1) = BASICBLOCK;
					((BasicBlock*)(*(object_array+count)))->SetTopCollide(false);
					((BasicBlock*)(*(object_array+count-1)))->SetTopCollide(false);
					((BasicBlock*)(*(object_array+count+1)))->SetTopCollide(false);
					enemy = new EnemyDoor(this,3,(object_array+count),(object_array+count-1),(object_array+count+1),level_data+count);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount+1,ycount - 1, -8, 0);
					enemy->setGravityConstant(0.0f);
					enemy->SetSprite(1,CR::AssetList::Doors);
					game_class->enemys.push_back(enemy);
					break;
				case REDDOOR:
					*(object_array+count) = new BasicBlock();
					*(object_array+count-1) = new BasicBlock();
					*(object_array+count+1) = new BasicBlock();
					*(level_data+count-1) = BASICBLOCK;
					*(level_data+count+1) = BASICBLOCK;
					((BasicBlock*)(*(object_array+count)))->SetTopCollide(false);
					((BasicBlock*)(*(object_array+count-1)))->SetTopCollide(false);
					((BasicBlock*)(*(object_array+count+1)))->SetTopCollide(false);
					enemy = new EnemyDoor(this,4,(object_array+count),(object_array+count-1),(object_array+count+1),level_data+count);
					enemy->SetProjectileList(projectile_list);
					enemy->SetWorldLocAbsoluteT(xcount,ycount - 1, -8, 0);
					enemy->setGravityConstant(0.0f);
					enemy->SetSprite(1,CR::AssetList::Doors);
					game_class->enemys.push_back(enemy);
					break;						
					/*default:
					 *(object_array+count) = 0;
					 break;*/
					
			}
			count++;
			
		}
	}
	
}

void Level::Render()
{
/*	int count = level_y_size*level_x_size;
	for(int ycount = 0;ycount < count;ycount++)
	{
			if(*(object_array+ycount) != 0)
			{
				if((*(object_array+ycount))->IsVisable())
					(*(object_array+ycount))->Render();
			}
	}*/
	list<Object*>::iterator tempi = object_list.begin();
/*	while(tempi != object_list.end())
	{
		if((*tempi)->IsVisable()) (*tempi)->Render();
		tempi++;
	}*/

	int count = object_list.size();
	for(int ycount = 0;ycount < count ;ycount++)
	{
		if((*tempi)->IsVisable()){
		//	(*tempi)->SetRenderOffset(rand()%100, rand()%100);
			(*tempi)->Render();
		}
		tempi++;
	}
}


bool Level::NextToLadder()
{
	return laddercollide;
}

bool Level::StandingOnGround()
{
	return onground;
}

bool Level::HeadCollission()
{
	return headcollide;
}


void Level::SetQuality(int arg)
{
	quality = arg;
	//if(tile_background_back != 0)
	//{
	//	if(quality == 0) graphics_engine->SetTileBackgroundImage(0,tile_background_back);
	//	else graphics_engine->SetTileBackgroundImage(0,0);
	//}
}

void Level::DisableLevel()
{
	graphics_engine->SetTileBackgroundImage(0,0);
	graphics_engine->SetTileBackgroundImage(1,0);
	
}

void Level::EnableLevel()
{
#if !defined HPTMIPS
	if(quality == 0) graphics_engine->SetTileBackgroundImage(0,tile_background_back);
	else graphics_engine->SetTileBackgroundImage(0,0);
#endif
	graphics_engine->SetTileBackgroundImage(1,tile_background_front);

}

HPTRect Level::GetWorldBounds()
{
	HPTRect temp;
	temp.p1.x = 240;
	temp.p1.y = 160;
	temp.p2.x = (level_x_size<<4) - 240;
	temp.p2.y = (level_y_size<<4) - 160;
	return temp;
}

void Level::Update()
{
/*	int count = level_y_size*level_x_size;
	for(int ycount = 0;ycount < count ;ycount++)
	{
			if(*(object_array+ycount) != 0)
			{
				(*(object_array+ycount))->Update();
			}
	}
*/
	list<Object*>::iterator tempi = object_list.begin();
/*	while(tempi != object_list.end())
	{
		(*tempi)->Update();
		tempi++;
	}*/

	int count = object_list.size();
	for(int ycount = 0;ycount < count ;ycount++)
	{
		(*tempi)->Update();
		tempi++;
	}
}

void Level::WeaponCollideCheck(IPlayer* arg)
{
	IPlayerFlags *flags = arg->GetStateFlags();
	if(!flags->S_ATTACK) return;

	HPTRect& bounds = arg->GetWeaponWorldLoc();
	if(bounds.p1.x < 0) bounds.p1.x = 0;
	if(bounds.p1.y < 0) bounds.p1.y = 0;
	if(bounds.p2.x < 0) bounds.p2.x = 0;
	if(bounds.p2.y < 0) bounds.p2.y = 0;
	if(bounds.p1.x >= (level_x_size<<4)) bounds.p1.x = (level_x_size<<4) - 1;
	if(bounds.p1.y >= (level_y_size<<4)) bounds.p1.y = (level_y_size<<4) - 1;
	if(bounds.p2.x >= (level_x_size<<4)) bounds.p2.x = (level_x_size<<4) - 1;
	if(bounds.p2.y >= (level_y_size<<4)) bounds.p2.y = (level_y_size<<4) - 1;

	int numy,numx;
	numy = (bounds.p2.y >> 4) - (bounds.p1.y >> 4) + 1;
	numx = (bounds.p2.x >> 4) - (bounds.p1.x >> 4) + 1;
	

	Object *tempo;

	int xcount,ycount,tempx,tempy;
	tempx = bounds.p1.x >> 4;
	tempy = bounds.p1.y >> 4;
	bool tempb;
	for(ycount = 0;ycount < numy;ycount++)
	{
		tempx = bounds.p1.x >> 4;
		int templocy = (tempy*level_x_size);
		for(xcount = 0;xcount < numx;xcount++)
		{
			int temploc = tempx + templocy;
			if((*(level_data + temploc)) != 0)
			{
				tempo = *(object_array+temploc);
				if(tempo != 0)
				{
					tempb = tempo->WeaponCollideCheck(arg);
					if(tempb)
					{
						(*(level_data + temploc)) = 0;
					}
				//MessageBox(0,("error"),("error"),MB_OK);
				}
			
			}
			tempx++;
		}
		tempy++;
	}

}

void Level::ProjectileCollideCheck(Projectile* arg)
{
	HPTRect& bounds = arg->GetWeaponBounds();
	if(bounds.p1.x < 0) bounds.p1.x = 0;
	if(bounds.p1.y < 0) bounds.p1.y = 0;
	if(bounds.p2.x < 0) bounds.p2.x = 0;
	if(bounds.p2.y < 0) bounds.p2.y = 0;
	if(bounds.p1.x >= (level_x_size<<4)) bounds.p1.x = (level_x_size<<4) - 1;
	if(bounds.p1.y >= (level_y_size<<4)) bounds.p1.y = (level_y_size<<4) - 1;
	if(bounds.p2.x >= (level_x_size<<4)) bounds.p2.x = (level_x_size<<4) - 1;
	if(bounds.p2.y >= (level_y_size<<4)) bounds.p2.y = (level_y_size<<4) - 1;

	int numy,numx;
	numy = (bounds.p2.y >> 4) - (bounds.p1.y >> 4) + 1;
	numx = (bounds.p2.x >> 4) - (bounds.p1.x >> 4) + 1;
	

	Object *tempo;

	int xcount,ycount,tempx,tempy;
	tempx = bounds.p1.x >> 4;
	tempy = bounds.p1.y >> 4;
	bool tempb;
	for(ycount = 0;ycount < numy;ycount++)
	{
		tempx = bounds.p1.x >> 4;
		int templocy = (tempy*level_x_size);
		for(xcount = 0;xcount < numx;xcount++)
		{
			int temploc = tempx + templocy;
			if((*(level_data + temploc)) != 0)
			{
				tempo = *(object_array+temploc);
				if(tempo != 0)
				{
					tempb = tempo->ProjectileCollideCheck(player, arg);
					if(tempb)
					{
						(*(level_data + temploc)) = 0;
					}
				//MessageBox(0,("error"),("error"),MB_OK);
				}			
			}
			tempx++;
		}
		tempy++;
	}


	/*
//	HPTRect& bounds = arg->GetWeaponWorldLoc();
//	if(bounds.p1.x < 0) bounds.p1.x = 0;
//	if(bounds.p1.y < 0) bounds.p1.y = 0;
//	if(bounds.p2.x < 0) bounds.p2.x = 0;
//	if(bounds.p2.y < 0) bounds.p2.y = 0;
//	if(bounds.p1.x >= (level_x_size<<4)) bounds.p1.x = (level_x_size<<4) - 1;
//	if(bounds.p1.y >= (level_y_size<<4)) bounds.p1.y = (level_y_size<<4) - 1;
//	if(bounds.p2.x >= (level_x_size<<4)) bounds.p2.x = (level_x_size<<4) - 1;
//	if(bounds.p2.y >= (level_y_size<<4)) bounds.p2.y = (level_y_size<<4) - 1;

	HPTPoint bounds;
	bounds.x = arg->GetXLoc();
	bounds.y = arg->GetYLoc();

	//(*graphics_engine) << bounds.x << " " << bounds.y;
	
	if(bounds.x < 0) bounds.x = 0;
	if(bounds.x >= (level_x_size<<4)) bounds.x = (level_x_size<<4) - 1;
	if(bounds.y < 0) bounds.y = 0;
	if(bounds.y >= (level_y_size<<4)) bounds.y = (level_y_size<<4) - 1;


	
	

	Object *tempo;

	int xcount,ycount,tempx,tempy;
	tempx = bounds.x >> 4;
	tempy = bounds.y >> 4;

	int temploc = tempx + (tempy*level_x_size);
	bool tempb;
	if((*(level_data + temploc)) != 0)
	{
		//MessageBox(0,("error"),("error"),MB_OK);
		tempo = *(object_array+temploc);
		if(tempo != 0)
		{
			tempb = tempo->ProjectileCollideCheck(arg);
			if(tempb)
			{
				(*(level_data + temploc)) = 0;
			}
		}
	
	}
*/
}

void Level::SetTime(float arg)
{
	Object::SetTime(arg);
/*	int count = 0;
	for(int ycount = 0;ycount < level_y_size*level_x_size;ycount++)
	{
	//	for(int xcount = 0;xcount < level_x_size;xcount++)
	//	{
			//char temp = *(level_data+count);
			if(*(object_array+count) != 0)
			{
				(*(object_array+count))->SetTime(arg);
				return;
			}
			count++;
	//	}
	}*/
}

void Level::UnloadLevel()
{
/*	Object *tempo;
	if(object_array != 0)
	{
		for(int count = 0;count < level_x_size*level_y_size;count++)
		{
			tempo = *(object_array+count);
			if(tempo != 0) delete tempo;
		}
		delete[] object_array;
	}
	if(level_data != 0) delete[] level_data;
	object_list.clear();
*/
#if !defined HPTMIPS
	tile_background_back->Release();
#endif
	tile_background_front->Release();


#if !defined HPTMIPS
	tile_background_back = graphics_engine->CreateHPTTileBackground();
#endif
	tile_background_front = graphics_engine->CreateHPTTileBackground();
//	level_data = 0;
//	object_array = 0;
//	player = 0;
//	projectile_list = 0;

//	x_render_offset = 0;
//	y_render_offset = 0;

}

void Level::ResetToSpawnPointData(SpawnPointInfo spawnInfo)
{
	//object_list.clear();
	//LoadObjects(false);
	
	// object states
	//list<Object*> object_list = level_class->GetObjectList();		
	int i = 0;
	for (list<Object*>::iterator tobject = object_list.begin(); tobject != object_list.end(); tobject++)
	{
		(*tobject)->Reinitialize();
		(*tobject)->SetState(spawnInfo.objectStates[i]);
		i++;
	}
}

bool Level::IsCollidable(int xLoc, int yLoc)
{
	int temploc = xLoc + (yLoc*level_x_size);
	Object *tempo;
	
	if((*(level_data + temploc)) != 0)
	{
		tempo = *(object_array+temploc);
		if(tempo != 0)
		{
			return tempo->IsCollidable();
		}
	}
	return false;
}