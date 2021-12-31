#pragma once
#include "Actor.h"

class GameRender;
class TransRender;

class BtMtMap :
	public Actor
{
private:
	TransRender* m_Render;

public:
	bool init() override;
	void Update() override;

public:
	BtMtMap();
	~BtMtMap();
};

