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

HRESULT cStaticMeshEffect::Setup()
{
	D3DXMatrixIdentity(&matWorld);
	
	return S_OK;
}

void cStaticMeshEffect::Update()
{

}

void cStaticMeshEffect::Render()
{
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	

	cStaticObj::Render();


	


	//cStaticObj* Crosshair = new cStaticObj("Effect", "Crosshair1.x");
	//Crosshair->SetWorldTM(matWorld);

	//Crosshair->Render();
	//Crosshair->Release();

	//m_pMesh->Render();

}

