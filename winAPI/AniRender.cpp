#include "AniRender.h"
#include "Res.h"
#include "RenderMgr.h"
#include "Actor.h"
#include <bTime.h>
#include "GameCore.h"


AniRender::AniRender() : m_CurAni(nullptr)
{
}


AniRender::~AniRender()
{
	std::map<std::wstring, ANI*>::iterator Start = m_AniMap.begin();
	std::map<std::wstring, ANI*>::iterator End = m_AniMap.end();

	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			delete Start->second;
			Start->second = nullptr;
		}
	}
}
AniRender::ANI* AniRender::FIndAni(const wchar_t* _aniName)
{
	std::map<std::wstring, ANI*>::iterator FindIter = m_AniMap.find(_aniName);

	if (FindIter == m_AniMap.end())
		return nullptr;
	
	return FindIter->second;
}

void AniRender::CreateAni(const wchar_t* _aniName, const wchar_t* _spriteName, int _start, int _end, bool _loop, float _aniTime/*= 0.1f*/)
{
	CreateAni(_aniName, _spriteName, _start, _end, _aniTime, _loop);
}

void AniRender::CreateAni(const wchar_t* _aniName, const wchar_t* _spriteName, int _start, int _end, float _aniTime /*= 0.1f*/, bool _loop/* = false*/)
{
	if (nullptr != FIndAni(_aniName))
	{
		assert(false);
	}

	Sprite* FindSprite = Res::SpriteFind(_spriteName);

	if (nullptr == FindSprite)
	{
		assert(false);
	}
	ANI* NewAni = new ANI();

	NewAni->m_Sprite = FindSprite;
	NewAni->m_StartIndex = _start;
	NewAni->m_EndIndex = _end;
	NewAni->m_AniTime = _aniTime;
	NewAni->m_bLoop = _loop;
	NewAni->ResetAni();

	m_AniMap.insert(std::map<std::wstring, ANI*>::value_type(_aniName, NewAni));
}

void AniRender::StartAni(const wchar_t* _aniName)
{
	ANI* ChangeAni = FIndAni(_aniName);

	if (nullptr == ChangeAni)
		assert(false);

	if (nullptr != m_CurAni && ChangeAni == m_CurAni && m_CurAni->m_bOver == false)
		return;
	
	m_CurAni = ChangeAni;
	m_CurAni->ResetAni();
}

void AniRender::Render()
{
	if (nullptr == m_CurAni)
		assert(false);

	TransRender = 0x00ff00ff;

	m_CurAni->m_CurTime -= bTime::DeltaTime();

	if (0 >= m_CurAni->m_CurTime)
	{
		++m_CurAni->m_CurIndex;
		m_CurAni->m_CurTime = m_CurAni->m_AniTime;

		if (m_CurAni->m_CurIndex == m_CurAni->m_EndIndex + 1)
		{
			if (true == m_CurAni->m_bLoop)
				m_CurAni->m_CurIndex = m_CurAni->m_StartIndex;
			else
				m_CurAni->m_CurIndex = m_CurAni->m_EndIndex;
		}
	}

	if (false == m_IsCustomSize)
		RenderRect.size = (*m_CurAni->m_Sprite)[m_CurAni->m_CurIndex].size;

	Pos RenderPos = CalPivotPos();
	if (255 <= BF.SourceConstantAlpha)
	{
		TransparentBlt(
			RenderMgr::BackDC(),
			RenderPos.IX(),
			RenderPos.IY(),
			RenderRect.size.IX(),
			RenderRect.size.IY(),
			m_CurAni->m_Sprite->Images()->DC(),
			(*m_CurAni->m_Sprite)[m_CurAni->m_CurIndex].pos.IX(),
			(*m_CurAni->m_Sprite)[m_CurAni->m_CurIndex].pos.IY(),
			(*m_CurAni->m_Sprite)[m_CurAni->m_CurIndex].size.IX(),
			(*m_CurAni->m_Sprite)[m_CurAni->m_CurIndex].size.IY(),
			TransRender
		);
	}
	else
	{
		AlphaBlend(
			RenderMgr::BackDC(),
			RenderPos.IX(),
			RenderPos.IY(),
			RenderRect.size.IX(),
			RenderRect.size.IY(),
			m_CurAni->m_Sprite->Images()->DC(),
			(*m_CurAni->m_Sprite)[m_CurAni->m_CurIndex].pos.IX(),
			(*m_CurAni->m_Sprite)[m_CurAni->m_CurIndex].pos.IY(),
			(*m_CurAni->m_Sprite)[m_CurAni->m_CurIndex].size.IX(),
			(*m_CurAni->m_Sprite)[m_CurAni->m_CurIndex].size.IY(),
			BF
		);
	}

/*	Rectangle(RenderMgr::BackDC()
		, ActorPos().IX() - 5
		, ActorPos().IY() - 5
		, ActorPos().IX() + 5
		, ActorPos().IY() + 5);*/
}

bool AniRender::IsAni(const wchar_t* _aniName)
{
	return m_CurAni == FIndAni(_aniName);
}
	 