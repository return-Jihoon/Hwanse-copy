#pragma once
#include <map>
#include <list>
#include "Collider.h"

class Scene;
class Collider;

class ColliderMgr
{
private:
	friend Scene;
	friend Collider;

public:
	static ColliderMgr& Inst()
	{
		static ColliderMgr Inst;
		return Inst;
	}

private:
	class LinkData
	{
	public:
		std::wstring Left;
		std::wstring Right;
	};

public:
	std::map<std::wstring, std::list<Collider*>>::iterator ColStart;
	std::map<std::wstring, std::list<Collider*>>::iterator ColEnd;

	std::list<Collider*>::iterator ColSecondStart;
	std::list<Collider*>::iterator ColSecondEnd;



	std::map<std::wstring, std::list<Collider*>>::iterator LeftGroup;
	std::map<std::wstring, std::list<Collider*>>::iterator RightGroup;

	std::list<Collider*>::iterator LeftStart;
	std::list<Collider*>::iterator LeftEnd;
				   
	std::list<Collider*>::iterator RightStart;
	std::list<Collider*>::iterator RightEnd;

	std::map<std::wstring, std::list<Collider*>> m_ColMap;


	std::map<std::wstring, LinkData>::iterator LinkStart;
	std::map<std::wstring, LinkData>::iterator LinkEnd;

	std::map<std::wstring, LinkData> m_LinkMap;

public:
	void AllColClear();

private:
	void GroupCol(const wchar_t* _left, const wchar_t* _right);
	void GroupCol(const wchar_t* _this);

private:
	void PushCol(Collider* _col);
	void Collision();

public:
	bool IsLink(const wchar_t* _left, const wchar_t* _right);
	void Link(const wchar_t* _left, const wchar_t* _right);

	void Release();
	void DebugRender();


public:
	ColliderMgr();
	~ColliderMgr();
};

