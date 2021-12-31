#pragma once
#include "Actor.h"

class GameRender;
class AniRender;
class TransRender;

class Monster :
	public Actor
{
private:
	TransRender* m_Render;
	AniRender* m_AniRender;

public:
	bool init() override;
	void Update() override;


public:
	Monster();
	~Monster();
};

