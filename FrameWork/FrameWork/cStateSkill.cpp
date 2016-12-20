#include "stdafx.h"
#include "cStateSkill.h"
#include "cDynamicObj.h"
#include "cPlayer.h"

cStateSkill::cStateSkill()
	: m_nSkillIndex(-1)
	, m_bNextAttack(false)
	, m_nCount(0)
{
}


cStateSkill::~cStateSkill()
{
}


void cStateSkill::Start()
{
	ST_ANIMATION_INFO aniInfo(m_nSkillIndex, true, true);
	m_pParent->AddAnimation(aniInfo);

	if (m_nSkillIndex == E_ANI_DOUBLEATTACK)
	{
		m_pParent->AnimationRemove();
		aniInfo.SetInfo(E_ANI_DOUBLEATTACK, true, false);
		m_pParent->AddAnimation(aniInfo);
		m_nCount++;
//		m_bNextAttack = true;
//		aniInfo.SetInfo(E_ANI_DOUBLEATTACKR, true, false);
//		m_pParent->AddAnimation(aniInfo);
	}

	m_pParent->AnimationStart();
}


void cStateSkill::Update()
{
	if (KEYBOARD->IsOnceKeyDown(DIK_2))
	{
		if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_DOUBLEATTACK)
		{
			if (!m_bNextAttack && m_nCount < 5)
			{
				if (m_pParent->GetCurrentAnimPosition() > 0.1f)
				{
					ST_ANIMATION_INFO aniInfo(E_ANI_DOUBLEATTACK, true, false);
					m_pParent->AddAnimation(aniInfo);
					m_nCount++;
					m_bNextAttack = true;
				}
			}
		}
	}

	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_STRIKE)
	{
		if (m_pParent->GetCurrentAnimPosition() > 0.8f)
			AddDamage(false);
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_DOUBLEATTACK)
	{
		if (m_pParent->GetCurrentAnimPosition() > 0.5f)
			AddDamage(false);
	}
}


void cStateSkill::End()
{
	for (int i = 0; i < m_vecHitted.size(); i++)
		m_vecHitted[i]->SetHit(false);
	m_vecHitted.clear();
	m_bHit = false;

	m_nCount = 0;
	m_pParent->AnimationRemove();
	((cPlayer*)m_pParent)->ChangeState(E_STATE_WAIT);
}


void cStateSkill::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DOUBLEATTACK)
	{
		AddDamage(true);
		for (int i = 0; i < m_vecHitted.size(); i++)
			m_vecHitted[i]->SetHit(false);
		m_vecHitted.clear();
		m_bHit = false;

		if (!m_pParent->AnimationNext())
		{
			ST_ANIMATION_INFO aniInfo(E_ANI_DOUBLEATTACKR, true, false);
			m_pParent->AddAnimation(aniInfo);
			m_pParent->AnimationNext();
		}
		m_bNextAttack = false;
		return;
	}
	End();
}
