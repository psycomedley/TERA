#include "stdafx.h"
#include "cMesh.h"


cMesh::cMesh()
	: m_vMin(0, 0, 0)
	, m_vMax(0, 0, 0)
{
}


cMesh::~cMesh()
{
}


void cMesh::Render()
{
	/*if (m_pBox)
		m_pBox->Render();
	if (m_pSphere)
		m_pSphere->Render();*/
}


void cMesh::Bounding_Update(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, float fAngle /*= 0*/, D3DXMATRIXA16* matRevision /*= NULL*/)
{
	if (m_pBox)
		m_pBox->Update(vPos, vScale, fAngle, matRevision);
}


void cMesh::Bounding_Render(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, float fAngle /*= 0*/, D3DXMATRIXA16* matRevision /*= NULL*/)
{
//	if (m_pBox)
//		m_pBox->Render(vPos, vScale, fAngle, matRevision);
	if (m_pSphere)
		m_pSphere->Render(vPos, vScale, matRevision);
}


void cMesh::Release()
{
	SAFE_RELEASE(m_pBox);
	SAFE_RELEASE(m_pSphere);
}


HRESULT cMesh::SetupBounding(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax)
{
	m_vMin = vMin;
	m_vMax = vMax;

	m_pBox = new cBoundingBox;
	if (FAILED(m_pBox->Setup(&m_vMin, &m_vMax)))
		return E_FAIL;

	m_pSphere = new cBoundingSphere;
	if (FAILED(m_pSphere->Setup(&((m_vMin + m_vMax) / 2), D3DXVec3Length(&(m_vMax - m_vMin)) / 2)))
		return E_FAIL;

	return S_OK;
}
HRESULT cMesh::ReSetupBoundingBox(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax)
{
	m_vMin = vMin;
	m_vMax = vMax;


	if (FAILED(m_pBox->Setup(&m_vMin, &m_vMax)))
		return E_FAIL;
}

cBoundingBox cMesh::GetBox(D3DXVECTOR3 vPosition, float fScale, float fAngle /*= 0*/)
{
	cBoundingBox box;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, fAngle);
	D3DXVECTOR3	vMin = m_pBox->GetvMin() * fScale;
	D3DXVECTOR3	vMax = m_pBox->GetvMax() * fScale;

//	D3DXVec3TransformCoord(&vMin, &vMin, &matR);
//	D3DXVec3TransformCoord(&vMax, &vMax, &matR);

	vMin += vPosition;
	vMax += vPosition;

	box.SetvMin(vMin);
	box.SetvMax(vMax);

	box.m_stObb = m_pBox->m_stObb;
	//임시
	/*D3DXVECTOR3 vPos = m_pBox->GetPosition();
	m_pBox->SetPosition(D3DXVECTOR3(vPosition.x,
		((m_pBox->GetvMax().y + m_pBox->GetvMin().y) / 2) + vPosition.y,
		vPosition.z));*/

	return box;
}


cBoundingBox cMesh::GetBox(D3DXMATRIXA16* mat)
{
	cBoundingBox box;
	D3DXVECTOR3	vMin = m_pBox->GetvMin();
	D3DXVECTOR3	vMax = m_pBox->GetvMax();

	D3DXVec3TransformCoord(&vMin, &vMin, mat);
	D3DXVec3TransformCoord(&vMax, &vMax, mat);

	box.SetvMin(vMin);
	box.SetvMax(vMax);

	box.m_stObb = m_pBox->m_stObb;
	//임시
	/*D3DXVECTOR3 vPos = m_pBox->GetPosition();
	m_pBox->SetPosition(D3DXVECTOR3(vPosition.x,
	((m_pBox->GetvMax().y + m_pBox->GetvMin().y) / 2) + vPosition.y,
	vPosition.z));*/

	return box;
}


cBoundingSphere cMesh::GetSphere(D3DXVECTOR3 vPosition, float fScale)
{
	cBoundingSphere sphere;
	D3DXVECTOR3 vPos = m_pSphere->GetCenter();
	/*m_pSphere->SetCenter(D3DXVECTOR3(vPosition.x,
		(m_pSphere->GetOriginalY() * fScale) + vPosition.y,
		vPosition.z));

	m_pSphere->SetRadius(m_pSphere->GetOriginalRadius() * fScale);*/
	
	sphere.SetCenter(D3DXVECTOR3(vPosition.x,
		(m_pSphere->GetOriginalY() * fScale) + vPosition.y,
		vPosition.z));
	sphere.SetRadius(m_pSphere->GetOriginalRadius() * fScale);

	return sphere;
}


cBoundingSphere cMesh::GetSphere(D3DXMATRIXA16* mat)
{
	cBoundingSphere sphere;
	D3DXVECTOR3 vPos = m_pSphere->GetCenter();

	D3DXVec3TransformCoord(&vPos, &vPos, mat);

	sphere.SetCenter(vPos);

	//임시
	/*D3DXVECTOR3 vPos = m_pBox->GetPosition();
	m_pBox->SetPosition(D3DXVECTOR3(vPosition.x,
	((m_pBox->GetvMax().y + m_pBox->GetvMin().y) / 2) + vPosition.y,
	vPosition.z));*/

	return sphere;
}