#include "stdafx.h"
#include "cStuff.h"


cStuff::cStuff(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
	D3DXMatrixIdentity(&matWorld);
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
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	D3DXMATRIXA16 InvMatView,matView;
	D3DXMATRIXA16	mat, matS, matT;

	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 10.0f);
	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	mat = matS * matT;


	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	cStaticObj::Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}