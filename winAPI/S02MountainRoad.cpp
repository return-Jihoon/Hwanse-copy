#include "S02MountainRoad.h"
#include "Ch01AtahoMove.h"
#include "Ch02LinsianMove.h"
#include "Ch03SmashMove.h"
#include "BattlePlayer.h"
#include "Monster.h"
#include "DoorRock.h"
#include "GameCore.h"
#include <Windows.h>
#include "MountainMap.h"
#include "Frame.h"
#include "RenderMgr.h"
#include "MsgWindow.h"
#include "Monkey.h"
#include "Girl.h"
#include "OldMan.h"
#include <bInput.h>
#include <bSound.h>
#include "TransRender.h"
#include "Flood.h"
#include "GameMenu.h"
#include "StatusBar.h"

MountainMap* StageMap2 = nullptr;
bSoundPlayer* HomeBgmPlay2 = nullptr;

DoorRock* Door = nullptr;
bool DoorKey = false;

Monkey* Monkey1 = nullptr;
Monkey* Monkey2 = nullptr;
Monkey* Monkey3 = nullptr;
Girl* Girl1 = nullptr;
OldMan* OldMan1 = nullptr;

S02MountainRoad::S02MountainRoad() : MtConversation(0)
{
}


S02MountainRoad::~S02MountainRoad()
{
}


bool S02MountainRoad::Loading()
{
	StageMap2 = Actor::CreateActor<MountainMap>(L"MtMAp");

	Door = Actor::CreateActor<DoorRock>(L"DoorRock");
	DoorKey = true;

	StageMap2->m_MainRender->SetAlpha(0);

	Monkey1 = Actor::CreateActor<Monkey>(L"Monkey1");
	Monkey1->pos({ 1150.0f, 176.0f });

	Monkey2 = Actor::CreateActor<Monkey>(L"Monkey2");
	Monkey2->pos({ 1130.0f, 230.0f });

	Monkey3 = Actor::CreateActor<Monkey>(L"Monkey3");
	Monkey3->pos({ 1185.0f, 245.0f });

	Girl1 = Actor::CreateActor<Girl>(L"Girl");
	Girl1->pos({ 1170.0f, 200.0f });

	OldMan1 = Actor::CreateActor<OldMan>(L"OldMan");
	OldMan1->pos({ 208.0f, 575.0f });

	Actor::CreateActor<Flood>(L"Flood");

	return true;
}


void S02MountainRoad::SceneUpdate()
{
	AtahoMove::MyPlayer1->CurMap = StageMap2;


	if (false == DoorKey)
	{
		Door->GetRender()->SetAlpha(255);
		DoorKey = true;
	}

	if (nullptr == HomeBgmPlay2)
	{
		HomeBgmPlay2 = bSound::SoundPlayNoneReturn();
		HomeBgmPlay2->Play(L"RoadMt.mid", 100);
	}

	SceneMgr::CameraPosSet(AtahoMove::MyPlayer1->pos(), StageMap2->pos(), 1280, 880);

	if (true == DoorKey && AtahoMove::MyPlayer1->pos().X < 280 && AtahoMove::MyPlayer1->pos().X > 220 && AtahoMove::MyPlayer1->pos().Y < 195)
	{
		Door->GetRender()->SetAlpha(0);
	}

	if (0 == MtConversation)
		PreEvent();

	if (AtahoMove::MyPlayer1->pos().X < 280 && AtahoMove::MyPlayer1->pos().X > 220 && AtahoMove::MyPlayer1->pos().Y < 185)
	{
		HomeBgmPlay2->Stop();
		HomeBgmPlay2 = nullptr;

		DoorKey = false;

		AtahoMove::MyPlayer1->pos({ 270.0f, 650.0f });
		LinsianMove::MyPlayer2->pos({ 270.0f, 650.0f });
		SmashMove::MyPlayer3->pos({ 270.0f, 650.0f });

		AtahoMove::MyPlayer1->ClearMoveList();
		LinsianMove::MyPlayer2->ClearMoveList();
		SmashMove::MyPlayer3->ClearMoveList();

		SceneMgr::Inst().ChangeScene(L"Stage01");
	}

	if (AtahoMove::MyPlayer1->pos().X > 1245 && AtahoMove::MyPlayer1->pos().Y > 575 && AtahoMove::MyPlayer1->pos().Y < 800)
	{
		HomeBgmPlay2->Stop();
		HomeBgmPlay2 = nullptr;

		DoorKey = false;

		AtahoMove::MyPlayer1->pos({ 40.0f, 880.2f });
		LinsianMove::MyPlayer2->pos({ 40.0f, 880.1f });
		SmashMove::MyPlayer3->pos({ 40.0f, 880.0f });

		AtahoMove::MyPlayer1->ClearMoveList();
		LinsianMove::MyPlayer2->ClearMoveList();
		SmashMove::MyPlayer3->ClearMoveList();

		SceneMgr::Inst().ChangeScene(L"Stage03");
	}


	if (false == MsgWindow::MsgWin->IsUpdate() && true == Input::Down(L"MENU"))
	{
		GameMenu::Menu();
	}

#pragma region Flow

	if (1 == MtConversation && AtahoMove::MyPlayer1->pos().X > 1030 && AtahoMove::MyPlayer1->pos().Y < 230 && AtahoMove::MyPlayer1->pos().Y > 140)
	{
		MtConversation = 2;
		MsgWindow::MsgEv(9, 14);
	}

	if (2 == MtConversation && false == MsgWindow::MsgWin->IsUpdate())
	{
		MtConversation = 3;
		HomeBgmPlay2->Stop();
		HomeBgmPlay2 = nullptr;
		SceneMgr::Inst().ChangeScene(L"BattleMt");
	}

	if (3 == MtConversation && false == MsgWindow::MsgWin->IsUpdate())
	{
		Monkey::Running = true;
		MtConversation = 4;
		ListPlayer::DontMove = true;
	}

	if (4 == MtConversation && false == Monkey1->IsUpdate())
	{
		MtConversation = 5;
		MsgWindow::MsgEv(15, 16);
		ListPlayer::DontMove = false;
	}

	if (5 == MtConversation && false == MsgWindow::MsgWin->IsUpdate())
	{
		MtConversation = 6;
		ListPlayer::Money += 10000;
		MsgWindow::MsgEv(17, 18);
		Girl::Running = true;
	}

	if (6 == MtConversation && AtahoMove::MyPlayer1->pos().X < 241 && AtahoMove::MyPlayer1->pos().Y < 590 && AtahoMove::MyPlayer1->pos().Y > 560)
	{
		MtConversation = 7;
		MsgWindow::MsgEv(19, 27);
	}

	if (7 == MtConversation && false == MsgWindow::MsgWin->IsUpdate())
	{
		MtConversation = 8;
		ListPlayer::Money -= 10000;
		MsgWindow::MsgEv(28, 30);
	}

	if (8 == MtConversation && false == MsgWindow::MsgWin->IsUpdate())
	{
		MtConversation = 9;
		OldMan::Running = true;
		ListPlayer::DontMove = true;
	}

	if (9 == MtConversation && false == OldMan1->IsUpdate())
	{
		MtConversation = 10;
		MsgWindow::MsgEv(31, 32);
		ListPlayer::DontMove = false;
		BattlePlayer::PowerUp = true;
	}
#pragma endregion

}

void S02MountainRoad::PreEvent()
{
	MtConversation = 1;
	MsgWindow::MsgEv(6, 8);
}

void S02MountainRoad::DebugRender()
{
	std::wstring DebugText;
	wchar_t ArrText[256];

	if (true == Input::Press(L"DEBUG") && false == MsgWindow::MsgWin->IsUpdate() && false == GameMenu::GaMenu->IsUpdate())
	{
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
			, AtahoMove::MyPlayer1->pos().IX() - SceneMgr::Inst().CurScene()->CameraPos.IX() + 16
			, AtahoMove::MyPlayer1->pos().IY() - SceneMgr::Inst().CurScene()->CameraPos.IY());*/


		StageMap2->m_MainRender->SetAlpha(255);
		StageMap2->m_Render_obj1->SetAlpha(0);
		AtahoMove::MyPlayer1->Speed = 3.0f;
	}
	else
	{
		AtahoMove::MyPlayer1->Speed = 1.0f;
		StageMap2->m_MainRender->SetAlpha(0);
		StageMap2->m_Render_obj1->SetAlpha(255);
	}
	Letter();
}

void S02MountainRoad::Letter()
{
	std::wstring DebugText;
	wchar_t ArrText[256];
	HFONT myFont;
	HFONT oldFont;
	SetTextColor(RenderMgr::BackDC(), RGB(255, 255, 255));
	SetBkMode(RenderMgr::BackDC(), TRANSPARENT);
#pragma	region Region
	myFont = CreateFont(18, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"±¼¸²");
	oldFont = (HFONT)SelectObject(RenderMgr::BackDC(), myFont);

	DebugText = L"È£¶ûÀÌ¹ÙÀ§ »ê±æ";
	TextOut(RenderMgr::BackDC(), 448, 380, DebugText.c_str(), (int)DebugText.size());
	swprintf_s(ArrText, L"¹ø µ· %8dG", ListPlayer::Money);
	DebugText = ArrText;
	TextOut(RenderMgr::BackDC(), 448, 415, DebugText.c_str(), (int)DebugText.size());

	SelectObject(RenderMgr::BackDC(), oldFont);
	DeleteObject(myFont);
#pragma endregion

#pragma	region Status
	myFont = CreateFont(12, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"±¼¸²");
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
		myFont = CreateFont(16, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"±¼¸²");
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
			DebugText = L"È£¶ûÀÌ ±Ç¹ý°¡";
			break;
		case 1:
			DebugText = L"°í¾çÀÌ ±Ç¹ý°¡";
			break;
		case 2:
			DebugText = L"°³ °Ë»ç";
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