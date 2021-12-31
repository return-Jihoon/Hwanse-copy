#include "bWindow.h"
#include <assert.h>


int bWindow::g_WinCount = 0;
HINSTANCE bWindow::m_MainHInst;
std::map<std::wstring, WNDCLASSEXW> bWindow::g_WinClassMap;
std::map<std::wstring, bWindow*> bWindow::g_WinMap;




LRESULT CALLBACK bWindow::DEFMSG(HWND _HWnd, UINT _Msg, WPARAM _W, LPARAM _L)
{
	switch (_Msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(_HWnd, &ps);
		EndPaint(_HWnd, &ps);
		break;
	}
	case WM_DESTROY:
		bDestroyWindow(_HWnd);
		break;
	default:
		return DefWindowProc(_HWnd, _Msg, _W, _L);
	}
	return 0;
}

void bWindow::Init(const HINSTANCE& _mainHInst)
{
	m_MainHInst = _mainHInst;

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DEFMSG;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_MainHInst;
	wcex.hIcon = 0;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AR22API));
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;// MAKEINTRESOURCEW(IDC_AR22API);
	wcex.lpszClassName = L"Default"; // L"AR22API"
	wcex.hIconSm = 0;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	bCreateWindowClass(wcex);
}


bool bWindow::bCreateWindowClass(const WNDCLASSEXW& wcex)
{
	if (0 == RegisterClassExW(&wcex))
	{
		assert(false);
		return false;
	}

	g_WinClassMap.insert(std::map<std::wstring, WNDCLASSEXW>::value_type(wcex.lpszClassName, wcex));

	return true;
}

WNDCLASSEXW bWindow::bFindWindowClass(const wchar_t* _name)
{
	std::map<std::wstring, WNDCLASSEXW>::iterator findIter = g_WinClassMap.find(_name);

	if (g_WinClassMap.end() == findIter)
	{
		WNDCLASSEXW W;
		W.hInstance = 0;
		return W;
	}
	return findIter->second;
}

bool bWindow::bDestroyWindow(HWND _hwnd)
{
	std::map<std::wstring, bWindow*>::iterator Loop = g_WinMap.begin();
	std::map<std::wstring, bWindow*>::iterator End = g_WinMap.end();

	for (; Loop != End; ++Loop)
	{
		if (Loop->second->m_HWnd == _hwnd)
		{
			if (nullptr != Loop->second)
			{
				delete Loop->second;
				Loop->second = nullptr;
			}
			g_WinMap.erase(Loop);
			--g_WinCount;
			return true;
		}
	}
	return true;
}

bWindow* bWindow::bCreateWindow(const wchar_t* _titleName, bool _isShow)
{
	return bCreateWindow(L"Default", _titleName, _titleName, _isShow);
}

bWindow* bWindow::bCreateWindow(const wchar_t* _windowName, const wchar_t* _titleName, bool _isShow)
{
	return bCreateWindow(L"Default", _windowName, _titleName, _isShow);
}

bWindow* bWindow::bCreateWindow(const wchar_t* _className, const wchar_t* _windowName, const wchar_t* _titleName, bool _isShow)
{
	if (g_WinMap.end() != g_WinMap.find(_windowName))
	{
		assert(false);
		return nullptr;
	}

	bWindow* newWindow = new bWindow();

	if (false == newWindow->Create(_className, _titleName))
	{
		assert(false);
		delete newWindow;
		return nullptr;
	}

	g_WinMap.insert(std::map<std::wstring, bWindow*>::value_type(_windowName, newWindow));

	if (true == _isShow)
		newWindow->Show();

	++g_WinCount;

	return newWindow;
}

void bWindow::AllWindowUpdate()
{
	std::map<std::wstring, bWindow*>::iterator StartIter = g_WinMap.begin();
	std::map<std::wstring, bWindow*>::iterator EndIter = g_WinMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter->second->Update();
	}
}

bool bWindow::Create(const wchar_t* _class, const wchar_t* _title)
{
	WNDCLASSEXW FindClass = bFindWindowClass(_class);

	if (0 == FindClass.hInstance)
		assert(false);

	m_Style = WS_OVERLAPPEDWINDOW;
	m_Menu = TRUE;

	if (nullptr == FindClass.lpszMenuName)
		m_Menu = FALSE;


	m_HWnd = CreateWindowW(_class, _title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_MainHInst, nullptr);

	if (nullptr == m_HWnd)
	{
		assert(false);
		return false;
	}

	m_HDC = GetDC(m_HWnd);

	if (nullptr == m_HDC)
	{
		assert(false);
		return false;
	}

	return true;
}

pSize bWindow::Size()
{
	return m_WinSize;
}

void bWindow::Size(int _x, int _y)
{
	m_WinSize.X = (float)_x;
	m_WinSize.Y = (float)_y;

	RECT Rc = { 0, 0, _x,_y };
	AdjustWindowRect(&Rc, m_Style, m_Menu);
	SetWindowPos(m_HWnd, 0, 0, 0, Rc.right - Rc.left, Rc.bottom - Rc.top,/* SWP_NOSIZE | */SWP_NOZORDER);
}
void bWindow::Pos(int _x, int _y)
{
	SetWindowPos(m_HWnd, 0 ,_x, _y, 0, 0, /*SWP_NOSIZE | */SWP_NOZORDER);
}
void bWindow::SizeAndPos(int _sx, int _sy, int _px, int _py)
{
	Pos(_px, _py);
	Size(_sx, _sy);
}

void bWindow::Show()
{
	ShowWindow(m_HWnd, SW_SHOW);
	UpdateWindow(m_HWnd);
}

void bWindow::Hide()
{
	ShowWindow(m_HWnd, SW_HIDE);
	UpdateWindow(m_HWnd);
}

void bWindow::Update()
{
	m_PrevMousePos = m_MousePos;
	POINT PT;
	GetCursorPos(&PT);
	ScreenToClient(m_HWnd, &PT);
	m_MousePos = { (float)PT.x, (float)PT.y };
}

Pos bWindow::MousePos()
{
	return m_MousePos;
}

Pos bWindow::MouseDir()
{
	return m_MousePos - m_PrevMousePos;
}