#include "ColliderMgr.h"
#include <assert.h>



ColliderMgr::ColliderMgr()
{
}


ColliderMgr::~ColliderMgr()
{
}

void ColliderMgr::AllColClear()
{
	ColStart = m_ColMap.begin();
	ColEnd = m_ColMap.end();

	for (; ColStart != ColEnd; ++ColStart)
	{
		ColStart->second.clear();
	}
}


void ColliderMgr::DebugRender()
{
	ColStart = m_ColMap.begin();
	ColEnd = m_ColMap.end();

	for (; ColStart != ColEnd; ++ColStart)
	{
		ColSecondStart = ColStart->second.begin();
		ColSecondEnd = ColStart->second.end();

		for (; ColSecondStart != ColSecondEnd; ++ColSecondStart)
		{
			if (false == (*ColSecondStart)->IsUpdate())
			{
				continue;
			}

			(*ColSecondStart)->DebugRender();
		}
	}
}

void ColliderMgr::Release()
{
	ColStart = m_ColMap.begin();
	ColEnd = m_ColMap.end();
	for (; ColStart != ColEnd; ++ColStart)
	{
		ColSecondStart = ColStart->second.begin();
		ColSecondEnd = ColStart->second.end();

		for (; ColSecondStart != ColSecondEnd; )
		{
			if (false == (*ColSecondStart)->IsDeath())
			{
				++ColSecondStart;
				continue;
			}

			ColSecondStart = ColStart->second.erase(ColSecondStart);
		}
	}
}

bool ColliderMgr::IsLink(const wchar_t* _left, const wchar_t* _right)
{
	std::wstring Left = _left;
	std::wstring Right = _right;

	return (m_LinkMap.end() == m_LinkMap.find(Left + Right)) &&
		   (m_LinkMap.end() == m_LinkMap.find(Right + Left));
}

void ColliderMgr::Link(const wchar_t* _left, const wchar_t* _right)
{
	if (false == IsLink(_left, _right))
	{
		assert(false);
	}

	std::map<std::wstring, std::list<Collider*>>::iterator ColGroupIter = m_ColMap.find(_left);
	if (m_ColMap.end() == ColGroupIter)
	{
		m_ColMap.insert(std::map<std::wstring, std::list<Collider*>>::value_type(_left, std::list<Collider*>()));
	}

	ColGroupIter = m_ColMap.find(_right);
	if (m_ColMap.end() == ColGroupIter)
	{
		m_ColMap.insert(std::map<std::wstring, std::list<Collider*>>::value_type(_right, std::list<Collider*>()));
	}

	LinkData Data;
	Data.Left = _left;
	Data.Right = _right;
	m_LinkMap.insert(std::map<std::wstring, LinkData>::value_type(Data.Left + Data.Right, Data));
}

void ColliderMgr::PushCol(Collider* _col)
{
	std::map<std::wstring, std::list<Collider*>>::iterator ColGroupIter = m_ColMap.find(_col->GroupName()); if (m_ColMap.end() == ColGroupIter)
	{
		m_ColMap.insert(std::map<std::wstring, std::list<Collider*>>::value_type(_col->GroupName(), std::list<Collider*>()));
		ColGroupIter = m_ColMap.find(_col->GroupName());
	}

	ColGroupIter->second.push_back(_col);
}

void ColliderMgr::Collision()
{
	LinkStart = m_LinkMap.begin();
	LinkEnd = m_LinkMap.end();

	for (; LinkStart != LinkEnd; ++LinkStart)
	{
		if (LinkStart->second.Left != LinkStart->second.Right)
		{
			GroupCol(LinkStart->second.Left.c_str(), LinkStart->second.Right.c_str());
		}
		else {

		}
	}
}

void ColliderMgr::GroupCol(const wchar_t* _left, const wchar_t* _right)
{
	LeftGroup = m_ColMap.find(_left);
	RightGroup = m_ColMap.find(_right);

	if (LeftGroup == m_ColMap.end())
	{
		assert(false);
	}

	if (RightGroup == m_ColMap.end())
	{
		assert(false);
	}

	if (0 >= LeftGroup->second.size())
	{
		return;
	}

	if (0 >= RightGroup->second.size())
	{
		return;
	}

	LeftStart = LeftGroup->second.begin();
	LeftEnd = LeftGroup->second.end();

	for (; LeftStart != LeftEnd; ++LeftStart)
	{
		if (false == (*LeftStart)->IsUpdate())
		{
			continue;
		}

		(*LeftStart)->ColDataSetting();
		RightStart = RightGroup->second.begin();
		RightEnd = RightGroup->second.end();

		for (; RightStart != RightEnd; ++RightStart)
		{
			if (false == (*RightStart)->IsUpdate())
			{
				continue;
			}

			(*RightStart)->ColDataSetting();

			(*LeftStart)->ColCheck((*RightStart));

		}
	}
}

void ColliderMgr::GroupCol(const wchar_t* _this)
{

}