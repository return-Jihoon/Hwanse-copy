#include "Ch01AtahoMove.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"

AtahoMove* AtahoMove::MyPlayer1 = nullptr;

AtahoMove::AtahoMove()
{
}


AtahoMove::~AtahoMove()
{
}

bool AtahoMove::init()
{
	m_AniRender = CreateRender <AniRender>();
	m_AniRender->RenderPosMode(Pivot::CENTER);

	m_AniRender->CreateAni(L"WalkLeft", L"Ataho_walk.bmp", 6, 9, true, 0.125f);
	m_AniRender->CreateAni(L"WalkRight", L"Ataho_walk.bmp", 17, 20, true, 0.125f);
	m_AniRender->CreateAni(L"WalkUp", L"Ataho_walk.bmp", 12, 15, true, 0.125f);
	m_AniRender->CreateAni(L"WalkDown", L"Ataho_walk.bmp", 1, 4, true, 0.125f);

	m_AniRender->CreateAni(L"StandLeft", L"Ataho_walk.bmp", 5, 5, false);
	m_AniRender->CreateAni(L"StandRight", L"Ataho_walk.bmp", 16, 16, false);
	m_AniRender->CreateAni(L"StandUp", L"Ataho_walk.bmp", 11, 11, false);
	m_AniRender->CreateAni(L"StandDown", L"Ataho_walk.bmp", 0, 0, false);

	m_AniRender->StartAni(L"StandDown");

	return true;
}

void AtahoMove::Update()
{
	MoveCheck();

}
