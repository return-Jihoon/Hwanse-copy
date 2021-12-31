#pragma once
#include "Npc.h"

class GameRender;
class TransRender;

class Boss :
	public Npc
{
private:
	TransRender* m_Render;

public:
	static bool Running;

	bool init() override;
	void Update() override;

public:
	Boss();
	~Boss();
};

