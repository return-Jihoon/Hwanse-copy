#pragma once

#include <map>
#include <string>
#include <Windows.h>

#include "bGeo.h"

class bWindow
{
private:
	static int g_WinCount;
	static HINSTANCE m_MainHInst;
	static std::map<std::wstring, WNDCLASSEXW> g_WinClassMap;
	static std::map<std::wstring, bWindow*> g_WinMap;

public:
	static int WinCount()
	{
		return g_WinCount;
	}

public: 
	static void Init(const HINSTANCE& _mainHInst);
	static LRESULT CALLBACK DEFMSG(HWND _HWnd, UINT _Msg, WPARAM _W, LPARAM _L);

public:
	static bool bCreateWindowClass(const WNDCLASSEXW& wcex);
	static WNDCLASSEXW bFindWindowClass(const wchar_t* _name);

	static bWindow* bCreateWindow(const wchar_t* _titleName, bool _isShow = true);
	static bWindow* bCreateWindow(const wchar_t* _windowName, const wchar_t* _titleName, bool _isShow = true);
	static bWindow* bCreateWindow(const wchar_t* _className, const wchar_t* _windowName, const wchar_t* _titleName, bool _isShow = true);
	static bool bDestroyWindow(HWND _hwnd);
	static void AllWindowUpdate();

private:
	HWND m_HWnd;
	HDC m_HDC;

	int m_Style;
	int m_Menu;

	pSize m_WinSize;

	Pos m_MousePos;
	Pos m_PrevMousePos;

public:
	HWND WND() const
	{
		return m_HWnd;
	}

	HDC DC() const
	{
		return m_HDC;
	}

private:
	bool Create(const wchar_t* _class, const wchar_t* _title);

public:
	Pos MousePos();
	Pos MouseDir();

	pSize Size();
	void Size(int _x, int _y);
	void Pos(int _x, int _y);
	void SizeAndPos(int _sx, int _sy, int _px, int _py);

	void Show();
	void Hide();

	void Update();


public:
	bWindow() : m_HWnd(nullptr), m_HDC(nullptr) {}
	~bWindow() {}
};

