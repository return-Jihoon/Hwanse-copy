#pragma once
#include "LogicDef.h"

#include <string>

class baseObj
{
private:
	std::wstring m_Name;

	bool m_IsUpdate;
	bool m_IsDeath;

public:
	virtual inline bool IsUpdate()
	{
		return m_IsUpdate && false == m_IsDeath;
	}

	virtual inline bool IsDeath()
	{
		return m_IsDeath;
	}

	virtual inline void On() 
	{
		m_IsUpdate = true;
	}

	virtual void Off() 
	{
		m_IsUpdate = false;
	}
	virtual void Death() 
	{
		m_IsDeath = true;
	}
	virtual void Live()
	{
		m_IsDeath = false;
	}

public:
	const wchar_t* PtrName() const
	{
		return m_Name.c_str();
	}

	std::wstring Name()
	{
		return m_Name;
	}

	void Name(const wchar_t* _name)
	{
		m_Name = _name;
	}

public:
	baseObj();
	virtual ~baseObj() = 0;
};

