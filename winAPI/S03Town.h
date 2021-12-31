#pragma once
#include "Scene.h"
class S03Town :
	public Scene
{
public:
	bool Loading() override;

public:
	int TwConversation;
	void SceneUpdate() override;
	void DebugRender() override;

	void Letter() override;

public:
	S03Town();
	~S03Town();
};

