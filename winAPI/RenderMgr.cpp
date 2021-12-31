#include "RenderMgr.h"
#include <Windows.h>
#include "GameCore.h"
#include "Image.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ColliderMgr.h"


Image* RenderMgr::g_BackBuffer = nullptr;

RenderMgr::RenderMgr()
{
}


RenderMgr::~RenderMgr()
{
	delete g_BackBuffer;
}

void RenderMgr::init()
{
	g_BackBuffer = new Image();
	g_BackBuffer->Create(GameCore::mainWindow().Size());

/*	HFONT myFont = CreateFont(12, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"±¼¸²");
	HFONT oldFont = (HFONT)SelectObject(g_BackBuffer->DC(), myFont);
	SetTextColor(g_BackBuffer->DC(), RGB(255, 255, 255));
	SetBkMode(g_BackBuffer->DC(), TRANSPARENT);*/
}

void RenderMgr::PushRender(GameRender* _render)
{
	std::map<int, std::list<GameRender*>>::iterator RenderGroupIter = m_RenderMap.find(_render->Order());

	if (m_RenderMap.end() == RenderGroupIter)
	{
		m_RenderMap.insert(std::map<int, std::list<GameRender*>>::value_type(_render->Order(), std::list<GameRender*>()));
		RenderGroupIter = m_RenderMap.find(_render->Order());
	}

	RenderGroupIter->second.push_back(_render);
}

void RenderMgr::AllRenderClear()
{
	RenderLoop = m_RenderMap.begin();
	RenderEnd = m_RenderMap.end();

	for (; RenderLoop != RenderEnd; ++RenderLoop)
		RenderLoop->second.clear();
}

void RenderMgr::Release()
{
	RenderLoop = m_RenderMap.begin();
	RenderEnd = m_RenderMap.end();

	for (; RenderLoop != RenderEnd; ++RenderLoop)
	{
		RendererStart = RenderLoop->second.begin();
		RendererEnd = RenderLoop->second.end();

		for (; RendererStart != RendererEnd;)
		{
			if (false == (*RendererStart)->IsDeath())
			{
				++RendererStart;
				continue;
			}

			RendererStart = RenderLoop->second.erase(RendererStart);
		}
	}
}

bool YSortSort(GameRender* _left, GameRender* _right)
{
	if (_left->ActorPos().Y < _right->ActorPos().Y)
	{
		return true;
	}
	return false;
}

void RenderMgr::Render()
{
	Rectangle(RenderMgr::BackDC()
		, 0, 0
		, 1280, 800);

	RenderLoop = m_RenderMap.begin();
	RenderEnd = m_RenderMap.end();

	for (; RenderLoop != RenderEnd; ++RenderLoop)
	{
		RendererStart = RenderLoop->second.begin();
		RendererEnd = RenderLoop->second.end();

		if (m_YSort.end() == m_YSort.find(RenderLoop->first))
		{
			RenderLoop->second.sort(YSortSort);
		}

		for (; RendererStart != RendererEnd; ++RendererStart)
		{
			if (false == (*RendererStart)->IsUpdate())
			{
				continue;
			}
			(*RendererStart)->Render();
		}
	}

	if (nullptr != SceneMgr::Inst().CurScene())
	{
		ColliderMgr::Inst().DebugRender();
		SceneMgr::Inst().CurScene()->DebugRender();
	}

	BitBlt(
		GameCore::mainWindow().DC()
		, 0, 0
		, GameCore::mainWindow().Size().IX(), GameCore::mainWindow().Size().IY()
		, RenderMgr::BackDC()
		, 0, 0
		, SRCCOPY);
}