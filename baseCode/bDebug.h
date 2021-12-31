#pragma once
#include <crtdbg.h>

class bDebug
{
public:
	static void leakCheck()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

public:
	bDebug() {}
	~bDebug() {}
};