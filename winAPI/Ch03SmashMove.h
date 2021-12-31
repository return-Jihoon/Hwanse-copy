#pragma once
#include "ListPlayer.h"
class GameRender;
class TransRender;
class AniRender;


class SmashMove : public ListPlayer
{
public:
	static SmashMove* MyPlayer3;

public:
	bool init() override;
	void Update() override;

public:
	SmashMove();
	~SmashMove();
};
