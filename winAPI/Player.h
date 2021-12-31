#pragma once
#include "ListPlayer.h"


class GameRender;
class TransRender;
class AniRender;
class Player : public ListPlayer
{
public:
	static Player* MyPlayer;

public:
	bool init() override;
	void Update() override;

public:

public:
	Player();
	~Player();
};

