#include "Ch01AtahoBattle.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"

AtahoBattle* AtahoBattle::BtPlayer1;

AtahoBattle::AtahoBattle()
{
}


AtahoBattle::~AtahoBattle()
{
}

bool AtahoBattle::init()
{
	m_AniRender = CreateRender <AniRender>();
	m_AniRender->RenderPosMode(Pivot::CENTER);

	m_AniRender->CreateAni(L"StandBase", L"Ataho.bmp", 0, 0, false);
	m_AniRender->CreateAni(L"Damage", L"Ataho.bmp", 1, 1, false);
	m_AniRender->CreateAni(L"Down", L"Ataho.bmp", 2, 4, true, 0.1f);
	m_AniRender->CreateAni(L"Vic", L"Ataho.bmp", 41, 46, false, 0.25f);
	m_AniRender->CreateAni(L"Kick", L"Ataho.bmp", 13, 16, false, 0.15f);
	m_AniRender->CreateAni(L"Rush", L"AtahoSkill.bmp", 0, 19, false, 0.10f);
	m_AniRender->CreateAni(L"Shout", L"Ataho.bmp", 37, 40, false, 0.2f);


	m_AniRender->StartAni(L"StandBase");
	
	return true;
}

void AtahoBattle::Update()
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
		pos({ 150.0f, 140.0f });
		return;
	}
	else if (false == SkillOn)
	{
		m_AniRender->StartAni(L"StandBase");
		pos({ 150.0f, 140.0f });
		return;
	}

	if (0 != BattlePlayer::CharIndex)
		return;
	
	if (true == SkillOn && false == SkillEnd)
	{
		if (0 == Skills[0])
		{
			pos({ 400.0f,140.0f + BattlePlayer::PlTarget[0] * 50.0f });
			m_AniRender->StartAni(L"Kick");
			SkillCount += 1.0f * bTime::DeltaTime();
			if (1.0f < SkillCount)
			{
				SkillCount = 0.0f;
				DMG = 2 * Status::BattleStatus[0]->Att;
				SkillEnd = true;
			}
		}
		else if (1 == Skills[0])
		{

			pos({ 350.0f,190.0f });
			m_AniRender->StartAni(L"Rush");

			SkillCount += 1.0f * bTime::DeltaTime();
			if (2.0f < SkillCount)
			{
				SkillCount = 0.0f;
				DMG = 10 * Status::BattleStatus[0]->Att;
				SkillEnd = true;
			}
		}
		else if (2 == Skills[0])
		{
			pos({ 350.0f,190.0f });
			m_AniRender->StartAni(L"Shout");

			SkillCount += 1.0f * bTime::DeltaTime();
			if (1.2f < SkillCount)
			{
				SkillCount = 0.0f;
				DMG = 1 * Status::BattleStatus[0]->Att;
				SkillEnd = true;
			}
		}
	}
	else if(false == Victory && true == SkillEnd)
	{
		SkillCount += 1.0f * bTime::DeltaTime();
		if (0.5f < SkillCount)
		{
			SkillCount = 0.0f;
			m_AniRender->StartAni(L"StandBase");
			pos({ 150.0f, 140.0f });
			SkillOn = false;
			SkillEnd = false;
			BattlePlayer::CharIndex++;
		}
	}
}
