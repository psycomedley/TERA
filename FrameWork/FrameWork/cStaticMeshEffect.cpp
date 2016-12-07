#include "stdafx.h"
#include "cStaticMeshEffect.h"
#include "cStaticMesh.h"


cStaticMeshEffect::cStaticMeshEffect(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
}


cStaticMeshEffect::~cStaticMeshEffect()
{
}

HRESULT cStaticMeshEffect::Setup()
{
	return S_OK;
}

void cStaticMeshEffect::Update()
{

}

void cStaticMeshEffect::Render()
{



	D3DXMATRIXA16 matWorld, matView;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixInverse(&matWorld, 0, &matView);

	//cStaticObj* Crosshair = new cStaticObj("Effect", "Crosshair1.x");
	//Crosshair->SetWorldTM(matWorld);

	//Crosshair->Render();
	//Crosshair->Release();

	m_pMesh->Render();

}

