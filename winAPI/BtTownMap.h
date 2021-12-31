#pragma once
#include "Actor.h"
class GameRender;
class TransRender;

class BtTownMap :
	public Actor
{
private:
	TransRender* m_Render;

public:
	bool init() override;
	void Update() override;

public:
	BtTownMap();
	~BtTownMap();
};

