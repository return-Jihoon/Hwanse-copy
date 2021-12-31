#include "Scene.h"
#include <assert.h>
#include "Actor.h"
#include "RenderMgr.h"
#include "ColliderMgr.h"


Scene::Scene() : m_Loading(false)
{
}


Scene::~Scene()
{
}

void Scene::Progress()
{
	Update();
	this->SceneUpdate();

	Render();
	this->DebugRender();

	Collision();
	ColAfterUpdate();
	Release();
	Actor::ReleaseActor();
}

bool Scene::Loading()
{
	return true;
}

bool Scene::MgrLoading()
{
	SceneMgr::Inst().m_CreateScene = this;
	bool Check = /**this.*/Loading();
	SceneMgr::Inst().m_CreateScene = nullptr;

	if (false == Check)
		assert(false);

	m_Loading = true;
	return Check;
}

void Scene::Update()
{
	Loop = m_ActorList.begin();
	End = m_ActorList.end();

	for (; Loop != End; ++Loop)
	{
		if(false == (*Loop)->IsUpdate())
			continue;

		// 저는 도중에 지우는걸 선호하지 않습니다.
		(*Loop)->Update();
	}
}

void Scene::ColAfterUpdate()
{
	Loop = m_ActorList.begin();
	End = m_ActorList.end();

	for (; Loop != End; ++Loop)
	{
		if (false == (*Loop)->IsUpdate())
			continue;

		// 저는 도중에 지우는걸 선호하지 않습니다.
		(*Loop)->ColAfterUpdate();
	}
}

void Scene::Render()
{
	
	RenderMgr::Inst().Render();
}

void Scene::Collision() 
{
	
	ColliderMgr::Inst().Collision();
}


void Scene::PushActor(Actor* _actor)
{
	if (nullptr == _actor)
	{
		assert(false);
	}

	m_ActorList.push_back(_actor);
}


void Scene::SceneUpdate()
{

}

void Scene::Release()
{
	RenderMgr::Inst().Release();
	ColliderMgr::Inst().Release();

	Loop = m_ActorList.begin();
	End = m_ActorList.end();

	for (; Loop != End;)
	{
		if (false == (*Loop)->IsDeath())
		{
			++Loop;
			continue;
		}
		Loop = m_ActorList.erase(Loop);
	}
}
void Scene::ChangeScene()
{
	RenderMgr::Inst().AllRenderClear();
	ColliderMgr::Inst().AllColClear();
	m_ActorList.clear();
	Actor::ChangeScenePushActor(this);
}

void Scene::DebugRender()
{

}

void Scene::Letter()
{

}
