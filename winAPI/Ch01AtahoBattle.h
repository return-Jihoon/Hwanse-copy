#pragma once
#include "BattlePlayer.h"


class GameRender;
class TransRender;
class AniRender;
class MyMap;

class AtahoBattle : public BattlePlayer
{
public:
	static AtahoBattle* BtPlayer1;

public:
	bool init() override;
	void Update() override;

public:

public:
	AtahoBattle();
	~AtahoBattle();
};

