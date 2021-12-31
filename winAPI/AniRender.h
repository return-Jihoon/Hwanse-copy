#pragma once
#include "GameRender.h"
#include <map>
#include "Sprite.h"

class AniRender : public GameRender
{
private:
	class ANI
	{
	public:
		Sprite*	m_Sprite;
		bool	m_bOver;
		bool	m_bLoop;
		int		m_StartIndex;
		int		m_EndIndex;
		int		m_CurIndex;
		float	m_AniTime;
		float	m_CurTime;

	public:
		void ResetAni()
		{
			m_CurIndex = m_StartIndex;
			m_CurTime = m_AniTime;
		}
	public:
		ANI() : m_Sprite(nullptr), m_bOver(false), m_bLoop(false), m_CurIndex(0) {}
		~ANI() {}
	};
private:
	std::map<std::wstring, ANI*> m_AniMap;
	ANI* m_CurAni;
	int TransRender;

private:
	ANI * FIndAni(const wchar_t* _aniName);

public:
	bool IsAni(const wchar_t* _aniName);
	void StartAni(const wchar_t* _aniName);
	void CreateAni(const wchar_t* _aniName, const wchar_t* _spriteName, int _start, int _end, float _aniTime = 0.1f, bool _loop = false);
	void CreateAni(const wchar_t* _aniName, const wchar_t* _spriteName, int _start, int _end, bool _loop, float _aniTime = 0.1f);

	void Render() override;

public:
	AniRender();
	~AniRender();
};

