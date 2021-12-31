#pragma once
#include "Collider.h"
class PointCol :
	public Collider
{
private:
	Pos m_Pos;

public:
	const Pos& GetColPos()
	{
		return m_Pos;
	}

public:
	bool IsCol(Collider* _other) override;
	void ColDataSetting() override;
	void DebugRender() override;


public:
	PointCol();
	~PointCol();
};

