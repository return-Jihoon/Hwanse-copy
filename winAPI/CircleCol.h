#pragma once
#include "Collider.h"
class CircleCol :
	public Collider
{
private:
	bCircle m_Circle;

public:
	const bCircle& GetColCircle()
	{
		return m_Circle;
	}

public:
	bool IsCol(Collider* _other) override;
	void ColDataSetting() override;
	void DebugRender() override;


public:
	CircleCol();
	~CircleCol();
};

