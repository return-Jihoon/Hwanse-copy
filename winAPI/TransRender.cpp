#include "TransRender.h"
#include <assert.h>
#include "Res.h"
#include "GameCore.h"
#include "Actor.h"
#include "RenderMgr.h"

#pragma comment(lib, "msimg32.lib")

TransRender::TransRender() : Percentage(1.0f)
{
}


TransRender::~TransRender()
{
}

void TransRender::Sprite(const wchar_t* _name, int _index/* = 0*/)
{
	m_Sprite = Res::SpriteFind(_name);
	m_Index = _index;

	if (nullptr == m_Sprite)
	{
		assert(false);
	}

	if (false == m_IsCustomSize)
	{
		SpriteSizeOn();
	}
}
void TransRender::Render()
{
	if (nullptr == m_Sprite)
		assert(false);


	char* p = (char*)&TransRenders;
	p[0] = (char)255;
	p[1] = 0;
	p[2] = (char)255;
	p[3] = 0;
	//TransRenders = 0x00fff00ff;

	if (false == m_IsCustomSize)
		SpriteSizeOn();

	Pos RenderPos = CalPivotPos();

	/*Rectangle(RenderMgr::BackDC()
		, RenderPos.IX()
		, RenderPos.IY()
		, RenderPos.IX() + RenderRect.size.IX()
		, RenderPos.IY() + RenderRect.size.IY());*/
	if (255 <= GetAlpha())
	{
		TransparentBlt(
			RenderMgr::BackDC()
			, RenderPos.IX()
			, RenderPos.IY()
			, (int)(RenderRect.size.IX() * Percentage)
			, RenderRect.size.IY()
			, m_Sprite->Images()->DC()
			, (*m_Sprite)[m_Index].pos.IX()
			, (*m_Sprite)[m_Index].pos.IY()
			, (int)((*m_Sprite)[m_Index].size.IX() * Percentage)
			, (*m_Sprite)[m_Index].size.IY()
			, 0x00ff00ff
		);
	}
	else
	{
		AlphaBlend(
			RenderMgr::BackDC()
			, RenderPos.IX()
			, RenderPos.IY()
			, RenderRect.size.IX()
			, RenderRect.size.IY()
			, m_Sprite->Images()->DC()
			, (*m_Sprite)[m_Index].pos.IX()
			, (*m_Sprite)[m_Index].pos.IY()
			, (*m_Sprite)[m_Index].size.IX()
			, (*m_Sprite)[m_Index].size.IY()
			, BF
		);
	}

/*	Rectangle(RenderMgr::BackDC()
		, RenderPos.IX() - 5
		, RenderPos.IY() - 5
		, RenderPos.IX() + 5
		, RenderPos.IY() + 5);*/ 

/*	Rectangle(RenderMgr::BackDC()
		, m_Actor->pos().IX() - 5
		, m_Actor->pos().IY() - 5
		, m_Actor->pos().IX() + 5
		, m_Actor->pos().IY() + 5);*/
}
void TransRender::SpriteSizeOn()
{
	RenderRect.size = (*m_Sprite)[m_Index].size;
}
