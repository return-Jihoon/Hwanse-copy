#include "GameMenu.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "RenderMgr.h"
#include "ImageRender.h"
#include "TransRender.h"
#include "GameCore.h"
#include <bWindow.h>
#include "BattlePlayer.h"

GameMenu* GameMenu::GaMenu = nullptr;

Pos ArrowInitHori = { 472.0f, 65.0f };
Pos ArrowInitVert = { 430.0f, 151.0f };
Pos ArrowPlusHori = { 48.0f, 0.0f };
Pos ArrowPlusVert = { 0.0f, 32.0f };
Pos CurArrowHori;
Pos CurArrowVert;

void GameMenu::Menu()
{
	if (nullptr == GameMenu::GaMenu)
		assert(false);

	if (true == GameMenu::GaMenu->IsUpdate())
	{
		GameMenu::GaMenu->ChIndex = 0;
		GameMenu::GaMenu->StIndex = 0;
		GameMenu::GaMenu->SbIndex = 0;
		GameMenu::GaMenu->m_ArrowSub->Off();
		GameMenu::GaMenu->Off();
		GameMenu::GaMenu->SubMenuIn = false;
		return;
	}
	GameMenu::GaMenu->On();
	return;
}


bool GameMenu::init()
{

	m_Render = CreateRender<TransRender>(2000);
	m_Render->RenderPosMode(Pivot::LT);
	m_Render->Sprite(L"GameMenu.bmp", 0);

	m_RenderChar = CreateRender<TransRender>(2000);
	m_RenderChar->RenderPosMode(Pivot::LT);
	m_RenderChar->Sprite(L"AtahoMenu.bmp", 0);

	m_RenderSub = CreateRender<TransRender>(2000);
	m_RenderSub->RenderPosMode(Pivot::LT);
	m_RenderSub->Sprite(L"SubMenu.bmp", 0);

	m_Arrow = CreateRender<TransRender>(2500);
	m_Arrow->RenderPosMode(Pivot::CENTER);
	m_Arrow->Sprite(L"Arrow.bmp", 0);
	m_Arrow->RenderPos(ArrowInitHori);
	

	m_ArrowSub = CreateRender<TransRender>(2500);
	m_ArrowSub->RenderPosMode(Pivot::LT);
	m_ArrowSub->Sprite(L"Arrow.bmp", 2);
	m_ArrowSub->RenderPos(ArrowInitVert);
	m_ArrowSub->Off();

	m_Mask = CreateRender<TransRender>(3000);
	m_Mask->RenderPosMode(Pivot::LT);
	m_Mask->Sprite(L"SubMenuMask.bmp", 0);
	m_Mask->RenderPos({ 28 * 16.0f,176.0f });



	pos({ 0.0f, 0.0f });
	m_Render->CamerEffectOff();
	m_RenderChar->CamerEffectOff();
	m_RenderSub->CamerEffectOff();
	m_Arrow->CamerEffectOff();
	m_ArrowSub->CamerEffectOff();
	m_Mask->CamerEffectOff();


	return true;
}

void GameMenu::Update()
{
	if (true == BattlePlayer::PowerUp)
	{
		m_Mask->Off();
	}

	if (true == Input::Down(L"ENTER"))
	{
		if (false == SubMenuIn)
		{
			SubMenuIn = true;
			m_ArrowSub->On();
		}
		else
		{
			if (2 == StIndex && 0 == SbIndex)
			{
				delete(Status::BattleStatus[0]);
				delete(Status::BattleStatus[1]);
				delete(Status::BattleStatus[2]);
				exit(1);
			}

			SubMenuIn = false;
			m_ArrowSub->Off();
			SbIndex = 0;
		}
	}

	if (false == SubMenuIn)
	{
		if (true == Input::Down(L"ARROW_DOWN"))
		{
			ChIndex++;
			if (ChIndex > 2)
				ChIndex = 0;
			SbIndex = 0;
		}

		if (true == Input::Down(L"ARROW_UP"))
		{
			ChIndex--;
			if (ChIndex < 0)
				ChIndex = 2;
			SbIndex = 0;
		}

		if (true == Input::Down(L"ARROW_RIGHT"))
		{
			StIndex++;
			if (StIndex > 2)
				StIndex = 0;
			SbIndex = 0;
		}

		if (true == Input::Down(L"ARROW_LEFT"))
		{
			StIndex--;
			if (StIndex < 0)
				StIndex = 2;
			SbIndex = 0;
		}
	}
	else
	{
		if (true == Input::Down(L"ARROW_DOWN"))
		{
			SbIndex++;
			if (true == BattlePlayer::PowerUp && 0 == StIndex)
			{
				if (SbIndex > 1)
					SbIndex = 0;
			}
			else
				SbIndex = 0;
		}

		if (true == Input::Down(L"ARROW_UP"))
		{
			SbIndex--;
			if (true == BattlePlayer::PowerUp && 0 == StIndex)
			{
				if (SbIndex < 0)
					SbIndex = 1;
			}
			else
				SbIndex = 0;
		}
	}




	switch (ChIndex)
	{
	case 0:
		m_RenderChar->Sprite(L"AtahoMenu.bmp", 0);
		break;
	case 1:
		m_RenderChar->Sprite(L"LinsianMenu.bmp", 0);
		break;
	case 2:
		m_RenderChar->Sprite(L"SmashMenu.bmp", 0);
		break;
	default:
		break;
	}






	CurArrowHori = ArrowInitHori;
	for (int i = 0; i < StIndex; i++)
		CurArrowHori += ArrowPlusHori;

	m_Arrow->RenderPos(CurArrowHori);

	if(false == SubMenuIn)
		m_Arrow->Sprite(L"Arrow.bmp", 0);
	else
		m_Arrow->Sprite(L"Arrow.bmp", 1);




	CurArrowVert = ArrowInitVert;
	for (int i = 0; i < SbIndex; i++)
		CurArrowVert += ArrowPlusVert;

	m_ArrowSub->RenderPos(CurArrowVert);

	if(2 == StIndex)
		m_RenderSub->Sprite(L"SubMenu.bmp", 0);
	else if (0 == ChIndex)
	{
		if (0 == StIndex)
			m_RenderSub->Sprite(L"SubMenuAtaho0.bmp", 0);
		else if (1 == StIndex)
			m_RenderSub->Sprite(L"SubMenuAtaho1.bmp", 0);
	}
	else if (1 == ChIndex)
	{
		if (0 == StIndex)
			m_RenderSub->Sprite(L"SubMenuLinsian0.bmp", 0);
		else if (1 == StIndex)
			m_RenderSub->Sprite(L"SubMenuLinsian1.bmp", 0);
	}
	else if (2 == ChIndex)
	{
		if (0 == StIndex)
			m_RenderSub->Sprite(L"SubMenuSmash0.bmp", 0);
		else if (1 == StIndex)
			m_RenderSub->Sprite(L"SubMenuSmash1.bmp", 0);
	}
}