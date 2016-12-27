#include "stdafx.h"
#include "cStateRun.h"
#include "cDynamicObj.h"


cStateRun::cStateRun()
{
}


cStateRun::~cStateRun()
{
}


void cStateRun::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_RUN, false, true);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateRun::Update()
{
	if (m_vTiming.size() >= 1)
	{
		if (m_pParent->GetCurrentAnimPosition() >= m_vTiming[0])
			PlaySound(E_SOUND_RUN, 0.7f, true);
	}
	if (m_vTiming.size() >= 2)
	{
		if (m_pParent->GetCurrentAnimPosition() >= m_vTiming[1])
			PlaySound(E_SOUND_RUN, 0.7f);
	}
}


void cStateRun::End()
{
	m_bSoundPlay = false;
	m_bSoundPlay2 = false;
	m_pParent->AnimationRemove();
}


void cStateRun::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	m_bSoundPlay = false;
	m_bSoundPlay2 = false;
}
