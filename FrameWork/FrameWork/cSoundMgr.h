#pragma once
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")
using namespace FMOD;

class cSoundMgr : public cSingleton<cSoundMgr>
{
private:
	map<string, Sound*> m_mapSound;

	System* m_pSystem;
	Sound** m_ppSound;
	Channel** m_ppChannel;

public:
	void Add(string sKey, string sPath, bool bBgm = false);
	void Play(string sKey, float fVolume = 1.0f);
	void Stop(string sKey);
	void Pause(string sKey);
	void Resume(string sKey);

	bool IsPlay(string sKey);
	bool IsPlay(int nCount);

public:
	void Setup();
	void Update();
	void Release();

public:
	cSoundMgr();
	~cSoundMgr();
};

