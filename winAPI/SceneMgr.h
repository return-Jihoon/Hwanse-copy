#pragma once
#include <map>
#include <assert.h>
#include <string>

class Scene;
class GameCore;
class Pos;

class SceneMgr
{
public:
	friend GameCore;
	friend Scene;

public:
	static SceneMgr& Inst()
	{
		static SceneMgr SingleObj;
		return SingleObj;
	}

	static void CameraPosSet(Pos _playerPos, Pos _mapPos, int _mapX, int _mapY);

	std::map<std::wstring, Scene*> m_SceneMap;

	Scene* m_CurScene;
	Scene* m_NextScene;

	Scene* m_CreateScene;

private:
	void Progress();

public:
	Scene * CurScene()
	{
		return m_CurScene;
	}

	Scene* FindScene(const wchar_t* _name);

	template <typename T>
	bool CreateScene(const wchar_t* _name, bool _isLoading = true)
	{
		Scene* pFindScene = FindScene(_name);

		if (nullptr != pFindScene)
		{
			assert(false);
		}

		Scene* pNewScene = new T();
		pNewScene->Name(_name);

		if (true == _isLoading)
		{
			pNewScene->MgrLoading();
		}

		m_SceneMap.insert(std::map<std::wstring, Scene*>::value_type(_name, pNewScene));
		return pFindScene;
	}
	bool ChangeScene(const wchar_t* _name);

public:
	SceneMgr();
	~SceneMgr();
};

