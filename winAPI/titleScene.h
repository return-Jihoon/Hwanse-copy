#pragma once
#include "Scene.h"

class bSoundPlayer;

class titleScene :
	public Scene
{
public:
	bSoundPlayer* TitleBgmPlay;

public:
	void SceneUpdate() override;
	bool Loading() override;
	void DebugRender() override;
public:
	titleScene();
	~titleScene();
};

