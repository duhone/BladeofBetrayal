// BOBAIEngine.h: interface for the BOBAIEngine class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BOBAIENGINE_H
#define BOBAIENGINE_H




#include "aiengine.h"
//#include "hptlist.h"
//#include "windows.h"
#include "baseenemy.h"
#include<list>


class BOBAIEngine : public AIEngine  
{
public:
	void SetPath(char *path_name);
	void Pause(){};
	void Start();
	void Resume();
	void Release();
	void RegisterAIObject(AIObject* arg);
	void RemoveAll();
	void AddAI(AIInput* aii, AIOutput* aio, enum ENEMY_TYPE enemy_type);
	BOBAIEngine();
	virtual ~BOBAIEngine();
	void IncReference(){ ++reference_count;};
	int GetRefCnt(){return reference_count;};
	//LPTHREAD_START_ROUTINE GetThreadProc(){return ThreadProc;};
	
	std::vector<BaseEnemy*> enemies;

	//HANDLE GethThread(){return thread_hndl;};
	
	int prev_time, curr_time ;
	float time_freq, time;
	
private:
	char path[257];
	bool paused;
	int reference_count;
//	static DWORD WINAPI ThreadProc(LPVOID arg);
	
	
//	HANDLE thread_hndl;
	AIObject* aiobject;
	int m_delay;
};

#endif // !defined(AFX_BOBAIENGINE_H__549DD0AA_97D6_459C_9F3B_22B68D36D51A__INCLUDED_)
