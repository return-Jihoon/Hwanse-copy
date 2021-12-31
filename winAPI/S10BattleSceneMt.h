#pragma once
#include "Scene.h"
class S10BattleSceneMt :
	public Scene
{
public:
	bool Loading() override;

public:
	void SceneUpdate() override;
	void DebugRender() override;
	void BattlePhase();

	void Letter() override;

private:
	bool BattleOn;
	float EvCounter;
public:
	S10BattleSceneMt();
	~S10BattleSceneMt();
};

