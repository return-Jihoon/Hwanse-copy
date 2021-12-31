#pragma once
#include "Enemy.h"

class GameRender;
class TransRender;
class AniRender;
class MyMap;

class BattleMonkey : public Enemy
{

public:
	bool init() override;
	void Update() override;

public:
	bool StandState;
	bool Death;
	float StateCount;

public:
	BattleMonkey();
	~BattleMonkey();
};

