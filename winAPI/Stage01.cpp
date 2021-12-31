#include "stdafx.h"
#include "Stage01.h"
#include "Player.h"
#include "GameCore.h"
#include <Windows.h>


Stage01::Stage01()
{
}


Stage01::~Stage01()
{
}

bool Stage01::Loading()
{
	Player* NewPlayer = Actor::CreateActor<Player>(L"Player", true);

	NewPlayer->OverScene(L"Stage01", L"Stage02", L"EndingScene");

	NewPlayer->pos({ 200.0f, 200.0f });
	NewPlayer->size({ 100.0f, 100.0f });

	return true;
}

void Stage01::SceneUpdate()
{
	if (0 != GetAsyncKeyState('O'))
	{
		SceneMgr::Inst().ChangeScene(L"Stage02");
	}
}

void Stage01::DebugRender()
{
	std::wstring Name = L"Stage01";
	TextOut(GameCore::mainWindow().DC(), 100, 100, Name.c_str(), (int)Name.size());
}