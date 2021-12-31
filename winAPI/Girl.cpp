#include "Girl.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"
#include "GameCore.h"
#include <bWindow.h>

Girl::Girl()
{
}


Girl::~Girl()
{
}

bool Girl::Running = false;


bool Girl::init()
{
	m_Render = CreateRender<TransRender>();

	m_Render->RenderPosMode(Pivot::B);

	m_Render->Sprite(L"npcs.bmp", 0);


	pos({ 0.0f, 0.0f });


	return true;
}

void Girl::Update()
{
	if (true == Running)
	{
		Off();
	}
}