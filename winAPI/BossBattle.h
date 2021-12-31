#pragma once
#include "Enemy.h"

class GameRender;
class TransRender;
class AniRender;
class MyMap;

class BossBattle : public Enemy
{

public:
	bool init() override;
	void Update() override;

public:
	bool StandState;
	bool Death;
	bool Attack;
	float StateCount;

public:
	BossBattle();
	~BossBattle();
};