#pragma once
#include "Actor.h"
#include <list>
#include <vector>

class AniRender;


class Status
{
public:
	bool isDown;
	int Level;
	int Max_Hp;
	int Cur_Hp;
	int Max_Mp;
	int Cur_Mp;
	int Exp;
	int Att;

	static Status* BattleStatus[3];

public:
	Status() : isDown(false), Level(1), Max_Hp(50), Cur_Hp(50), Max_Mp(50), Cur_Mp(50), Exp(0), Att(10) {}
	~Status() {}
};


class BattlePlayer :
	public Actor
{
public:
/*
	static BattlePlayer* FrontBtPlayer;

protected:
	static std::list<BattlePlayer*> AllBattlePlayer;*/

	AniRender* m_AniRender;
/*	BattlePlayer* m_Front;
	BattlePlayer* m_Back;

public:
	void SetFront(BattlePlayer* _Front)
	{
		m_Front = _Front;
	}

	void SetBack(BattlePlayer* _Back)
	{
		m_Back = _Back;
	}*/

public:
	static int Skills[3];
	static bool PowerUp;
	static bool SkillOn;
	static int CharIndex;
	static int DMG;
	static int PlTarget[3];

	float SkillCount;

	bool Victory;
	bool SkillEnd;
	bool Damage;
	bool Die;
	

public:
	BattlePlayer();
	~BattlePlayer();
};

