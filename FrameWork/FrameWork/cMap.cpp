#include "stdafx.h"
#include "cMap.h"


cMap::cMap(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
	D3DXMatrixIdentity(&m_matWorld);
}


cMap::cMap()
{
	D3DXMatrixIdentity(&m_matWorld);
}
cMap::~cMap()
{
}
void cMap::Update()
{
	
}
void cMap::Render()
{
	D3DXMATRIXA16	mat, matS, matT;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, -110, -77, -300);
	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	mat = matS*matT;
	//m_matWorld = m_matWorld* mat;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	cStaticObj::Render();
}