#pragma once
#include "Npc.h"
class GameRender;
class TransRender;

class OldMan :
	public Npc
{
private:
	TransRender* m_Render;

public:
	static bool Running;

	bool init() override;
	void Update() override;

public:
	OldMan();
	~OldMan();
};

