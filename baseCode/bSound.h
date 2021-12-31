#pragma once
#include <fmod.hpp>
#include <map>
#include <set>
#include <stack>
#include <string>

#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "\\x86\\fmodL_vc.lib")
#elif RELEASEMODE
#pragma comment(lib, "\\x86\\fmod_vc.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "\\x64\\fmodL_vc.lib")
#elif RELEASEMODE
#pragma comment(lib, "\\x64\\fmod_vc.lib")
#endif
#endif

// 복사 가능한 카세트
// 카세트라고 생각해라.
class bSound;
class bSoundPlayer;
class bSoundClip
{
	// 실제로 로드된 녀석의 권한을 가지는 포인터
public:
	friend bSound;
	friend bSoundPlayer;

private:
	FMOD::Sound* m_pSound;

	unsigned int SoundLen()
	{
		unsigned int Value = -1;
		m_pSound->getLength(&Value, FMOD_TIMEUNIT_MS);
		return Value;
	}

private:
	bSoundClip();
	~bSoundClip();
};

// 사운드를 재생해주는 주체가 된다.
class bSoundPlayer
{
private: 
	friend bSound;

private:
	bSoundClip* m_SoundClip;
	FMOD::Channel* m_pChannel;
	bool m_Rental;

public:
	bool IsRental()
	{
		return m_Rental;
	}

public:
	bool ReturnPool();
	bool Play(const wchar_t* _sound, int _loop);
	void Stop();

private:
	bSoundPlayer() : m_Rental(false) {}
	~bSoundPlayer() {}
};

class bSound
{
public:
	friend bSoundPlayer;

private:
	static FMOD::System* m_pMainSoundSystem;

public:
	static bool Init(int _count = 128);
	static void Update();
	static void End();

private:
	static std::map<std::wstring, bSoundClip*> m_ClipMap;

	static std::stack<bSoundPlayer*> m_SoundPlayerPool;
	static std::set<bSoundPlayer*> m_PlayPlayer;

public:
	static bSoundClip* SoundLoad(const wchar_t* _Path);
	static bSoundClip* SoundLoad(const wchar_t* _Name, const wchar_t* _Path);

	static void SoundPlay(const wchar_t* _name, int _loop = 0);

	static bSoundPlayer* SoundPlayNoneReturn();
	static void AllSoundPlayerStop();

private:
	static bSoundClip* FindSound(const wchar_t* _name);



private:
	bSound() {};
	~bSound() {};
};