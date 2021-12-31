#pragma once
#include "BattlePlayer.h"

class GameRender;
class TransRender;
class AniRender;
class MyMap;

class SmashBattle : public BattlePlayer
{
public:
	static SmashBattle* BtPlayer3;

public:
	bool init() override;
	void Update() override;

public:

public:
	SmashBattle();
	~SmashBattle();
};
