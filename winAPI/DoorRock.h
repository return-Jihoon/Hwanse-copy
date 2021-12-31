#pragma once
#include "Actor.h"
class GameRender;
class TransRender;

class DoorRock :
	public Actor
{
private:
	TransRender* m_Render;

public:
	TransRender* GetRender()
	{
		return m_Render;
	}

public:
	bool init() override;
	void Update() override;

public:
	DoorRock();
	~DoorRock();
};
