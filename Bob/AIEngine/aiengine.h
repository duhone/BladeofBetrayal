#ifndef AIENGINE_H
#define AIENGINE_H


#include "../AILevel.h"
//#include "AIInput.h"
//#include "AIoutput.h"
#include "../IPlayer.h"





enum ENEMY_TYPE {
//	eBear,
//	eEliteGuard,
//	eFalcon,
//	eGeneticMonster,
//	eMutatedPrisoner,
//	eNinja,
	eBlueNinja,
	eRedNinja,
	eBrownNinja,
	eGreenNinja,
	eEliteBatonGuard,
	eElitePistolGuard,
	eEliteSemiAutoGuard,
	eFlyingSentryA,
	eFlyingSentryB,
	eTowerBot,
	eLandMine,
	eMrThomas,
	eLabScientist,
	ePrisoner,
	ePrisonerRock,
	eGMonsterFire,
	eGMonsterSpit,
	eGMonsterSmall,
	eZombie,
	eJunkbotWalking,
	eJunkbotTrack,
	eJunkbotLarge,
	eAdvancedGeneticMonster,
	eGeneticMonster,
	eGawain,
	eWolf,
	eJunkbotFlying,
	eJunkbotFlying2,
	eBird,
	eWaterMine,
	ePunk,
	eBaseballPunk,
	eKnifePunk,
	eDockWrenchThrower,
	eDockWrench,
	eDockRope,
	eBullDozer,
	eCrash,
	eJacob,
	eAGM
//	eThug,
//	eWolf
 };


class AIObject
{
public:
	AIObject(){ ai_map =0;};
	virtual ~AIObject(){};

	AIInput* player_input;
	AILevel* level_interface;
	int level;

	unsigned char *ai_map;
	int aimap_width;
	int aimap_height;

};




class AIEngine
{
public:
	AIEngine(){};
	virtual ~AIEngine(){};

	virtual void AddAI(AIInput* aii, AIOutput* aio, enum ENEMY_TYPE enemy_type)=0;
	//virtual void RemoveAI()=0;
	virtual void RemoveAll()=0;
	virtual void RegisterAIObject(AIObject* arg)=0;
	virtual void Release()=0;
	virtual void Start()=0;
	virtual void Resume()=0;
	virtual void Pause()=0;
	virtual void SetPath(char *path_name)=0;


};

AIEngine* GetAIEngine();


#endif