#include "Bullet.h"
#include <bTime.h>
#include "CircleCol.h"
#include "RectCol.h"
#include "PointCol.h"


Bullet::Bullet() : m_DeathTime(1000.0f)
{
}


Bullet::~Bullet()
{

	// 맵이라는 것을 하나 둔다.
	// 맵을 랜덤으로 만든다.
	// D_IN_TILE_AADS_TOINDEX_TPE()

}

bool Bullet::init()
{
	CircleCol* P = CreateCol<CircleCol>(L"Bullet", { 30, 30 });
	return true;
}

void Bullet::Update()
{
	m_DeathTime -= DTIME;

	if (0 >= m_DeathTime)
	{
		Death();
	}

	m_Pos.X += MUL(100.0f, bTime::DeltaTime());
}

void Bullet::ColEnter(Collider* _this, Collider* _other)
{
	int a = 0;
	Death(); // 총알 죽는다.
	_other->ThisActor()->Death(); // 몬스터 죽는거죠?
}

void Bullet::ColStay(Collider* _this, Collider* _other)
{
	int a = 0;
}

void Bullet::ColExit(Collider* _this, Collider* _other)
{
	int a = 0;
}