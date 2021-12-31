#pragma once
#include "Actor.h"

class GameRender;
class TransRender;
class AniRender;

class TitleMap :
	public Actor
{
private:
	TransRender * m_Render;

public:
	bool init() override;
	void Update() override;

public:
	TitleMap();
	~TitleMap();
};

