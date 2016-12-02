#include "stdafx.h"
#include "cStateCombo.h"
#include "cDynamicObj.h"
#include "cPlayer.h"


cStateCombo::cStateCombo()
	: m_bNextAttack(false)
{
}


cStateCombo::~cStateCombo()
{
}


void cStateCombo::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_COMBO1, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO1R, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO2, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO2R, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO3, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO3R, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO4, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO4R, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO5, true, false);
	m_pParent->AddAnimation(aniInfo);

	m_pParent->AnimationStart();
}


void cStateCombo::Update()
{
	if (MOUSE->IsOnceKeyDown(MOUSEBTN_LEFT))
		m_bNextAttack = true;
}


void cStateCombo::End()
{
	m_pParent->AnimationRemove();
	((cPlayer*)m_pParent)->ChangeState(E_STATE_WAIT);
}


void cStateCombo::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_COMBO1 ||
		animInfo.nIndex == E_ANI_COMBO2 ||
		animInfo.nIndex == E_ANI_COMBO3 ||
		animInfo.nIndex == E_ANI_COMBO4)
	{
		pController->AnimationNext();
	}
	if (animInfo.nIndex == E_ANI_COMBO1R ||
		animInfo.nIndex == E_ANI_COMBO2R ||
		animInfo.nIndex == E_ANI_COMBO3R ||
		animInfo.nIndex == E_ANI_COMBO4R)
	{
		if (m_bNextAttack)
		{
			pController->AnimationNext();
			m_bNextAttack = false;
		}
		else
			End();
	}
	if (animInfo.nIndex == E_ANI_COMBO5)
		End();
}
