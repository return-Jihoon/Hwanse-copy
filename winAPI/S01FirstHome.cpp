#include "S01FirstHome.h"
#include "Ch01AtahoMove.h"
#include "Ch02LinsianMove.h"
#include "Ch03SmashMove.h"
#include "BattlePlayer.h"
#include "GameMenu.h"
#include "Monster.h"
#include "GameCore.h"
#include <Windows.h>
#include "MyMap.h"
#include "Frame.h"
#include "MsgWindow.h"
#include "RenderMgr.h"
#include "StatusBar.h"
#include <bInput.h>
#include <bSound.h>
#include <Windows.h>


enum RENDERNUM
{
	OBJECT = 0,
	UI = 10000,
};

MyMap* StageMap1 = nullptr;
Frame* StageFrame = nullptr;
bSoundPlayer* HomeBgmPlay1 = nullptr;

S01FirstHome::S01FirstHome() : EventCheck(false)
{
}


S01FirstHome::~S01FirstHome()
{
}

bool S01FirstHome::Loading()
{
	RenderMgr::Inst().YSortOn(OBJECT);

	StageMap1 = Actor::CreateActor<MyMap>(L"Map");

	AtahoMove::MyPlayer1 = Actor::CreateActor<AtahoMove>(L"Player", true);
	AtahoMove::MyPlayer1->OverScene(L"Stage01", L"Stage02", L"Stage03", L"EndingScene");
	AtahoMove::MyPlayer1->pos({ 320.0f, 200.02f });

	AtahoMove::MyPlayer1->CurMap = StageMap1;

	LinsianMove::MyPlayer2 = Actor::CreateActor<LinsianMove>(L"Player2", true);
	LinsianMove::MyPlayer2->OverScene(L"Stage01", L"Stage02", L"Stage03", L"EndingScene");
	LinsianMove::MyPlayer2->pos({ 320.0f, 200.01f });

	SmashMove::MyPlayer3 = Actor::CreateActor<SmashMove>(L"Player3", true);
	SmashMove::MyPlayer3->OverScene(L"Stage01", L"Stage02", L"Stage03", L"EndingScene");
	SmashMove::MyPlayer3->pos({ 320.0f, 200.0f });

	AtahoMove::MyPlayer1->SetBack(LinsianMove::MyPlayer2);
	LinsianMove::MyPlayer2->SetBack(SmashMove::MyPlayer3);

	LinsianMove::MyPlayer2->SetFront(AtahoMove::MyPlayer1);
	SmashMove::MyPlayer3->SetFront(LinsianMove::MyPlayer2);


	StageFrame = Actor::CreateActor<Frame>(L"Frame");
	StageFrame->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");

	StageMap1->m_MainRender->SetAlpha(255);

	GameMenu::GaMenu = Actor::CreateActor<GameMenu>(L"GameMenu");
	GameMenu::GaMenu->OverScene(L"Stage01", L"Stage02", L"Stage03");
	GameMenu::GaMenu->Off();

#pragma	region SBar
	StatusBar::SBar[0][0] = Actor::CreateActor<StatusBar>(L"StatusBar11");
	StatusBar::SBar[0][0]->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");
	StatusBar::SBar[0][0]->pos({ 128.0f, 392.0f });
	StatusBar::SBar[0][1] = Actor::CreateActor<StatusBar>(L"StatusBar12");
	StatusBar::SBar[0][1]->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");
	StatusBar::SBar[0][1]->pos({ 128.0f + 96.0f, 392.0f });
	StatusBar::SBar[0][2] = Actor::CreateActor<StatusBar>(L"StatusBar13");
	StatusBar::SBar[0][2]->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");
	StatusBar::SBar[0][2]->pos({ 128.0f + 192.0f, 392.0f });
	StatusBar::SBar[1][0] = Actor::CreateActor<StatusBar>(L"StatusBar21");
	StatusBar::SBar[1][0]->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");
	StatusBar::SBar[1][0]->pos({ 128.0f, 392.0f + 32.0f});
	StatusBar::SBar[1][1] = Actor::CreateActor<StatusBar>(L"StatusBar22");
	StatusBar::SBar[1][1]->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");
	StatusBar::SBar[1][1]->pos({ 128.0f + 96.0f, 392.0f + 32.0f });
	StatusBar::SBar[1][2] = Actor::CreateActor<StatusBar>(L"StatusBar23");
	StatusBar::SBar[1][2]->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");
	StatusBar::SBar[1][2]->pos({ 128.0f + 192.0f, 392.0f + 32.0f });
	StatusBar::SBar[2][0] = Actor::CreateActor<StatusBar>(L"StatusBar31");
	StatusBar::SBar[2][0]->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");
	StatusBar::SBar[2][0]->pos({ 128.0f, 392.0f + 64.0f });
	StatusBar::SBar[2][1] = Actor::CreateActor<StatusBar>(L"StatusBar32");
	StatusBar::SBar[2][1]->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");
	StatusBar::SBar[2][1]->pos({ 128.0f + 96.0f, 392.0f + 64.0f });
	StatusBar::SBar[2][2] = Actor::CreateActor<StatusBar>(L"StatusBar33");
	StatusBar::SBar[2][2]->OverScene(L"Stage01", L"Stage02", L"Stage03", L"BattleMt", L"BattleTown", L"EndingScene");
	StatusBar::SBar[2][2]->pos({ 128.0f + 192.0f, 392.0f + 64.0f });
#pragma endregion
	return true;
}

void S01FirstHome::SceneUpdate()
{

	AtahoMove::MyPlayer1->CurMap = StageMap1;

	SceneMgr::CameraPosSet(AtahoMove::MyPlayer1->pos(), StageMap1->pos(), 640, 688);

	if(true != EventCheck)
		PreEvent();

	if (nullptr == HomeBgmPlay1)
	{
		HomeBgmPlay1 = bSound::SoundPlayNoneReturn();
		HomeBgmPlay1->Play(L"Home.mid", 100);
	}
	if (AtahoMove::MyPlayer1->pos().X < 300 && AtahoMove::MyPlayer1->pos().X > 240 && AtahoMove::MyPlayer1->pos().Y > 660)
	{
		HomeBgmPlay1->Stop();
		HomeBgmPlay1 = nullptr;
		AtahoMove::MyPlayer1->pos({ 250.0f, 200.0f });
		LinsianMove::MyPlayer2->pos({ 250.0f, 200.0f });
		SmashMove::MyPlayer3->pos({ 250.0f, 200.0f });

		AtahoMove::MyPlayer1->ClearMoveList();
		LinsianMove::MyPlayer2->ClearMoveList();
		SmashMove::MyPlayer3->ClearMoveList();

		SceneMgr::Inst().ChangeScene(L"Stage02");
	}

	if (false == MsgWindow::MsgWin->IsUpdate() && true == Input::Down(L"MENU"))
	{
		GameMenu::Menu();
	}

	if (true == Input::Down(L"-KEY"))
	{
		Status::BattleStatus[2]->Cur_Hp--;
		if (1 > Status::BattleStatus[2]->Cur_Hp)
			Status::BattleStatus[2]->Cur_Hp = 1;
	}
	if (true == Input::Down(L"+KEY"))
	{
		Status::BattleStatus[2]->Cur_Hp++;
		if (Status::BattleStatus[2]->Max_Hp < Status::BattleStatus[2]->Cur_Hp)
			Status::BattleStatus[2]->Cur_Hp = Status::BattleStatus[2]->Max_Hp;
	}
}

void S01FirstHome::PreEvent()
{
	EventCheck = true;
	MsgWindow::MsgEv(0, 5);
}

void S01FirstHome::DebugRender()
{



	std::wstring DebugText;
	wchar_t ArrText[256];

	if (true == Input::Press(L"DEBUG") && false == MsgWindow::MsgWin->IsUpdate() && false == GameMenu::GaMenu->IsUpdate())
	{
		StageMap1->m_MainRender->SetAlpha(255);
		StageMap1->m_Render_obj1->SetAlpha(0);


		swprintf_s(ArrText, L"Mouse Pos  x : %f y : %f", GameCore::mainWindow().MousePos().X, GameCore::mainWindow().MousePos().Y);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 30, 60, DebugText.c_str(), (int)DebugText.size());

		swprintf_s(ArrText, L"Player Pos x : %f y : %f", AtahoMove::MyPlayer1->pos().X, AtahoMove::MyPlayer1->pos().Y);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 30, 90, DebugText.c_str(), (int)DebugText.size());

		swprintf_s(ArrText, L"Camera Pos x : %f y : %f", SceneMgr::Inst().CurScene()->CameraPos.X, SceneMgr::Inst().CurScene()->CameraPos.Y);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 30, 120, DebugText.c_str(), (int)DebugText.size());

	/*	Rectangle(RenderMgr::BackDC()
		, AtahoMove::MyPlayer1->pos().IX() - SceneMgr::Inst().CurScene()->CameraPos.IX() - 16
		, AtahoMove::MyPlayer1->pos().IY() - SceneMgr::Inst().CurScene()->CameraPos.IY() - 16
		, AtahoMove::MyPlayer1->pos().IX() - SceneMgr::Inst().CurScene()->CameraPos.IX() + 167
		, AtahoMove::MyPlayer1->pos().IY() - SceneMgr::Inst().CurScene()->CameraPos.IY());*/

		AtahoMove::MyPlayer1->Speed = 3.0f;
	}
	else
	{
		AtahoMove::MyPlayer1->Speed = 1.0f;
		StageMap1->m_MainRender->SetAlpha(0);
		StageMap1->m_Render_obj1->SetAlpha(255);
	}
	Letter();
}

void S01FirstHome::Letter()
{
	std::wstring DebugText;
	wchar_t ArrText[256];
	HFONT myFont;
	HFONT oldFont;
	SetTextColor(RenderMgr::BackDC(), RGB(255, 255, 255));
	SetBkMode(RenderMgr::BackDC(), TRANSPARENT);
#pragma	region Region
	myFont = CreateFont(18, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
	oldFont = (HFONT)SelectObject(RenderMgr::BackDC(), myFont);

	DebugText = L"아타호의 거처";
	TextOut(RenderMgr::BackDC(), 448, 380, DebugText.c_str(), (int)DebugText.size());
	swprintf_s(ArrText, L"번 돈 %8dG", ListPlayer::Money);
	DebugText = ArrText;
	TextOut(RenderMgr::BackDC(), 448, 415, DebugText.c_str(), (int)DebugText.size());

	SelectObject(RenderMgr::BackDC(), oldFont);
	DeleteObject(myFont);
#pragma endregion

#pragma	region Status
	myFont = CreateFont(12, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
	oldFont = (HFONT)SelectObject(RenderMgr::BackDC(), myFont);

	for (int i = 0; i < 3; ++i)
	{
		swprintf_s(ArrText, L"%4d%8d",Status::BattleStatus[i]->Cur_Hp,Status::BattleStatus[i]->Max_Hp);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 144, 380 + i * 32, DebugText.c_str(), (int)DebugText.size());
		StatusBar::SBar[i][0]->m_Render->Percentage = (float)Status::BattleStatus[i]->Cur_Hp / (float)Status::BattleStatus[i]->Max_Hp;
	
		swprintf_s(ArrText, L"%4d%8d",Status::BattleStatus[i]->Cur_Mp,Status::BattleStatus[i]->Max_Mp);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 240, 380 + i * 32, DebugText.c_str(), (int)DebugText.size());
		StatusBar::SBar[i][1]->m_Render->Percentage = (float)Status::BattleStatus[i]->Cur_Mp / (float)Status::BattleStatus[i]->Max_Mp;

		swprintf_s(ArrText, L"%4d%8d",Status::BattleStatus[i]->Exp, 100);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 336, 380 + i * 32, DebugText.c_str(), (int)DebugText.size());
		StatusBar::SBar[i][2]->m_Render->Percentage = (float)Status::BattleStatus[i]->Exp * 0.01f;
	}

	SelectObject(RenderMgr::BackDC(), oldFont);
	DeleteObject(myFont);
#pragma endregion

#pragma	region Menu
	if (true == GameMenu::GaMenu->IsUpdate())
	{
		myFont = CreateFont(16, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
		oldFont = (HFONT)SelectObject(RenderMgr::BackDC(), myFont);

		swprintf_s(ArrText, L"%9d",Status::BattleStatus[GameMenu::GaMenu->ChIndex]->Level);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 288, 64, DebugText.c_str(), (int)DebugText.size());
		swprintf_s(ArrText, L"%3d/%3d",Status::BattleStatus[GameMenu::GaMenu->ChIndex]->Cur_Hp,Status::BattleStatus[GameMenu::GaMenu->ChIndex]->Max_Hp);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 288, 96, DebugText.c_str(), (int)DebugText.size());
		swprintf_s(ArrText, L"%3d/%3d",Status::BattleStatus[GameMenu::GaMenu->ChIndex]->Cur_Mp,Status::BattleStatus[GameMenu::GaMenu->ChIndex]->Max_Mp);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 288, 128, DebugText.c_str(), (int)DebugText.size());
		swprintf_s(ArrText, L"%3d/%3d",Status::BattleStatus[GameMenu::GaMenu->ChIndex]->Exp, 100);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 288, 160, DebugText.c_str(), (int)DebugText.size());
		swprintf_s(ArrText, L"%8d",Status::BattleStatus[GameMenu::GaMenu->ChIndex]->Att);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 288, 192, DebugText.c_str(), (int)DebugText.size());

		switch (GameMenu::GaMenu->ChIndex)
		{
		case 0:
			DebugText = L"호랑이 권법가";
			break;
		case 1:
			DebugText = L"고양이 권법가";
			break;
		case 2:
			DebugText = L"개 검사";
			break;
		default:
			break;
		}
		
		TextOut(RenderMgr::BackDC(), 80, 272, DebugText.c_str(), (int)DebugText.size());

		SelectObject(RenderMgr::BackDC(), oldFont);
		DeleteObject(myFont);
	}
#pragma endregion
	SetTextColor(RenderMgr::BackDC(), RGB(0, 0, 0));
	SetBkMode(RenderMgr::BackDC(), OPAQUE);
}