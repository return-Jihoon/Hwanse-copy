#include "BossBattle.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"
#include <time.h>
#include "BattlePlayer.h"

BossBattle::BossBattle() : Death(false), StandState(false), StateCount(0.0f)
{
}


BossBattle::~BossBattle()
{
}

bool BossBattle::init()
{
	char a;
	srand((unsigned int)(&a));
	m_AniRender = CreateRender <AniRender>();
	m_AniRender->RenderPosMode(Pivot::CENTER);
	m_AniRender->CreateAni(L"StandBase", L"Boss.bmp", 2, 2, false);
	m_AniRender->CreateAni(L"Damage", L"Boss.bmp", 13, 13, false);
	m_AniRender->CreateAni(L"Rush", L"Boss.bmp", 3, 12, false, 0.2f);

	m_AniRender->StartAni(L"StandBase");

	Enemy::EnTarget[3] = rand() % 3;
	return true;
}

void BossBattle::Update()
{
	if (true == Attack)
	{
		StateCount += 1.0f * bTime::DeltaTime();

		if (0.5 < StateCount)
		{
			m_AniRender->StartAni(L"Rush");
			pos({ 200.0f, 100.0f + 50.0f * Enemy::EnTarget[3] });
		}
		if (3.1 < StateCount)
		{
			StateCount = 0.0f;
			Status::BattleStatus[Enemy::EnTarget[3]]->Cur_Hp -= 50;
			pos({ 496.0f, 142.0f });
			m_AniRender->StartAni(L"StandBase");
			Attack = false;
		}
	}
	else if (true == StandState)
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