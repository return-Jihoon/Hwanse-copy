#include "Monkey.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"
#include "GameCore.h"
#include <bWindow.h>

bool Monkey::Running = false;

float count = 0.0f;

Monkey::Monkey()
{
}


Monkey::~Monkey()
{
}


bool Monkey::init()
{
	m_Render = CreateRender<AniRender>();

	m_Render->RenderPosMode(Pivot::B);

	m_Render->CreateAni(L"Stand", L"Monkey.bmp", 0, 0, false);
	m_Render->CreateAni(L"Dance1", L"Monkey.bmp", 1, 8, true, 0.25f);
	m_Render->CreateAni(L"Dance2", L"Monkey.bmp", 2, 9, true, 0.075f);
	m_Render->CreateAni(L"Run", L"Monkey.bmp", 13, 14, true, 0.1f);


	pos({ 0.0f, 0.0f });


	return true;
}
void Monkey::Update()
{
	if (true != Running)
	{
		if (200.0f > pos().Y)
			m_Render->StartAni(L"Stand");
		else if (1150.0f > pos().X)
			m_Render->StartAni(L"Dance1");
		else
			m_Render->StartAni(L"Dance2");
	}
	else
	{
		m_Render->StartAni(L"Run");
		count += 1.0f * bTime::DeltaTime();
		if (count > 3.5f)
		{
			Pos MovePos = { 0.0f, 300.0f * bTime::DeltaTime() };
			pos(pos() + MovePos);
		}
	}	
	if (450.0f < pos().Y)
		Off();
}