#include "OldMan.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"
#include "GameCore.h"
#include <bWindow.h>

OldMan::OldMan()
{
}


OldMan::~OldMan()
{
}

bool OldMan::Running = false;

float count1 = 0.0f;

bool OldMan::init()
{
	m_Render = CreateRender<TransRender>();

	m_Render->RenderPosMode(Pivot::B);

	m_Render->Sprite(L"npcs.bmp", 1);


	pos({ 0.0f, 0.0f });


	return true;
}

void OldMan::Update()
{
	if (true == Running)
	{
		count1 += 1.0f * bTime::DeltaTime();
		if (count1 > 1.0f)
			Off();
	}
}