#include "StdAfx.h"
#include "Sound.h"


Sound::Sound(void)
{
	FMOD_RESULT result = FMOD::System_Create(&m_pSystem);
	result = m_pSystem->init(32, FMOD_INIT_NORMAL, NULL);
}

Sound::~Sound(void)
{
	FMOD_RESULT result = m_pSystem->close();
	result = m_pSystem->release();
	m_pSystem = nullptr;
}

//한번에 등록을 함.
void Sound::CreateBGSound( int nCount, string *SoundFileName )
{
		// 효과 사운드 생성
	{
		m_nBGSoundCount = nCount;
		m_ppBGSound = new FMOD::Sound * [nCount];
		m_ppBGChannel = new FMOD::Channel * [nCount];

		for (int i = 0; i < nCount; i++)
		{
			FMOD_RESULT result = m_pSystem->createSound(SoundFileName[i].data(), FMOD_LOOP_NORMAL, 0, &m_ppBGSound[i]);
			int k = 0;
		}
	}
}
//한번에 등록을 함.
void Sound::CreateEffectSound(int nCount, string* SoundFileName)
{
	// 백 그라운드 사운드 생성
	m_nEFSoundCount = nCount;
	m_ppEFFChannel = new FMOD::Channel * [nCount];
	m_ppEFFSound = new FMOD::Sound * [nCount];

	for (int i = 0; i < nCount; i++)
	{
		FMOD_RESULT result = m_pSystem->createSound(SoundFileName[i].data(), FMOD_DEFAULT, 0, &m_ppEFFSound[i]);
		//result = m_ppEFFSound[i]->setSoundGroup(m_SoundGroup);
		int k = 0;
	}
}


void Sound::PlaySoundEffect(int nIndex)
{
	
	FMOD_RESULT result = m_pSystem->playSound(m_ppEFFSound[nIndex], 0,false, &m_ppEFFChannel[nIndex]);
	int k;
}

void Sound::PlaySoundBG(int nIndex)
{
	FMOD_RESULT result = m_pSystem->playSound(m_ppBGSound[nIndex], 0, false, &m_ppBGChannel[nIndex]);
	int k;
}

void Sound::StopSoundBG(int nIndex)
{
	
	FMOD_RESULT result = m_ppBGChannel[nIndex]->stop();
	
	int k = 0;
}
bool Sound::IsPlayingEffect(int nIndex)
{
	bool playing = false;

	if (m_ppEFFSound[nIndex] == NULL)
	{
		return false;
	}
	FMOD_RESULT result = m_ppEFFChannel[nIndex]->isPlaying(&playing);
	playing_ = playing;
	return playing_;
}
bool Sound::IsPlayingBGM(int nIndex)
{
	bool playing = false;

	if (m_ppBGChannel[nIndex] == NULL)
	{
		return false;
	}
	FMOD_RESULT result = m_ppBGChannel[nIndex]->isPlaying(&playing);
	playing_ = playing;
	return playing_;
}

void Sound::StopSoundEff(int nIndex)
{
	FMOD_RESULT result = m_ppEFFChannel[nIndex]->stop();
	int k = 0;
}

void Sound::AllBgSoundOFF(int lastIndex,int myIndex)
{
	for (int i = 0; i <= lastIndex; i++)
	{
		if (i == myIndex)
			continue;
		if (IsPlayingBGM(i))
			StopSoundBG(i);
	}
}

void Sound::release()
{
	int i;

	delete [] m_ppBGChannel;
	
	for (i = 0; i < m_nBGSoundCount; i++)
		FMOD_RESULT result = m_ppBGSound[i]->release();
	delete [] m_ppBGSound;
	for( i = 0 ; i <  m_nEFSoundCount ; i++ )
		FMOD_RESULT result = m_ppEFFSound[i]->release();
	delete [] m_ppEFFSound;
}

void Sound::update()
{
	if (!m_pSystem)
		FMOD_RESULT result = m_pSystem->update();
}
