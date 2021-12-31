#include "bSound.h"
#include <string>
#include <assert.h>
#include "bPath.h"
#include "bTemplate.h"
#include <list>

// wchar -> char을 위한 헤더
#include <atlstr.h>

///////////////////// Clip

bSoundClip::bSoundClip() {

}
bSoundClip::~bSoundClip()
{
	m_pSound->release();
	m_pSound = nullptr;
}


///////////////////// Sound
FMOD::System* bSound::m_pMainSoundSystem = nullptr;
std::map<std::wstring, bSoundClip*> bSound::m_ClipMap;
std::stack<bSoundPlayer*> bSound::m_SoundPlayerPool;
std::set<bSoundPlayer*> bSound::m_PlayPlayer;

FMOD_RESULT __stdcall SoundPlayerCallBack(
	FMOD_CHANNELCONTROL* channelcontrol,
	FMOD_CHANNELCONTROL_TYPE controltype,
	FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
	void* commanddata1,
	void* commanddata2)
{
	switch (controltype)
	{
	case FMOD_CHANNELCONTROL_CHANNEL:

		switch (callbacktype)
		{
		case FMOD_CHANNELCONTROL_CALLBACK_END:
		{
			FMOD::Channel* pPointer = ((FMOD::Channel*)channelcontrol);

			void* pSoundPlayer = nullptr;
			pPointer->getUserData(&pSoundPlayer);

			if (nullptr == pSoundPlayer)
			{
				assert(false);
			}

			bSoundPlayer* CallPlayer = (bSoundPlayer*)pSoundPlayer;

			if (true == CallPlayer->IsRental())
			{
				return FMOD_OK;
			}

			CallPlayer->ReturnPool();

			return FMOD_OK;
		}
		case FMOD_CHANNELCONTROL_CALLBACK_VIRTUALVOICE:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_SYNCPOINT:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_OCCLUSION:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_MAX:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_FORCEINT:
			break;
		default:
			break;
		}
		break;
	case FMOD_CHANNELCONTROL_CHANNELGROUP:
		break;
	case FMOD_CHANNELCONTROL_MAX:
		break;
	case FMOD_CHANNELCONTROL_FORCEINT:
		break;
	default:
		break;
	}

	return FMOD_OK;

}

bool bSoundPlayer::ReturnPool()
{
	if (bSound::m_PlayPlayer.end() != bSound::m_PlayPlayer.find(this))
		bSound::m_PlayPlayer.erase(this);

	bSound::m_SoundPlayerPool.push(this);

	return true;
}

bool bSoundPlayer::Play(const wchar_t* _sound, int _loop)
{
	bSoundClip* fClip = bSound::FindSound(_sound);

	if (nullptr == fClip)
	{
		assert(false);
		return false;
	}

	bSound::m_pMainSoundSystem->playSound(fClip->m_pSound, nullptr, false, &m_pChannel);
	
	if (nullptr == m_pChannel)
	{
		assert(false);
		return false;
	}

	m_pChannel->setCallback(SoundPlayerCallBack);
	m_pChannel->setUserData(this);
	m_pChannel->setMode(FMOD_LOOP_NORMAL);
	m_pChannel->setLoopCount(_loop);

	if (bSound::m_PlayPlayer.end() == bSound::m_PlayPlayer.find(this))
	{
		bSound::m_PlayPlayer.insert(this);
	}

	return true;
}

void bSoundPlayer::Stop()
{
	if (nullptr == m_pChannel)
	{
		assert(false);
	}

	m_pChannel->stop();
	m_pChannel = nullptr;
}

bool bSound::Init(int _count)
{

	// Fmode
	// m_pMainSoundSystem;
	FMOD_RESULT Return = FMOD::System_Create(&m_pMainSoundSystem);
	if (nullptr == m_pMainSoundSystem || FMOD_OK != Return)
	{
		assert(false);
		return false;
	}

	// 동시에 몇개의 사운드가 틀어질수 있느냐에 대한것.
	// 32채널이면 8012개 인가????
	Return = m_pMainSoundSystem->init(32, FMOD_DEFAULT, nullptr);
	if (FMOD_OK != Return)
	{
		assert(false);
		return false;
	}

	for (size_t i = 0; i < _count; i++)
	{
		m_SoundPlayerPool.push(new bSoundPlayer());
	}

	return true;
}

void bSound::End()
{
	std::map<std::wstring, bSoundClip*>::iterator Start = m_ClipMap.begin();
	std::map<std::wstring, bSoundClip*>::iterator End = m_ClipMap.end();

	for (; Start != End; ++Start)
	{
		delete Start->second;
	}

	while (0 < m_SoundPlayerPool.size())
	{
		bSoundPlayer* pPlayer = m_SoundPlayerPool.top();
		delete pPlayer;
		m_SoundPlayerPool.pop();
	}

	std::set<bSoundPlayer*>::iterator PlayStart = m_PlayPlayer.begin();
	std::set<bSoundPlayer*>::iterator PlayEnd = m_PlayPlayer.end();

	for (; PlayStart != PlayEnd; ++PlayStart)
	{
		delete(*PlayStart);
	}

	m_pMainSoundSystem->release();
}

void bSound::Update()
{
	if (nullptr != m_pMainSoundSystem)
	{
		// 이벤트를 체크해준다.
		// 사운드재생이 끝났어요.
		m_pMainSoundSystem->update();
	}
}


bSoundClip* bSound::SoundLoad(const wchar_t* _Path)
{
	std::wstring Key = bPath::PathToFileName(_Path);
	return SoundLoad(Key.c_str(), _Path);
}

bSoundClip* bSound::SoundLoad(const wchar_t* _Name, const wchar_t* _Path)
{
	if (nullptr != FindSound(_Name))
	{
		assert(false);
	}

	std::string Str = CW2A(_Path/*, CP_UTF8*/).m_psz;

	FMOD::Sound* pNewSound = nullptr;

	FMOD_RESULT Return = m_pMainSoundSystem->createSound(Str.c_str(), FMOD_DEFAULT, nullptr, &pNewSound);

	if (FMOD_OK != Return || nullptr == pNewSound)
	{
		assert(false);
	}

	bSoundClip* NewSound = new bSoundClip();
	NewSound->m_pSound = pNewSound;

	m_ClipMap.insert(std::map<std::wstring, bSoundClip*>::value_type(_Name, NewSound));

	return nullptr;
}

bSoundClip* bSound::FindSound(const wchar_t* _name)
{
	return bTemplate::MapFindToPointer<bSoundClip>(_name, m_ClipMap);
}

void bSound::SoundPlay(const wchar_t* _name, int _loop)
{
	if (0 == m_SoundPlayerPool.size())
	{
		return;
	}

	bSoundPlayer* NewPlayer = m_SoundPlayerPool.top();
	m_SoundPlayerPool.pop();
	NewPlayer->Play(_name, _loop);
	return;
}

bSoundPlayer* bSound::SoundPlayNoneReturn()
{
	if (0 == m_SoundPlayerPool.size())
	{
		return nullptr;
	}

	bSoundPlayer* NewPlayer = m_SoundPlayerPool.top();
	m_SoundPlayerPool.pop();
	NewPlayer->m_Rental = true;
	m_PlayPlayer.insert(NewPlayer);
	return NewPlayer;
}

void bSound::AllSoundPlayerStop()
{
	if (0 >= m_PlayPlayer.size())
	{
		return;
	}

	std::set<bSoundPlayer*>::iterator Start = m_PlayPlayer.begin();
	std::set<bSoundPlayer*>::iterator End = m_PlayPlayer.end();

	std::vector<bSoundPlayer*> OutList;

	for (; Start != End; ++Start)
	{
		OutList.push_back(*Start);
	}

	for (size_t i = 0; i < OutList.size(); i++)
	{
		OutList[i]->Stop();
	}

	m_PlayPlayer.clear();
}