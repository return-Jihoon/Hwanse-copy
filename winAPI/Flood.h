#pragma once
#include "Actor.h"
class GameRender;
class AniRender;

class Flood :
	public Actor
{
private:
	AniRender* m_Render;

public:
	AniRender* GetRender()
	{
		return m_Render;
	}

public:
	bool init() override;
	void Update() override;

public:
	Flood();
	~Flood();
};