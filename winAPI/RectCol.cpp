#include "CircleCol.h"
#include "PointCol.h"
#include "RectCol.h"
#include <assert.h>
#include <Windows.h>
#include "RenderMgr.h"
#include "Actor.h"


RectCol::RectCol() : m_Rect(CENTER)
{
	m_ColType = RECT;
}


RectCol::~RectCol()
{
}

bool RectCol::IsCol(Collider* _other)
{
	COLTYPE CT = _other->ColType();

	switch (CT)
	{
	case Collider::RECT:
		return Geomath::RectToRect(m_Rect, ((RectCol*)_other)->m_Rect);
	case Collider::CIRCLE:
		return Geomath::RectToCircle(m_Rect, ((CircleCol*)_other)->GetColCircle());
	case Collider::POINT:
		return Geomath::RectToPoint(m_Rect, ((PointCol*)_other)->GetColPos());
	case Collider::MAX:
	default:
		assert(false);
		break;
	}
	return false;
}

void RectCol::ColDataSetting()
{
	m_Rect.pos = ActorPos();
	m_Rect.size = RenderRect.size;
}

void RectCol::DebugRender()
{
	Rectangle(RenderMgr::BackDC(),
		ActorPos().IX() - RenderRect.size.IHX(),
		ActorPos().IY() - RenderRect.size.IHY(),
		ActorPos().IX() + RenderRect.size.IHX(),
		ActorPos().IY() + RenderRect.size.IHY());
}
