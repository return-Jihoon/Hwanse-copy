#include "Monster.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"
#include "CircleCol.h"
#include "RectCol.h"
#include "PointCol.h"


Monster::Monster()
{
}


Monster::~Monster()
{
}

bool Monster::init()
{
	m_AniRender = CreateRender<AniRender>();
	m_AniRender->RenderPosMode(Pivot::CENTER);

	m_AniRender->CreateAni(L"StartMotion", L"Ataho.bmp", 0, 20, false, 0.1f);
	m_AniRender->CreateAni(L"Run", L"Ataho.bmp", 50, 62, true);

	m_AniRender->StartAni(L"StartMotion");

	RectCol* P = CreateCol<RectCol>(L"Monster", { 100,100 });

	return true;
}

void Monster::Update()
{

}