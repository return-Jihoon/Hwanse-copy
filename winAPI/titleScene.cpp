#include "titleScene.h"
#include <Windows.h>
#include "GameCore.h"
#include "SceneMgr.h"
#include <bWindow.h>
#include <bPath.h>
#include "Res.h"
#include <bInput.h>
#include "MsgWindow.h"
#include "ColliderMgr.h"
#include "TitleMap.h"
#include <bSound.h>

TitleMap* StageMap1 = nullptr;

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}

bool titleScene::Loading()
{
	bPath::CreatePath(L"Sound");
	bPath::CreatePath(L"Sprite");
	bPath::CreatePath(L"character", L"Sprite\\character");
	bPath::CreatePath(L"map", L"Sprite\\map");
	bPath::CreatePath(L"object", L"Sprite\\object");
	bPath::CreatePath(L"enemy", L"Sprite\\enemy");
	bPath::CreatePath(L"npc", L"Sprite\\npc");

#pragma	region MOVING

	Res::ImageLoad((bPath::FindPathToDir(L"character").FullPathString() + L"\\" + L"Ataho_walk.bmp").c_str());
	Res::SpriteCreate(L"Ataho_walk.bmp", 5, 5);

	Res::ImageLoad((bPath::FindPathToDir(L"character").FullPathString() + L"\\" + L"Linsian_walk.bmp").c_str());
	Res::SpriteCreate(L"Linsian_walk.bmp", 5, 5);

	Res::ImageLoad((bPath::FindPathToDir(L"character").FullPathString() + L"\\" + L"Smash_walk.bmp").c_str());
	Res::SpriteCreate(L"Smash_walk.bmp", 5, 5);


	Res::ImageLoad((bPath::FindPathToDir(L"character").FullPathString() + L"\\" + L"Ataho.bmp").c_str());
	Res::SpriteCreate(L"Ataho.bmp", 5, 10);

	Res::ImageLoad((bPath::FindPathToDir(L"character").FullPathString() + L"\\" + L"AtahoSkill.bmp").c_str());
	Res::SpriteCreate(L"AtahoSkill.bmp", 5, 4);

	Res::ImageLoad((bPath::FindPathToDir(L"character").FullPathString() + L"\\" + L"Linsian.bmp").c_str());
	Res::SpriteCreate(L"Linsian.bmp", 5, 12);

	Res::ImageLoad((bPath::FindPathToDir(L"character").FullPathString() + L"\\" + L"Smash.bmp").c_str());
	Res::SpriteCreate(L"Smash.bmp", 5, 10);

#pragma	endregion

#pragma	region MAP_OBJ

	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"Title.bmp").c_str());
	Res::SpriteCreate(L"Title.bmp", 1, 1);



	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"Home1.bmp").c_str());
	Res::SpriteCreate(L"Home1.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"Home1_1.bmp").c_str());
	Res::SpriteCreate(L"Home1_1.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"Home1_mask.bmp").c_str());
	Res::SpriteCreate(L"Home1_mask.bmp", 1, 1);



	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"MountainRoad.bmp").c_str());
	Res::SpriteCreate(L"MountainRoad.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"MountainRoad_mask.bmp").c_str());
	Res::SpriteCreate(L"MountainRoad_mask.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"MountainRoad_1.bmp").c_str());
	Res::SpriteCreate(L"MountainRoad_1.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"MountainRoad_Rock.bmp").c_str());
	Res::SpriteCreate(L"MountainRoad_Rock.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"Flood.bmp").c_str());
	Res::SpriteCreate(L"Flood.bmp", 3, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"enemy").FullPathString() + L"\\" + L"Monkey.bmp").c_str());
	Res::SpriteCreate(L"Monkey.bmp", 5, 3);

	Res::ImageLoad((bPath::FindPathToDir(L"npc").FullPathString() + L"\\" + L"npcs.bmp").c_str());
	Res::SpriteCreate(L"npcs.bmp", 2, 1);



	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"Town.bmp").c_str());
	Res::SpriteCreate(L"Town.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"Town_mask.bmp").c_str());
	Res::SpriteCreate(L"Town_mask.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"Town_1.bmp").c_str());
	Res::SpriteCreate(L"Town_1.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"enemy").FullPathString() + L"\\" + L"Boss.bmp").c_str());
	Res::SpriteCreate(L"Boss.bmp", 5, 3);




	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"BattleMt.bmp").c_str());
	Res::SpriteCreate(L"BattleMt.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"map").FullPathString() + L"\\" + L"BattleTown.bmp").c_str());
	Res::SpriteCreate(L"BattleTown.bmp", 1, 1);

#pragma	endregion

#pragma	region UI


	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"Frame.bmp").c_str());
	Res::SpriteCreate(L"Frame.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"MsgV.bmp").c_str());
	Res::SpriteCreate(L"MsgV.bmp", 3, 20);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"Faces.bmp").c_str());
	Res::SpriteCreate(L"Faces.bmp", 4, 1);



	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"GameMenu.bmp").c_str());
	Res::SpriteCreate(L"GameMenu.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"AtahoMenu.bmp").c_str());
	Res::SpriteCreate(L"AtahoMenu.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"LinsianMenu.bmp").c_str());
	Res::SpriteCreate(L"LinsianMenu.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SmashMenu.bmp").c_str());
	Res::SpriteCreate(L"SmashMenu.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"Arrow.bmp").c_str());
	Res::SpriteCreate(L"Arrow.bmp", 4, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"StatusBarSub.bmp").c_str());
	Res::SpriteCreate(L"StatusBarSub.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"StatusBar.bmp").c_str());
	Res::SpriteCreate(L"StatusBar.bmp", 1, 1);



	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuMask.bmp").c_str());
	Res::SpriteCreate(L"SubMenuMask.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuOther.bmp").c_str());
	Res::SpriteCreate(L"SubMenuOther.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenu.bmp").c_str());
	Res::SpriteCreate(L"SubMenu.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuAtaho0.bmp").c_str());
	Res::SpriteCreate(L"SubMenuAtaho0.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuAtaho1.bmp").c_str());
	Res::SpriteCreate(L"SubMenuAtaho1.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuAtaho2.bmp").c_str());
	Res::SpriteCreate(L"SubMenuAtaho2.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuLinsian0.bmp").c_str());
	Res::SpriteCreate(L"SubMenuLinsian0.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuLinsian1.bmp").c_str());
	Res::SpriteCreate(L"SubMenuLinsian1.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuLinsian2.bmp").c_str());
	Res::SpriteCreate(L"SubMenuLinsian2.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuSmash0.bmp").c_str());
	Res::SpriteCreate(L"SubMenuSmash0.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuSmash1.bmp").c_str());
	Res::SpriteCreate(L"SubMenuSmash1.bmp", 1, 1);

	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"SubMenuSmash2.bmp").c_str());
	Res::SpriteCreate(L"SubMenuSmash2.bmp", 1, 1);




	Res::ImageLoad((bPath::FindPathToDir(L"object").FullPathString() + L"\\" + L"BattleMenuMain.bmp").c_str());
	Res::SpriteCreate(L"BattleMenuMain.bmp", 1, 1);

#pragma	endregion

#pragma	region BGM

	bSound::SoundLoad((bPath::FindPathToDir(L"Sound").FullPathString() + L"\\" + L"Home.mid").c_str());

	bSound::SoundLoad((bPath::FindPathToDir(L"Sound").FullPathString() + L"\\" + L"RoadMt.mid").c_str());

	bSound::SoundLoad((bPath::FindPathToDir(L"Sound").FullPathString() + L"\\" + L"TitleS.mid").c_str());

	bSound::SoundLoad((bPath::FindPathToDir(L"Sound").FullPathString() + L"\\" + L"Battle.mid").c_str());

	bSound::SoundLoad((bPath::FindPathToDir(L"Sound").FullPathString() + L"\\" + L"BossBattle.mid").c_str());

	bSound::SoundLoad((bPath::FindPathToDir(L"Sound").FullPathString() + L"\\" + L"Inn.mid").c_str());

	bSound::SoundLoad((bPath::FindPathToDir(L"Sound").FullPathString() + L"\\" + L"LevelUp.mid").c_str());

	bSound::SoundLoad((bPath::FindPathToDir(L"Sound").FullPathString() + L"\\" + L"BattleEnd.mid").c_str());

#pragma	endregion

	Input::CreateKey(L"UP", 'W');
	Input::CreateKey(L"DOWN", 'S');
	Input::CreateKey(L"LEFT", 'A');
	Input::CreateKey(L"RIGHT", 'D');
	Input::CreateKey(L"LKEY", 'L');
	Input::CreateKey(L"KKEY", 'K');
	Input::CreateKey(L"DEBUG", VK_SPACE);
	Input::CreateKey(L"MLB", VK_LBUTTON);
	Input::CreateKey(L"MENU", VK_ESCAPE);
	Input::CreateKey(L"ENTER", VK_RETURN);
	Input::CreateKey(L"ARROW_UP", VK_UP);
	Input::CreateKey(L"ARROW_DOWN", VK_DOWN);
	Input::CreateKey(L"ARROW_LEFT", VK_LEFT);
	Input::CreateKey(L"ARROW_RIGHT", VK_RIGHT);
	Input::CreateKey(L"+KEY", VK_OEM_PLUS);
	Input::CreateKey(L"-KEY", VK_OEM_MINUS);

	TitleBgmPlay = bSound::SoundPlayNoneReturn();
	TitleBgmPlay->Play(L"TitleS.mid", 0);

	//ColliderMgr::Inst().Link(L"pBullet", L"Monster");

	MsgWindow::MsgWin = Actor::CreateActor<MsgWindow>(L"MsgWin");
	MsgWindow::MsgWin->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown");
	MsgWindow::MsgWin->Off();

	return true;
}

void titleScene::SceneUpdate()
{
	StageMap1 = Actor::CreateActor<TitleMap>(L"Title");
	StageMap1->OverScene(L"titleScene");

	if (0 != GetAsyncKeyState(VK_RETURN))
	{
		TitleBgmPlay->Stop();
		SceneMgr::Inst().ChangeScene(L"Stage01");
	}
}

void titleScene::DebugRender()
{
	/*std::wstring Name = L"titleScene";
	TextOut(GameCore::mainWindow().DC(), 
		100, 100, 
		Name.c_str(), 
		(int)Name.size());

	TextOut(GameCore::mainWindow().DC(), 
		100, 80,
		bPath::FindPathToString(L"character").c_str(),
		(int)bPath::FindPathToString(L"character").size());*/
}
