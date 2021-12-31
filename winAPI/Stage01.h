#pragma once
#include "Scene.h"
class Stage01 :
	public Scene
{
public:
	bool Loading() override;

public:
	void SceneUpdate() override;
	void DebugRender() override;

public:
	Stage01();
	~Stage01();
};

