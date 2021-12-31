#include "ListPlayer.h"
#include <bInput.h>
#include <bTime.h>
#include "AniRender.h"
#include "GameMenu.h"
#include "MsgWindow.h"

std::list<ListPlayer*> ListPlayer::AllListPlayer;
ListPlayer* ListPlayer::FrontPlayer;
bool ListPlayer::DontMove = false;

int ListPlayer::Money = 0;

ListPlayer::ListPlayer() : m_Front(nullptr), m_Back(nullptr), LastDir(MoveDir::DOWN), CurMap(nullptr), Speed(1.0f)
{
	AllListPlayer.push_back(this);
}


ListPlayer::~ListPlayer()
{
}

float ListPlayer::AllLen()
{
	float Sum = 0.0f;

	std::list<float>::iterator Start = MoveLen.begin();
	std::list<float>::iterator End = MoveLen.end();

	for (; Start != End; ++Start)
	{
		Sum += (*Start);
	}

	return Sum;
}

bool ListPlayer::MapPixelAllow(Pos _pos)
{
	return CurMap->m_MainRender->m_Sprite->GetPosPixel(_pos);
}

bool ListPlayer::MapPixelAllow(float _x, float _y)
{
	Pos tmp = { _x, _y };
	return MapPixelAllow(tmp);
}

void ListPlayer::MoveCheck()
{
	if (true == DontMove)
		return;

	if (true == GameMenu::GaMenu->IsUpdate() || true == MsgWindow::MsgWin->IsUpdate())
		Speed = 0.0f;

	LastPos = m_Pos;
	Pos tmpPos = m_Pos;
	

	if (nullptr == m_Front)
	{
		if (nullptr == CurMap)
			return;


		FrontPlayer = this;
		Sign = -1;

		if (true == Input::Press(L"LEFT"))
			Sign = 1;
		else if (true == Input::Press(L"RIGHT"))
			Sign = 2;
		else if (true == Input::Press(L"DOWN"))
			Sign = 3;
		else if (true == Input::Press(L"UP"))
			Sign = 4;

			if (1 == Sign)
			{
				tmpPos.X = m_Pos.X - Speed * 150.0f * bTime::DeltaTime();
				if (0 != MapPixelAllow(tmpPos.X - 16, tmpPos.Y)		&&
					0 != MapPixelAllow(tmpPos.X - 16, tmpPos.Y - 8) &&
					0 != MapPixelAllow(tmpPos.X - 16, tmpPos.Y - 16))
				{
					m_Pos = tmpPos;
					Sign = 0;
				}
			}
			else if (2 == Sign)
			{
				tmpPos.X = m_Pos.X + Speed * 150.0f * bTime::DeltaTime();
				if (0 != MapPixelAllow(tmpPos.X + 16, tmpPos.Y)		&&
					0 != MapPixelAllow(tmpPos.X + 16, tmpPos.Y - 8) &&
					0 != MapPixelAllow(tmpPos.X + 16, tmpPos.Y - 16))
				{
					m_Pos = tmpPos;
					Sign = 0;
				}
			}
			else if (3 == Sign)
			{
				tmpPos.Y = m_Pos.Y + Speed * 150.0f * bTime::DeltaTime();
				if (0 != MapPixelAllow(tmpPos.X - 16, tmpPos.Y) &&
					0 != MapPixelAllow(tmpPos.X, tmpPos.Y)		&&
					0 != MapPixelAllow(tmpPos.X + 16, tmpPos.Y))
				{
					m_Pos = tmpPos;
					Sign = 0;
				}
			}
			else if (4 == Sign)
			{
				tmpPos.Y = m_Pos.Y - Speed * 150.0f * bTime::DeltaTime();
				if (0 != MapPixelAllow(tmpPos.X - 16, tmpPos.Y - 16)&&
					0 != MapPixelAllow(tmpPos.X, tmpPos.Y - 16)		&&
					0 != MapPixelAllow(tmpPos.X + 16, tmpPos.Y - 16))
				{
					m_Pos = tmpPos;
					Sign = 0;
				}
			}
			else {
			}
		if (0 == Sign)
		{
			MoveLen.push_back(Speed * 150.0f * bTime::DeltaTime());
			MoveDirBox.push_back(m_Pos);
			SceneMgr::Inst().CurScene()->CameraPos = (m_Pos - Pos(640 * 0.5f, 352 * 0.5f));
			Sign = 5;
		}
	}
	else if (5 == FrontPlayer->Sign)
	{
		while (40.0f < m_Front->AllLen())
		{
			m_Pos = m_Front->MoveDirBox.front();
			if (nullptr != m_Back)
			{
				MoveLen.push_back(m_Front->MoveLen.front());
				MoveDirBox.push_back(m_Pos);
			}
			m_Front->MoveLen.pop_front();
			m_Front->MoveDirBox.pop_front();
		}
	}

	LastPos = m_Pos - LastPos;

	
	if (0 > LastPos.X)
	{
		m_AniRender->StartAni(L"WalkLeft");
		LastDir = MoveDir::LEFT;
	}
	else if (0 < LastPos.X)
	{
		m_AniRender->StartAni(L"WalkRight");
		LastDir = MoveDir::RIGHT;
	}
	else if (0 < LastPos.Y)
	{
		m_AniRender->StartAni(L"WalkDown");
		LastDir = MoveDir::DOWN;
	}
	else if (0 > LastPos.Y)
	{
		m_AniRender->StartAni(L"WalkUp");
		LastDir = MoveDir::UP;
	}
	else if (0 == FrontPlayer->LastPos.X && 0 == FrontPlayer->LastPos.Y)
	{
		switch (LastDir)
		{
		case MoveDir::LEFT:
			m_AniRender->StartAni(L"StandLeft");
			break;
		case MoveDir::RIGHT:
			m_AniRender->StartAni(L"StandRight");
			break;
		case MoveDir::DOWN:
			m_AniRender->StartAni(L"StandDown");
			break;
		case MoveDir::UP:
			m_AniRender->StartAni(L"StandUp");
			break;
		default:
			break;
		}
	}
}

void ListPlayer::ClearMoveList()
{
	LastDir = FrontPlayer->LastDir;
	MoveDirBox.clear();
	MoveLen.clear();
}

