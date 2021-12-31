#pragma once
#include <Windows.h>

class bTime
{
public:
	class bTimer
	{
	public:
		friend bTime;

	private:
		LARGE_INTEGER m_CountingTime;
		LARGE_INTEGER m_CurTime;
		LARGE_INTEGER m_PrevTime;
		double m_dDeltaTime;
		float m_DeltaTime;

	public:
		float Update();
		void Reset();

	private:
		bTimer();
		~bTimer();
	};

private:
	static bTimer MainTimer;

public:
	static float DeltaTime()
	{
		return MainTimer.m_DeltaTime;
	}

public:
	static void Update();
	static void Reset();

	bTime() {}
	~bTime() {}
};

