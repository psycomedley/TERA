#include "stdafx.h"
#include "cBoundingBox.h"


cBoundingBox::cBoundingBox()
{
}


cBoundingBox::~cBoundingBox()
{
}


HRESULT cBoundingBox::Setup(D3DXVECTOR3* pMin, D3DXVECTOR3* pMax)
{
	/*if (FAILED(D3DXCreateBox(g_pD3DDevice, pMax->x - pMin->x,
		pMax->y - pMin->y, pMax->z - pMin->z, &m_pBoxMesh, NULL)))
	{
		MSGBOX("Bounding Box Setup Fail");
		return E_FAIL;
	}*/

	m_vMin = *pMin;
	m_vMax = *pMax;

	m_stObb.vOrgCenterPos = (m_vMin + m_vMax) / 2.f;

	m_stObb.vOrgAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_stObb.vOrgAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_stObb.vOrgAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_stObb.fAxisLen[0] = fabs(m_vMax.x - m_vMin.x);
	m_stObb.fAxisLen[1] = fabs(m_vMax.y - m_vMin.y);
	m_stObb.fAxisLen[2] = fabs(m_vMax.z - m_vMin.z);

	m_stObb.fAxisHalfLen[0] = m_stObb.fAxisLen[0] / 2.0f;
	m_stObb.fAxisHalfLen[1] = m_stObb.fAxisLen[1] / 2.0f;
	m_stObb.fAxisHalfLen[2] = m_stObb.fAxisLen[2] / 2.0f;

	//D3DXMatrixIdentity(&m_matWorldTM);

	return S_OK;
}
HRESULT cBoundingBox::ReSetup(float Scale)
{
	m_stObb.fAxisHalfLen[0] =m_stObb.fAxisHalfLen[0]*Scale;
	m_stObb.fAxisHalfLen[1] =m_stObb.fAxisHalfLen[1]*Scale;
	m_stObb.fAxisHalfLen[2] =m_stObb.fAxisHalfLen[2]*Scale;
	return S_OK;
}

void cBoundingBox::Update(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, float fAngle, D3DXMATRIXA16* matRevision)
{
	D3DXMATRIXA16 matS, matR, matT, mat;
	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
	D3DXMatrixRotationY(&matR, fAngle);
	D3DXMatrixTranslation(&matT,
		vPos.x,
		vPos.y + ((m_vMax.y + m_vMin.y) / 2) * vScale.y,
		vPos.z);
	mat = *matRevision * matS * matR * matT;

	for (int i = 0; i < 3; ++i)
	{
		D3DXVec3TransformNormal(
			&m_stObb.vAxisDir[i],
			&m_stObb.vOrgAxisDir[i],
			&mat);
	}

	D3DXVec3TransformCoord(
		&m_stObb.vCenterPos,
		&m_stObb.vOrgCenterPos,
		&mat);

	//D3DXVec3TransformCoord(
	//	&m_vMin,
	//	&m_vMin,
	//	&matS);

	//D3DXVec3TransformCoord(
	//	&m_vMax,
	//	&m_vMax,
	//	&matS);

	//m_stObb.fAxisLen[0] = fabs(m_vMax.x - m_vMin.x);
	//m_stObb.fAxisLen[1] = fabs(m_vMax.y - m_vMin.y);
	//m_stObb.fAxisLen[2] = fabs(m_vMax.z - m_vMin.z);

	//m_stObb.fAxisHalfLen[0] = m_stObb.fAxisLen[0] / 2.0f;
	//m_stObb.fAxisHalfLen[1] = m_stObb.fAxisLen[1] / 2.0f;
	//m_stObb.fAxisHalfLen[2] = m_stObb.fAxisLen[2] / 2.0f;

}


void cBoundingBox::Render(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, float fAngle, D3DXMATRIXA16* matRevision /*= NULL*/)
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	D3DXMATRIXA16 matS, matR, matT, mat;
//	D3DXMatrixIdentity(&mat);
	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
	D3DXMatrixRotationY(&matR, fAngle);
	D3DXMatrixTranslation(&matT,
		vPos.x,
		vPos.y /*+ ((m_vMax.y + m_vMin.y) / 2) * vScale.y*/,
		vPos.z);
	mat = *matRevision * matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat); 
//	m_pBoxMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);


	/*D3DXMATRIXA16 matS, matR, matT, mat;
	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
	D3DXMatrixRotationY(&matR, fAngle);
	D3DXMatrixTranslation(&matT,
		vPos.x,
		vPos.y + ((m_vMax.y + m_vMin.y) / 2) * vScale.y,
		vPos.z);
	mat = *matRevision * matS * matR * matT;*/


	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	std::vector<ST_PC_VERTEX> vecVertex;
	vecVertex.reserve(8);

	ST_PC_VERTEX v;
	v.c = XRED;
	v.p = D3DXVECTOR3(
		m_stObb.vOrgCenterPos.x - m_stObb.fAxisLen[0] / 2.0f,
		m_stObb.vOrgCenterPos.y - m_stObb.fAxisLen[1] / 2.0f,
		m_stObb.vOrgCenterPos.z - m_stObb.fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		m_stObb.vOrgCenterPos.x - m_stObb.fAxisLen[0] / 2.0f,
		m_stObb.vOrgCenterPos.y + m_stObb.fAxisLen[1] / 2.0f,
		m_stObb.vOrgCenterPos.z - m_stObb.fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		m_stObb.vOrgCenterPos.x + m_stObb.fAxisLen[0] / 2.0f,
		m_stObb.vOrgCenterPos.y + m_stObb.fAxisLen[1] / 2.0f,
		m_stObb.vOrgCenterPos.z - m_stObb.fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		m_stObb.vOrgCenterPos.x + m_stObb.fAxisLen[0] / 2.0f,
		m_stObb.vOrgCenterPos.y - m_stObb.fAxisLen[1] / 2.0f,
		m_stObb.vOrgCenterPos.z - m_stObb.fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		m_stObb.vOrgCenterPos.x - m_stObb.fAxisLen[0] / 2.0f,
		m_stObb.vOrgCenterPos.y - m_stObb.fAxisLen[1] / 2.0f,
		m_stObb.vOrgCenterPos.z + m_stObb.fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		m_stObb.vOrgCenterPos.x - m_stObb.fAxisLen[0] / 2.0f,
		m_stObb.vOrgCenterPos.y + m_stObb.fAxisLen[1] / 2.0f,
		m_stObb.vOrgCenterPos.z + m_stObb.fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		m_stObb.vOrgCenterPos.x + m_stObb.fAxisLen[0] / 2.0f,
		m_stObb.vOrgCenterPos.y + m_stObb.fAxisLen[1] / 2.0f,
		m_stObb.vOrgCenterPos.z + m_stObb.fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);

	v.p = D3DXVECTOR3(
		m_stObb.vOrgCenterPos.x + m_stObb.fAxisLen[0] / 2.0f,
		m_stObb.vOrgCenterPos.y - m_stObb.fAxisLen[1] / 2.0f,
		m_stObb.vOrgCenterPos.z + m_stObb.fAxisLen[2] / 2.0f);
	vecVertex.push_back(v);


	std::vector<WORD> vecIndex;
	vecIndex.reserve(24);

	vecIndex.push_back(0); vecIndex.push_back(1);
	vecIndex.push_back(1); vecIndex.push_back(2);
	vecIndex.push_back(2); vecIndex.push_back(3);
	vecIndex.push_back(3); vecIndex.push_back(0);
	vecIndex.push_back(4); vecIndex.push_back(5);
	vecIndex.push_back(5); vecIndex.push_back(6);
	vecIndex.push_back(6); vecIndex.push_back(7);
	vecIndex.push_back(7); vecIndex.push_back(4);
	vecIndex.push_back(0); vecIndex.push_back(4);
	vecIndex.push_back(1); vecIndex.push_back(5);
	vecIndex.push_back(2); vecIndex.push_back(6);
	vecIndex.push_back(3); vecIndex.push_back(7);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_LINELIST,
		0,
		8,
		12,
		&vecIndex[0],
		D3DFMT_INDEX16,
		&vecVertex[0],
		sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}


void cBoundingBox::Release()
{
	SAFE_RELEASE(m_pBoxMesh);
}