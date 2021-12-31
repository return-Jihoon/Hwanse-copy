#include "BattleMonkey.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"

BattleMonkey::BattleMonkey() : Death(false), StandState(false), StateCount(0.0f)
{
}


BattleMonkey::~BattleMonkey()
{
}

bool BattleMonkey::init()
{
	m_AniRender = CreateRender <AniRender>();
	m_AniRender->RenderPosMode(Pivot::CENTER);
	m_AniRender->CreateAni(L"StandBase", L"Monkey.bmp", 10, 10, false);
	m_AniRender->CreateAni(L"Damage", L"Monkey.bmp", 12, 12, false);

	m_AniRender->StartAni(L"StandBase");

	return true;
}

void BattleMonkey::Update()
{
	if (true == StandState)
	{
		m_AniRender->StartAni(L"Damage");
		StateCount += 1.0f * bTime::DeltaTime();
		if (0.5 < StateCount)
		{
			StandState = false;
			StateCount = 0.0f;
			if (true == Death)
				Off();
		}
	}
	else
		m_AniRender->StartAni(L"StandBase");
}