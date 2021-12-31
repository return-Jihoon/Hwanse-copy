#pragma once
#include "Actor.h"
class GameRender;
class TransRender;

class BattleMenu :
	public Actor
{
public:
	static BattleMenu* BtMenu;

	TransRender* m_Mask;

private:
	TransRender* m_MenuMain;
	TransRender* m_MenuSub;

	TransRender* m_Arrow;
	TransRender* m_ArrowSub;
	TransRender* m_ArrowSubSub;
	
public:
	static bool Runaway;
	static int CharIndex;
	int MenuIndex;
	int SubIndex;
	int SubSubIndex;
	int EnemyIndex;
	static bool CurMap;

public:
	bool init() override;
	void Update() override;

public:
	BattleMenu();
	~BattleMenu();
};

