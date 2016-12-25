#include "stdafx.h"
#include "cStateHit.h"
#include "cDynamicObj.h"


cStateHit::cStateHit()
{
}


cStateHit::~cStateHit()
{
}


void cStateHit::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_HIT, true, true);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();

	PlaySound(E_SOUND_HIT);
}


void cStateHit::Update()
{

}


void cStateHit::End()
{
	m_pParent->AnimationRemove();
	m_pParent->ChangeState(E_STATE_WAIT);
}


void cStateHit::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	End();
	m_bSoundPlay = false;
	m_bSoundPlay2 = false;
}
