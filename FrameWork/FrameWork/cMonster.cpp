#include "stdafx.h"
#include "cMonster.h"
#include "cUIObject.h"
#include "cUITextView.h"
#include "cUIImageView.h"


cMonster::cMonster(char* szFolder, char* szFilename)
	: m_fDetectRange(0.0f)
	, m_bIsBattle(false)
	, m_pUIHp(NULL)
	, m_pShotSphere(NULL)
	, m_pMoveColBox(NULL)
	, m_pMoveColSphere(NULL)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	ZeroMemory(&m_stInfo, sizeof(ST_UNIT_INFO));
}


cMonster::cMonster()
	: m_fDetectRange(0.0f)
	, m_bIsBattle(false)
	, m_pUIHp(NULL)
	, m_pShotSphere(NULL)
	, m_pMoveColBox(NULL)
	, m_pMoveColSphere(NULL)
{
	ZeroMemory(&m_stInfo, sizeof(ST_UNIT_INFO));
}


cMonster::~cMonster()
{
	SAFE_DELETE(m_pShotSphere);
	SAFE_DELETE(m_pMoveColBox);
	SAFE_DELETE(m_pMoveColSphere);
}


void cMonster::Update()
{
	if (m_pUIHp)
	{
		float fHpRatio = m_stInfo.fHp / m_stInfo.fMaxHp;

		char szStr[16] = { '\0', };
		sprintf_s(szStr, sizeof(szStr), "%.0f%%", fHpRatio * 100);
		((cUITextView*)m_pUIHp->FindChildByTag(E_UITAG_HPTEXT))->SetText(szStr);
		((cUIImageView*)m_pUIHp->FindChildByTag(E_UITAG_HP))->SetScaleX(fHpRatio);
	}
}


void cMonster::UpdateAndRender(D3DXMATRIXA16* pmat /*= NULL*/)
{
	if (m_fPassedVanishTime < 1.0f)
		cDynamicObj::UpdateAndRender(pmat);

//	m_pMoveColBox->Render(m_vPosition, m_vScale, m_fAngle, &m_matRevision);
	m_pMoveColSphere->Render(m_vPosition, m_vScale);
}


cBoundingSphere cMonster::GetShotSphere()
{
	cBoundingSphere sphere;
	sphere.SetCenter(m_vPosition);
	sphere.SetRadius(m_pShotSphere->GetRadius());
	return sphere;
}


void cMonster::SetShotSphere(float fRadius)
{
	m_pShotSphere = new cBoundingSphere;
	m_pShotSphere->SetRadius(fRadius);
}


void cMonster::ResetHp()
{
	m_stInfo.fHp = m_stInfo.fMaxHp;
}


void cMonster::SetBox()
{
	m_pMoveColBox = new cBoundingBox;
	D3DXVECTOR3 vMin = m_pMesh->m_pBox->GetvMin();
	vMin.x *= 0.3f;
	vMin.z *= 0.3f;
	D3DXVECTOR3 vMax = m_pMesh->m_pBox->GetvMax() * 0.3f;
	m_pMoveColBox->Setup(&vMin, &vMax);

	m_pMoveColSphere = new cBoundingSphere;
	m_pMoveColSphere->Setup(&m_vPosition, GetSphere().GetRadius() * 0.2f);
}


cBoundingBox cMonster::GetMoveColBox()
{
	float fAngle = m_fAngle + m_fRevisionAngle;

	cBoundingBox box;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, fAngle);
	D3DXVECTOR3	vMin = m_pMoveColBox->GetvMin() * m_vScale.x;
	D3DXVECTOR3	vMax = m_pMoveColBox->GetvMax() * m_vScale.x;

	//	D3DXVec3TransformCoord(&vMin, &vMin, &matR);
	//	D3DXVec3TransformCoord(&vMax, &vMax, &matR);

	vMin += m_vPosition;
	vMax += m_vPosition;

	box.SetvMin(vMin);
	box.SetvMax(vMax);

	box.m_stObb = m_pMoveColBox->m_stObb;

	return box;
}


cBoundingSphere cMonster::GetMoveColSphere()
{
	cBoundingSphere sphere;

	D3DXVECTOR3 vPos = m_vPosition;
	float fRadius = m_pMoveColSphere->GetRadius();

	sphere.SetCenter(vPos);
	sphere.SetRadius(fRadius * m_vScale.x);

	return sphere;
}