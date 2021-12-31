#pragma once
#include "GameRender.h"
#include "Image.h"
#include <map>
#include <set>
#include <list>

class GameCore;

class RenderMgr
{
public:
	friend GameCore;

private:
	static Image* g_BackBuffer;

public:
	static HDC BackDC()
	{
		return g_BackBuffer->DC();
	}

public:
	static RenderMgr& Inst()
	{
		static RenderMgr Inst;
		return Inst;
	}

private:
	std::map<int, std::list<GameRender*>>::iterator RenderLoop;
	std::map<int, std::list<GameRender*>>::iterator RenderEnd;

	std::list<GameRender*>::iterator RendererStart;
	std::list<GameRender*>::iterator RendererEnd;

	std::map<int, std::list<GameRender*>> m_RenderMap;
	std::set<int> m_YSort;

public:
	void YSortOn(int _select)
	{
		if (m_YSort.end() == m_YSort.find(_select))
		{
			return;
		}
		m_YSort.insert(_select);
	}

private:
	void init();

private:
	friend class Scene;

private:
	void AllRenderClear();

public:
	void PushRender(GameRender* _render);

public:
	void Render();
	void Release();

public:
	RenderMgr();
	~RenderMgr();
};

