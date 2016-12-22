#include "stdafx.h"
#include "cStateSkill.h"
#include "cDynamicObj.h"
#include "cPlayer.h"
#include "cVerticalCircleEffect.h"

cStateSkill::cStateSkill()
	: m_bNextAttack(false)
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
		{
			GETSINGLE(cBattleMgr)->PlayerDamage(false);

			

		}
		if (m_pParent->GetCurrentAnimPosition() > 0.65f &&
			m_pParent->GetCurrentAnimPosition() < 0.7f)
		{
			D3DXMATRIXA16 mat;
			D3DXVECTOR3 vec;

			vec = m_pParent->GetPosition() + m_pParent->GetDirection() * -2.0f;
			D3DXMatrixIdentity(&mat);
			D3DXMatrixRotationX(&mat, D3DX_PI / 2);
			GETSINGLE(cEffectMgr)->AddList("badak", vec, mat);
		}

		if (m_pParent->GetCurrentAnimPosition() > 0.2f &&
			m_pParent->GetCurrentAnimPosition() < 0.3f)
		{
			if (!StartEffect1)
			{
				m_pEffect1 = new cVerticalCircleEffect("Effect", "blueCircle2.x");
				StartEffect1 = true;
				m_pEffect1->Setup(1, 0.2f, true, D3DXVECTOR3(0.15f, 0.15f, 0.15f), m_pParent->GetPosition(), m_pParent->GetAngle());
				m_pEffect1->Start();
			}
		}
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_DOUBLEATTACK)
	{
		if (m_pParent->GetCurrentAnimPosition() > 0.5f)
			GETSINGLE(cBattleMgr)->PlayerDamage(false);
	}

	if (StartEffect1)
	{
		m_pEffect1->Update();
		m_pEffect1->Render();
		if (!m_pEffect1->isStart())
		{
			StartEffect1 = false;
			SAFE_RELEASE(m_pEffect1);
		}
	}
}


void cStateSkill::End()
{
	GETSINGLE(cBattleMgr)->Reset();
	m_nCount = 0;
	m_pParent->AnimationRemove();
	((cPlayer*)m_pParent)->ChangeState(E_STATE_WAIT);
}


void cStateSkill::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DOUBLEATTACK)
	{
		GETSINGLE(cBattleMgr)->PlayerDamage(true);

		GETSINGLE(cBattleMgr)->ResetList();

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
