#include "Ch02LinsianBattle.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"

LinsianBattle* LinsianBattle::BtPlayer2;

LinsianBattle::LinsianBattle()
{
}


LinsianBattle::~LinsianBattle()
{
}

bool LinsianBattle::init()
{
	m_AniRender = CreateRender <AniRender>();
	m_AniRender->RenderPosMode(Pivot::CENTER);

	m_AniRender->CreateAni(L"StandBase", L"Linsian.bmp", 0, 0, false);

	m_AniRender->CreateAni(L"Damage", L"Linsian.bmp", 2, 2, false);
	m_AniRender->CreateAni(L"Down", L"Linsian.bmp", 28, 30, true, 0.1f);
	m_AniRender->CreateAni(L"Vic", L"Linsian.bmp", 53, 58, false, 0.15f);
	m_AniRender->CreateAni(L"Kick", L"Linsian.bmp", 16, 17, false, 0.25f);
	m_AniRender->CreateAni(L"Punch", L"Linsian.bmp", 22, 27, false, 0.10f);
	m_AniRender->CreateAni(L"KickKick", L"Linsian.bmp", 6, 21, false, 0.2f);


	m_AniRender->StartAni(L"StandBase");

	return true;
}

void LinsianBattle::Update()
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
		pos({ 135.0f, 190.0f });
		return;
	}
	else if (false == SkillOn)
	{
		m_AniRender->StartAni(L"StandBase");
		pos({ 135.0f, 190.0f });
		return;
	}

	if (1 != BattlePlayer::CharIndex)
		return;

	if (true == SkillOn && false == SkillEnd)
	{
		if (0 == Skills[1])
		{
			pos({ 400.0f,140.0f + BattlePlayer::PlTarget[1] * 50.0f });
			m_AniRender->StartAni(L"Kick");
			SkillCount += 1.0f * bTime::DeltaTime();
			if (0.8f < SkillCount)
			{
				SkillCount = 0.0f;
				DMG = 2 * Status::BattleStatus[1]->Att;
				SkillEnd = true;
			}
		}
		else if (1== Skills[1])
		{

			pos({ 350.0f,190.0f });
			m_AniRender->StartAni(L"KickKick");

			SkillCount += 1.0f * bTime::DeltaTime();
			if (3.0f < SkillCount)
			{
				SkillCount = 0.0f;
				DMG = 10 * Status::BattleStatus[1]->Att;
				SkillEnd = true;
			}
		}
		else if (2 == Skills[1])
		{
			pos({ 350.0f,190.0f });
			m_AniRender->StartAni(L"Punch");

			SkillCount += 1.0f * bTime::DeltaTime();
			if (1.0f < SkillCount)
			{
				SkillCount = 0.0f;
				DMG = 1 * Status::BattleStatus[1]->Att;
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
			pos({ 135.0f, 190.0f });
			SkillOn = false;
			SkillEnd = false;
			BattlePlayer::CharIndex++;
		}
	}

}
