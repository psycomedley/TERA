#include "stdafx.h"
#include "cStaticMeshEffect.h"
#include "cStaticMesh.h"
#include "cPlayer.h"


cStaticMeshEffect::cStaticMeshEffect(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
}


cStaticMeshEffect::~cStaticMeshEffect()
{
}

HRESULT cStaticMeshEffect::Setup(D3DXVECTOR3 s, D3DXVECTOR3 t, float Angle)
{
	m_fAngle = Angle;
	
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, s.x, s.y, s.z);
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXMatrixTranslation(&matT, t.x, t.y, t.z);
	matWorld = matS * matR * matT;
	return S_OK;
}

void cStaticMeshEffect::Update()
{

}

void cStaticMeshEffect::Render()
{

	//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000044);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//cStaticObj::Render();
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x0000088);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DXMatrixRotationY(&matR, m_fAngle);
	matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	cStaticObj::Render();
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

}

