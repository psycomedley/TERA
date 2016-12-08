#include "stdafx.h"
#include "cDynamicEffectObj.h"
#include "cDynamicMesh.h"
#include "cAnimationController.h"




cDynamicEffectObj::cDynamicEffectObj(char * szFolder, char * szFilename)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);
}

cDynamicEffectObj::cDynamicEffectObj()
{
}


cDynamicEffectObj::~cDynamicEffectObj()
{
}

void cDynamicEffectObj::UpdateAndRender(D3DXMATRIXA16 * pmat)
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

	((cDynamicMesh*)m_pMesh)->UpdateAndRender(&mat);
}

void cDynamicEffectObj::AddAnimation(ST_ANIMATION_INFO stAnimationInfo)
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->AddAnimation(stAnimationInfo);
}

void cDynamicEffectObj::SetAnimationIdx(int nIdx, bool bPlayOnce)
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->SetAnimationIdx(nIdx, bPlayOnce);
}

void cDynamicEffectObj::SetAnimationIdxBlend(int nIdx, bool bPlayOnce)
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->SetAnimationIdxBlend(nIdx, bPlayOnce);
}

void cDynamicEffectObj::AnimationStart()
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->AnimationStart();
}

bool cDynamicEffectObj::AnimationNext()
{
	if (m_pMesh)
		return ((cDynamicMesh*)m_pMesh)->AnimationNext();
}

void cDynamicEffectObj::AnimationRemove()
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->AnimationRemove();
}

ST_ANIMATION_INFO cDynamicEffectObj::GetCurrentAnimInfo()
{
	return ((cDynamicMesh*)m_pMesh)->GetAnimController()->GetCurrentAnimInfo();
}

double cDynamicEffectObj::GetCurrentAnimPosition()
{
	return ((cDynamicMesh*)m_pMesh)->GetAnimController()->GetCurrentAnimPosition();
}
