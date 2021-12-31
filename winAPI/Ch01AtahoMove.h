#pragma once
#include "ListPlayer.h"


class GameRender;
class TransRender;
class AniRender;
class MyMap;

class AtahoMove : public ListPlayer
{
public:
	static AtahoMove* MyPlayer1;

public:
	bool init() override;
	void Update() override;

public:

public:
	AtahoMove();
	~AtahoMove();
};

