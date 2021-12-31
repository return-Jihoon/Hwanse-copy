#include "Ch02LinsianMove.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"


LinsianMove* LinsianMove::MyPlayer2 = nullptr;

LinsianMove::LinsianMove()
{
}


LinsianMove::~LinsianMove()
{
}

bool LinsianMove::init()
{
	m_AniRender = CreateRender <AniRender>();
	m_AniRender->RenderPosMode(Pivot::CENTER);

//	m_AniRender->CreateAni(L"StartMotion", L"Linsian.bmp", 0, 0, false);

	m_AniRender->CreateAni(L"WalkLeft", L"Linsian_walk.bmp", 6, 9, true, 0.125f);
	m_AniRender->CreateAni(L"WalkRight", L"Linsian_walk.bmp", 17, 20, true, 0.125f);
	m_AniRender->CreateAni(L"WalkUp", L"Linsian_walk.bmp", 12, 15, true, 0.125f);
	m_AniRender->CreateAni(L"WalkDown", L"Linsian_walk.bmp", 1, 4, true, 0.125f);

	m_AniRender->CreateAni(L"StandLeft", L"Linsian_walk.bmp", 5, 5, false);
	m_AniRender->CreateAni(L"StandRight", L"Linsian_walk.bmp", 16, 16, false);
	m_AniRender->CreateAni(L"StandUp", L"Linsian_walk.bmp", 11, 11, false);
	m_AniRender->CreateAni(L"StandDown", L"Linsian_walk.bmp", 0, 0, false);

	m_AniRender->StartAni(L"StandDown");

	return true;
}

void LinsianMove::Update()
{
	MoveCheck();
}