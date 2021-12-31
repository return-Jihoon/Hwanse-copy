#pragma once
#include "Scene.h"
class S11BattleSceneTown :
	public Scene
{
public:
	bool Loading() override;

public:
	void SceneUpdate() override;
	void DebugRender() override;

	void Letter() override;

	void BattlePhase();
	void BossAttack();

private:
	bool BattleOn;
	float EvCounter;
	float BsCounter;

public:
	S11BattleSceneTown();
	~S11BattleSceneTown();
};

