#pragma once
#include "Collider.h"
class RectCol :
	public Collider
{
private:
	bRect m_Rect;

public:
	const bCircle& GetColRect()
	{
		return m_Rect;
	}

public:
	bool IsCol(Collider* _other) override;
	void ColDataSetting() override;
	void DebugRender() override;

public:
	RectCol();
	~RectCol();
};

