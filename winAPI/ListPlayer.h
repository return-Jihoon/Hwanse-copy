#pragma once
#include "Actor.h"
#include <list>
#include <queue>

enum MoveDir
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	CENTRE
};

// OverScene 
class AniRender;

class ListPlayer : public Actor
{
public:
	static ListPlayer* FrontPlayer;

	static int Money;

protected:
	static std::list<ListPlayer*> AllListPlayer;


	AniRender* m_AniRender;
	ListPlayer* m_Front;
	ListPlayer* m_Back;

public:
	void SetFront(ListPlayer* _Front)
	{
		m_Front = _Front;
	}

	void SetBack(ListPlayer* _Back)
	{
		m_Back = _Back;
	}

public:
	float Speed;
	static bool DontMove;

public:
	void MoveCheck();

public:
	std::list<float> MoveLen;
	std::list<Pos> MoveDirBox;

public:
	float AllLen();

public:
	Pos LastPos;
	MoveDir LastDir;
	int Sign;

public:
	void ClearMoveList();

public:
	Actor* CurMap;
	bool MapPixelAllow(Pos _pos);
	bool MapPixelAllow(float _x, float _y);

public:
	ListPlayer();
	~ListPlayer();
};

