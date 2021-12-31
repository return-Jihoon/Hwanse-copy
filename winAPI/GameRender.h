#pragma once
#include "ActorSub.h"
#include <Windows.h>
class RenderMgr;
class Actor;

class GameRender : public ActorSub
{
private:
	friend RenderMgr;
	friend Actor;

private:
	int m_Order;
	int m_Alpha;

protected:
	BLENDFUNCTION BF;

public:
	int GetAlpha()
	{
		return BF.SourceConstantAlpha;
	}

	void SetAlpha(int _alpha)
	{
		BF.SourceConstantAlpha = _alpha;
	}

public:
	inline int Order() const
	{
		return m_Order;
	}

	inline void Order(int _value)
	{
		m_Order = _value;
	}

private:
	void PushRenderMgr();

public:
	virtual void Init(int _value, Actor* _actor);
	virtual void Render() = 0;

public:
	GameRender();
	~GameRender();
};

