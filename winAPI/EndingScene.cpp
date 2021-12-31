#include "EndingScene.h"
#include "GameCore.h"


EndingScene::EndingScene()
{
}


EndingScene::~EndingScene()
{
}

void EndingScene::DebugRender()
{
	std::wstring Name = L"EndingScene";
	TextOut(GameCore::mainWindow().DC(), 100, 100, Name.c_str(), (int)Name.size());
}