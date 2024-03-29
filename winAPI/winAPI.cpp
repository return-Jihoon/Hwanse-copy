
//#include "winAPI.h"
#include <assert.h>
#include "GameCore.h"
#include <bDebug.h>
#include <bDirect.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	bDebug::leakCheck();

	bWindow::Init(hInstance);

	GameCore::Start();
	MSG msg = GameCore::Loop();
	GameCore::End();

	return (int)msg.wParam;
}


