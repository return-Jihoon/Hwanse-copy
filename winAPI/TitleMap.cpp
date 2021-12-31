#include "TitleMap.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "GameCore.h"
#include <bWindow.h>



TitleMap::TitleMap()
{
}


TitleMap::~TitleMap()
{
}


bool TitleMap::init()
{
	m_Render = CreateRender<TransRender>(-100);

	m_Render->RenderPosMode(Pivot::CENTER);
	// 플레이어보다 뒤에 랜더가 되어야 하므로 이렇게 만든다.
	m_Render->Sprite(L"Title.bmp", 0);
	pos({ 320.0f, 240.0f });


	return true;
}
void TitleMap::Update()
{

}