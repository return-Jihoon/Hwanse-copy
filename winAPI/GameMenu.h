#pragma once
#include "Actor.h"
#include <string>

class GameRender;
class TransRender;
class AniRender;

class GameMenu :
	public Actor
{
public:
	static GameMenu* GaMenu;
	static void Menu();

	TransRender* m_Mask;

private:
	TransRender* m_Render;
	TransRender* m_RenderChar;
	TransRender* m_RenderSub;

	TransRender* m_Arrow;
	TransRender* m_ArrowSub;

	

	bool SubMenuIn;

public:
	int ChIndex;
	int StIndex;
	int SbIndex;

public:
	bool init() override;
	void Update() override;

public:
	GameMenu() : ChIndex(0), StIndex(0), SbIndex(0), SubMenuIn(false){}
	~GameMenu() {}
};