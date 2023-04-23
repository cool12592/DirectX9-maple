#pragma once
#include "ECS.h"
#include "../../include/fmod.h"
#include <string>
#include <conio.h>
#pragma warning(disable: 4996)

using namespace std;

class CFmodSound: public Component
{
private:
	FMOD_SYSTEM* m_pSystem;
	FMOD_SOUND** m_ppBGSound;
	FMOD_SOUND** m_ppEFFSound;
	FMOD_CHANNEL** m_ppBGChannel;
	int m_nEFSoundCount;
	int m_nBGSoundCount;	
public:
	void CreateEffectSound( int nCount, string *SoundFileName );
	void CreateBGSound( int nCount, string *SoundFileName );
	void CreateEffectSound(int nCount, wstring *SoundFileName);
	void CreateBGSound(int nCount, wstring *SoundFileName);
	void PlaySoundEffect( int nIndex );
	void PlaySoundBG( int nIndex );
	void StopSoundBG( int nIndex );
	void ReleaseSound();
	void Update();

public:
	CFmodSound(void);
	~CFmodSound(void);
};

