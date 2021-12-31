#pragma once
#include "Actor.h"
#include <list>
#include <vector>

class AniRender;

class StatusEnemy
{
public:
	bool isDown;
	int Level;
	int Max_Hp;
	int Cur_Hp;
	int Att;

public:
	StatusEnemy() : isDown(false), Level(1), Max_Hp(50), Cur_Hp(50), Att(10) {}
	~StatusEnemy() {}
};

static StatusEnemy BattleEnemyStatus[5];

class Enemy :
	public Actor
{
public:

	AniRender* m_AniRender;

public:
	static int Skills[3];
	static bool PowerUp;
	static bool SkillOn;
	static int EnTarget[4];

public:
	Enemy();
	~Enemy();
};