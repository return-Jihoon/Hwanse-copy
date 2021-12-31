#include "CircleCol.h"
#include "PointCol.h"
#include "RectCol.h"
#include <assert.h>
#include <Windows.h>
#include "RenderMgr.h"
#include "Actor.h"



PointCol::PointCol()
{
	m_ColType = CIRCLE;
}


PointCol::~PointCol()
{
}

bool PointCol::IsCol(Collider* _other)
{
	COLTYPE CT = _other->ColType();

	switch (CT)
	{
	case Collider::RECT:
		return Geomath::RectToPoint(((RectCol*)_other)->GetColRect(), m_Pos);
	case Collider::CIRCLE:
		return Geomath::CircleToPoint(((CircleCol*)_other)->GetColCircle(), m_Pos);
	case Collider::POINT:
		return m_Pos == ((PointCol*)_other)->m_Pos;
	case Collider::MAX:
	default:
		assert(false);
		break;
	}
	return false;
}

void PointCol::ColDataSetting()
{
	m_Pos = ActorPos();
}

void PointCol::DebugRender()
{
	Ellipse(RenderMgr::BackDC(),
		ActorPos().IX() - 3,
		ActorPos().IY() - 3,
		ActorPos().IX() + 3,
		ActorPos().IY() + 3);
}

