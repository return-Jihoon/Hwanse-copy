#include "Boss.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"
#include "GameCore.h"
#include <bWindow.h>

Boss::Boss()
{
}


Boss::~Boss()
{
}

bool Boss::Running = false;

float countB = 0.0f;

bool Boss::init()
{
	m_Render = CreateRender<TransRender>(50);

	m_Render->RenderPosMode(Pivot::B);

	m_Render->Sprite(L"Boss.bmp", 0);


	pos({ 640.0f, 490.0f });


	return true;
}

void Boss::Update()
{
	if (true == Running)
	{
		countB += 1.0f * bTime::DeltaTime();
		if (0.1f < countB)
		{
			m_Render->Sprite(L"Boss.bmp", 1);
			Running = false;
		}
	}
}