#pragma once
#include "ActorSub.h"
#include <bGeo.h>
#include <set>

class Actor;

class Collider : public ActorSub
{
public:
	enum COLTYPE
	{
		RECT,
		CIRCLE,
		POINT,
		MAX
	};

protected:
	std::wstring m_GroupName;
	COLTYPE m_ColType;
	std::set<Collider*>::iterator FindIter;
	std::set<Collider*> m_ColOther;

public:
	COLTYPE ColType()
	{
		return m_ColType;
	}

	const wchar_t* GroupName()
	{
		return m_GroupName.c_str();
	}

public:
	bool Init(const wchar_t* _groupName, Actor* _actor, pSize _size = { 10,10 });

public:
	virtual void DebugRender() = 0;
	void PushColMgr();
	void ColCheck(Collider* _other);

	virtual void ColDataSetting() = 0;

	virtual bool IsCol(Collider* _other) = 0;

public:
	Collider();
	~Collider();
};

