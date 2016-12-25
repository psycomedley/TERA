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
	m_pParent->AnimationRemove();
	((cDynamicMesh*)m_pParent->GetpMesh())->SetTechnique(E_DYNA_TECH_DIE);
}


void cStateDeath::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DEATH)
		m_pParent->AnimationNext();
	else
		End();
}
