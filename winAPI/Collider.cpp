#include "Collider.h"
#include "ColliderMgr.h"
#include <assert.h>
#include "Actor.h"


Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::PushColMgr()
{
	ColliderMgr::Inst().PushCol(this);
}

bool Collider::Init(const wchar_t* _groupName, Actor* _actor, pSize _size)
{
	m_Actor = _actor;
	m_GroupName = _groupName;
	m_Pivot = CENTER;
	RenderRect.size = _size;
	PushColMgr();
	return true;
}

void Collider::ColCheck(Collider* _other)
{
	if (this == _other)
		assert(false);

	if (true == IsCol(_other))
	{
		FindIter = m_ColOther.find(_other);

		if (FindIter == m_ColOther.end())
		{
			m_ColOther.insert(_other);
			m_Actor->ColEnter(this, _other);
		}
		else {
			m_Actor->ColStay(this, _other);
		}
	}
	else
	{
		FindIter = m_ColOther.find(_other);
		if (FindIter != m_ColOther.end())
		{
			m_ColOther.erase(_other);
			m_Actor->ColExit(this, _other);
		}
	}
}