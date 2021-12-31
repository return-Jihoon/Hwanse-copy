#include "S11BattleSceneTown.h"
#include "Ch01AtahoBattle.h"
#include "Ch02LinsianBattle.h"
#include "Ch03SmashBattle.h"
#include "GameCore.h"
#include <Windows.h>
#include "BtTownMap.h"
#include "RenderMgr.h"
#include <bInput.h>
#include <bTime.h>
#include <bSound.h>
#include <Windows.h>
#include "StatusBar.h"
#include "BossBattle.h"
#include "BattleMenu.h"
#include "MsgWindow.h"

BtTownMap* StageMapBTT = nullptr;
bSoundPlayer* BattleBgm_Town = nullptr;
bSoundPlayer* BattleBgm_Other = nullptr;

BossBattle* BattleBoss = nullptr;

int BossMaxHp = 500;
int BossCurHp = 500;

S11BattleSceneTown::S11BattleSceneTown() : BattleOn(false), EvCounter(0.0f), BsCounter(0.0f)
{
}


S11BattleSceneTown::~S11BattleSceneTown()
{
}

bool S11BattleSceneTown::Loading()
{

	BattleBoss = Actor::CreateActor<BossBattle>(L"BtBoss", true);
	BattleBoss->pos({ 496.0f, 142.0f });

	StageMapBTT = Actor::CreateActor<BtTownMap>(L"BtTownMap");

	StatusBar::EBar[3] = Actor::CreateActor<StatusBar>(L"StatusE4");
	StatusBar::EBar[3]->pos({ 544.0f, 392.0f + 32.0f });

	return true;
}

void S11BattleSceneTown::SceneUpdate()
{
	BattleMenu::CurMap = true;

	if (nullptr == BattleBgm_Town && false == AtahoBattle::BtPlayer1->Victory)
	{
		BattleBgm_Town = bSound::SoundPlayNoneReturn();
		BattleBgm_Town->Play(L"Battle.mid", 100);
	}
	if (0 != GetAsyncKeyState('K'))
	{
		BattleBgm_Town->Stop();
		BattleBgm_Town = nullptr;

		BattleBgm_Other = bSound::SoundPlayNoneReturn();
		BattleBgm_Other->Play(L"BattleEnd.mid", 0);
		//	BattleBgm_End = nullptr;

		SceneMgr::Inst().ChangeScene(L"Stage03");
	}

	BattlePhase();
}

void S11BattleSceneTown::DebugRender()
{
	std::wstring DebugText = L"Stage01";

	if (true == Input::Press(L"DEBUG"))
	{

	}

	Letter();
}

void S11BattleSceneTown::BattlePhase()
{
	if (true == BattleMenu::Runaway)
	{
		MsgWindow::MsgEv(59, 59);
		BattleMenu::Runaway = false;
	}
	for (int i = 0; i < 3; i++)
	{
		BattlePlayer::PlTarget[i] = 1;
	}

	if (true == BattleBoss->Attack && false == BattleOn)
	{
		BsCounter += 1.0f * bTime::DeltaTime();
		switch (Enemy::EnTarget[3])
		{
			case 0:
			{
				if (2.3f < BsCounter)
				{
					AtahoBattle::BtPlayer1->Damage = true;
				}
				if (3.0f < BsCounter)
				{
					AtahoBattle::BtPlayer1->Damage = false;
					BsCounter = 0.0f;
				}
				break;
			}
			case 1:
			{
				if (2.3f < BsCounter)
				{
					LinsianBattle::BtPlayer2->Damage = true;
				}
				if (3.0f < BsCounter)
				{
					LinsianBattle::BtPlayer2->Damage = false;
					BsCounter = 0.0f;
				}
				break;
			}
			case 2:
			{
				if (2.3f < BsCounter)
				{
					SmashBattle::BtPlayer3->Damage = true;
				}
				if (3.0f < BsCounter)
				{
					SmashBattle::BtPlayer3->Damage = false;
					BsCounter = 0.0f;
				}
				break;
			}
			default:
				break;
		}
	}

	if (Status::BattleStatus[0]->Cur_Hp <= 0)
	{
		Status::BattleStatus[0]->Cur_Hp = 0;
		AtahoBattle::BtPlayer1->Die = true;
	}
	if (Status::BattleStatus[1]->Cur_Hp <= 0)
	{
		Status::BattleStatus[1]->Cur_Hp = 0;
		LinsianBattle::BtPlayer2->Die = true;
	}
	if (Status::BattleStatus[2]->Cur_Hp <= 0)
	{
		Status::BattleStatus[2]->Cur_Hp = 0;
		SmashBattle::BtPlayer3->Die = true;
	}

	if (false == BattleMenu::BtMenu->IsUpdate() && false == BattleOn && false == MsgWindow::MsgWin->IsUpdate() && false == AtahoBattle::BtPlayer1->Victory && false == BattleBoss->Attack)
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
	if (true == BattleOn)
	{
		if (false == BattlePlayer::SkillOn && 0 == BattlePlayer::CharIndex)
		{
			BattlePlayer::SkillOn = true;
			if (0 == Status::BattleStatus[BattlePlayer::CharIndex]->Cur_Hp)
			{
				BattlePlayer::CharIndex++;
				BattlePlayer::SkillOn = false;
			}
		}

		if (false == BattlePlayer::SkillOn && 1 == BattlePlayer::CharIndex)
		{
			BattlePlayer::SkillOn = true;
			if (0 == Status::BattleStatus[BattlePlayer::CharIndex]->Cur_Hp)
			{
				BattlePlayer::CharIndex++;
				BattlePlayer::SkillOn = false;
			}
		}

		if (false == BattlePlayer::SkillOn && 2 == BattlePlayer::CharIndex)
		{
			BattlePlayer::SkillOn = true;
			if (0 == Status::BattleStatus[BattlePlayer::CharIndex]->Cur_Hp)
			{
				BattlePlayer::CharIndex++;
				BattlePlayer::SkillOn = false;
			}
		}

		if (false == BattlePlayer::SkillOn && 3 == BattlePlayer::CharIndex)
		{
			BossAttack();
			BattlePlayer::CharIndex = 0;
		}

		if (BattlePlayer::DMG > 0)
		{
			Status::BattleStatus[BattlePlayer::CharIndex]->Cur_Mp -= 10;
			
			BossCurHp -= BattlePlayer::DMG;
			BattleBoss->StandState = true;
			BattlePlayer::DMG = 0;
		}
		if (BossCurHp <= 0)
			{
			BossCurHp = 0;
			if (false == BattleBoss->Death)
			{
				Status::BattleStatus[BattlePlayer::CharIndex]->Exp += 69;
			}
			BattleBoss->Death = true;
			BattlePlayer::SkillOn = false;
		}
		
	}
	if (true == BattleBoss->Death && false == BattlePlayer::SkillOn)
	{
		if (0.0f == EvCounter)
		{
			BattleBgm_Town->Stop();
			BattleBgm_Town = nullptr;
			BattleBgm_Other = bSound::SoundPlayNoneReturn();
			BattleBgm_Other->Play(L"BattleEnd.mid", 0);
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
			SceneMgr::Inst().ChangeScene(L"Stage03");
		}

	}
}

void S11BattleSceneTown::BossAttack()
{
	BattleBoss->Attack = true;
	BattleOn = false;
}

void S11BattleSceneTown::Letter()
{

	std::wstring DebugText;
	wchar_t ArrText[256];
	HFONT myFont;
	HFONT oldFont;
	SetTextColor(RenderMgr::BackDC(), RGB(255, 255, 255));
	SetBkMode(RenderMgr::BackDC(), TRANSPARENT);

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

	
	swprintf_s(ArrText, L"%4d%8d", BossCurHp, BossMaxHp);
	DebugText = ArrText;
	TextOut(RenderMgr::BackDC(), 560, 412, DebugText.c_str(), (int)DebugText.size());
	StatusBar::EBar[3]->m_Render->Percentage = (float)BossCurHp / (float)BossMaxHp;

	SelectObject(RenderMgr::BackDC(), oldFont);
	DeleteObject(myFont);

	myFont = CreateFont(15, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"±¼¸²");
	oldFont = (HFONT)SelectObject(RenderMgr::BackDC(), myFont);
	
	swprintf_s(ArrText, L"¾Ï°¢±Ç ÃÑÅë");
	DebugText = ArrText;
	TextOut(RenderMgr::BackDC(), 448, 412, DebugText.c_str(), (int)DebugText.size());

	SelectObject(RenderMgr::BackDC(), oldFont);
	DeleteObject(myFont);
#pragma endregion

}



