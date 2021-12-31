#include "CircleCol.h"
#include "PointCol.h"
#include "RectCol.h"
#include <assert.h>
#include <Windows.h>
#include "RenderMgr.h"
#include "Actor.h"


CircleCol::CircleCol()
{
	m_ColType = CIRCLE;
}


CircleCol::~CircleCol()
{
}

bool CircleCol::IsCol(Collider* _other)
{
	COLTYPE CT = _other->ColType();

	switch (CT)
	{
	case Collider::RECT:
		return Geomath::RectToCircle(((RectCol*)_other)->GetColRect(), m_Circle);
	case Collider::CIRCLE:
		return Geomath::CircleToCircle(m_Circle, ((CircleCol*)_other)->m_Circle);
	case Collider::POINT:
		return Geomath::CircleToPoint(m_Circle, ((PointCol*)_other)->GetColPos());
	case Collider::MAX:
	default:
		assert(false);
		break;
	}
	return false;
}

void CircleCol::ColDataSetting()
{
	m_Circle.pos = ActorPos();
	m_Circle.size = RenderRect.size;
}

void CircleCol::DebugRender()
{
	Ellipse(RenderMgr::BackDC(),
		ActorPos().IX() - RenderRect.size.IX(),
		ActorPos().IY() - RenderRect.size.IX(),
		ActorPos().IX() + RenderRect.size.IX(),
		ActorPos().IY() + RenderRect.size.IX());
}
