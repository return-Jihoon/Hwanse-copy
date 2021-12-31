#include "bTime.h"


bTime::bTimer::bTimer() : m_DeltaTime(0.0f)
{
	Reset();
}

bTime::bTimer::~bTimer()
{

}

float bTime::bTimer::Update()
{
	QueryPerformanceCounter(&m_CurTime);

	m_dDeltaTime = ((double)m_CurTime.QuadPart - (double)m_PrevTime.QuadPart) / (double)m_CountingTime.QuadPart;
	m_DeltaTime = (float)m_dDeltaTime;
	m_PrevTime = m_CurTime;

	return m_DeltaTime;
}
void bTime::bTimer::Reset() 
{
	QueryPerformanceFrequency(&m_CountingTime);

	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_PrevTime);
}

bTime::bTimer bTime::MainTimer;

void bTime::Update()
{
	MainTimer.Update();
}
void bTime::Reset()
{
	MainTimer.Reset();
}