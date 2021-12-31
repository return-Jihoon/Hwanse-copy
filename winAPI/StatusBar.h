#pragma once
#include "Actor.h"

class GameRender;
class TransRender;
class AniRender;

class StatusBar :
	public Actor
{
public:
	TransRender* m_Render;
	TransRender* m_SubRender;

public:

	static StatusBar* SBar[3][3];
	static StatusBar* EBar[5];

	bool init() override;
	void Update() override;

public:
	StatusBar();
	~StatusBar();
};

