#pragma once
#include "Scene.h"
class EndingScene :
	public Scene
{
public:
	void DebugRender() override;

public:
	EndingScene();
	~EndingScene();
};

