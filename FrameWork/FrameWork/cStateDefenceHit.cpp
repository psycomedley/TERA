#include "stdafx.h"
#include "cStateDefenceHit.h"
#include "cDynamicObj.h"
#include "cPlayer.h"


cStateDefenceHit::cStateDefenceHit()
{
}


cStateDefenceHit::~cStateDefenceHit()
{
}


void cStateDefenceHit::Start()
{
	m_pParent->AnimationRemove();
	ST_ANIMATION_INFO aniInfo(E_ANI_DEFENCE_HIT, true, false);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateDefenceHit::Update()
{

}


void cStateDefenceHit::End()
{
	m_pParent->AnimationRemove();
	((cPlayer*)m_pParent)->ChangeState(E_STATE_DEFENCE, 1);
}


void cStateDefenceHit::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DEFENCE_HIT)
	{
		End();
	}
}

