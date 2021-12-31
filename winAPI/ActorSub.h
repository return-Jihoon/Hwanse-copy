#pragma once
#include "baseObj.h"
#include <bGeo.h>

class Actor;

class ActorSub : public baseObj
{
public:
	bool m_IsCameraEffect;

public:
	void CameraEffectOn()
	{
		m_IsCameraEffect = true;
	}

	void CamerEffectOff()
	{
		m_IsCameraEffect = false;
	}

protected:
	Actor* m_Actor;
	bool m_IsCustomSize;
	Pivot m_Pivot;
	bRect RenderRect;

public:
	inline bool IsUpdate() override;
	inline bool IsDeath() override;

public:
	Pos ActorPos();

	Actor* ThisActor()
	{
		return m_Actor;
	}

public:
	Pos ThisRenderPos()
	{
		return RenderRect.pos;
	}

	void RenderSize(const pSize& _RenderSize)
	{
		RenderRect.size = _RenderSize;
		m_IsCustomSize = true;
	}

	void RenderPos(const Pos& _RenderPivot)
	{
		RenderRect.pos = _RenderPivot;
		m_Pivot = CUSTOM;
	}

	void RenderPosMode(Pivot _pivot)
	{
		m_Pivot = _pivot;
	}

	Pos CalPivotPos();


protected:
	ActorSub();
	virtual ~ActorSub() = 0;
};

