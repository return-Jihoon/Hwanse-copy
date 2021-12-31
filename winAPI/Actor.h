#pragma once
#include <bGeo.h>
#include "baseObj.h"
#include <list>
#include <map>
#include <set>

#include "SceneMgr.h"
#include "Scene.h"
#include "GameRender.h"
#include "Collider.h"
#include "TransRender.h"

class Actor : public baseObj
{


private:
	class Destructor
	{
	public:
		~Destructor()
		{
			Actor::ActorEnd();
		}
	};
	static Destructor Des;
	friend Destructor;

private:
	static std::list<Actor*>::iterator Loop;
	static std::list<Actor*>::iterator End;
	static std::list<Actor*> m_AllActorList;
	static std::map<std::wstring, Actor*> m_FindActor;

public:
	static void ReleaseActor();
	static void ChangeScenePushActor(Scene* _scene);
	static void ActorEnd();

public:
	template <typename T>
	static T* CreateActor(const wchar_t* _name = L"", bool _isFind = false)
	{
		T* NewActor = new T();
		NewActor->Name(_name);

		m_AllActorList.push_back(NewActor);

		if (nullptr != SceneMgr::Inst().m_CreateScene)
		{
			NewActor->m_SceneSet.insert(SceneMgr::Inst().m_CreateScene->Name());
			SceneMgr::Inst().m_CreateScene->PushActor(NewActor);
		}
		else if (nullptr != SceneMgr::Inst().m_CurScene)
		{
			NewActor->m_SceneSet.insert(SceneMgr::Inst().m_CurScene->Name());
			SceneMgr::Inst().m_CurScene->PushActor(NewActor);
		}

		if (true == _isFind)
		{
			m_FindActor.insert(std::map<std::wstring, Actor*>::value_type(_name, NewActor));
		}

		NewActor->init();

		return NewActor;
	}

public:
	friend Scene;

private:
	std::set<std::wstring> m_SceneSet;

	bool IsScene(Scene* _scene)
	{
		if (nullptr == _scene)
		{
			assert(false);
		}
		return IsScene(_scene->Name());
	}
	bool IsScene(const std::wstring& _name)
	{
		return IsScene(_name.c_str());
	}
	bool IsScene(const wchar_t* _name)
	{
		return m_SceneSet.end() != m_SceneSet.find(_name);
	}

public:
	template<typename ...Rest>
	void OverScene(const wchar_t* _name, Rest ..._arg)
	{
		int a = sizeof ...(_arg);

		if (false == IsScene(_name))
			m_SceneSet.insert(_name);

		OverScene(_arg...);
	}

	void OverScene()
	{
		int a = 0;
	}


protected:
	Pos m_Pos;
	//pSize m_Size;

public:
	/*void size(pSize _size)
	{
		m_Size = _size;
	}

	Pos size()
	{
		return m_Size;
	}*/

	void pos(Pos _pos)
	{
		m_Pos = _pos;
	}

	Pos pos()
	{
		return m_Pos;
	}

	void Move(const Pos& _pos)
	{
		m_Pos += _pos;
	}

private:
	virtual bool init();

private:
	virtual void Update();
	virtual void ColAfterUpdate();
//	virtual void Render();

private:
	std::list<GameRender*>::iterator RenderStart;
	std::list<GameRender*>::iterator RenderEnd;
	std::list<GameRender*> m_RenderList;

private:
	void AllRenderRePush();

public:
	template<typename T>
	T* CreateRender(int _order = 0)
	{
		T* NewRender = new T();
		NewRender->Init(_order, this);
		m_RenderList.push_back(NewRender);
		return NewRender;
	}

private:
	std::list<Collider*>::iterator ColStart;
	std::list<Collider*>::iterator ColEnd;
	std::list<Collider*> m_ColList;


public:
	template<typename T>
	T* CreateCol(const wchar_t* _groupName = L"Default", pSize _size = { 10, 10 })
	{
		T* NewCol = new T();
		NewCol->Init(_groupName, this, _size);
		m_ColList.push_back(NewCol);
		return NewCol;
	}

private:
	void AllColRePush();

public:
	virtual void ColEnter(Collider* _this, Collider* _other) {}
	virtual void ColStay(Collider* _this, Collider* _other) {}
	virtual void ColExit(Collider* _this, Collider* _other) {}

public:
	TransRender* m_MainRender;

protected:
	Actor();
	virtual ~Actor()/* = 0*/;
};

