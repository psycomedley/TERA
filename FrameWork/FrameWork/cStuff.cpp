#include "stdafx.h"
#include "cStuff.h"


cStuff::cStuff(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
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
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000000);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DXMATRIXA16 matWorld, matView;
	D3DXMATRIXA16	mat, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matT, -10.0f, -15.0f, 30.0f);
	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	mat = matS*matT;
	
	

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matWorld, 0, &matView);

	matWorld = matWorld*mat;
	////memset(&matView._41, 0, sizeof(D3DXVECTOR3));
	//matWorld._11 = matView._11;
	//matWorld._13 = matView._13;
	//matWorld._31 = matView._31;
	//matWorld._33 = matView._33;
	//D3DXMatrixInverse(&matWorld, 0, &matWorld);
	//D3DXVECTOR3 pos = D3DXVECTOR3(-10, -15, 30);
	//memcpy(&matWorld._41, &pos, sizeof(D3DXVECTOR3));
	//float fScale[3];
	//fScale[0] = 0.05f; fScale[1] = 0.05f; fScale[2] = 0.05f;
	//for (int i = 0; i < 3; ++i)
	//{
	//	for (int j = 0; j < 4; ++j)
	//		matWorld(i, j) *= fScale[i];
	//}
	//matWorld._41 = 0;
	//matWorld._42 = 0;
	//matWorld._43 = 1;
	g_pD3DDevice->SetFVF(((cStaticMesh*)m_pMesh)->GetStaticMeshFVF());
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	cStaticObj::Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}