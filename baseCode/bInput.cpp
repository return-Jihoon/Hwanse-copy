#include "bInput.h"
#include <Windows.h>


Input::Key* Input::NewKey = nullptr;

std::map<std::wstring, Input::Key*>::iterator Input::KeyStart;
std::map<std::wstring, Input::Key*>::iterator Input::KeyEnd;
std::map<std::wstring, Input::Key*> Input::m_AllKey;

Input::Destructor Input::DES;

Input::Key::Key() : m_Up(false), m_UpAway(false), m_Down(false), m_Press(false)
{}

Input::Key::~Key() {}

void Input::Key::Update()
{
	if (true == IskeyCheck())
	{
		if (true == m_UpAway)
		{
			m_Up = false;
			m_UpAway = false;
			m_Down = true;
			m_Press = true;
		}
		else
		{
			m_Up = false;
			m_UpAway = false;
			m_Down = false;
			m_Press = true;
		}
	}
	else
	{
		if (true == m_Press)
		{
			m_Up = true;
			m_UpAway = true;
			m_Down = false;
			m_Press = false;
		}
		else
		{
			m_Up = false;
			m_UpAway = true;
			m_Down = false;
			m_Press = false;
		}
	}
}

bool Input::Key::IskeyCheck()
{
	for (size_t i = 0; i < m_KeyArray.size(); ++i)
	{
		if (0 == GetAsyncKeyState(m_KeyArray[i]))
		{
			return false;
		}
	}
	return true;
}




Input::Input()
{
}


Input::~Input()
{
}


void Input::InputEnd()
{
	KeyStart = m_AllKey.begin();
	KeyEnd = m_AllKey.end();

	for (; KeyStart != KeyEnd; ++KeyStart)
	{
		if (nullptr != KeyStart->second)
		{
			delete KeyStart->second;
			KeyStart->second = nullptr;
		}
	}
}

Input::Key* Input::FindKey(const wchar_t* _name)
{
	std::map<std::wstring, Key*>::iterator FindIter = m_AllKey.find(_name);

	if (FindIter == m_AllKey.end())
		return nullptr;

	return FindIter->second;
}

void Input::Update()
{
	KeyStart = m_AllKey.begin();
	KeyEnd = m_AllKey.end();

	for (; KeyStart != KeyEnd; ++KeyStart)
	{
		KeyStart->second->Update();
	}
}


bool Input::Down(const wchar_t* _name)
{
	Input::Key* Finder = FindKey(_name);

	if (nullptr == Finder)
		assert(false);

	return Finder->m_Down;
}

bool Input::Press(const wchar_t* _name)
{
	Input::Key* Finder = FindKey(_name);

	if (nullptr == Finder)
		assert(false);

	return Finder->m_Press;
}

bool Input::Up(const wchar_t* _name)
{
	Input::Key* Finder = FindKey(_name);

	if (nullptr == Finder)
		assert(false);

	return Finder->m_Up;
}

bool Input::UpAway(const wchar_t* _name)
{
	Input::Key* Finder = FindKey(_name);

	if (nullptr == Finder)
		assert(false);

	return Finder->m_UpAway;
}