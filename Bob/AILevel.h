// AILevel.h: interface for the AILevel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AILEVEL_H__A3759B16_950B_41A1_8B00_69D9F873ABAF__INCLUDED_)
#define AFX_AILEVEL_H__A3759B16_950B_41A1_8B00_69D9F873ABAF__INCLUDED_


#define BASICBLOCK 1  /* collidable */
#define DESTROYABLEBLOCK 2 /* collidable */
#define BOUNCEBLOCK 3 
#define NONSIDEBASICBLOCK 4
#define CONVEYORBLOCKLEFT 5 /* collidable */
#define CONVEYORBLOCKRIGHT 6 /* collidable */
#define CONVEYORBLOCKLEFTENDLEFT 36 /* collidable */
#define CONVEYORBLOCKRIGHTENDLEFT 37 /* collidable */
#define CONVEYORBLOCKLEFTENDRIGHT 38 /* collidable */
#define CONVEYORBLOCKRIGHTENDRIGHT 39 /* collidable */

//#define CLIMBBLOCK 7
#define NONTOPBASICBLOCK 8 /* collidable sides, non collidable top and bottom */
#define CLIMBBLOCKLEFT 9 
#define CLIMBBLOCKRIGHT 10
#define SMALLHEALTH 11 /* collidable */
#define LARGEHEALTH 12 /* collidable */
#define FREELIFE 13 /* collidable */
#define SMALLENERGY 14 /* collidable */
#define LARGEENERGY 15 /* collidable */
//#define ATTACK1 16 /* collidable */
//#define ATTACK2 17 /* collidable */
//#define ATTACK3 18 /* colliaable */
//#define ATTACK4 19 /* collidable */
//#define ATTACK5 20 /* collidable */
//#define ATTACK6 40 /* collidable */
//#define HEALTHUPGRADE 21 /* collidable */
//#define ENERGYUPGRADE 22 /* collidable */
#define CLIMBLADDER 23
#define CLIMBROPE 24
#define ENDLEVEL 25
#define WATERBLOCK 26
#define SPAWNFLAG 27
#define GASBLOCK 28

#define TREASURE1 30 //documents  //is now 1 grenade
#define TREASURE2 31 //folder   //is now 5 grenades
#define TREASURE3 32 //disk     //is now the goal marker
#define TREASURE4 33 //microfilm
#define TREASURE5 34 //breifcase
#define TREASURE6 35 //attack upgrade
#define TUTORIAL_CROUCH 40
#define TUTORIAL_EXPLORE 41

#define BEACON 42

#define FAN3B 43

#define FIREBLOCK 128
#define SPIKEBLOCK 129 /* collidable */

//codes 140-184 are reserved for enemys. all enemies must be here, and no non enemies must be in this range
#define ENEMYFIRST 140
#define GREENNINJA 140
#define BLUENINJA 141
#define REDNINJA 142
#define LANDMINE 143
#define ELITEBATONGAURDS 144
#define ELITEPISTOLGAURDS 145
#define ELITERIFLEGAURDS 146
#define SENTRYA 147
#define SENTRYB 148
#define MRTHOMAS 149
#define PRISONER 150
#define ROCKTHROWERPRISONER 151
#define LARGEGENETICMONSTER 152
#define SMALLGENETICMONSTER 154
#define FLAMEGENETICMONSTER 155
#define ZOMBIE 156
#define ADVANCEDGENETICMONSTER 157
#define FLYINGJUNKBOTVERTICAL 158
#define FLYINGJUNKBOTHORIZONTAL 159
#define WALKINGJUNKBOT 160
#define TRACKBOT 161
#define FALCON 162
#define WOLF1 163
#define WOLF2 164
#define GAWAIN 165
#define WATERMINE 166
#define BASEBALLPUNK 167
#define MOHAWKPUNKS 168
#define MONKEYPUNKS 169
#define KNIFEPUNK 170
#define DOCKWORKERWRENCHTHROWER 171
#define DOCKWORKERLARGEWRENCH 172
//#define DOCKWORKERROPE 173
#define FLAMETHROWEROBSTACLELEFT 173
//#define BULLDOZER 174
#define MADSCIENTIST 174
#define CRASH 175
#define FLAMETHROWEROBSTACLEVERTICLE 176
#define FLAMETHROWEROBSTACLERIGHT 177
#define SHOCKOBSTICLEVERTICAL 178
#define SHOCKOBSTICLEHORIZONTAL 179
#define SHADOWELITEBATONGUARD 180
#define SHADOWELITEPISTOLGUARD 181
#define SHADOWELITERIFLEGUARD 182
#define SPITGENETICMONSTER 183
#define JACOB 184
//#define ENEMYLAST 184

#define BLUEDOOR 185
#define ORANGEDOOR 186
//#define PURPLEDOOR 187
#define GREENDOOR 187
#define REDDOOR 188
#define ENEMYLAST 188


#define ATTACK1NKEY 200 /* collidable */
#define ATTACK1BKEY 201 /* collidable */
#define ATTACK1OKEY 202 /* collidable */
#define ATTACK1GKEY 203 /* collidable */
#define ATTACK1RKEY 204 /* collidable */
#define ATTACK2NKEY 205 /* collidable */
#define ATTACK2BKEY 206 /* collidable */
#define ATTACK2OKEY 207 /* collidable */
#define ATTACK2GKEY 208 /* collidable */
#define ATTACK2RKEY 209 /* collidable */
#define ATTACK3NKEY 210 /* collidable */
#define ATTACK3BKEY 211 /* collidable */
#define ATTACK3OKEY 212 /* collidable */
#define ATTACK3GKEY 213 /* collidable */
#define ATTACK3RKEY 214 /* collidable */
#define ATTACK4NKEY 215 /* collidable */
#define ATTACK4BKEY 216 /* collidable */
#define ATTACK4OKEY 217 /* collidable */
#define ATTACK4GKEY 218 /* collidable */
#define ATTACK4RKEY 219 /* collidable */
#define HEALTHUPGRADENKEY 220 /* collidable */
#define HEALTHUPGRADEBKEY 221 /* collidable */
#define HEALTHUPGRADEOKEY 222 /* collidable */
#define HEALTHUPGRADEGKEY 223 /* collidable */
#define HEALTHUPGRADERKEY 224 /* collidable */
#define ENERGYUPGRADENKEY 225 /* collidable */
#define ENERGYUPGRADEBKEY 226 /* collidable */
#define ENERGYUPGRADEOKEY 227 /* collidable */
#define ENERGYUPGRADEGKEY 228 /* collidable */
#define ENERGYUPGRADERKEY 229 /* collidable */

class AILevel  
{
public:
	virtual bool NextToLadder() = 0;
	virtual bool StandingOnGround() = 0;
	virtual bool HeadCollission() = 0;
	virtual unsigned char GetLevelData(int x,int y) = 0;
	AILevel();
	virtual ~AILevel();

};

#endif // !defined(AFX_AILEVEL_H__A3759B16_950B_41A1_8B00_69D9F873ABAF__INCLUDED_)
