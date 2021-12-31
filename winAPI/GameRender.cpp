#include "GameRender.h"
#include "RenderMgr.h"
#include <assert.h>
#include "Actor.h"

GameRender::GameRender()// : m_IsCustomSize(false)
{
	BF.BlendOp = AC_SRC_OVER;
	BF.BlendFlags = 0;
	BF.SourceConstantAlpha = 255;
	BF.AlphaFormat = AC_SRC_ALPHA;
}


GameRender::~GameRender()
{
}

void GameRender::Init(int _value, Actor* _actor)
{
	m_Actor = _actor;
	m_Order = _value;
	PushRenderMgr();
}

void GameRender::PushRenderMgr()
{
	RenderMgr::Inst().PushRender(this);
}
