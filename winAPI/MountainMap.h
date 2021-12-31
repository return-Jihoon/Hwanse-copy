#pragma once
#include "Actor.h"

class GameRender;
class TransRender;
class AniRender;

class MountainMap :
	public Actor
{
public:
	TransRender* m_Render;
	TransRender* m_Render_obj1;

public:
	bool init() override;
	void Update() override;

public:
	MountainMap();
	~MountainMap();
};

