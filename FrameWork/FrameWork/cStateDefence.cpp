#include "stdafx.h"
#include "cStateDefence.h"
#include "cDynamicObj.h"
#include "cStaticMeshEffect.h"


cStateDefence::cStateDefence()
	: nowEffect(false)
	
{	
	m_pEffect = new cStaticMeshEffect("Effect", "Shield2.x");
//	m_pStaticMeshEffect->Setup(s, t, Angle);
}


cStateDefence::~cStateDefence()
{
	SAFE_RELEASE(m_pEffect);
}


void cStateDefence::Start()
{
	m_fPassedTime = 0.0f;
	ST_ANIMATION_INFO aniInfo(E_ANI_DEFENCE_START, true, false);

	if (m_nSkillIndex == -1)
		m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_DEFENCE_LOOP, false, true);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();

	if (!nowEffect)
	{
		nowEffect = true;
	//	GETSINGLE(cEffectMgr)->AddStaticMeshEffect("Effect", "Shield2.x", D3DXVECTOR3(0.055f, 0.055f, 0.055f), m_pParent->GetPosition(), m_pParent->GetAngle());
		m_pEffect->Setup(D3DXVECTOR3(0.055f, 0.055f, 0.055f), m_pParent->GetPosition(), m_pParent->GetAngle());
		if (!GETSINGLE(cEffectMgr)->IsInStaticEffect(m_pEffect))
			GETSINGLE(cEffectMgr)->AddStaticMeshEffect(m_pEffect);
	}
}


void cStateDefence::Update()
{
	m_fPassedTime += GETSINGLE(cTimeMgr)->getElapsedTime();
}


void cStateDefence::End()
{
	m_pParent->AnimationRemove();
	ST_ANIMATION_INFO aniInfo(E_ANI_DEFENCE_CALCEL, true, true);
	m_pParent->AddAnimation(aniInfo);
//	pObj->GetAnimController()->m_pController->SetTrackPosition(0, 0);

//	pObj->GetAnimController()->m_stCurrentAnimation = ST_ANIMATION_INFO(5, true, false);
//	pObj->AnimationStart();
//	pObj->GetAnimController()->m_pController->SetTrackPosition(0, 0.0f);
//	pObj->SetAnimationIdx(5, false);
	GETSINGLE(cEffectMgr)->RemoveStaticMeshEffect();
	nowEffect = false;
}


void cStateDefence::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DEFENCE_START)
	{
		pController->AnimationNext();
	}
	if (animInfo.nIndex == E_ANI_DEFENCE_HIT)
	{
		m_pParent->AnimationRemove();
		ST_ANIMATION_INFO aniInfo(E_ANI_DEFENCE_LOOP, false, true);
		m_pParent->AddAnimation(aniInfo);
		m_pParent->AnimationStart();
	}
	/*if (animInfo.nIndex == 5)
	{
		if (animInfo.bBlend)
			pController->SetAnimationIdxBlend(0, false);
		else
			pController->SetAnimationIdx(0, false);
		pController->m_stCurrentAnimation = ST_ANIMATION_INFO(0, false, true);
	}*/

	//char msg[128];
	//static int a = 0;
	//a++;
	//OutputInteger(msg, "x", animInfo.nIndex);
}