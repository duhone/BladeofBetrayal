#include "AIEngine.h"
#include "BOBAIEngine.h"

extern void AINEW(void *arg);

BOBAIEngine* aiengine = NULL;

AIEngine* GetAIEngine()
{

	if(aiengine == NULL) {
		aiengine = new BOBAIEngine;
		AINEW(aiengine);
	}
	
	aiengine->IncReference();

	return aiengine;

}