#include "stdafx.h"
#include "cStuff.h"


cStuff::cStuff(char* szFolder, char* szFilename)
	:m_vPosition(0,0,0)
	, m_vScale(0, 0, 0)
	, m_fRotX(0.0f)
	, m_fRotY(0.0f)
	, m_fRotZ(0.0f)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matT);
	D3DXMatrixIdentity(&m_matRX);
	D3DXMatrixIdentity(&m_matRY);
	D3DXMatrixIdentity(&m_matRZ);

}
cStuff::cStuff()
{
}

cStuff::~cStuff()
{
}

void cStuff::Update()
{
}
void cStuff::Render()
{
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DXMATRIXA16	pRot;
	D3DXMatrixIdentity(&pRot);
	D3DXMatrixTranslation(&m_matT, 0.0f, 0.0f, 10.0f);
	D3DXMatrixScaling(&m_matS, 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationX(&m_matRX, m_fRotX);
	D3DXMatrixRotationY(&m_matRY, m_fRotY);
	D3DXMatrixRotationZ(&m_matRZ, m_fRotZ);
	pRot = m_matRX*m_matRY*m_matRZ;
	m_matWorld = m_matS * pRot * m_matT;


	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	((cStaticMesh*)m_pMesh)->SetIsCullMode(true);
	((cStaticMesh*)m_pMesh)->SetDwSubSetNum(0);
	cStaticObj::Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}