#include "BtTownMap.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "GameCore.h"
#include <bWindow.h>



BtTownMap::BtTownMap()
{
}


BtTownMap::~BtTownMap()
{
}


bool BtTownMap::init()
{
	m_Render = CreateRender<TransRender>(-200);

	m_Render->RenderPosMode(Pivot::LT);
	// 플레이어보다 뒤에 랜더가 되어야 하므로 이렇게 만든다.
	m_Render->Sprite(L"BattleTown.bmp", 0);
	pos({ 0.0f, 0.0f });

	return true;
}
void BtTownMap::Update()
{

}