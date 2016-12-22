#include "stdafx.h"
#include "cStuff.h"


cStuff::cStuff(char* szFolder, char* szFilename)
	: m_IsCullMode(false)
	, m_SubSetNum(0)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matT);

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
	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	D3DXMATRIXA16	pRot, matS, matRx, matRy, matRz;
	D3DXMatrixIdentity(&pRot);
	D3DXMatrixIdentity(&matRx);
	D3DXMatrixIdentity(&matRy);
	D3DXMatrixIdentity(&matRz);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationX(&matRx, m_fRotX);
	D3DXMatrixRotationY(&matRy, m_fRotY);
	D3DXMatrixRotationZ(&matRz, m_fRotZ);
	pRot = matRx*matRy*matRz;
	cGameObject::m_matWorld = m_matS * pRot * m_matT;


	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(cGameObject::m_matWorld));
	((cStaticMesh*)m_pMesh)->SetIsCullMode(m_IsCullMode);
	((cStaticMesh*)m_pMesh)->SetDwSubSetNum(m_SubSetNum);
	cStaticObj::Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}