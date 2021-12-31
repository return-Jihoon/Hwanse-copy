#include "StatusBar.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "GameCore.h"
#include <bWindow.h>

StatusBar* StatusBar::SBar[3][3];
StatusBar* StatusBar::EBar[5];


StatusBar::StatusBar()
{
}


StatusBar::~StatusBar()
{
}


bool StatusBar::init()
{
	m_Render = CreateRender<TransRender>(3000);

	m_Render->RenderPosMode(Pivot::LT);
	m_Render->Sprite(L"StatusBar.bmp", 0);
	m_Render->CamerEffectOff();

	m_SubRender = CreateRender<TransRender>(2999);
	m_SubRender->RenderPosMode(Pivot::LT);
	m_SubRender->Sprite(L"StatusBarSub.bmp", 0);
	m_SubRender->RenderPos({0.0f, -8.0f});
	m_SubRender->CamerEffectOff();

	return true;
}
void StatusBar::Update()
{

}