#pragma once
#include "baseObj.h"
#include <bGeo.h>
#include <list>

class Actor;
class SceneMgr;
class RenderMgr;

class Scene : public baseObj
{
public: 
	friend RenderMgr;
	friend SceneMgr;
	friend Actor;

private:
	bool m_Loading;

public:
	bool IsLoading()
	{
		return m_Loading;
	}
private:
	void Progress();

private:
	virtual void SceneUpdate();

public:
	void Update();
	void Render();
	void Collision();
	void ColAfterUpdate();
	void Release();

	virtual void Letter();

public:
	bool MgrLoading();

private:
	virtual bool Loading();

protected:
	std::list<Actor*>::iterator Loop;
	std::list<Actor*>::iterator End;
	std::list<Actor*> m_ActorList;

public:
	Pos CameraPos;

private:
	void PushActor(Actor* _actor);

private:
	void ChangeScene();

	virtual void DebugRender();

public:
	Scene();
	virtual ~Scene() = 0;
};

