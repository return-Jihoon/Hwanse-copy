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

	// ���̶�� ���� �ϳ� �д�.
	// ���� �������� �����.
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
	Death(); // �Ѿ� �״´�.
	_other->ThisActor()->Death(); // ���� �״°���?
}

void Bullet::ColStay(Collider* _this, Collider* _other)
{
	int a = 0;
}

void Bullet::ColExit(Collider* _this, Collider* _other)
{
	int a = 0;
}