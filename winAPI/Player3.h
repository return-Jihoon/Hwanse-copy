#pragma once
#include "ListPlayer.h"
class GameRender;
class TransRender;
class AniRender;


class Player3 : public ListPlayer
{
public:
	static Player3* MyPlayer3;

public:
	bool init() override;
	void Update() override;

public:
	Player3();
	~Player3();
};
