#pragma once
#include "ListPlayer.h"
class GameRender;
class TransRender;
class AniRender;


class Player2 : public ListPlayer
{
public:
	static Player2* MyPlayer2;

public:
	bool init() override;
	void Update() override;

public:
	Player2();
	~Player2();
};
