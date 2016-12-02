#include "stdafx.h"
#include "cDynamicObj.h"
#include "cDynamicMesh.h"


cDynamicObj::cDynamicObj(char* szFolder, char* szFilename)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);
}


cDynamicObj::cDynamicObj()
{
}


cDynamicObj::~cDynamicObj()
{
}


void cDynamicObj::UpdateAndRender(D3DXMATRIXA16* pmat /*= NULL*/)
{
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


void cDynamicObj::AnimationNext()
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->AnimationNext();
}


void cDynamicObj::AnimationRemove()
{
	if (m_pMesh)
		((cDynamicMesh*)m_pMesh)->AnimationRemove();
}


void cDynamicObj::ChangeState(int n)
{

}