#include "stdafx.h"
#include "cDynamicObj.h"
#include "cDynamicMesh.h"
#include "cAnimationController.h"


cDynamicObj::cDynamicObj(char* szFolder, char* szFilename)
	: m_bHit(false)
	, m_fPassedVanishTime(0.0f)
	, m_fPassedHitTime(0.0f)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);
	SetBoundingPos();

	for (int i = 0; i < E_STATE_END; i++)
		m_aStates[i] = NULL;
}


cDynamicObj::cDynamicObj()
	: m_bHit(false)
	, m_fPassedVanishTime(0.0f)
	, m_fPassedHitTime(0.0f)
{
	for (int i = 0; i < E_STATE_END; i++)
		m_aStates[i] = NULL;
}


cDynamicObj::~cDynamicObj()
{
}


void cDynamicObj::UpdateAndRender(D3DXMATRIXA16* pmat /*= NULL*/)
{
	cGameObject::Update();

	D3DXMATRIXA16 matS, matR, matT, mat;
	if (pmat)
	{
		mat = *pmat;
	}
	else
	{
		D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		
		D3DXMatrixRotationY(&matR, m_fAngle);
		m_vDirection = D3DXVECTOR3(0, 0, -1);
		D3DXVec3TransformCoord(&m_vDirection, &m_vDirection, &matR);

		D3DXMatrixLookAtLH(&matR,
			&D3DXVECTOR3(0, 0, 0),
			&m_vDirection,
			&D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);

		mat = m_matRevision * matS * matR * matT;

		m_matWorld = mat;
	}
	/*if (((cDynamicMesh*)m_pMesh)->GetAnimController()->GetCurrentAnimInfo().nIndex == E_ANI_DEATHWAIT)
	{
		((cDynamicMesh*)m_pMesh)->SetTechnique(E_DYNA_TECH_DIE);
		m_fPassedVanishTime += GETSINGLE(cTimeMgr)->getElapsedTime() * 0.5f;
		((cDynamicMesh*)m_pMesh)->GetEffect()->SetFloat("g_fPassedTime", m_fPassedVanishTime);
	}*/

	if (((cDynamicMesh*)m_pMesh)->GetTechnique() == E_DYNA_TECH_DIE)
	{
		m_fPassedVanishTime += GETSINGLE(cTimeMgr)->getElapsedTime() * 0.5f;
		((cDynamicMesh*)m_pMesh)->GetEffect()->SetFloat("g_fPassedTime", m_fPassedVanishTime);
	}

	if (((cDynamicMesh*)m_pMesh)->GetTechnique() == E_DYNA_TECH_HIT)
	{
		m_fPassedHitTime += GETSINGLE(cTimeMgr)->getElapsedTime();
		if (m_fPassedHitTime >= 0.15f)
		{
			m_fPassedHitTime = 0.0f;
			((cDynamicMesh*)m_pMesh)->SetTechnique(E_DYNA_TECH_NORMAL);
		}
	}

	((cDynamicMesh*)m_pMesh)->UpdateAndRender(&mat);
}


void cDynamicObj::AddAnimation(ST_ANIMATION_INFO stAnimationInfo)
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->AddAnimation(stAnimationInfo);
}


void cDynamicObj::SetAnimationIdx(int nIdx, bool bPlayOnce)
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->SetAnimationIdx(nIdx, bPlayOnce);
}


void cDynamicObj::SetAnimationIdxBlend(int nIdx, bool bPlayOnce)
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->SetAnimationIdxBlend(nIdx, bPlayOnce);
}


void cDynamicObj::AnimationStart()
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->AnimationStart();
}


bool cDynamicObj::AnimationNext()
{
	if (m_pMesh)
		return ((cDynamicMesh*)m_pMesh)->AnimationNext();
}


void cDynamicObj::AnimationRemove()
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->AnimationRemove();
}


ST_ANIMATION_INFO cDynamicObj::GetCurrentAnimInfo()
{
	return ((cDynamicMesh*)m_pMesh)->GetAnimController()->GetCurrentAnimInfo();
}


double cDynamicObj::GetCurrentAnimPosition()
{
	return ((cDynamicMesh*)m_pMesh)->GetAnimController()->GetCurrentAnimPosition();
}


bool cDynamicObj::IsTargetCollision()
{
	if (GETSINGLE(cCollision)->Collision(&m_pTarget->GetSphere(), &GetSphere()))
		return true;
	return false;
}


bool cDynamicObj::IsTargetBoxCollision()
{
	if (GETSINGLE(cCollision)->Collision(&m_pTarget->GetBox(), &GetBox()))
		return true;
	return false;
}


void cDynamicObj::LookTarget()
{
	if (m_pTarget)
	{
		D3DXVECTOR3 vTargetPos = m_pTarget->GetPosition();
		m_vDirection = m_vPosition - vTargetPos;
		D3DXVec3Normalize(&m_vDirection, &m_vDirection);

		float nX = vTargetPos.x - m_vPosition.x;
		float nZ = vTargetPos.z - m_vPosition.z;

		m_fAngle = D3DX_PI / 2 - atan2(nZ, nX);
	}
}


float cDynamicObj::Damaged(ST_UNIT_INFO stInfo)
{
	float fDamage = GetFromIntTo(stInfo.fMinDamage, stInfo.fMaxDamage);
	if (m_pState != m_aStates[E_STATE_DEATH])
	{
		fDamage = fDamage - m_stInfo.fDefence;

		if (m_stInfo.fDefence > fDamage)
			fDamage = 1;
		
		m_stInfo.fHp -= fDamage;
		m_bHit = true;

		if (m_stInfo.fHp <= 0)
		{
			ChangeState(E_STATE_DEATH);
			m_stInfo.fHp = 0;
		}
		else
		{
			if (IsMoveAble() && m_aStates[E_STATE_HIT])
				ChangeState(E_STATE_HIT);
			if (m_pMesh)
				((cDynamicMesh*)m_pMesh)->SetTechnique(E_DYNA_TECH_HIT);
			
		}

		return fDamage;
	}
	return -1;
}