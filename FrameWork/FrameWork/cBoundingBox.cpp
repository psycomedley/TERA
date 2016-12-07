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
	if (FAILED(D3DXCreateBox(g_pD3DDevice, pMax->x - pMin->x,
		pMax->y - pMin->y, pMax->z - pMin->z, &m_pBoxMesh, NULL)))
	{
		MSGBOX("Bounding Box Setup Fail");
		return E_FAIL;
	}

	m_vMin = *pMin;
	m_vMax = *pMax;

	return S_OK;
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
		vPos.y + ((m_vMax.y + m_vMin.y) / 2) * vScale.y,
		vPos.z);
	mat = *matRevision * matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat); 
	m_pBoxMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
}


void cBoundingBox::Release()
{
	SAFE_RELEASE(m_pBoxMesh);
}