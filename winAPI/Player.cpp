#include "Player.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "Bullet.h"
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"
#include "CircleCol.h"

Player* Player::MyPlayer = nullptr;

Player::Player()
{
}


Player::~Player()
{
}

bool Player::init()
{
	m_AniRender = CreateRender <AniRender>();
	m_AniRender->RenderPosMode(Pivot::CENTER);

	//m_AniRender->CreateAni(L"StartMotion", L"Ataho.bmp", 0, 0, false);

	m_AniRender->CreateAni(L"WalkLeft", L"Ataho_walk.bmp", 6, 9, true, 0.15f);
	m_AniRender->CreateAni(L"WalkRight", L"Ataho_walk.bmp", 17, 20, true, 0.15f);
	m_AniRender->CreateAni(L"WalkUp", L"Ataho_walk.bmp", 12, 15, true, 0.15f);
	m_AniRender->CreateAni(L"WalkDown", L"Ataho_walk.bmp", 1, 4, true, 0.15f);

	m_AniRender->CreateAni(L"StandLeft", L"Ataho_walk.bmp", 5, 5, false);
	m_AniRender->CreateAni(L"StandRight", L"Ataho_walk.bmp", 16, 16, false);
	m_AniRender->CreateAni(L"StandUp", L"Ataho_walk.bmp", 11, 11, false);
	m_AniRender->CreateAni(L"StandDown", L"Ataho_walk.bmp", 0, 0, false);

	m_AniRender->StartAni(L"StandDown");

	return true;
}

void Player::Update()
{
	MoveCheck();

}
