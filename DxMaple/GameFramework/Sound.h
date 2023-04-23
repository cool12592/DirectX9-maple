#pragma once
#include "ECS.h"
#include <string>
#include "../include/fmod/fmod.h"
#include "../include/fmod/fmod.hpp"
#include "../include/fmod/fmod_errors.h"

#pragma warning(disable: 4996)
#pragma comment(lib,"../lib/fmod/fmodex_vc.lib")
//using namespace FMOD;
using namespace std;

class Sound : public Component
{
private:
	FMOD::System* m_pSystem;

	int m_nEFSoundCount;
	FMOD::Sound** m_ppBGSound;
	FMOD::Channel** m_ppBGChannel;

	int m_nBGSoundCount;
	FMOD::Sound** m_ppEFFSound;
	FMOD::Channel** m_ppEFFChannel;

	FMOD::SoundGroup* m_SoundGroup;

	bool playing_ = false;
	//////FMODE namespace
	//static FMOD::ChannelGroup* g_BGMGroup;
	//static FMOD::ChannelGroup* g_UIGroup;
	//static FMOD::ChannelGroup* g_EffectGroup;
	//static FMOD::ChannelGroup* g_IngameGroup;



public:
	void CreateEffectSound( int nCount, string *SoundFileName );
	void CreateBGSound( int nCount, string *SoundFileName );

	void PlaySoundEffect( int nIndex );
	void PlaySoundBG( int nIndex );
	void StopSoundBG( int nIndex );

	bool IsPlayingEffect(int nIndex);

	bool IsPlayingBGM(int nIndex);

	void StopSoundEff(int nIndex);

	void AllBgSoundOFF(int lastIndex,int myIndex);
	void initialize()
	{

	}
	void update();
	void lateUpdate()
	{
	}
	void render() {
	}
	void release();



public:
	Sound(void);
	Sound(int BGMCount, string * SoundFile, int type);
	~Sound(void);
};

