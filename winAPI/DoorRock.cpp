#include "DoorRock.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "GameCore.h"
#include <bWindow.h>


DoorRock::DoorRock()
{
}


DoorRock::~DoorRock()
{
}

bool DoorRock::init()
{
	m_Render = CreateRender<TransRender>(-199);

	m_Render->RenderPosMode(Pivot::LT);
	m_Render->Sprite(L"MountainRoad_Rock.bmp", 0);
	pos({ 0.0f, 0.0f });

	return true;
}
void DoorRock::Update()
{

}