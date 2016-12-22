#include "stdafx.h"
#include "cStateReaction.h"
#include "cDynamicObj.h"
#include "cPlayer.h"


cStateReaction::cStateReaction()
{
}


cStateReaction::~cStateReaction()
{
}


void cStateReaction::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_REACTION, true, true);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_REACTIONCOM, true, false);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateReaction::Update()
{
	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_REACTION)
	{
		if (m_pParent->GetCurrentAnimPosition() <= 0.44f)
			m_pParent->Move(-0.2f);
//		else if (m_pParent->GetCurrentAnimPosition() >= 0.44f &&
//			m_pParent->GetCurrentAnimPosition() >= 0.53f)
//			m_pParent->Move(-0.05f);
	}
}


void cStateReaction::End()
{
	m_pParent->AnimationRemove();
	((cPlayer*)m_pParent)->ChangeState(E_STATE_WAIT);
}


void cStateReaction::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_REACTION)
	{
		pController->AnimationNext();
	}
	else
		End();
}
