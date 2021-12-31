#pragma once
#include "BattlePlayer.h"

class GameRender;
class TransRender;
class AniRender;
class MyMap;

class LinsianBattle : public BattlePlayer
{
public:
	static LinsianBattle* BtPlayer2;

public:
	bool init() override;
	void Update() override;

public:

public:
	LinsianBattle();
	~LinsianBattle();
};

