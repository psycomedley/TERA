#include "stdafx.h"
#include "cSoundMgr.h"


cSoundMgr::cSoundMgr()
{
}


cSoundMgr::~cSoundMgr()
{
}


void cSoundMgr::Setup()
{
	System_Create(&m_pSystem);

	m_pSystem->init(MAXSOUND, FMOD_INIT_NORMAL, 0);

	m_ppSound = new Sound *[MAXSOUND];
	m_ppChannel = new Channel *[MAXSOUND];

	memset(m_ppSound, 0, sizeof(Sound*) *  MAXSOUND);
	memset(m_ppChannel, 0, sizeof(Channel*) * MAXSOUND);
}


void cSoundMgr::Update()
{
	m_pSystem->update();
}


void cSoundMgr::Release()
{
	if (m_ppChannel || m_ppSound)
	{
		for (int i = 0; i < 2; i++)
		{
			if (m_ppChannel)
				if (m_ppChannel[i])
					m_ppChannel[i]->stop();

			if (m_ppSound)
				if (m_ppSound[i])
					m_ppSound[i]->release();
		}
	}

	SAFE_DELETE_ARRAY(m_ppChannel);
	SAFE_DELETE_ARRAY(m_ppSound);

	if (m_pSystem)
	{
		m_pSystem->release();
		m_pSystem->close();
	}

	cSingleton::Release();
}


void cSoundMgr::Add(string sKey, string sPath, bool bBgm /*= false*/)
{
	if (bBgm)
		m_pSystem->createStream(sPath.c_str(), FMOD_LOOP_NORMAL, 0, &m_ppSound[m_mapSound.size()]);
	else
	{
		m_pSystem->createSound(sPath.c_str(), FMOD_DEFAULT, 0, &m_ppSound[m_mapSound.size()]);
	}

	m_mapSound.insert(make_pair(sKey.c_str(), m_ppSound[m_mapSound.size()]));
}


void cSoundMgr::Play(string sKey, float fVolume /*= 1.0f*/)
{
	int count = 0;

	for (auto iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, count++)
	{
		if (sKey == iter->first)
		{
			m_pSystem->playSound(FMOD_CHANNEL_FREE, iter->second, false, &m_ppChannel[count]);
			m_ppChannel[count]->setVolume(fVolume);
			break;
		}
	}
}


void cSoundMgr::Stop(string sKey)
{
	int count = 0;

	for (auto iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, count++)
	{
		if (sKey == iter->first)
		{
			m_ppChannel[count]->stop();
			break;
		}
	}
}


void cSoundMgr::Pause(string sKey)
{
	int count = 0;

	for (auto iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, count++)
	{
		if (sKey == iter->first)
		{
			m_ppChannel[count]->setPaused(true);
			break;
		}
	}
}


void cSoundMgr::Resume(string sKey)
{
	int count = 0;

	for (auto iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, count++)
	{
		if (sKey == iter->first)
		{
			m_ppChannel[count]->setPaused(false);
			break;
		}
	}
}


bool cSoundMgr::IsPlay(string sKey)
{
	bool isPlay = true;
	int count = 0;
	for (auto iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, count++)
		if (sKey == iter->first)
			if (m_ppChannel[count]->isPlaying(&isPlay))
				return true;

	return false;
}


bool cSoundMgr::IsPlay(int nCount)
{
	bool isPlay = true;
	if (m_ppChannel[nCount]->isPlaying(&isPlay))
		return true;

	return false;
}
