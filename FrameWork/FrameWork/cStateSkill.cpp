#include "stdafx.h"
#include "cStateSkill.h"
#include "cDynamicObj.h"
#include "cPlayer.h"
#include "cVerticalCircleEffect.h"
#include "cCircleEffect.h"

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
	}
	else if (m_nSkillIndex == E_ANI_SKILL)
	{
		m_pParent->AnimationRemove();
		aniInfo.SetInfo(E_ANI_SKILL, true, false);
		m_pParent->AddAnimation(aniInfo);
		aniInfo.SetInfo(E_ANI_SKILLR, true, true);
		m_pParent->AddAnimation(aniInfo);
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
				if (((cPlayer*)m_pParent)->UseSkill(120 - ((++m_nCount) * 20)))
				{
					if (m_pParent->GetCurrentAnimPosition() > 0.1f)
					{
						ST_ANIMATION_INFO aniInfo(E_ANI_DOUBLEATTACK, true, false);
						m_pParent->AddAnimation(aniInfo);
						m_bNextAttack = true;
					}
				}
			}
		}
	}

	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_STRIKE)
	{
		if (m_pParent->GetCurrentAnimPosition() > 0.8f)
		{
			GETSINGLE(cBattleMgr)->PlayerDamage(false, 50.0f);

			PlaySound(E_SOUND_SKILL1);
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
		{
			GETSINGLE(cBattleMgr)->PlayerDamage(false, -20.0f);

			PlaySound(E_SOUND_SKILL2, true);
		}
		if (m_pParent->GetCurrentAnimPosition() > 0.3f && m_pParent->GetCurrentAnimPosition() < 0.4f)
		{
			D3DXMATRIXA16 mat;
			D3DXVECTOR3 vec;
			vec = m_pParent->GetPosition() + m_pParent->GetDirection() * -1.0f;
			vec = D3DXVECTOR3(vec.x, vec.y + 1.5f, vec.z);
			D3DXMatrixIdentity(&mat);
			GETSINGLE(cEffectMgr)->AddList("skill2", vec, mat);
		}
		if (m_pParent->GetCurrentAnimPosition() > 0.7f && m_pParent->GetCurrentAnimPosition() < 0.8f)
		{
			D3DXMATRIXA16 mat;
			D3DXVECTOR3 vec;
			vec = m_pParent->GetPosition() + m_pParent->GetDirection() * -1.0f;
			vec = D3DXVECTOR3(vec.x, vec.y + 1.5f, vec.z);
			D3DXMatrixIdentity(&mat);
			GETSINGLE(cEffectMgr)->AddList("skill2", vec, mat);
		}
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_SKILL)
	{
		if (m_pParent->GetCurrentAnimPosition() >= 0.27f &&
			m_pParent->GetCurrentAnimPosition() <= 0.5f)
			m_pParent->Move(0.4f);
		else if (m_pParent->GetCurrentAnimPosition() >= 0.5f &&
			m_pParent->GetCurrentAnimPosition() <= 0.68f)
			m_pParent->Move(0.05f);
		if (m_pParent->GetCurrentAnimPosition() >= 0.4f &&
			m_pParent->GetCurrentAnimPosition() <= 0.6f)
		{
			GETSINGLE(cBattleMgr)->PlayerDamage(false, 100.0f);
			PlaySound(E_SOUND_SKILL3);
		}
		
		if (m_pParent->GetCurrentAnimPosition() >= 0.4f &&
			m_pParent->GetCurrentAnimPosition() <= 0.5f)
		{
			if (!StartSkill3)
			{
				m_pSkill3Effect = new cCircleEffect("Effect", "blueCircle.x");
				StartSkill3 = true;
				m_pSkill3Effect->Setup(1, 0.2f, false, D3DXVECTOR3(0.2f, 0.2f, 0.2f), D3DXVECTOR3(m_pParent->GetPosition().x,
					m_pParent->GetPosition().y + 1,
					m_pParent->GetPosition().z), m_pParent->GetAngle() - D3DX_PI / 2);
				m_pSkill3Effect->Start();
			}
		}
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
	if (StartSkill3)
	{
		m_pSkill3Effect->SetPosition(D3DXVECTOR3(m_pParent->GetPosition().x,
			m_pParent->GetPosition().y + 1,
			m_pParent->GetPosition().z));
		m_pSkill3Effect->Update();
		m_pSkill3Effect->Render();
		if (!m_pSkill3Effect->isStart())
		{
			StartSkill3 = false;
			SAFE_RELEASE(m_pSkill3Effect);
		}
	}
}


void cStateSkill::End()
{
	GETSINGLE(cBattleMgr)->Reset(E_PLAYER);
	m_bSoundPlay = false;
	m_bSoundPlay2 = false;
	m_nCount = 0;
	m_pParent->AnimationRemove();
	((cPlayer*)m_pParent)->ChangeState(E_STATE_WAIT);


	StartEffect1 = false;
	SAFE_RELEASE(m_pEffect1);
	StartSkill3 = false;
	SAFE_RELEASE(m_pSkill3Effect);
}


void cStateSkill::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DOUBLEATTACK)
	{
		GETSINGLE(cBattleMgr)->PlayerDamage(true, -20.0f);
		PlaySound(E_SOUND_SKILL2);

		GETSINGLE(cBattleMgr)->ResetList(E_PLAYER);

		if (!m_pParent->AnimationNext())
		{
			ST_ANIMATION_INFO aniInfo(E_ANI_DOUBLEATTACKR, true, false);
			m_pParent->AddAnimation(aniInfo);
			m_pParent->AnimationNext();
		}
		m_bSoundPlay = false;
		m_bSoundPlay2 = false;
		m_bNextAttack = false;

		StartEffect1 = false;
		SAFE_RELEASE(m_pEffect1);
		StartSkill3 = false;
		SAFE_RELEASE(m_pSkill3Effect);

		return;
	}
	else if (animInfo.nIndex == E_ANI_SKILL)
	{
		m_bSoundPlay = false;
		m_bSoundPlay2 = false;
		m_pParent->AnimationNext();

		StartEffect1 = false;
		SAFE_RELEASE(m_pEffect1);
		StartSkill3 = false;
		SAFE_RELEASE(m_pSkill3Effect);

		return;
	}
	End();
}
