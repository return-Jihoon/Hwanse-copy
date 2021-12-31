#include "BattleMenu.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "GameCore.h"
#include "Ch01AtahoBattle.h"
#include "Ch02LinsianBattle.h"
#include "Ch03SmashBattle.h"
#include <bWindow.h>

Pos _ArrowInitHori = { 264.0f, 65.0f };
Pos _ArrowInitVert = { 222.0f, 151.0f };
Pos _ArrowPlusHori = { 48.0f, 0.0f };
Pos _ArrowPlusVert = { 0.0f, 32.0f };
Pos _CurArrowHori;
Pos _CurArrowVert;

Pos _ArrowInitSub = { 430.0f, 380.0f };
Pos _ArrowPlusSub = { 0.0f, 32.0f };
Pos _CurArrowSub;

BattleMenu* BattleMenu::BtMenu = nullptr;

int BattleMenu::CharIndex = 0;

bool BattleMenu::Runaway = false;
bool BattleMenu::CurMap = false;

BattleMenu::BattleMenu()
{
}


BattleMenu::~BattleMenu()
{
}


bool BattleMenu::init()
{
	m_MenuMain = CreateRender<TransRender>(2000);
	m_MenuMain->RenderPosMode(Pivot::LT);
	m_MenuMain->Sprite(L"BattleMenuMain.bmp", 0);

	m_MenuSub = CreateRender<TransRender>(2000);
	m_MenuSub->RenderPosMode(Pivot::LT);
	m_MenuSub->Sprite(L"SubMenuAtaho0.bmp", 0);
	m_MenuSub->RenderPos({ -208.f ,0.0f });

	m_Arrow = CreateRender<TransRender>(2500);
	m_Arrow->RenderPosMode(Pivot::CENTER);
	m_Arrow->Sprite(L"Arrow.bmp", 0);
	m_Arrow->RenderPos(_ArrowInitHori);

	m_ArrowSub = CreateRender<TransRender>(2500);
	m_ArrowSub->RenderPosMode(Pivot::LT);
	m_ArrowSub->Sprite(L"Arrow.bmp", 2);
	m_ArrowSub->RenderPos(_ArrowInitVert);

	m_ArrowSubSub = CreateRender<TransRender>(2500);
	m_ArrowSubSub->RenderPosMode(Pivot::LT);
	m_ArrowSubSub->Sprite(L"Arrow.bmp", 2);
	m_ArrowSubSub->RenderPos(_ArrowInitSub);
	m_ArrowSubSub->Off();

	m_Mask = CreateRender<TransRender>(3000);
	m_Mask->RenderPosMode(Pivot::LT);
	m_Mask->Sprite(L"SubMenuMask.bmp", 0);
	m_Mask->RenderPos({ 240.f ,176.0f });



	pos({ 0.0f, 0.0f });

	return true;
}

void BattleMenu::Update()
{
	if (true == BattlePlayer::PowerUp)
	{
		m_Mask->Off();
	}

	if (0 == Status::BattleStatus[CharIndex]->Cur_Hp)
	{
		CharIndex++;
		if (3 == CharIndex)
		{
			CharIndex = 2;
		}
		return;
	}

	if (true == CurMap || false == m_ArrowSubSub->IsUpdate())
	{
		if (true == Input::Down(L"ARROW_DOWN"))
		{
			SubIndex++;
			if (true == BattlePlayer::PowerUp && 0 == MenuIndex)
			{
				if (SubIndex > 1)
					SubIndex = 0;
			}
			else
				SubIndex = 0;
			
		}

		if (true == Input::Down(L"ARROW_UP"))
		{
			SubIndex--;
			if (true == BattlePlayer::PowerUp && 0 == MenuIndex)
				{
				if (SubIndex < 0)
					SubIndex = 1;
			}
			else
				SubIndex = 0;
		}

		if (true == Input::Down(L"ARROW_RIGHT"))
		{
			MenuIndex++;
			if (MenuIndex > 2)
				MenuIndex = 0;
			SubIndex = 0;
		}

		if (true == Input::Down(L"ARROW_LEFT"))
		{
			MenuIndex--;
			if (MenuIndex < 0)
				MenuIndex = 2;
			SubIndex = 0;
		}
	}
	else
	{
		if (true == Input::Down(L"ARROW_DOWN"))
		{
			SubSubIndex++;
			if (SubSubIndex > 2)
				SubSubIndex = 0;
		}
		if (true == Input::Down(L"ARROW_UP"))
		{
			SubSubIndex--;
			if (SubSubIndex < 0)
				SubSubIndex = 2;
		}
	}


	if (true == Input::Down(L"ENTER"))
	{

		if (2 == MenuIndex && 0 == SubIndex)
		{
			Runaway = true;
			MenuIndex = 0;
			SubIndex = 0;
			Off();
			return;
		}

		if (false == CurMap && 0 == MenuIndex && true == m_ArrowSubSub->IsUpdate())
		{
			BattlePlayer::PlTarget[CharIndex] = SubSubIndex;
			BattlePlayer::Skills[CharIndex] = MenuIndex * 2 + SubIndex;
			CharIndex++;
			MenuIndex = 0;
			SubIndex = 0;
			SubSubIndex = 0;
			m_ArrowSubSub->Off();
			Off();
			return;
		}

		if (1 == MenuIndex || (true == CurMap && 0 == MenuIndex))
		{
			BattlePlayer::PlTarget[CharIndex] = -1;
			BattlePlayer::Skills[CharIndex] = MenuIndex * 2 + SubIndex;
			CharIndex++;
			MenuIndex = 0;
			SubIndex = 0;
			Off();
			return;
		}

		m_ArrowSubSub->On();
	}

	if (true == Input::Down(L"MENU"))
	{
		if (0 < CharIndex)
		{
			CharIndex--;
			MenuIndex = 0;
			SubIndex = 0;
			Off();
		}
	}


	_CurArrowHori = _ArrowInitHori;
	for (int i = 0; i < MenuIndex; i++)
		_CurArrowHori += _ArrowPlusHori;

	m_Arrow->RenderPos(_CurArrowHori);


	_CurArrowVert = _ArrowInitVert;
	for (int i = 0; i < SubIndex; i++)
		_CurArrowVert += _ArrowPlusVert;

	m_ArrowSub->RenderPos(_CurArrowVert);

	if (false == CurMap && true == m_ArrowSubSub->IsUpdate())
	{
		_CurArrowSub = _ArrowInitSub;
		for (int i = 0; i < SubSubIndex; i++)
			_CurArrowSub += _ArrowPlusSub;

		m_ArrowSubSub->RenderPos(_CurArrowSub);
	}

	if (2 == MenuIndex)
		m_MenuSub->Sprite(L"SubMenuOther.bmp", 0);
	else if (0 == CharIndex)
	{
		if (0 == MenuIndex)
			m_MenuSub->Sprite(L"SubMenuAtaho0.bmp", 0);
		else if (1 == MenuIndex)
			m_MenuSub->Sprite(L"SubMenuAtaho1.bmp", 0);
	}
	else if (1 == CharIndex)
	{
		if (0 == MenuIndex)
			m_MenuSub->Sprite(L"SubMenuLinsian0.bmp", 0);
		else if (1 == MenuIndex)
			m_MenuSub->Sprite(L"SubMenuLinsian1.bmp", 0);
	}
	else if (2 == CharIndex)
	{
		if (0 == MenuIndex)
			m_MenuSub->Sprite(L"SubMenuSmash0.bmp", 0);
		else if (1 == MenuIndex)
			m_MenuSub->Sprite(L"SubMenuSmash1.bmp", 0);
	}
}