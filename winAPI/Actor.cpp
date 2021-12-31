#include "Actor.h"
#include "GameCore.h"
#include "RenderMgr.h"
#include "ColliderMgr.h"


Actor::Actor() : m_MainRender(nullptr)
{
}


Actor::~Actor()
{
	std::list<GameRender*>::iterator Loop = m_RenderList.begin();
	std::list<GameRender*>::iterator End = m_RenderList.end();


	for (; Loop != End; ++Loop)
	{
		if (nullptr != (*Loop))
		{
			delete (*Loop);
			(*Loop) = nullptr;
		}
	}

	std::list<Collider*>::iterator ColLoop = m_ColList.begin();
	std::list<Collider*>::iterator ColEnd = m_ColList.end();

	for (; ColLoop != ColEnd; ++ColLoop)
	{
		if (nullptr != (*ColLoop))
		{
			delete (*ColLoop);
			(*ColLoop) = nullptr;
		}
	}
}

std::list<Actor*>::iterator Actor::Loop;
std::list<Actor*>::iterator Actor::End;
std::list<Actor*> Actor::m_AllActorList;
std::map<std::wstring, Actor*> Actor::m_FindActor;
Actor::Destructor Actor::Des;

void Actor::ReleaseActor()
{
	Loop = m_AllActorList.begin();
	End = m_AllActorList.end();

	for (; Loop != End;)
	{
		if (false == (*Loop)->IsDeath())
		{
			++Loop;
			continue;
		}
		delete (*Loop);
		Loop = m_AllActorList.erase(Loop);
	}
}
void Actor::ChangeScenePushActor(Scene* _scene)
{
	Loop = m_AllActorList.begin();
	End = m_AllActorList.end();

	for (; Loop != End; ++Loop)
	{
		if (true == (*Loop)->IsScene(_scene))
		{
			(*Loop)->AllRenderRePush();
			(*Loop)->AllColRePush();
			_scene->PushActor((*Loop));
		}
		//delete (*Loop);
	}
}
void Actor::ActorEnd()
{
	Loop = m_AllActorList.begin();
	End = m_AllActorList.end();

	for (; Loop != End; ++Loop)
	{
		delete (*Loop);
	}
}

bool Actor::init()
{
	return true;
}



void Actor::Update()
{

}

/*void Actor::Render()
{
	Rectangle(GameCore::mainWindow().DC()
		, (int)(m_Pos.X - m_Size.HX())
		, (int)(m_Pos.Y - m_Size.HY())
		, (int)(m_Pos.X + m_Size.HX())
		, (int)(m_Pos.Y + m_Size.HY()));
}*/

void Actor::AllRenderRePush()
{
	RenderStart = m_RenderList.begin();
	RenderEnd = m_RenderList.end();

	for (; RenderStart != RenderEnd; ++RenderStart)
	{
		(*RenderStart)->PushRenderMgr();
	}
}

void Actor::AllColRePush()
{
	ColStart = m_ColList.begin();
	ColEnd = m_ColList.end();

	for (; ColStart != ColEnd; ++ColStart)
	{
		(*ColStart)->PushColMgr();
	}
}

void Actor::ColAfterUpdate() {

}