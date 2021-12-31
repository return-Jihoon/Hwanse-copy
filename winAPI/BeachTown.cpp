#include "BeachTown.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "GameCore.h"
#include <bWindow.h>



BeachTown::BeachTown()
{
}


BeachTown::~BeachTown()
{
}


bool BeachTown::init()
{
	m_MainRender = CreateRender<TransRender>(-100);
	m_MainRender->RenderPosMode(Pivot::LT);
	m_MainRender->Sprite(L"Town_mask.bmp", 0);

	m_Render = CreateRender<TransRender>(-200);
	m_Render->RenderPosMode(Pivot::LT);
	m_Render->Sprite(L"Town.bmp", 0);
	pos({ 0.0f, 0.0f });

	m_Render_obj1 = CreateRender<TransRender>(200);
	m_Render_obj1->RenderPosMode(Pivot::LT);
	m_Render_obj1->Sprite(L"Town_1.bmp", 0);

	return true;
}
void BeachTown::Update()
{

}