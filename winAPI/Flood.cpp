#include "Flood.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "AniRender.h"
#include "GameCore.h"
#include <bWindow.h>


Flood::Flood()
{
}


Flood::~Flood()
{
}

bool Flood::init()
{
	m_Render = CreateRender <AniRender>(-201);
	m_Render->RenderPosMode(Pivot::LT);

	m_Render->CreateAni(L"FloodFlow", L"Flood.bmp", 0, 2, true, 0.2f);
	pos({ 479.0f, 0.0f });


	m_Render->StartAni(L"FloodFlow");

	return true;
}
void Flood::Update()
{

}