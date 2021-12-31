#include "stdafx.h"
#include "Stage02.h"
#include "GameCore.h"


Stage02::Stage02()
{
}


Stage02::~Stage02()
{
}

void Stage02::DebugRender()
{
	std::wstring Name = L"Stage02";
	TextOut(GameCore::mainWindow().DC(), 100, 100, Name.c_str(), (int)Name.size());
}
