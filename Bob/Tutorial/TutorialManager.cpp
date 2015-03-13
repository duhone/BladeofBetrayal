#include "TutorialManager.h"
#include "AssetListFull.h"
#include "AppConfig.h"

using namespace std;

extern Input_Engine   *input_engine;

TutorialManager::TutorialManager() : m_baseAnim(NULL) , m_textSprite(NULL)
{
	m_button = new Input_Button();
	m_button->Disabled(true);
	m_button->OnClicked += Delegate(this,&TutorialManager::Finished);
	input_objects.push_back(m_button);

	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage1));
	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage2));
	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage3));
	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage4));
	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage5));
	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage6));
	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage7));
	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage8));
	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage9));
	m_tutorials.push_back(Tutorial(CR::AssetList::TutorialMessage10));
	
	HPTGraphicsEngine *gengine = GetHPTGraphicsEngine();
	gengine->CacheTexture(CR::AssetList::TutorialMessage1);
	gengine->CacheTexture(CR::AssetList::TutorialMessage2);
	gengine->CacheTexture(CR::AssetList::TutorialMessage3);
	gengine->CacheTexture(CR::AssetList::TutorialMessage4);
	gengine->CacheTexture(CR::AssetList::TutorialMessage5);
	gengine->CacheTexture(CR::AssetList::TutorialMessage6);
	gengine->CacheTexture(CR::AssetList::TutorialMessage7);
	gengine->CacheTexture(CR::AssetList::TutorialMessage8);
	gengine->CacheTexture(CR::AssetList::TutorialMessage9);
	gengine->CacheTexture(CR::AssetList::TutorialMessage10);

	m_baseAnim = gengine->CreateSprite1(true);
	m_textSprite = gengine->CreateSprite1(true);
	if(AppConfig::Instance().IsIpad())
		m_textSprite->SetDesignSize(181,50);
	gengine->Release();
	m_baseAnim->SetImage(CR::AssetList::TutorialAnim);
	if(AppConfig::Instance().IsIpad())
		m_baseAnim->SetDesignSize(243,109);
	if(AppConfig::Instance().IsIpad())		
		m_button->SetSpriteAndBounds(291,245,CR::AssetList::TutorialButton);
	else
		m_button->SetSpriteAndBounds(306,192,CR::AssetList::TutorialButton);
	if(AppConfig::Instance().IsIpad())
		m_button->DesignSize(59,25);	
}

void TutorialManager::Cleanup()
{
	m_button->FreeResources();
	delete m_button;
	if(m_baseAnim)
		m_baseAnim->Release();
	if(m_textSprite)
		m_textSprite->Release();
}

void TutorialManager::CheckForTutorial(Game *_game)
{
	m_game = _game;
	if(m_game->player->ipFlags.S_ON_LADDER)
		Trigger(TLADDERS);
	for(int i = 0;i < m_tutorials.size();++i)
	{
		if(m_tutorials[i].Trigger)
		{
			m_tutorials[i].Triggered = true;
			m_tutorials[i].Trigger = false;
			_game->ChangeState(game_tutorial);
			
			m_baseAnim->SetFrame(0);
			m_baseAnim->SetFrameSet(0);
			m_baseAnim->SetFrameRate(30.0f);
			m_baseAnim->SetAutoAnimate(true);
			m_baseAnim->AutoStopAnimate();
			if(AppConfig::Instance().IsIpad())	
			{
				m_baseAnim->SetPositionAbsalute(238,223);
				m_textSprite->SetPositionAbsalute(238,220);
			}
			else	
			{
				m_baseAnim->SetPositionAbsalute(240,160);
				m_textSprite->SetPositionAbsalute(240,157);
			}
		
			m_textSprite->SetImage(m_tutorials[i].Text);

			m_button->Disabled(false);
			
			input_engine->RegisterInputController(this);
			return;
		}
	}
}

void TutorialManager::Tick()
{
	if(m_baseAnim)
	{
		m_baseAnim->Render();
		if(!m_baseAnim->IsAnimating())
		{
			m_button->Render();
			m_textSprite->Render();
		}
	}
}

void TutorialManager::Trigger(Tutorials _tutorial)
{
	if(!m_tutorials[_tutorial].Triggered)
	{
		m_tutorials[_tutorial].Trigger = true;
		m_currentTutorial = _tutorial;
	}
}
void TutorialManager::Finished()
{
	//m_button->FreeResources();
	//m_baseAnim->Release();
	//m_baseAnim = NULL;
	//m_textSprite->Release();
	//m_textSprite = NULL;
	m_game->GetSaveGameManager()->SaveToDisk(DEFAULT_SAVE_FILE);
	m_game->ChangeState(game_ingame);
	input_engine->RegisterInputController(m_game);
}

void TutorialManager::SetTriggers(bool *_triggers)
{
	for(int i = 0;i < TMAX;++i)
	{
		m_tutorials[i].Triggered = _triggers[i];
	}
}

void TutorialManager::GetTriggers(bool *_triggers)
{
	for(int i = 0;i < TMAX;++i)
	{
		_triggers[i] = m_tutorials[i].Triggered;
	}
}
	
void TutorialManager::Clear()
{
	for(int i = 0;i < TMAX;++i)
	{
		m_tutorials[i].Triggered = false;
	}
}