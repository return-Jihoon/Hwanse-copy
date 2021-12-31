#include "Ch03SmashBattle.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"

SmashBattle* SmashBattle::BtPlayer3;

SmashBattle::SmashBattle()
{
}


SmashBattle::~SmashBattle()
{
}

bool SmashBattle::init()
{
	m_AniRender = CreateRender <AniRender>();
	m_AniRender->RenderPosMode(Pivot::CENTER);

	m_AniRender->CreateAni(L"StandBase", L"Smash.bmp", 0, 0, false);
	m_AniRender->CreateAni(L"Damage", L"Smash.bmp", 1, 1, false);
	m_AniRender->CreateAni(L"Down", L"Smash.bmp", 39, 41, true, 0.1f);
	m_AniRender->CreateAni(L"Vic", L"Smash.bmp", 42, 45, false, 0.15f);
	m_AniRender->CreateAni(L"Slash", L"Smash.bmp", 25, 27, false, 0.25f);
	m_AniRender->CreateAni(L"Assult", L"Smash.bmp", 7, 9, false, 0.10f);
	m_AniRender->CreateAni(L"Hack", L"Smash.bmp", 10, 13, false, 0.15f);


	m_AniRender->StartAni(L"StandBase");

	return true;
}

void SmashBattle::Update()
{
	if (true == Die)
	{
		m_AniRender->StartAni(L"Down");
		return;
	}

	if (true == Damage)
	{
		m_AniRender->StartAni(L"Damage");
	}
	else if (true == Victory)
	{
		m_AniRender->StartAni(L"Vic");
		pos({ 120.0f, 240.0f });
		return;
	}
	else if (false == SkillOn)
	{
		m_AniRender->StartAni(L"StandBase");
		pos({ 120.0f, 240.0f });
		return;
	}

	if (2 != BattlePlayer::CharIndex)
		return;


	if (true == SkillOn && false == SkillEnd)
	{
		if (0 == Skills[2])
		{
			pos({ 400.0f,140.0f + BattlePlayer::PlTarget[2] * 50.0f });
			m_AniRender->StartAni(L"Slash");
			SkillCount += 1.0f * bTime::DeltaTime();
			if (1.0f < SkillCount)
			{
				SkillCount = 0.0f;
				DMG = 2 * Status::BattleStatus[1]->Att;
				SkillEnd = true;
			}
		}
		else if (1 == Skills[2])
		{
			m_AniRender->StartAni(L"Assult");

			SkillCount += 1.0f * bTime::DeltaTime();
			if (0.5f < SkillCount)
			{
				SkillCount = 0.0f;
				DMG = 10 * Status::BattleStatus[2]->Att;
				SkillEnd = true;
			}
			else
				pos({ 120.0f + 680.0f * SkillCount, 240.0f - 100 * SkillCount });
		}
		else if (2 == Skills[2])
		{
			pos({ 350.0f,190.0f });
			m_AniRender->StartAni(L"Hack");

			SkillCount += 1.0f * bTime::DeltaTime();
			if (1.0f < SkillCount)
			{
				SkillCount = 0.0f;
				DMG = 1 * Status::BattleStatus[2]->Att;
				SkillEnd = true;
			}
		}
	}
	else if (false == Victory && true == SkillEnd)
	{
		SkillCount += 1.0f * bTime::DeltaTime();
		if (0.5f < SkillCount)
		{
			SkillCount = 0.0f;
			m_AniRender->StartAni(L"StandBase");
			pos({ 120.0f, 240.0f });
			SkillOn = false;
			SkillEnd = false;
			BattlePlayer::CharIndex++;
		}
	}

}
