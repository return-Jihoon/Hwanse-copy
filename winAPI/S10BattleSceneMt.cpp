#include "S10BattleSceneMt.h"
#include "Ch01AtahoBattle.h"
#include "Ch02LinsianBattle.h"
#include "Ch03SmashBattle.h"

#include "BattleMonkey.h"

#include "GameCore.h"
#include <Windows.h>
#include "BtMtMap.h"
#include "BattleMenu.h"

#include "RenderMgr.h"
#include <bInput.h>

#include <bTime.h>
#include <bSound.h>
#include <Windows.h>
#include "StatusBar.h"
#include "MsgWindow.h"

BtMtMap* StageMapBTM = nullptr;

bSoundPlayer* BattleBgm_Mt = nullptr;
bSoundPlayer* BattleBgm_End = nullptr;

BattleMonkey* MonkeyEnemy[3] = { nullptr,nullptr,nullptr };


S10BattleSceneMt::S10BattleSceneMt() : BattleOn(false), EvCounter(0.0f)
{
}


S10BattleSceneMt::~S10BattleSceneMt()
{
}

bool S10BattleSceneMt::Loading()
{

	StageMapBTM = Actor::CreateActor<BtMtMap>(L"BtMtMap");

	BattleMenu::BtMenu = Actor::CreateActor<BattleMenu>(L"BattleM");
	BattleMenu::BtMenu->OverScene(L"BattleMt", L"BattleTown");
	BattleMenu::BtMenu->Off();

	AtahoBattle::BtPlayer1 = Actor::CreateActor<AtahoBattle>(L"BtPlayer1", true);
	AtahoBattle::BtPlayer1->OverScene(L"BattleMt", L"BattleTown");
	AtahoBattle::BtPlayer1->pos({ 150.0f, 140.0f });

	LinsianBattle::BtPlayer2 = Actor::CreateActor<LinsianBattle>(L"BtPlayer2", true);
	LinsianBattle::BtPlayer2->OverScene(L"BattleMt", L"BattleTown");
	LinsianBattle::BtPlayer2->pos({ 135.0f, 190.0f });

	SmashBattle::BtPlayer3 = Actor::CreateActor<SmashBattle>(L"BtPlayer3", true);
	SmashBattle::BtPlayer3->OverScene(L"BattleMt", L"BattleTown");
	SmashBattle::BtPlayer3->pos({ 120.0f, 240.0f });

	MonkeyEnemy[0] = Actor::CreateActor<BattleMonkey>(L"MonkeyEnemy1", true);
	MonkeyEnemy[0]->pos({550.0f, 115.f});

	MonkeyEnemy[1] = Actor::CreateActor<BattleMonkey>(L"MonkeyEnemy2", true);
	MonkeyEnemy[1]->pos({ 535.0f, 165.f });

	MonkeyEnemy[2] = Actor::CreateActor<BattleMonkey>(L"MonkeyEnemy3", true);
	MonkeyEnemy[2]->pos({ 520.0f, 215.f });

	StatusBar::EBar[0] = Actor::CreateActor<StatusBar>(L"StatusE1");
	StatusBar::EBar[0]->pos({ 544.0f, 392.0f });
	StatusBar::EBar[1] = Actor::CreateActor<StatusBar>(L"StatusE2");
	StatusBar::EBar[1]->pos({ 544.0f, 392.0f + 32.0f });
	StatusBar::EBar[2] = Actor::CreateActor<StatusBar>(L"StatusE3");
	StatusBar::EBar[2]->pos({ 544.0f, 392.0f + 64.0f });



	return true;
}

void S10BattleSceneMt::SceneUpdate()
{

	if (nullptr == BattleBgm_Mt && false == AtahoBattle::BtPlayer1->Victory)
	{
		BattleBgm_Mt = bSound::SoundPlayNoneReturn();
		BattleBgm_Mt->Play(L"Battle.mid", 100);
	}
	if (true == Input::Down(L"KKEY"))
	{
		BattleBgm_Mt->Stop();
		BattleBgm_Mt = nullptr;

		BattleBgm_End = bSound::SoundPlayNoneReturn();
		BattleBgm_End->Play(L"BattleEnd.mid", 0);
	//	BattleBgm_End = nullptr;

		SceneMgr::Inst().ChangeScene(L"Stage02");
	}

	BattlePhase();
}

void S10BattleSceneMt::DebugRender()
{

	Letter();
}

void S10BattleSceneMt::BattlePhase()
{
	if (true == BattleMenu::Runaway)
	{
		MsgWindow::MsgEv(59, 59);
		BattleMenu::Runaway = false;
	}

	if (false == BattleMenu::BtMenu->IsUpdate() && false == BattleOn && false == MsgWindow::MsgWin->IsUpdate() && false == AtahoBattle::BtPlayer1->Victory)
	{
		if (0 <= BattleMenu::CharIndex && 2 >= BattleMenu::CharIndex)
		{
			BattleMenu::BtMenu->On();
		}
		else if (2 < BattleMenu::CharIndex)
		{
			BattleOn = true;
			BattleMenu::CharIndex = 0;
		}
	}

	if (true == BattleOn) // 시전할 기술 선택 상태
	{
		if (false == BattlePlayer::SkillOn && 0 == BattlePlayer::CharIndex) 
		{
			BattlePlayer::SkillOn = true;// 캐릭터 1 스킬 시전완료
		}

		if (false == BattlePlayer::SkillOn && 1 == BattlePlayer::CharIndex) 
		{
			BattlePlayer::SkillOn = true;// 캐릭터 2 스킬 시전완료
		}

		if (false == BattlePlayer::SkillOn && 2 == BattlePlayer::CharIndex)
		{
			BattlePlayer::SkillOn = true;// 캐릭터 3 스킬 시전완료
		}

		if (false == BattlePlayer::SkillOn && 3 == BattlePlayer::CharIndex) // 기술을 시전하고 순서 초기화
		{
			BattleOn = false;
			BattlePlayer::CharIndex = 0;
		}

		if (BattlePlayer::DMG > 0)
		{
			Status::BattleStatus[BattlePlayer::CharIndex]->Cur_Mp -= 10;
			if (-1 == BattlePlayer::PlTarget[BattlePlayer::CharIndex])
			{
				for (int i = 0; i < 3; ++i)
				{
					BattleEnemyStatus[i].Cur_Hp -= BattlePlayer::DMG;
					MonkeyEnemy[i]->StandState = true;
				}
			}
			else
			{
				BattleEnemyStatus[BattlePlayer::PlTarget[BattlePlayer::CharIndex]].Cur_Hp -= BattlePlayer::DMG;
				MonkeyEnemy[BattlePlayer::PlTarget[BattlePlayer::CharIndex]]->StandState = true;
			}
			BattlePlayer::DMG = 0;
		}

		for (int i = 0; i < 3; ++i)
		{
			if (BattleEnemyStatus[i].Cur_Hp <= 0)
			{
				BattleEnemyStatus[i].Cur_Hp = 0;
				if (false == MonkeyEnemy[i]->Death)
				{
					Status::BattleStatus[BattlePlayer::CharIndex]->Exp += 10;
				}

				MonkeyEnemy[i]->Death = true;
			}
		}
	}
	if (true == MonkeyEnemy[0]->Death && true == MonkeyEnemy[1]->Death && true == MonkeyEnemy[2]->Death && false == BattlePlayer::SkillOn)
	{
		if (0.0f == EvCounter)
		{
			BattleBgm_Mt->Stop();
			BattleBgm_Mt = nullptr;
			BattleBgm_End = bSound::SoundPlayNoneReturn();
			BattleBgm_End->Play(L"BattleEnd.mid", 0);
		}

		EvCounter += 1.0f * bTime::DeltaTime();
		AtahoBattle::BtPlayer1->Victory = true;
		LinsianBattle::BtPlayer2->Victory = true;
		SmashBattle::BtPlayer3->Victory = true;

		if (2.0f < EvCounter)
		{
			AtahoBattle::BtPlayer1->Victory = false;
			LinsianBattle::BtPlayer2->Victory = false;
			SmashBattle::BtPlayer3->Victory = false;
			SceneMgr::Inst().ChangeScene(L"Stage02");
		}
		
	}
}

void S10BattleSceneMt::Letter()
{

	std::wstring DebugText;
	wchar_t ArrText[256];
	HFONT myFont;
	HFONT oldFont;
	SetTextColor(RenderMgr::BackDC(), RGB(255, 255, 255));
	SetBkMode(RenderMgr::BackDC(), TRANSPARENT);
#pragma	region Region
	/*
	myFont = CreateFont(18, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
	oldFont = (HFONT)SelectObject(RenderMgr::BackDC(), myFont);

	DebugText = L"산기슭 전투맵";
	TextOut(RenderMgr::BackDC(), 448, 380, DebugText.c_str(), (int)DebugText.size());

	SelectObject(RenderMgr::BackDC(), oldFont);
	DeleteObject(myFont);*/
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

	for (int i = 0; i < 3; ++i)
	{
		swprintf_s(ArrText, L"%4d%8d", BattleEnemyStatus[i].Cur_Hp, BattleEnemyStatus[i].Max_Hp);
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 560, 380 + i * 32, DebugText.c_str(), (int)DebugText.size());
		StatusBar::EBar[i]->m_Render->Percentage = (float)BattleEnemyStatus[i].Cur_Hp / (float)BattleEnemyStatus[i].Max_Hp;
	}

	SelectObject(RenderMgr::BackDC(), oldFont);
	DeleteObject(myFont);


	myFont = CreateFont(15, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
	oldFont = (HFONT)SelectObject(RenderMgr::BackDC(), myFont);

	for (int i = 0; i < 3; ++i)
	{
		swprintf_s(ArrText, L"원숭이");
		DebugText = ArrText;
		TextOut(RenderMgr::BackDC(), 448, 380 + i * 32, DebugText.c_str(), (int)DebugText.size());
	}

	SelectObject(RenderMgr::BackDC(), oldFont);
	DeleteObject(myFont);
#pragma endregion

}