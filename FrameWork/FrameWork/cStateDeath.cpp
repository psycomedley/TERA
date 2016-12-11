#include "stdafx.h"
#include "cStateDeath.h"
#include "cDynamicObj.h"


cStateDeath::cStateDeath()
{
}


cStateDeath::~cStateDeath()
{
}


void cStateDeath::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_DEATH, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_DEATHWAIT, false, false);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateDeath::Update()
{

}


void cStateDeath::End()
{
//	m_pParent->AnimationRemove();
}


void cStateDeath::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	m_pParent->AnimationNext();
}
