#include "stdafx.h"
#include "cMesh.h"


cMesh::cMesh()
	: m_vMin(0, 0, 0)
	, m_vMax(0, 0, 0)
	, m_pBox(NULL)
	, m_pSphere(NULL)
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


void cMesh::Bounding_Render()
{
	if (m_pBox)
		m_pBox->Render();
	if (m_pSphere)
		m_pSphere->Render();
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