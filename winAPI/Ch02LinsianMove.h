#pragma once
#include "ListPlayer.h"
class GameRender;
class TransRender;
class AniRender;


class LinsianMove : public ListPlayer
{
public:
	static LinsianMove* MyPlayer2;

public:
	bool init() override;
	void Update() override;

public:
	LinsianMove();
	~LinsianMove();
};
