#include "BtMtMap.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "GameCore.h"
#include <bWindow.h>



BtMtMap::BtMtMap()
{
}


BtMtMap::~BtMtMap()
{
}


bool BtMtMap::init()
{
	m_Render = CreateRender<TransRender>(-200);

	m_Render->RenderPosMode(Pivot::LT);
	// �÷��̾�� �ڿ� ������ �Ǿ�� �ϹǷ� �̷��� �����.
	m_Render->Sprite(L"BattleMt.bmp", 0);
	pos({ 0.0f, 0.0f });

	return true;
}
void BtMtMap::Update()
{

}