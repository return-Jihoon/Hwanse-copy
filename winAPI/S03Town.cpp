#include "S03Town.h"
#include "Ch01AtahoMove.h"
#include "Ch02LinsianMove.h"
#include "Ch03SmashMove.h"
#include "BattlePlayer.h"
#include "Monster.h"
#include "GameCore.h"
#include <Windows.h>
#include "BeachTown.h"
#include "Frame.h"
#include "RenderMgr.h"
#include "MsgWindow.h"
#include <bInput.h>
#include <bSound.h>
#include "TransRender.h"
#include "Flood.h"
#include "GameMenu.h"
#include <bTime.h>
#include "StatusBar.h"
#include "Boss.h"

BeachTown* StageMap3 = nullptr;
bSoundPlayer* HomeBgmPlay3 = nullptr;
Boss* Boss1 = nullptr;

S03Town::S03Town() : TwConversation(0)
{
}


S03Town::~S03Town()
{
}


bool S03Town::Loading()
{
	StageMap3 = Actor::CreateActor<BeachTown>(L"TownMap");

	StageMap3->m_MainRender->SetAlpha(0);

	Boss1 = Actor::CreateActor<Boss>(L"Boss");

	return true;
}


void S03Town::SceneUpdate()
{
	AtahoMove::MyPlayer1->CurMap = StageMap3;

	if (nullptr == HomeBgmPlay3)
	{
		HomeBgmPlay3 = bSound::SoundPlayNoneReturn();
		HomeBgmPlay3->Play(L"Home.mid", 100);
	}
	if (3 < TwConversation)
		SceneMgr::CameraPosSet(AtahoMove::MyPlayer1->pos(), StageMap3->pos(), 1304, 944);


	if (AtahoMove::MyPlayer1->pos().X < 20 && AtahoMove::MyPlayer1->pos().Y > 850 && AtahoMove::MyPlayer1->pos().Y < 912)
	{
		HomeBgmPlay3->Stop();
		HomeBgmPlay3 = nullptr;

		AtahoMove::MyPlayer1->pos({ 1230.0f, 680.0f });
		LinsianMove::MyPlayer2->pos({ 1230.0f, 680.0f });
		SmashMove::MyPlayer3->pos({ 1230.0f, 680.0f });

		AtahoMove::MyPlayer1->ClearMoveList();
		LinsianMove::MyPlayer2->ClearMoveList();
		SmashMove::MyPlayer3->ClearMoveList();

		SceneMgr::Inst().ChangeScene(L"Stage02");
	}

	if (0 != GetAsyncKeyState('L'))
	{
		HomeBgmPlay3->Stop();
		HomeBgmPlay3 = nullptr;
		SceneMgr::Inst().ChangeScene(L"BattleTown");
	}

	if (false == MsgWindow::MsgWin->IsUpdate() && true == Input::Down(L"MENU"))
	{
		GameMenu::Menu();
	}

#pragma region Flow

	if (0 == TwConversation)
	{
		SceneMgr::CameraPosSet(AtahoMove::MyPlayer1->pos(), StageMap3->pos(), 1304, 944);
		TwConversation = 1;
	}

	if (1 == TwConversation)
	{
		ListPlayer::DontMove = true;
		if (SceneMgr::Inst().CurScene()->CameraPos.X < 320.0f)
			SceneMgr::Inst().CurScene()->CameraPos += {200.0f * bTime::DeltaTime(), 0.0f};
		else if ((SceneMgr::Inst().CurScene()->CameraPos.Y > 320.0f))
			SceneMgr::Inst().CurScene()->CameraPos += {0.0f, -200.0f * bTime::DeltaTime()};
		else
			TwConversation = 2;
	}

	if (2 == TwConversation)
	{
		ListPlayer::DontMove = false;
		MsgWindow::MsgEv(33, 35);
		TwConversation = 3;
	}

	if (3 == TwConversation)
	{
		SceneMgr::Inst().CurScene()->CameraPos = Pos({ 320.0f,320.0f });
		if (false == MsgWindow::MsgWin->IsUpdate())
		{
			TwConversation = 4;
			MsgWindow::MsgEv(36, 38);
		}
	}

	if (4 == TwConversation && AtahoMove::MyPlayer1->pos().X > 542 && AtahoMove::MyPlayer1->pos().X < 610 && AtahoMove::MyPlayer1->pos().Y > 335 && AtahoMove::MyPlayer1->pos().Y < 368)
	{
		TwConversation = 5;
		MsgWindow::MsgEv(39, 43);
	}

	if (5 == TwConversation && false == MsgWindow::MsgWin->IsUpdate())
	{
		TwConversation = 6;
		HomeBgmPlay3->Stop();
		HomeBgmPlay3 = nullptr;
		SceneMgr::Inst().ChangeScene(L"BattleTown");
	}

	if (6 == TwConversation && false == MsgWindow::MsgWin->IsUpdate())
	{
		TwConversation = 7;
		Boss1->Running = true;
	}

	if (7 == TwConversation && false == MsgWindow::MsgWin->IsUpdate() && false == Boss1->Running)
	{
		TwConversation = 8;
		MsgWindow::MsgEv(44, 48);
	}

	if (8 == TwConversation && false == MsgWindow::MsgWin->IsUpdate())
	{
		TwConversation = 9;
		ListPlayer::Money += 10;
	}


#pragma endregion

}


void S03Town::DebugRender()
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

		AtahoMove::MyPlayer1->Speed = 3.0f;
		StageMap3->m_MainRender->SetAlpha(255);
		StageMap3->m_Render_obj1->SetAlpha(0);
	}
	else
	{
		AtahoMove::MyPlayer1->Speed = 1.0f;
		StageMap3->m_MainRender->SetAlpha(0);
		StageMap3->m_Render_obj1->SetAlpha(255);
	}
	Letter();
}

void S03Town::Letter()
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

	DebugText = L"해변마을";
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
		swprintf_s(ArrText, L"%4d%8d", Status::BattleStatus[i]->Cur_Hp,Status::BattleStatus[i]->Max_Hp);
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