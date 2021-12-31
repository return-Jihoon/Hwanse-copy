#pragma once
#include <bWindow.h>

class Scene;
class GameCore
{
public:
	friend int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPWSTR    lpCmdLine,
		_In_ int       nCmdShow);

private:
	static bWindow* g_MainWindow;

public:
	static bWindow& mainWindow();

private:
	static void Run();

	static void Start();
	static MSG Loop();
	static void End();



public:
	GameCore();
	~GameCore();
};

