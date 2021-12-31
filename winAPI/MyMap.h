#pragma once
#include "Actor.h"
//#include "TransRender.h"

class TransRender;
class GameRender;
class AniRender;

class MyMap :
	public Actor
{
public:
	TransRender* m_Render; 
	TransRender* m_Render_obj1;

public:
	bool init() override;
	void Update() override;

public:
	MyMap();
	~MyMap();
};

