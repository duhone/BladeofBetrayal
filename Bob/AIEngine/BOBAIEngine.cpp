// BOBAIEngine.cpp: implementation of the BOBAIEngine class.
//
//////////////////////////////////////////////////////////////////////



#include "BOBAIEngine.h"
//#include "hptlist.h"

#include "AIEnemyGreenNinja.h"
#include "AIEnemyRedNinja.h"
#include "AIEnemyBrownNinja.h"
#include "../EnemyTowerBot.h"
#include "AIEnemyLandMine.h"
#include "AIEnemyBlueNinja.h"
#include "AIEnemyFlyingSentryA.h"
#include "AIEnemyFlyingSentryB.h"

#include "AIEnemyMrThomas.h"
#include "AIEnemyEliteBatonGaurd.h"
#include "AIEnemyElitePistolGaurd.h"
#include "AIEnemyEliteSemiAutoGuard.h"

#include "AIEnemyPrisoner.h"
#include "AIEnemyPrisonerRock1.h"

#include "AIEnemyGMonsterFire.h"
#include "AIEnemyGMonsterSmall.h"

#include "AIEnemyLabScientist.h"
#include "AIEnemyZombie.h"

#include "AIEnemyJunkbotWalking.h"
#include "AIEnemyJunkbotTrack.h"
#include "AIEnemyJunkbotLarge.h"

#include "AIEnemyAdvancedGeneticMonster.h"

#include "AIEnemyGMonster.h"

#include "AIEnemyGawain.h"

#include "AIEnemyWolf.h"
#include "AIEnemyJunkbotFlying.h"
#include "AIEnemyJunkbotFlying2.h"
#include "AIEnemyBird.h"

#include "AIEnemyWaterMine.h"

#include "AIEnemyPunk.h"
#include "AIEnemyBaseballPunk.h"
#include "AIEnemyKnifePunk.h"

#include "AIEnemyDocWrenchThrower.h"
#include "AIEnemyDocWrench.h"
#include "AIEnemyDocRope.h"

#include "AIEnemyBullDozer.h"

#include "AIEnemyCrash.h"

#include "AIEnemyJacob.h"

#include "AIEnemyGMonsterSpit.h"

#include "AIEnemyAdvancedGeneticMonster2.h"

#include <stdio.h>
//#include <mach/mach.h>
//#include <mach/mach_time.h>
#include "../FilePaths.h"
#include "s3eTimer.h"

#include "../../Engines/Utility/FunctionObjects.h"

extern BOBAIEngine* aiengine;

using namespace std;
using namespace CR::Utility;

void AINEW(void *arg)
{
	//if(arg == NULL);
		//MessageBox(NULL,"Out of memory aiengine","Error"),MB_OK);
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOBAIEngine::BOBAIEngine()
{
	m_delay=0;
	reference_count =0;
	paused = false;
	//thread_hndl = CreateThread(NULL, 0, GetThreadProc(), this, CREATE_SUSPENDED, NULL);
	//SetThreadPriority(thread_hndl,THREAD_PRIORITY_ABOVE_NORMAL);
	//int tf;
	//QueryPerformanceFrequency(&tf);
	//time_freq = 1.0f/SysTicksPerSecond();
	//mach_timebase_info_data_t time_info;
	//mach_timebase_info(&time_info);
	//time_freq = time_info.numer/(float)time_info.denom;
	time_freq = 1/1000.0f;
	
	aiobject=0;
	srand( s3eTimerGetMs() ); 
	sprintf(path, "");
	prev_time = s3eTimerGetMs();
	curr_time = s3eTimerGetMs();
}

BOBAIEngine::~BOBAIEngine()
{
	//MessageBox(NULL, _T("aiengine"), _T("error"), MB_OK);
	RemoveAll();
	//MessageBox(NULL, _T("aiengine"), _T("error"), MB_OK);
	if(aiobject != NULL) 
	{
		if(aiobject->ai_map != NULL) delete[] aiobject->ai_map;
	}
	
	//TerminateThread(thread_hndl, 0);
	//CloseHandle(thread_hndl);


}

void BOBAIEngine::Resume()
{	
	prev_time = s3eTimerGetMs();
	curr_time = s3eTimerGetMs();
}

void BOBAIEngine::AddAI(AIInput *aii, AIOutput *aio, enum ENEMY_TYPE enemy_type)
{
	
	BaseEnemy *new_enemy=0;

	switch(enemy_type)
	{
	case eGreenNinja:
		new_enemy = new AIEnemyGreenNinja;
		//MessageBox(NULL, _T(""), _T(""), MB_OK);
		break;
	case eRedNinja:
		new_enemy = new AIEnemyRedNinja;
		break;
	case eBrownNinja:
		new_enemy = new AIEnemyBrownNinja;
		break;
	case eBlueNinja:
		new_enemy = new AIEnemyBlueNinja;
		break;
	case eFlyingSentryA:
		new_enemy = new AIEnemyFlyingSentryA;
		break;
	case eFlyingSentryB:
		new_enemy = new AIEnemyFlyingSentryB;
		break;
	case eLandMine:
		new_enemy = new AIEnemyLandMine;
		break;
	
	case eEliteBatonGuard:
		new_enemy = new AIEnemyEliteBatonGaurd;
		break;
	case eEliteSemiAutoGuard:
//		new_enemy = new EnemyRedNinja;
//		new_enemy = new EnemyElitePistolGaurd;
		new_enemy = new AIEnemyEliteSemiAutoGuard;
		break;
	case eElitePistolGuard:
		new_enemy = new AIEnemyElitePistolGaurd;
		break;
	case eMrThomas:
		new_enemy = new AIEnemyMrThomas;
		break;
	case ePrisoner:
		new_enemy = new AIEnemyPrisoner;
		break;
	case ePrisonerRock:
		new_enemy = new AIEnemyPrisonerRock;
		break;
	case eGMonsterFire:
		new_enemy = new AIEnemyGMonsterFire;
		break;
	case eGMonsterSmall:
		new_enemy = new AIEnemyGMonsterSmall;
		break;
	case eLabScientist:
		new_enemy = new AIEnemyLabScientist;
		break;
	case eZombie:
		new_enemy = new AIEnemyZombie;
		break;
	case eJunkbotWalking:
		new_enemy = new AIEnemyJunkbotWalking;
		break;
	case eJunkbotTrack:
		new_enemy = new AIEnemyJunkbotTrack;
		break;
	case eJunkbotLarge:
		new_enemy = new AIEnemyJunkbotLarge;
		break;
	case eAdvancedGeneticMonster:
		new_enemy = new AIEnemyAdvancedGeneticMonster;
		break;
	case eGeneticMonster:
		new_enemy = new AIEnemyGMonster;
		break;
	case eGawain:
		new_enemy = new AIEnemyGawain;
		break;
	case eWolf:
		new_enemy = new AIEnemyWolf;
		break;
	case eJunkbotFlying:
		new_enemy = new AIEnemyJunkbotFlying;
		break;
	case eJunkbotFlying2:
		new_enemy = new AIEnemyJunkbotFlying2;
		break;
	case eBird:
		new_enemy = new AIEnemyBird;
		break;
	case eWaterMine:
		new_enemy = new AIEnemyWaterMine;
		break;
	case ePunk:
		new_enemy = new AIEnemyPunk;
		break;
	case eBaseballPunk:
		new_enemy = new AIEnemyBaseballPunk;
		break;
	case eKnifePunk:
		new_enemy = new AIEnemyKnifePunk;
		break;
	case eDockWrenchThrower:
		new_enemy = new AIEnemyDocWrenchThrower;
		break;
	case eDockWrench:
		new_enemy = new AIEnemyDocWrench;
		break;
	case eDockRope:
		new_enemy = new AIEnemyDocRope;
		break;
	case eBullDozer:
		new_enemy = new AIEnemyBullDozer;
		break;
	case eCrash:
		new_enemy = new AIEnemyCrash;
		break;
	case eJacob:
		new_enemy = new AIEnemyJacob;
		break;
	case eGMonsterSpit:
		new_enemy = new AIEnemyGMonsterSpit;
		break;
	case eAGM:
		new_enemy = new AIEnemyAdvancedGeneticMonster;
		break;
	default:
		new_enemy = new BaseEnemy;
		break;

	}

	AINEW(new_enemy);

	new_enemy->aiinput = aii;
	new_enemy->aioutput = aio;
	new_enemy->aio = aiobject;
	new_enemy->tileheight = aii->GetTileHeight();
//	new_enemy->debug = _tfopen(_T("aidebug.txt"), _T("w"));
	new_enemy->new_enemy = true;
	new_enemy->Init();
	


	enemies.push_back(new_enemy);
	
}

void BOBAIEngine::RemoveAll()
{
	//list<BaseEnemy*>::iterator iter;
	BaseEnemy* temp;
	
	/*for(iter = enemies.begin(); iter != enemies.end(); iter++)
	{
		temp = (*iter);
		delete temp;
	}*/
	ForEach(enemies, DeleteFO());
	enemies.clear();
}

void BOBAIEngine::RegisterAIObject(AIObject *arg)
{
	// HACK: Bonus levels don't have AI
	if (arg->level >= 16) return;

	//char file[512];
	char  HLF[3];
	int version;
	FILE  *fp=0;
	int width, height;

	aiobject = arg;

	if(aiobject->ai_map != NULL) delete[] aiobject->ai_map;

	//sprintf(file, "%slevels/ai%i.hlf", path, aiobject->level);
	int level = aiobject->level;
	if(level >= 13)
		level -= 6;
	//cout << FilePaths::Instance().GetAILevelPath(level) << " / " << level;
  	fp = fopen(FilePaths::Instance().GetAILevelPath(level).c_str(), "rb");
	//if(fp == NULL) MessageBox(NULL, path, _T("AI_ERROR"), MB_OK);
	//else
	//{
	if(fp != NULL)
	{
		fread(HLF, sizeof(char), 3, fp);
		fread(&version, sizeof(int), 1, fp);
		fread(&width, sizeof(int), 1, fp);
		fread(&height, sizeof(int), 1, fp);
		
		aiobject->aimap_width = width;
		aiobject->aimap_height = height;
		
		aiobject->ai_map = new unsigned char[width*height];
		AINEW(aiobject->ai_map);
		
		fread(aiobject->ai_map, sizeof(unsigned char), width*height, fp);
		
		fclose(fp);
	}
	//fp = _tfopen( _T("aimap.txt"), _T("w"));
	//_ftprintf(fp, _T("%s\n"), file);
	//_ftprintf(fp, _T("%i %i\n"), width, height);
	/*for(int i=0; i< (width * height);	i++)
	{
		_ftprintf(fp, _T("%i\n"), aiobject->ai_map[i]);
	}

	fclose(fp);*/


	
}

void BOBAIEngine::Release()
{
	--reference_count;

	if(reference_count <= 0)
	{
		reference_count = 0;
		delete this;
	}

	aiengine = NULL;

}		

void BOBAIEngine::Start()
{
	m_delay++;
	if((m_delay&0x03) != 0)
		return;
	else
		m_delay=0;
	
	vector<BaseEnemy*>::iterator iter;
	vector<BaseEnemy*>::iterator end;
	BaseEnemy* enemy;


//	QueryPerformanceCounter(&aiengine->curr_time);
//	QueryPerformanceCounter(&aiengine->prev_time);

//	for(;;)
//	{
//		QueryPerformanceCounter(&aiengine->curr_time);
		curr_time = s3eTimerGetMs();
		time = (curr_time - prev_time)*time_freq;
	
		time = min(time, 1.0f);

		prev_time = curr_time;

	end = enemies.end();
		for(iter = enemies.begin(); iter != end; ++iter)
		{
			if((*iter)->aiinput->ipFlags.S_ACTIVE)
			{
				(*iter)->time = aiengine->time;
				(*iter)->UseBrain();
			}
		}
		
		
		//QueryPerformanceCounter(&current_time);
		//SuspendThread(aiengine->GethThread());
	//}
}

/*void BOBAIEngine::Pause()
{
	paused = true;
	//SuspendThread(thread_hndl);	
}*/

/*DWORD WINAPI BOBAIEngine::ThreadProc(LPVOID arg)
{
	BOBAIEngine* aiengine;
	BaseEnemy* enemy;

	aiengine = (BOBAIEngine*)arg;

	HPTList<BaseEnemy*>::iterator iter;

	QueryPerformanceCounter(&aiengine->curr_time);
	QueryPerformanceCounter(&aiengine->prev_time);

	for(;;)
	{
		QueryPerformanceCounter(&aiengine->curr_time);
		aiengine->time = (aiengine->curr_time.QuadPart - aiengine->prev_time.QuadPart)*aiengine->time_freq;
		aiengine->prev_time = aiengine->curr_time;

		for(iter = aiengine->enemies.begin(); iter != aiengine->enemies.end(); iter++)
		{
			
			enemy = (*iter);
			if(/*((enemy->aiinput->GetStateFlags())->S_ACTIVE) && (!(enemy->aiinput->GetStateFlags())->S_DEAD)) */
/*			{
				enemy->time = aiengine->time;
				enemy->UseBrain();
			}
		}
		
		
		//QueryPerformanceCounter(&current_time);
		SuspendThread(aiengine->GethThread());
	}
	

	return 0;
}*/

void BOBAIEngine::SetPath(char *path_name)
{
	sprintf(path, "%s", path_name);
//	MessageBox(NULL, path, _T("AI"), MB_OK);
}

