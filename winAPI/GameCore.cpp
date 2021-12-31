#include "GameCore.h"
#include <bTime.h>
#include <bInput.h>
#include <bSound.h>
#include <bGeo.h>
#include "titleScene.h"
#include "SceneMgr.h"
#include "S01FirstHome.h"
#include "S02MountainRoad.h"
#include "S03Town.h"
#include "S10BattleSceneMt.h"
#include "S11BattleSceneTown.h"
#include "EndingScene.h"
#include <bPath.h>
#include "RenderMgr.h"


bWindow* GameCore::g_MainWindow = nullptr;

GameCore::GameCore()
{
}


GameCore::~GameCore()
{
}


void GameCore::Start()
{
	bSound::Init();

	bDirect Dic = bPath::RootDir();
	/*Dic.MoveParent();
	Dic.Move(L"BIN");*/
	bPath::SetRootDir(Dic);
	g_MainWindow = bWindow::bCreateWindow(L"MainWindow");
	g_MainWindow->Size(640, 480);

	SceneMgr::Inst().CreateScene<titleScene>(L"titleScene");
	SceneMgr::Inst().CreateScene<S01FirstHome>(L"Stage01");
	SceneMgr::Inst().CreateScene<S02MountainRoad>(L"Stage02");
	SceneMgr::Inst().CreateScene<S03Town>(L"Stage03");
	SceneMgr::Inst().CreateScene<S10BattleSceneMt>(L"BattleMt");
	SceneMgr::Inst().CreateScene<S11BattleSceneTown>(L"BattleTown");
	SceneMgr::Inst().CreateScene<EndingScene>(L"EndingScene");


	SceneMgr::Inst().ChangeScene(L"titleScene");
}


bWindow& GameCore::mainWindow()
{
	return (*g_MainWindow);
}

void GameCore::Run()
{
	bTime::Update();
	Input::Update();
	bWindow::AllWindowUpdate();

	bSound::Update();

	SceneMgr::Inst().Progress();
}



MSG GameCore::Loop()
{
	bTime::Reset();
	RenderMgr::Inst().init();
	MSG msg;
	while (0 != bWindow::WinCount())
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Run();
		}
	}

	bSound::End();

	return msg;
}
void GameCore::End()
{

}