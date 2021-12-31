#include "ActorSub.h"
#include <assert.h>
#include "SceneMgr.h"
#include "Scene.h"
#include "Actor.h"



ActorSub::ActorSub() : m_IsCustomSize(false), m_IsCameraEffect(true)
{
}


ActorSub::~ActorSub()
{
}


Pos ActorSub::ActorPos()
{
	if (false == m_IsCameraEffect)
	{
		return m_Actor->pos();
	}
	else
	{
		return m_Actor->pos() - SceneMgr::Inst().CurScene()->CameraPos;
	}
}

bool ActorSub::IsUpdate()
{
	return baseObj::IsUpdate() && m_Actor->IsUpdate();
}

bool ActorSub::IsDeath()
{
	return baseObj::IsDeath() || m_Actor->IsDeath();
}

Pos ActorSub::CalPivotPos()
{
	Pos PivotSize = RenderRect.size * -0.5f;

	switch (m_Pivot)
	{
	case LT:
		PivotSize.Y -= PivotSize.Y;
		PivotSize.X -= PivotSize.X;
		return ActorPos() + PivotSize;
		break;
	case T:
		break;
	case RT:
		break;
	case R:
		PivotSize.X += PivotSize.X;
		return ActorPos() + PivotSize;
	case RB:
		PivotSize.Y += PivotSize.Y;
		PivotSize.X += PivotSize.X;
		return ActorPos() + PivotSize;
		break;
	case B:
		PivotSize.Y += PivotSize.Y;
		return ActorPos() + PivotSize;
	case LB:
		PivotSize.Y += PivotSize.Y;
		PivotSize.X -= PivotSize.X;
		return ActorPos() + PivotSize;
	case L:
		PivotSize.X -= PivotSize.X;
		return ActorPos() + PivotSize;
	case CENTER:
		return ActorPos() + PivotSize;
	case CUSTOM:
		return ActorPos() + RenderRect.pos;
	default:
		assert(false);
		break;
	}

	assert(false);
	return Pos::ZERO;
}