#include "stdafx.h"
#include "cStateBossSkill.h"
#include "cDynamicObj.h"
#include "cOrca.h"


cStateBossSkill::cStateBossSkill()
	: m_nSkillIndex(-1)
	, m_nEffect(0)
{
}


cStateBossSkill::~cStateBossSkill()
{
}


void cStateBossSkill::Start()
{
	ST_ANIMATION_INFO aniInfo(m_nSkillIndex, true, true);
	m_pParent->AddAnimation(aniInfo);

	if (m_nSkillIndex == E_BOSS_LONGMOVE_START)
	{
		m_pParent->AnimationRemove();
		aniInfo.SetInfo(m_nSkillIndex, true, false);
		m_pParent->AddAnimation(aniInfo);
		
		aniInfo.SetInfo(E_BOSS_LONGMOVE_LOOP, true, false);
		int loop = GetFromIntTo(1, 3);
		for (int i = 0; i < loop; i++)
			m_pParent->AddAnimation(aniInfo);
		
		aniInfo.SetInfo(E_BOSS_LONGMOVE_RUN, true, false);
		m_pParent->AddAnimation(aniInfo);
		aniInfo.SetInfo(E_BOSS_LONGMOVE_END, true, true);
		m_pParent->AddAnimation(aniInfo);
	}
	else if (m_nSkillIndex == E_BOSS_HEAVYATK_START)
	{
		m_pParent->AnimationRemove();
		aniInfo.SetInfo(m_nSkillIndex, true, false);
		m_pParent->AddAnimation(aniInfo);
		aniInfo.SetInfo(E_BOSS_HEAVYATK_LOOP, true, false);
		m_pParent->AddAnimation(aniInfo);
		aniInfo.SetInfo(E_BOSS_HEAVYATK_END, true, true);
		m_pParent->AddAnimation(aniInfo);
	}

	m_pParent->AnimationStart();
}


void cStateBossSkill::Update()
{
	if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_LONGMOVE_RUN)
	{
		m_pParent->Move(1.5f);
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_HEAVYATK_LOOP)
	{
		m_pParent->Move(0.2f);
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_HEAVYATK2)
	{
		switch (m_nEffect)
		{
		case 0:
		{
			D3DXVECTOR3 vec = m_pParent->GetDirection();
			vec.y = 0.1f;
			D3DXMATRIXA16 matR;
			D3DXMatrixRotationX(&matR, D3DX_PI / 2);
			GETSINGLE(cEffectMgr)->AddList("MagicArray", vec, matR);
			m_nEffect++;
			break;
		}
		case 1:
		{
			if (m_pParent->GetCurrentAnimPosition() >= 0.51f)
			{
				float angle = m_pParent->GetAngle();
				D3DXVECTOR3 vec;
				vec = D3DXVECTOR3(-sinf(angle + D3DX_PI / 3 * 2), 0.5f, -cosf(angle + D3DX_PI / 3 * 2)) * 6;
				D3DXMATRIXA16 matR;
				D3DXMatrixIdentity(&matR);
				GETSINGLE(cEffectMgr)->AddList("orca1", m_pParent->GetPosition() + vec, matR);
				m_nEffect++;
			}
			break;
		}
		case 2:
		{
			if (m_pParent->GetCurrentAnimPosition() >= 0.58f)
			{
				float angle = m_pParent->GetAngle();
				D3DXVECTOR3 vec;
				vec = D3DXVECTOR3(-sinf(angle + D3DX_PI / 3 * 4), 0.5f, -cosf(angle + D3DX_PI / 3 * 4)) * 6;
				D3DXMATRIXA16 matR;
				D3DXMatrixIdentity(&matR);
				GETSINGLE(cEffectMgr)->AddList("orca1", m_pParent->GetPosition() + vec, matR);
				m_nEffect++;
			}
			break;
		}
		case 3:
		{
			if (m_pParent->GetCurrentAnimPosition() >= 0.65f)
			{
				float angle = m_pParent->GetAngle();
				D3DXVECTOR3 vec;
				vec = D3DXVECTOR3(-sinf(angle), 0.5f, -cosf(angle)) * 6;
				D3DXMATRIXA16 matR;
				D3DXMatrixIdentity(&matR);
				GETSINGLE(cEffectMgr)->AddList("orca1", m_pParent->GetPosition() + vec, matR);
				m_nEffect++;
			}
			break;
		}
		default:
			break;
		}
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_ATK2)
	{
		if (m_pParent->GetCurrentAnimPosition() >= 0.475f &&
			m_pParent->GetCurrentAnimPosition() <= 0.485f)
		{
			D3DXVECTOR3 vec1;
			vec1 = -m_pParent->GetDirection() * 13;
			vec1.y = 0.1f;
			D3DXMATRIXA16 matR;
			D3DXMatrixRotationX(&matR, D3DX_PI / 2);
			GETSINGLE(cEffectMgr)->AddList("orca2", m_pParent->GetPosition() + vec1, matR);
		}
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_BACKATK)
	{
		if (m_pParent->GetCurrentAnimPosition() >= 0.5f &&
			m_pParent->GetCurrentAnimPosition() <= 0.55f)
		{
			float angle = m_pParent->GetAngle();
			D3DXVECTOR3 vec1, vec2;
			D3DXMATRIXA16 matR, matR2, matX, matY;
			D3DXMatrixRotationX(&matX, D3DX_PI / 2);
			D3DXMatrixRotationY(&matY, angle + D3DX_PI / 6);
			matR = matX * matY;
			vec1 = D3DXVECTOR3(-sinf(angle + D3DX_PI / 6), 0.1f, -cosf(angle + D3DX_PI / 6)) * 8;
			D3DXMatrixRotationY(&matY, angle - D3DX_PI / 6);
			matR2 = matX * matY;
			vec2 = D3DXVECTOR3(-sinf(angle - D3DX_PI / 6), 0.1f, -cosf(angle - D3DX_PI / 6)) * 8;

			GETSINGLE(cEffectMgr)->AddList("orcaBackAtk", m_pParent->GetPosition() + vec1, matR);
			GETSINGLE(cEffectMgr)->AddList("orcaBackAtk", m_pParent->GetPosition() + vec2, matR2);
		}
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_ATK1)
	{
		if (m_pParent->GetCurrentAnimPosition() <= 0.7f)
			m_pParent->Move(0.01f);
	}
	/*else if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_HEAVYATK_LOOP)
	{
		m_pParent->Move(0.2f);
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_HEAVYATK_LOOP)
	{
		m_pParent->Move(0.2f);
	}*/
}


void cStateBossSkill::End()
{
	m_pParent->AnimationRemove();
	m_pParent->ChangeState(E_STATE_WAIT);
}


void cStateBossSkill::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_BOSS_HEAVYATK_END ||
		animInfo.nIndex == E_BOSS_LONGMOVE_END ||
		animInfo.nIndex == E_BOSS_ATK1 ||
		animInfo.nIndex == E_BOSS_ATK2 ||
		animInfo.nIndex == E_BOSS_HEAVYATK2 ||
		animInfo.nIndex == E_BOSS_BACKATK)
	{
		End();
	}
	else
	{
		m_pParent->AnimationNext();
	}
	m_nEffect = 0;
}
