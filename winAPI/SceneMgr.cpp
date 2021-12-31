#include "SceneMgr.h"
#include "Scene.h"


SceneMgr::SceneMgr() : m_CurScene(nullptr)
{
}


SceneMgr::~SceneMgr()
{
	std::map<std::wstring, Scene*>::iterator Loop = m_SceneMap.begin();
	std::map<std::wstring, Scene*>::iterator End = m_SceneMap.end();

	for (; Loop != End; ++Loop)
	{
		if (nullptr != Loop->second)
		{
			delete Loop->second;
			Loop->second = nullptr;
		}
	}
}

void SceneMgr::CameraPosSet(Pos _playerPos, Pos _mapPos, int _mapX, int _mapY)
{
	SceneMgr::Inst().CurScene()->CameraPos = (_playerPos - Pos(640 * 0.5f, 352 * 0.5f));

	if (SceneMgr::Inst().CurScene()->CameraPos.X < _mapPos.X)
	{
		SceneMgr::Inst().CurScene()->CameraPos.X = _mapPos.X;
	}
	else if (SceneMgr::Inst().CurScene()->CameraPos.X + 640/*화면 해상도 (640 * 352)*/ > _mapPos.X + _mapX/*맵 크기(원래는 다르다)*/)
	{
		SceneMgr::Inst().CurScene()->CameraPos.X = _mapPos.X + _mapX/*맵 크기*/ - 640/*해상도*/;
	}

	if (SceneMgr::Inst().CurScene()->CameraPos.Y < _mapPos.Y)
	{
		SceneMgr::Inst().CurScene()->CameraPos.Y = _mapPos.Y;
	}
	else if (SceneMgr::Inst().CurScene()->CameraPos.Y + 352 > _mapPos.Y + _mapY)
	{
		SceneMgr::Inst().CurScene()->CameraPos.Y = _mapPos.Y + (_mapY - 352);
	}
}

void SceneMgr::Progress()
{
	if (nullptr != m_NextScene)
	{
		m_CurScene = m_NextScene;

		if (false == m_CurScene->IsLoading())
		{
			m_CurScene->MgrLoading();
		}

		m_CurScene->ChangeScene();

		m_NextScene = nullptr;
	}

	if (nullptr != m_CurScene)
	{
		m_CurScene->Progress();
	}
	else
		assert(false);
}

Scene* SceneMgr::FindScene(const wchar_t* _name)
{
	std::map<std::wstring, Scene*>::iterator FindIter = m_SceneMap.find(_name);

	if (m_SceneMap.end() == FindIter)
		return nullptr;
	return FindIter->second;
}

bool SceneMgr::ChangeScene(const wchar_t* _name)
{
	m_NextScene = FindScene(_name);

	if (nullptr == m_NextScene)
		assert(false);

	return true;
}