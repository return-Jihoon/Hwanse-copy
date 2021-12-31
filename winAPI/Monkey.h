#pragma once
#include "Npc.h"

class GameRender;
class AniRender;

class Monkey :
	public Npc
{
private:
	AniRender* m_Render;

public:
	static bool Running;

	bool init() override;
	void Update() override;

public:
	Monkey();
	~Monkey();
};

