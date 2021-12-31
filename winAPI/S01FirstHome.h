#pragma once
#include "Scene.h"
class S01FirstHome :
	public Scene
{
public:
	bool Loading() override;

public:
	void SceneUpdate() override;
	void DebugRender() override;

public:
	bool EventCheck;
	void PreEvent();

	void Letter() override;

public:
	S01FirstHome();
	~S01FirstHome();
};

