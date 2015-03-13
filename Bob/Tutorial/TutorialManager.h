#pragma once

#include "Singleton.h"
#include "HPTGraphics.h"
#include "Game.h"
#include "vector"
#include <string>
#include "Input_Button.h"

struct Tutorial
{
	Tutorial(int _text) : Trigger(false), Triggered(false), Text(_text) {}
	bool Trigger;
	bool Triggered;
	int Text;
};

class TutorialManager : public CR::Utility::Singleton<TutorialManager>, public Input_Controller
{
	friend class CR::Utility::Singleton<TutorialManager>;
public:
	enum Tutorials
	{
		TBASIC,
		TLADDERS,
		TATTACK,
		TCROUCH,
		TEXPLORE,
		TGRENADES,
		TWEAPON,
		TWEAPON2,
		TDOOR,
		TDOOR2,
		TMAX
	};
	void CheckForTutorial(Game *_game);
	void Cleanup();
	void Tick();
	void Trigger(Tutorials _tutorial);
	void InputChanged() {}
	void SetTriggers(bool *_triggers);
	void GetTriggers(bool *_triggers);
	void Clear();
private:
	TutorialManager();
	TutorialManager(const TutorialManager &) {}
	~TutorialManager() {}
	void Finished();

	HPTSprite1 *m_baseAnim;
	HPTSprite1 *m_textSprite;
	std::vector<Tutorial> m_tutorials;
	Tutorials m_currentTutorial;
	Input_Button *m_button;
	Game *m_game;
};