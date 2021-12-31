#pragma once
#include "Actor.h"

class Collider;

class Bullet : public Actor
{
private:
	float m_DeathTime;

public:
	bool init() override;
	void Update() override;

	void ColEnter(Collider* _this, Collider* _other) override;
	void ColStay(Collider* _this, Collider* _other) override;
	void ColExit(Collider* _this, Collider* _other) override;

public:
	Bullet();
	~Bullet();
};

