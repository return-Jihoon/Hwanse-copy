#pragma once
#include "Scene.h"
class S02MountainRoad :
	public Scene
{
public:
	bool Loading() override;

public:
	void SceneUpdate() override;
	void DebugRender() override;

public:
	bool MonkeyEvent;
	int MtConversation;
	void PreEvent();

	void Letter() override;

public:
	S02MountainRoad();
	~S02MountainRoad();
};

